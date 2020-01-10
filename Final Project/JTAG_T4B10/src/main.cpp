  
#include <Arduino.h>

#define TMS 8
#define TDO 11
#define TDI  10
#define TCK  9

#define TMS0 2
#define TMS1 3

int i;

void TAPclk(int value){
  switch(value){
    case TMS0:
      digitalWrite(TMS, HIGH);
      digitalWrite(TDO, LOW);
      digitalWrite(TCK, HIGH);
      delay(2);
      digitalWrite(TCK, LOW);
      break;

    case TMS1:
      digitalWrite(TMS, HIGH);
      digitalWrite(TDO, HIGH);
      digitalWrite(TCK, HIGH);
      delay(2);
      digitalWrite(TCK, LOW);
      break;

    case 0:
      digitalWrite(TMS, LOW);
      digitalWrite(TDO, LOW);
      digitalWrite(TCK, HIGH);
      delay(2);
      digitalWrite(TCK, LOW);
      break;

    case 1:
      digitalWrite(TMS, LOW);
      digitalWrite(TDO, HIGH);
      digitalWrite(TCK, HIGH);
      delay(2);
      digitalWrite(TCK, LOW);
      break;

    default:
      digitalWrite(TMS, LOW);
      digitalWrite(TDO, LOW);
  }
}

uint32_t read_TDI(int n){
 uint32_t TDObuff=0x00;
    for(i=0; i<(n-1); i++)
      {
        TAPclk(0);
        TDObuff |= ((uint32_t)digitalRead(TDI)<<i);
      }
    TAPclk(TMS0);
    TAPclk(TMS0);
    TAPclk(0);
  return TDObuff;
}

uint32_t read_TDI_b(){
  char TDObuff;
  TAPclk(TMS0);
  TDObuff = (digitalRead(TDI));

  TAPclk(TMS0);
  TAPclk(TMS0);
  TAPclk(0);
  return TDObuff;
}

void test_reset(){
    for(i=0; i<5; i++) TAPclk(TMS0);
}
void setup() {
  
  pinMode( TMS, OUTPUT);
  pinMode( TDI, INPUT);
  pinMode( TDO, OUTPUT);
  pinMode( TCK, OUTPUT);

  Serial.begin(9600);
  
  test_reset();
  Serial.println("----SELE Project----");
  Serial.println("choose a command:");
  Serial.println("d -> print id code");
  Serial.println("b -> print button state");
  Serial.println("1 -> turn on led");
  Serial.println("0 -> turn off led");
  Serial.println("-------------------");
  }

void shift_IR(){
  TAPclk(0);
  TAPclk(TMS0);
  TAPclk(TMS0);
  TAPclk(0);
  TAPclk(0);
}

uint32_t read_IDCODE(){
  shift_IR();
  TAPclk(1);
  TAPclk(0);
  TAPclk(0);
  TAPclk(0);
  TAPclk(TMS0);
  TAPclk(TMS0);
  
  TAPclk(0);
  TAPclk(TMS0);
  TAPclk(0);

  return read_TDI(32);
}
void shift_DR(){
  TAPclk(0);
  TAPclk(TMS0);
  TAPclk(0);
  TAPclk(0);
}


int print_button_state(){
  shift_IR();
  TAPclk(0);
  TAPclk(1);
  TAPclk(0);
  TAPclk(0);
  TAPclk(TMS0);
  TAPclk(TMS0);

  shift_DR();

  TAPclk(0);
  TAPclk(0);
  TAPclk(0);

return read_TDI_b();

}

void write_led1(){

  shift_IR();

  TAPclk(0);
  TAPclk(1);
  TAPclk(1);
  TAPclk(0);
  TAPclk(TMS0);
  TAPclk(TMS0);

  shift_DR();

  for(i=0; i<19;i++)  TAPclk(0);
  TAPclk(1);
  TAPclk(1);
  for(i=0;i<108;i++) TAPclk(0);
  TAPclk(1);
  for(i=0;i<17;i++) TAPclk(0);
  TAPclk(TMS0);
  TAPclk(TMS0);
  TAPclk(0);
}

void write_led0(){

  shift_IR();

  TAPclk(0);
  TAPclk(1);
  TAPclk(1);
  TAPclk(0);
  TAPclk(TMS0);
  TAPclk(TMS0);

  shift_DR();

  for(i=0; i<19;i++)  TAPclk(0);
  TAPclk(0);
  TAPclk(1);
  for(i=0;i<108;i++) TAPclk(0);
  TAPclk(1);
  for(i=0;i<17;i++) TAPclk(0);
  TAPclk(TMS0);
  TAPclk(TMS0);
  TAPclk(0);
}
void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    uint32_t tdo32;
    switch(command){
      case 'd':
        tdo32 = read_IDCODE();
     
        Serial.println(tdo32, BIN);
        Serial.println(tdo32, HEX);
        break;
      case 'b':
        Serial.println("button state: ");
        Serial.println(print_button_state());

        break;
      case '1':
        write_led1();
        Serial.println("LED ON");
        break;
      case '0': 
        write_led0();
        Serial.println("LED OFF");
        break;
        }
    }
}
