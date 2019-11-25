#include <Arduino.h>
#include <avr/io.h>

// Baudrate
#define BAUD 9600
#define UBBR_VAL (((F_CPU / (BAUD * 16UL))) - 1)

#define MASTER_ADDR 15
#define SLAVE1_ADDR 13
#define SLAVE2_ADDR 14

#define LED_PIN 13
#define ADDR3_PIN 11
#define ADDR2_PIN 10
#define ADDR1_PIN 9
#define ADDR0_PIN 8

#define BUT1_PIN 7
#define BUT2_PIN 6

#define WREN_PIN 2

#define ON 1
#define OFF 0

uint8_t ADDR;
uint8_t RXSTATE = 0;

uint8_t oldstate1 = HIGH, oldstate2 = HIGH;

void asynch9_init(uint8_t mode)
{
  // Define baudrate
  UBRR0H = (unsigned char)((UBBR_VAL) >> 8);
  UBRR0L = (unsigned char)UBBR_VAL;

  // Define frame format
  UCSR0B = (1 << UCSZ02);
  UCSR0C = (1 << UCSZ00) | (1 << UCSZ01) // 9 data bits
           | (0 << UPM00)                // no parity
           | (0 << USBS0);               // 1 stop bit

  // If is slave, put in Multi processor slave mode and activate Rx
  if (1 == mode)
  {
    UCSR0B |= (1 << RXEN0);
    UCSR0A |= (1 << MPCM0);
    UCSR0B |= (1 << RXCIE0); // Receive complete interrupt
    return;
  }
  else
  {
    // If is master, active Tx
    UCSR0B |= (1 << TXEN0);
    UCSR0B |= (1 << TXCIE0); // Transfer complete interrupt
  }
}

void send_addr(uint8_t addr)
{
  // Wait for transmit buffer to be empty
  while ((UCSR0A & (1 << UDRE0)) == 0)
    ;

  // Activate transceiver trasnmission mode
  digitalWrite(WREN_PIN, HIGH);

  UCSR0B |= (1 << TXB80); // Address frame and not data frame
  UDR0 = addr;            // Send to serial port
}

void send_data(uint8_t data)
{
  // Wait for transmit buffer to be empty
  while ((UCSR0A & (1 << UDRE0)) == 0)
    ;
  // Activate transceiver trasnmission mode
  digitalWrite(WREN_PIN, HIGH);

  UCSR0B &= ~(1 << TXB80); // Data frame and not address frame
  UDR0 = data;             // Send to serial port
}

void setup()
{

  // Set led and transceiver pins as outputs...
  pinMode(LED_PIN, OUTPUT);
  pinMode(WREN_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);
  digitalWrite(WREN_PIN, LOW);

  //set pins as inputs
  pinMode(ADDR3_PIN,INPUT_PULLUP);
  pinMode(ADDR2_PIN,INPUT_PULLUP);
  pinMode(ADDR1_PIN,INPUT_PULLUP);
  pinMode(ADDR0_PIN,INPUT_PULLUP);

  pinMode(BUT1_PIN,INPUT_PULLUP);
  pinMode(BUT2_PIN,INPUT_PULLUP);

  pinMode(BUT1_PIN, INPUT_PULLUP);
  pinMode(BUT2_PIN, INPUT_PULLUP);

  // Check to see which address this hardware will call itself
  ADDR = digitalRead(ADDR3_PIN) * 8 + digitalRead(ADDR2_PIN) * 4 + digitalRead(ADDR1_PIN) * 2 + digitalRead(ADDR0_PIN) * 1;

  if (MASTER_ADDR == ADDR)
  {
    // Set this hadrware as master
    asynch9_init(0x00);
    send_addr(SLAVE1_ADDR);
    send_data(OFF);
    send_addr(SLAVE2_ADDR);
    send_data(OFF);
  }
  else
  {
    // Set this hadrware as slave
    asynch9_init(0x01);
  } 
}

void loop()
{
  if (MASTER_ADDR == ADDR)
  {
    // If I'm master send to correct slave ON signal according to button pressed
    // If not clicked, then send OFF signal
    // State machine to each button ensures something is sent only in rising edge or falling edge of the buttons
    if (LOW == oldstate1 && HIGH == digitalRead(BUT1_PIN))
    {
      oldstate1 = HIGH;
      send_addr(SLAVE1_ADDR);
      send_data(ON);
    }
    else if (HIGH == oldstate1 && LOW == digitalRead(BUT1_PIN))
    {
      oldstate1 = LOW;
      send_addr(SLAVE1_ADDR);
      send_data(OFF);
    }
    if (LOW == oldstate2 && HIGH == digitalRead(BUT2_PIN))
    {
      oldstate2 = HIGH;
      send_addr(SLAVE2_ADDR);
      send_data(ON);
    }
    else if (HIGH == oldstate2 && LOW == digitalRead(BUT2_PIN))
    {
      oldstate2 = LOW;
      send_addr(SLAVE2_ADDR);
      send_data(OFF);
    }
  }

  // Recalculates address, doesn't change mode 
  // Used in cases where slaves switch addresses on the fly
  ADDR = digitalRead(ADDR3_PIN) * 8 + digitalRead(ADDR2_PIN) * 4 + digitalRead(ADDR1_PIN) * 2 + digitalRead(ADDR0_PIN) * 1;
}

ISR(USART_TX_vect)
{
  // When we finish sending something, set transceiver to receive mode, safer
  digitalWrite(WREN_PIN, LOW);
}

ISR(USART_RX_vect)
{
  unsigned char status, data;

  // This cli and the sei at the end make sure we don't start an interruption in the middle of
  // another and this way, keep a consistent transmission
  cli();

  // Check if we receive address/ data information
  status = (UCSR0B >> RXB80) & 0x01; // Stores address
  data = UDR0;                       // Stores data

  // If we're dealing with an address frame
  if (1 == status)
  {
    // if received address is the same as this hardware address...
    if (ADDR == data)
    {
      // ... set uart to receive all frames...
      UCSR0A &= ~(1 << MPCM0);
    }
    else
    {
      // ...if it's not the proper receiver, set uart to only receive address frames
      UCSR0A |= (1 << MPCM0);
    }
  }
  // If we're dealing with data frame
  else if (0 == status)
  {
    //if not address control led
    if(1 == data) digitalWrite(LED_PIN, LOW);
    else if(0 == data) digitalWrite(LED_PIN, HIGH);
  }

  sei();
}
