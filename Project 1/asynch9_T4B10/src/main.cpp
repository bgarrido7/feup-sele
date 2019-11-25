#include <Arduino.h>

#define MASTER_ADDR 15
#define SLAVE1_ADDR 13
#define SLAVE2_ADDR 14

#define LED_PIN   13
#define ADDR3_PIN 11
#define ADDR2_PIN 10
#define ADDR1_PIN 9
#define ADDR0_PIN 8
#define BUT1_PIN  7
#define BUT2_PIN  6
#define WREN_PIN  2


int master=0, state;
uint8_t self_adress;

void asynch9_init(long BAUD) {
  UBRR0L = (uint8_t) (16000000 / (16*BAUD) -1);
  UBRR0H = (uint8_t) ( (16000000 / (16*BAUD) -1) >>8 );

}

void send_addr(uint8_t addr) {
  while ( !( UCSR0A & (1<<UDRE0)));
  UCSR0B |= (1<<TXB80);

  UDR0 = addr;
}

void send_data(uint8_t data) {
  while ( !( UCSR0A & (1<<UDRE0))) ;
  UCSR0B &= ~(1<<TXB80);

//  if ( data & 0x0100 )
 //   UCSR0B |= (1<<TXB80);

  UDR0 = data;
}

uint8_t get_data() {
 
  uint8_t resh, resl;

  while ( !(UCSR0A & (1<<RXC0)) );

  resh = UCSR0B;
  resh = (resh >> 1) & 0x01;
  resl = UDR0;
  
  if(1==resh){
    if(resl == self_adress){
      UCSR0A &= ~(1 << MPCM0);
      return 0;
    }
    else {
      UCSR0A |= (1 << MPCM0);
      return 0;
    }
  }

  else if(UCSR0A & 0b00000001){
      return 0;      
  }
  
  else
    return resl;
  
}

void setup() {
  
  pinMode( ADDR3_PIN, INPUT_PULLUP);
  pinMode( ADDR2_PIN, INPUT_PULLUP);
  pinMode( ADDR1_PIN, INPUT_PULLUP);
  pinMode( ADDR0_PIN, INPUT_PULLUP);
  pinMode( BUT1_PIN, INPUT_PULLUP);
  pinMode( BUT2_PIN, INPUT_PULLUP);
  pinMode( WREN_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  state=0;

  UCSR0B = (1 << UCSZ02);
  UCSR0C |= (1<<USBS0) | (3<<UCSZ00);             

  UCSR0C &= ~(1 << UMSEL00) & ~(1 << UMSEL01) & ~(1 << UPM00) & ~(1 << USBS0);   //parity and stop bit           

  asynch9_init(9600);

  self_adress=digitalRead(ADDR0_PIN) + (digitalRead(ADDR3_PIN ) *8) + (digitalRead(ADDR2_PIN ) *4) + (digitalRead(ADDR1_PIN ) *2);

  if(MASTER_ADDR==self_adress){
    digitalWrite(WREN_PIN,HIGH);
    master = 1;
    UCSR0B|=(1<<TXEN0);
  }
  else{
    UCSR0B|=(1<<RXEN0); 
    UCSR0A |= (1 << MPCM0);
}
  UCSR0C &= 0b00111111;
    
}

void loop() {
    
  if(1==master){

    if(0==state &&  LOW == digitalRead(BUT1_PIN)){
      state=2;
      send_addr(SLAVE1_ADDR);
      send_data(LED_PIN);
    }
        
    else if(0==state &&  LOW == digitalRead(BUT2_PIN)){
      state=1;
      send_addr(SLAVE2_ADDR);
      send_data(LED_PIN);
    }
    else if(1==state &&  LOW == digitalRead(BUT1_PIN)){
      state=3;
      send_addr(SLAVE1_ADDR);
      send_data(LED_PIN);
    }
   else if((1==state) &&  (HIGH == digitalRead(BUT2_PIN))){
      state=0;
      send_addr(SLAVE2_ADDR);
      send_data(1);
    }
   else if((2==state) &&  (LOW == digitalRead(BUT2_PIN))){
      state=3;
      send_addr(SLAVE2_ADDR);
      send_data(LED_PIN);
    }

    else if((2==state) &&  (HIGH == digitalRead(BUT1_PIN))){
      state=0;
      send_addr(SLAVE1_ADDR);
      send_data(1);
    }

 else if((3==state) &&  (HIGH == digitalRead(BUT1_PIN))){
      state=1;
      send_addr(SLAVE1_ADDR);
      send_data(1);
    }


 else if((3==state) &&  (HIGH == digitalRead(BUT2_PIN))){
      state=2;
      send_addr(SLAVE2_ADDR);
      send_data(1);
    }



  }
  else { //slave
    uint8_t x = get_data();
    if(0 != x){

      if(LED_PIN == x)
        digitalWrite(LED_PIN, HIGH);
  
      else{
        digitalWrite(LED_PIN, LOW);
        UCSR0A |= (1 << MPCM0);
      }

    }
  }

}