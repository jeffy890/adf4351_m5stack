// 
// 2022.4.2
// written by jeffy890
// 
// adf4351 with m5stack using hspi
// output 2.45 ghz, -4 dbm
//
// By using software developed and released by analog devices,
// six registers' value can be obtained.
//

#include <M5Stack.h>
#include <SPI.h>

#define CK 5  // -> CLK
#define MI 16 // -> n/a
#define MO 17 // -> DATA
#define SS 2 // -> LE

SPIClass hspi(HSPI);
SPISettings spiSettings = SPISettings(1000000,SPI_MSBFIRST,SPI_MODE0);

void SendRegisterData();

void setup() {
  // put your setup code here, to run once:
  M5.begin();

  pinMode(CK,OUTPUT);
  pinMode(MI,INPUT);
  pinMode(MO,OUTPUT);
  pinMode(SS,OUTPUT);
  digitalWrite(SS, HIGH);

  hspi.begin(CK,MI,MO,SS);

  SendRegisterData();
}

void loop() {
  // put your main code here, to run repeatedly:

}

void SendRegisterData(){
  //beginning of spi communication
  hspi.beginTransaction(spiSettings);
  delay(10);

  //R5
  digitalWrite(SS, LOW);
  hspi.transfer(0x00);
  hspi.transfer(0x58);
  hspi.transfer(0x00);
  hspi.transfer(0x05);
  delay(10);
  digitalWrite(SS, HIGH);
  delay(10);

  //R4
  digitalWrite(SS, LOW);
  hspi.transfer(0x00);
  hspi.transfer(0x85);
  hspi.transfer(0x00);
  hspi.transfer(0x24);
  delay(10);
  digitalWrite(SS, HIGH);
  delay(10);

  //R3
  digitalWrite(SS, LOW);
  hspi.transfer(0x00);
  hspi.transfer(0x00);
  hspi.transfer(0x04);
  hspi.transfer(0xB3);
  delay(10);
  digitalWrite(SS, HIGH);
  delay(10);

  //R2
  digitalWrite(SS, LOW);
  hspi.transfer(0x00);
  hspi.transfer(0x00);
  hspi.transfer(0x4E);
  hspi.transfer(0x42);
  delay(10);
  digitalWrite(SS, HIGH);
  delay(10);

  //R1
  digitalWrite(SS, LOW);
  hspi.transfer(0x08);
  hspi.transfer(0x00);
  hspi.transfer(0x80);
  hspi.transfer(0x11);
  delay(10);
  digitalWrite(SS, HIGH);
  delay(10);

  //R0
  digitalWrite(SS, LOW);
  hspi.transfer(0x00);
  hspi.transfer(0x7A);
  hspi.transfer(0x80);
  hspi.transfer(0x00);
  delay(10);
  digitalWrite(SS, HIGH);
  delay(10);

  //end of spi communication
  hspi.endTransaction();
}
