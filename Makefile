TARGET = bin/modbus_monitor
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))
CFLAGS =-Iinclude -I/usr/local/include/modbus 
LDFLAGS = -lmodbus -L/usr/local/lib


default: $(TARGET)

run: clean default
	./$(TARGET)

clean: 
	rm -f obj/*.o
	rm -f bin/*

$(TARGET): $(OBJ)
	gcc -o $@ $? $(LDFLAGS)

obj/%.o: src/%.c
	gcc -c $< -o $@ $(CFLAGS) -g
