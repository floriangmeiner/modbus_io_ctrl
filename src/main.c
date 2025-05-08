#include <stdio.h>

#include <modbus.h>

int main(void) {
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
  
    modbus_close(mb);
    modbus_free(mb);
    
    return 0;
  }