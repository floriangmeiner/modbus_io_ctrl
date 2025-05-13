#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/time.h>
#include <termios.h>
#include <modbus.h>
#include <fcntl.h>
#include "commands.h"

static uint8_t current_state[7];

int main(void) {
    int rc = -1; 

    modbus_t *mb;
    int connection = -1;
    uint16_t tab_reg[32];
  
    mb = modbus_new_tcp("10.1.1.48", 502);
    if (mb == NULL){
      printf("Unable to allocate context.");
      return -1;
    }
    connection = modbus_connect(mb);
    if (connection < 0) {
      printf("Failed to connect.\n");
      return -1;
    }
    printf("Connection established\n");
  
    /* Read 5 registers from the address 0 */
    modbus_read_registers(mb, 0, 5, tab_reg);

    uint8_t read_bits[8] = {TRUE};
    modbus_read_bits(mb,0, 8,read_bits);
    
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

    //gettimeofday(&last, NULL);
    while (1) {
        ch = getchar();
        if (ch == 27) { // 27 is ASCII for ESC
            break;
        }
        // gettimeofday(&now, NULL);
        // long elapsed_ms = (now.tv_sec - last.tv_sec) * 1000L + (now.tv_usec - last.tv_usec) / 1000L;
        // if (elapsed_ms >= 200) {
        //     toggle_digital_out(mb, current_state, 3); // Call your function
        //     last = now;
        // }

        // usleep(10000); // Sleep 10ms to avoid busy-waiting
        
        toggle_every_Xms(500, mb, current_state, 0);
        toggle_every_Xms(200, mb, current_state, 2);
        
        usleep(10000); // Sleep 10ms to avoid busy-waiting
    }

    // Restore terminal and file settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    printf("Exited loop.\n");
    modbus_close(mb);
    modbus_free(mb);
    return 0;
}