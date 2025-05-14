#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/time.h>
#include <termios.h>
#include <fcntl.h>
#include <getopt.h>
#include <stdlib.h>
#include <modbus.h>

#include "debug.h"
#include "commands.h"

static uint8_t current_state[7];

int main(int argc, char *argv[]) {
  int rc = -1;

  modbus_t *mb;
  int connection = -1;
  uint16_t tab_reg[32];

  int opt = 0;
  char ipAddr[16] = "255.255.255.255";
  int port = 502; // default modbus port
  char *endptr;
  int ip_provided, port_provided = 0;

  while ((opt = getopt(argc, argv, "hi:p:")) != -1)
  {
    switch (opt)
    {
    case 'h':
      debug("Case 'h'");
      show_usage();
      return 0;
    case 'i':
      debug("Case 'i' with argument %s", optarg);
      strncpy(ipAddr, optarg, sizeof(ipAddr) - 1);
      ipAddr[sizeof(ipAddr) - 1] = '\0';
      ip_provided = 1;
      debug("IP Address: %s", ipAddr);
      break;
    case 'p':
      debug("Case 'p' with argument %s", optarg);
      port = strtol(optarg, &endptr, 10);
      port_provided = 1;
      debug("Port: %d", port);
      break;
    default: /* ? */
      show_usage();
      return -1;
    }
  }

  if (!ip_provided)
  {
    log_err("Error: Missing -i (IP address)\n");
    show_usage();
    return -1;
  }

  mb = modbus_new_tcp(ipAddr, port);
  if (mb == NULL)
  {
    log_err("Cannot allocated pointer to modbus_t structure.");
    return -1;
  }
  rc = modbus_connect(mb);
  if (rc < 0)
  {
    log_err("Failed to connect to Modbus Server at: %s:%d", ipAddr, port);
    return -1;
  }
  debug("Connection established.");

  /* Read 5 registers from the address 0 */
  modbus_read_registers(mb, 0, 5, tab_reg);

  uint8_t read_bits[8] = {TRUE};
  modbus_read_bits(mb, 0, 8, read_bits);

  struct termios oldt, newt;
  int ch;
  // Get current terminal settings
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  // Disable canonical mode and echo
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  // Set stdin to non-blocking
  int oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
  printf("Press ESC to exit the loop.\n");

  while (1)
  {
    ch = getchar();
    if (ch == 27){ // 27 is ASCII for ESC
      break;
    }
    toggle_every_Xms(500, mb, current_state, 0);
    toggle_every_Xms(200, mb, current_state, 2);

    usleep(10000); // Sleep 10ms to avoid busy-waiting
  }

  // Restore terminal and file settings
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
  debug("Exited loop.");

  modbus_close(mb);
  modbus_free(mb);

  return 0;
}