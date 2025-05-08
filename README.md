# README



## Project Motivation
On occasion I work on mechatronic systems remotely and have a need for a way 
to remotely monitor and set various voltage levels. I have an old piece of 
industrial IO hardware the [Advantech ADAM-6250](https://www.advantech.com/en/products/7447e150-338d-402d-b5a1-c9ce6d98816e/adam-6250/mod_da940b26-501f-413e-bfbc-732fd7496782)
that would work for getting "debounced" state for 8-digital inputs and 
7-digital outputs using MQTT(TLS), SNMP, Modbus TCP, RESTful, ASCII APIs. 
I would like to create a program that continuously monitors the IO for changes in state. 

## Requirements

- [ ] Limit dependencies
- [ ] Use the `libmodbus` library and Modbus TCP protocol
- [ ] Create a Unix style command interface to allow for scripting and
application interaction.
- [ ] Provide option for:
    - [ ] an IP address and network port
- [ ] Provide default "help" menu
- [ ] Provide option for setting individual digital output pins.
- [ ] Provide option for setting all digital output pins.
- [ ] Provide option for continually reading single digital input state.

## Background

Once over 5 years ago I experimented with this library but have not looked 
at it since. Now seemed like a good time opportunity to do a small project 
that could show how I work. 

## Current State

The current hardware architecture is as show below:
```
              ┌───────────┐                   
              │  Network  │                   
              │  Switch   │                   
              └───────────┘                   
                  ▲   ▲                       
                  │   │            ┌─────────┐
┌─────┐   ┌───────┘   └───────────►│  Linux  │
│ SW1 │   │                        │ Laptop  │
└──┬──┘   │                        └─────────┘
   │      │     ┌───────┐                     
   ▼      ▼     │       │                     
┌─────────────┐ │       │                     
│             │ │       │                     
│  ADAM-6250  │ │  24V  │                     
│             │ │  PSU  │                     
└─────────────┘ │       │                     
          ▲     │       │                     
          └─────┤       │                     
                └───────┘                     
```
- There is a normally open switch (`SW1`) connected between `DO1` & `DGND`
on the [ADAM-6250]() IO module.
- The IO module is has DHCP configured and is currently at the following IP:
`10.1.1.48` and the Modbus TCP por is `501`. 

On the software side, I've configured an "empty" project that I will use to 
develop features in. All it currently does is, build and "connect" to Modbus 
module. All other features need to built out.

I think this is a pretty good 'green-field' place to start and build 
something out. 


## Resources

I've included a few link and documents in the repo that I'll use as a reference and starting point for development. 

- [libmodbus](https://libmodbus.org/)
- [Advantech ADAM-6250](https://www.advantech.com/en/products/7447e150-338d-402d-b5a1-c9ce6d98816e/adam-6250/mod_da940b26-501f-413e-bfbc-732fd7496782)
- [Datasheet](./resources/ADAM-6250/datasheets/ADAM-625020180910102029.pdf)
- [User Manual](./resources/ADAM-6250/Manuals/ADAM-6200_User_Manual_Ed_4.pdf)
- [Startup Guide](./resources/ADAM-6250/Manuals/ADAM-6250%20Startup%20Manual%20V1.0.pdf) 
