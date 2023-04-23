//
//  written by K.Kobayashi(jeffy890)
//  2023.4.23
//

#include <M5Stack.h>
#include <SPI.h>

#define CK 5  // -> CLK
#define MI 16 // -> n/a
#define MO 17 // -> DATA
#define SS 2 // -> LE

SPIClass hspi(HSPI);
SPISettings spiSettings = SPISettings(1000000, SPI_MSBFIRST, SPI_MODE0);

int set_freq = 35;
int rf_status = 0;

void drawUI();
void drawRFbutton();
void SendRegisterData_35_on();
void SendRegisterData_35_off();

void setup() {
  // put your setup code here, to run once:
  // put your setup code here, to run once:
  M5.begin();

  pinMode(CK, OUTPUT);
  pinMode(MI, INPUT);
  pinMode(MO, OUTPUT);
  pinMode(SS, OUTPUT);
  digitalWrite(SS, HIGH);

  hspi.begin(CK, MI, MO, SS);

  //SendRegisterData_35_on();
  M5.Lcd.setRotation(1);
  M5.Lcd.fillScreen(0xd697);

  drawUI();
  drawRFbutton();
}

void loop() {
  // put your main code here, to run repeatedly:
  M5.update();
  //M5.Lcd.fillScreen(0xd697);

  if (M5.BtnC.wasPressed()) {
    if (rf_status == 0) {
      rf_status = 1;
      SendRegisterData_35_on();
      drawRFbutton();
      delay(10);
    }
    else if (rf_status == 1) {
      rf_status = 0;
      SendRegisterData_35_off();
      drawRFbutton();
      delay(10);
    }
  }
}

void drawUI() {
  M5.Lcd.setTextColor(BLACK, 0xd697);

  M5.Lcd.fillRect(3, 3, 314, 230, 0x8c91);
  M5.Lcd.fillRect(6, 6, 308, 67, 0xd697);
  M5.Lcd.fillRect(6, 6, 308, 2, BLACK);
  M5.Lcd.fillRect(6, 6, 2, 67, BLACK);
  M5.Lcd.fillRect(6, 76, 308, 67, 0xd697);
  M5.Lcd.fillRect(6, 76, 308, 2, BLACK);
  M5.Lcd.fillRect(6, 76, 2, 67, BLACK);

  M5.Lcd.setCursor(10, 10);
  M5.Lcd.setTextSize(2);
  M5.Lcd.print("FREQUENCY");

  M5.Lcd.setCursor(20, 30);
  M5.Lcd.setTextSize(5);
  M5.Lcd.print("35");

  M5.Lcd.setCursor(145, 37);
  M5.Lcd.setTextSize(3);
  M5.Lcd.print("MHz");

  M5.Lcd.setCursor(10, 80);
  M5.Lcd.setTextSize(2);
  M5.Lcd.print("AMPLITUDE");

  M5.Lcd.setCursor(20, 100);
  M5.Lcd.setTextSize(5);
  M5.Lcd.print("+5");

  M5.Lcd.setCursor(145, 107);
  M5.Lcd.setTextSize(3);
  M5.Lcd.print("dBm");

  M5.Lcd.setTextColor(BLACK, 0x8c91);
  M5.Lcd.setCursor(10, 215);
  M5.Lcd.setTextSize(2);
  M5.Lcd.print("ADF4351 SG");
}

void drawRFbutton() {
  if (rf_status == 1) {   
    M5.Lcd.fillRect(220, 150, 71, 76, 0x8c91); 
    M5.Lcd.fillRect(220, 150, 70, 3, 0xd697);
    M5.Lcd.fillRect(220, 150, 3, 75, 0xd697);
    M5.Lcd.fillRect(290, 150, 3, 75, BLACK);
    M5.Lcd.fillRect(220, 225, 70, 3, BLACK);
    M5.Lcd.fillTriangle(290, 225, 290, 226, 292, 225, BLACK);
    M5.Lcd.fillTriangle(290, 150, 290, 152, 292, 150, 0xd697);
    M5.Lcd.fillTriangle(220, 225, 220, 227, 222, 225, 0xd697);
    M5.Lcd.setTextColor(BLACK, 0x8c91);
    M5.Lcd.setCursor(230, 160);
    M5.Lcd.setTextSize(3);
    M5.Lcd.print("RF");
    M5.Lcd.setCursor(230, 185);
    M5.Lcd.print("ON");
  }
  if (rf_status == 0) {
    M5.Lcd.fillRect(290, 150, 3, 75, 0x8c91);
    M5.Lcd.fillRect(220, 225, 70, 3, 0x8c91);
    M5.Lcd.fillTriangle(290, 225, 290, 226, 292, 225, 0x8c91);

    M5.Lcd.fillRect(220, 150, 70, 75, 0xd697);
    M5.Lcd.fillRect(220, 150, 70, 2, BLACK);
    M5.Lcd.fillRect(220, 150, 2, 75, BLACK);
    M5.Lcd.setTextColor(BLACK, 0xd697);
    M5.Lcd.setCursor(230, 160);
    M5.Lcd.setTextSize(3);
    M5.Lcd.print("RF");
    M5.Lcd.setCursor(230, 185);
    M5.Lcd.print("OFF");
  }
}

void SendRegisterData_35_on() {
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
  hspi.transfer(0xE5);
  hspi.transfer(0x00);
  hspi.transfer(0x3C);
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
  hspi.transfer(0x70);
  hspi.transfer(0x00);
  hspi.transfer(0x00);
  delay(10);
  digitalWrite(SS, HIGH);
  delay(10);

  //end of spi communication
  hspi.endTransaction();
}

void SendRegisterData_35_off() {
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
  hspi.transfer(0xE5);
  hspi.transfer(0x00);
  hspi.transfer(0x1C);
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
  hspi.transfer(0x70);
  hspi.transfer(0x00);
  hspi.transfer(0x00);
  delay(10);
  digitalWrite(SS, HIGH);
  delay(10);

  //end of spi communication
  hspi.endTransaction();
}
