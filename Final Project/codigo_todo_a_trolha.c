  
#include <Arduino.h>

#define TMS 8
#define TDI 10
#define TDO  11
#define TCK  9

int read_TDO(int n){
 int TDO_buff=0;
    for(i=0; i<(n-1); i++)
      {
        TAPclk(0);
        TDO_buff=TDO_buff+(digitalRead(TDO)<<(2*i));
      }
    TAPclk(TMS0);
    TDO_buff=TDO_buff+(digitalRead(TDO)<<(2*i));
    for(i=0; i<4; i++) TAPclk(TMS0);
  return TDO_buff;
}

void setup() {
  
  pinMode( TMS, OUTPUT);
  pinMode( TDO, INPUT);
  pinMode( TDI, OUTPUT);
  pinMode( TCK, OUTPUT);

  Serial.begin(9600);
    
}

void TAPclk(string value){
  switch(value){
    case TMS0:
      digitalWrite(TMS, HIGH);
      digitalWrite(TDI, LOW);
      digitalWrite(TCK, HIGH);
      delay(20);
      digitalWrite(TCK, LOW);
      break;

    case TMS1:
      digitalWrite(TMS, HIGH);
      digitalWrite(TDI, HIGH);
      digitalWrite(TCK, HIGH);
      delay(20);
      digitalWrite(TCK, LOW);
      break;

    case 0:
      digitalWrite(TMS, LOW);
      digitalWrite(TDI, LOW);
      digitalWrite(TCK, HIGH);
      delay(20);
      digitalWrite(TCK, LOW);
      break;

    case 1:
      digitalWrite(TMS, LOW);
      digitalWrite(TDI, HIGH);
      digitalWrite(TCK, HIGH);
      delay(20);
      digitalWrite(TCK, LOW);
      break;

    default:
      digitalWrite(TMS, LOW);
      digitalWrite(TDI, LOW);
  }
}

int read_IDCODE(){
  test_reset();
  TAPclk(0);
  TAPclk(TMS0);
  TAPclk(0);
  TAPclk(0);

  return read_TDO(32)
}
void test_reset(){
    for(i=0; i<5; i++) TAPclk(TMS0);
}

void shift_DR(){
  TAPclk(0);
  TAPclk(TMS0);
  TAPclk(0);
  TAPclk(0);
}

void shift_IR(){
  TAPclk(0);
  TAPclk(TMS0);
  TAPclk(TMS0);
  TAPclk(0);
  TAPclk(0);
}

int print_button_state(){
  test_reset();
  shift_IR();
  TAPclk(0);
  TAPclk(1);
  TAPclk(0);
  TAPclk(0);
  TAPclk(TMS0);
  
  test_reset();

  shift_DR();

  TAPclock(0);
  TAPclock(0);
  TAPclock(0);

  read_TDO(1);

  test_reset();
}

void write_led1(){
  test_reset();

  shift_IR();

  TAPclk(0);
  TAPclk(1);
  TAPclk(1);
  TAPclk(0);
  TAPclk(TMS0);

  test_reset();

  shift_DR();

  for(i=0; i<19;i++)  TAPclk(0);
  TAPclk(1);
  TAPclk(1);
  for(i=0;i<108;i++) TAPclk(0);
  TAPclk(1);
  for(i=0;i<17;i++) TAPclk(0);
  TAPclk(TMS0);
  test_reset();
}

void write_led0(){
  test_reset();

  shift_IR();

  TAPclk(0);
  TAPclk(1);
  TAPclk(1);
  TAPclk(0);
  TAPclk(TMS0);

  test_reset();

  shift_DR();

  for(i=0; i<19;i++)  TAPclk(0);
  TAPclk(0);
  TAPclk(1);
  for(i=0;i<108;i++) TAPclk(0);
  TAPclk(1);
  for(i=0;i<17;i++) TAPclk(0);
  TAPclk(TMS0);
  test_reset();
}

void loop() {
  int command;
  if (Serial.available() > 0) {
    command = Serial.read();
    swtich(command){
      case d:
        Serial.println(read_IDCODE(), HEX);
        break;
      case b:
        Serial.println(print_button_state);
        break;
      case 1:
        write_led1();
        break;
      case 0: 
        write_led0();
        break;}
    }
}
