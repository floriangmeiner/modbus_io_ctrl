#include <modbus.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>

#include "commands.h"



int set_digital_out(modbus_t *ctx, uint8_t *current_state, uint8_t pin, uint8_t state){

  if( state == 0){
    current_state[pin] = 0; 
  } else {
    current_state[pin] = 1; 
  }

  return modbus_write_bits(ctx, 16, 8, current_state);
}

int get_digital_in(modbus_t *ctx, uint8_t *current_state, uint8_t pin, uint8_t state){

  if( state == 0){
    current_state[pin] = 0; 
  } else {
    current_state[pin] = 1; 
  }

  return modbus_read_bits(ctx, 16, 8, current_state);
}

int toggle_digital_out(modbus_t *ctx, uint8_t *current_state, uint8_t pin){

    uint8_t pin_state;

    pin_state  = current_state[pin];
    if (current_state[pin] == 0){
        pin_state = TRUE; 
    } else {
        pin_state = FALSE;
    }
    current_state[pin] = pin_state;
    return modbus_write_bits(ctx, 16, 8, current_state);
}

void toggle_every_Xms(int milliseconds, modbus_t *ctx, uint8_t *current_state, uint8_t pin ){

    static struct timeval last[8] = {{0, 0}}; // Support up to 8 pins
    struct timeval now;

    gettimeofday(&now, NULL);

    // Initialize last[pin] on first call for this pin
    if (last[pin].tv_sec == 0 && last[pin].tv_usec == 0) {
        last[pin] = now;
    }

    long elapsed_ms = (now.tv_sec - last[pin].tv_sec) * 1000L +
                      (now.tv_usec - last[pin].tv_usec) / 1000L;

    if (elapsed_ms >= milliseconds) {
        toggle_digital_out(ctx, current_state, pin);
        last[pin] = now;
    }
}

void show_usage(void){
  printf("Usage: modbus_monitor -i <ip address> -p <port number>\n"
    "\t-h - this menu\n"
    "\t-i <ip address> - (required) the modbus server IPv4 address\n" 
    "\t-p <port number> - (default: 502) the modbusTCP port number\n"
  );
}