TARGET = bin/modbus_monitor
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))
CFLAGS =-Iinclude -I/usr/local/include/modbus
LDFLAGS = -lmodbus -L/usr/local/lib

NDEBUG ?= 0
ifeq ($(NDEBUG), 1)
	CFLAGS += -DNDEBUG 
else 
	CFLAGS +=-g
endif
default: $(TARGET)

run: clean default
	./$(TARGET) -i 10.1.1.48 -p 502

test: clean default
	./$(TARGET) -i 10.1.1.48
	./$(TARGET) -i 10.1.1.48 -h
	./$(TARGET) -i 10.1.1.48 -p 502
	./$(TARGET) -i 10.1.1.48 -p 501

clean: 
	rm -f obj/*.o
	rm -f bin/*

$(TARGET): $(OBJ)
	gcc -o $@ $? $(LDFLAGS)

obj/%.o: src/%.c
	gcc -c $< -o $@ $(CFLAGS)
