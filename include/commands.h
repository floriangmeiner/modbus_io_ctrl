#ifndef __COMMANDS_H__
#define __COMANDS_H__

int set_digital_out(modbus_t*, uint8_t*, uint8_t, uint8_t);

int get_digital_in(modbus_t*, uint8_t* ,uint8_t, uint8_t);

int toggle_digital_out(modbus_t*, uint8_t* , uint8_t);

typedef void (*dio_callback_t)(modbus_t *, uint8_t *, uint8_t);

void toggle_every_Xms(int milliseconds, modbus_t *ctx, uint8_t *current_state, uint8_t pin );

#endif