# Asynchronous Communication System

## Objective

  - Development of an asynchronous communication system composed by several nodes (at least 1 master and 2 slaves). These nodes have the same hardware and are be based in the ATmega328P MCU and MAX485 transceivers. 

### Requirements

  - Develop the schematic and the corresponding PCB for the nodes that have in fact the same hardware and only differ in the firmware. 

  - Develop both versions of the firmware (master and slave) using a 9th bit for differentiating the address and data frames
  
## Software

Here are the functions used in the implementation

### asynch9_init(long BAUD)

  - configure the BAUD rate

### send_addr(uint8_t addr) 

  - puts the message's 9th bit at 1, sinalizing if the frame will send an adress
  - send the address value to SLAVE

### send_data(uint8_t data) 

  - puts the message's 9th bit at 0, sinalizing if the frame will send an adress
  - sends the data value to SLAVE

### get_data() 

  - gets the 9th bit to indicate if it's an adress or data
    - if it's an address and it's not its own, turns on MPCM0, otherwise turns off MPCM0
    - if it's data, returns it
    
  - if the 9th bit indicates an address but the slave is not in receiving mode, this function ignores the value

### setup()

- sets the mode of the pins for buttons 1 and 2,
- sets as inputs and connect pull up resistors to pins that choose the adresses
- sets write/read enable and LED as outputs

> NOTE: pull up resistors are used to ensure that the stanby value is 1

###  loop()

 - for the master:
    
    the following state mahcine applies:
    
    <img src="https://github.com/bgarrido7/feup-sele/blob/master/Async%20Project/asynch9_T4B10/images/state%20machine.PNG" width=500>
    
    where:
      -  **state 0:** both LEDs off 
      -  **state 1:** LED for Slave2 on, LED for Slave1 off
      -  **state 2:** LED for Slave1 on, LED for Slave2 off
      -  **state 3:** both LEDs on
      
  - for the slave:
  
    turn on the LED if the correct data is sent. Otherwise, turns off the LED and ends its receiveing mode

## PCB Layout

<img src=https://github.com/bgarrido7/feup-sele/blob/master/Async%20Project/asynch9_T4B10/images/pcb.png width="500">
  

## Authors

* **Beatriz Garrido** - [bgarrido7](https://github.com/bgarrido7)
* **Francisco Lobo Ávila** - [Francisc7](https://github.com/Francisc7)
