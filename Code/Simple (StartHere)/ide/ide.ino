#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_INA219.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define Pin_i2c_scl 4
#define Pin_i2c_sda 5
#define Pin_buzzer 19
#define Pin_ds18b20 18
#define Pin_LedGreen 1
#define Pin_LedRed 2
#define Pin_LedYellow 3
#define Pin_FreeButton 10

Adafruit_INA219 VoltageSensor;
OneWire oneWire(Pin_ds18b20);
DallasTemperature ds18(&oneWire);
Adafruit_SSD1306 display;

int playMelody(int melody[], int noteDuration)
{
  for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++)
  {
    tone(Pin_buzzer, melody[i], noteDuration);
    delay(noteDuration);
  }
  noTone(Pin_buzzer);
  return 0;
}
int playSuccessMelody()
{ 
  int successMelody[] = {262, 330, 392, 523, 392, 330, 262, 392, 523, 659, 523, 392, 262, 659, 784, 880};
  int noteDuration = 400; 
  playMelody(successMelody, noteDuration);    
  return 0; 
}
int playErrorMelody()
{
  int errorMelody[] = {262, 196, 196, 262, 330, 247, 247, 330};
  int noteDuration = 400;
  playMelody(errorMelody, noteDuration);
  return 0;
}

void handleButtonPress()
{
  static bool buttonState = HIGH;
  static bool lastButtonState = HIGH;

  buttonState = digitalRead(Pin_FreeButton);

  if (buttonState == LOW && lastButtonState == HIGH)
  {
    digitalWrite(Pin_LedGreen, !digitalRead(Pin_LedGreen));
    digitalWrite(Pin_LedRed, !digitalRead(Pin_LedRed));
  }
  lastButtonState = buttonState;
}

int getIna219Data()
{
  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;
  float power_mW = 0;

  shuntvoltage = VoltageSensor.getShuntVoltage_mV();
  busvoltage = VoltageSensor.getBusVoltage_V();
  current_mA = VoltageSensor.getCurrent_mA();
  power_mW = VoltageSensor.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);

  Serial.print("Bus Voltage:   ");
  Serial.print(busvoltage);
    drawVoltage(String(busvoltage)+" V");   
  Serial.println(" V");
  Serial.print("Shunt Voltage: ");
  Serial.print(shuntvoltage);
  Serial.println(" mV");
  Serial.print("Load Voltage:  ");
  Serial.print(loadvoltage);
  Serial.println(" V");
  Serial.print("Current:       ");
  Serial.print(current_mA);
  Serial.println(" mA");
  Serial.print("Power:         ");
  Serial.print(power_mW);
  Serial.println(" mW");
  Serial.println("");

  return 0;
}
int setLedRainbow()
{

  int ledPins[] = {Pin_LedGreen, Pin_LedRed, Pin_LedYellow};

  for (int i = 0; i < 3; i++)
  {
    digitalWrite(ledPins[i], HIGH);
    delay(200);
    digitalWrite(ledPins[i], LOW);
    delay(200);
  }

  for (int i = 2; i >= 0; i--)
  {
    digitalWrite(ledPins[i], HIGH);
    delay(200);
    digitalWrite(ledPins[i], LOW);
    delay(200);
  }
}

int getDS18Temp()
{
  ds18.requestTemperatures();
  Serial.print("Temperature: ");
  Serial.print(ds18.getTempCByIndex(0));
  drawVoltage(String(ds18.getTempCByIndex(0))+" C"); 
  Serial.print((char)176);
  Serial.print("C  |  ");
  Serial.print((ds18.getTempCByIndex(0) * 9.0) / 5.0 + 32.0);
  Serial.print((char)176);
  Serial.println("F");

  return 0;
}

int drawLoadingBar(int percentage)
{
  display.clearDisplay(); // Очистка дисплея

  int x = 2;
  int y = 12;
  int width = 124;
  int height = 8;
  int fillWidth = map(percentage, 0, 100, 0, width);
  display.drawRect(x, y, width, height, WHITE);
  display.fillRect(x, y, fillWidth, height, WHITE);

  display.display();

  return 0;
}

int drawVoltage(String voltage)
{     
  display.clearDisplay();
  display.setCursor(10, 10);
  display.println(voltage.c_str());
  display.display();
  return 0;
}

void setup()
{

  Serial.begin(115200);
  pinMode(Pin_buzzer, OUTPUT);
  pinMode(Pin_ds18b20, INPUT);
  pinMode(Pin_LedGreen, OUTPUT);
  pinMode(Pin_LedRed, OUTPUT);
  pinMode(Pin_LedYellow, OUTPUT);
  pinMode(Pin_FreeButton, INPUT);

  ds18.begin();
  Wire.begin(Pin_i2c_sda, Pin_i2c_scl);

  display = Adafruit_SSD1306(128, 32, &Wire);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();

  display.setTextSize(1);
  display.setTextColor(WHITE);

  if (!VoltageSensor.begin(&Wire))
  {
    Serial.print("INA219 - Failed to find INA219 chip");
    while (1)
    {
      delay(10);
    }
  }
}

void loop()
{
  for (int percentage = 0; percentage <= 100; percentage++)
  {
    drawLoadingBar(percentage);
    delay(10);
  }

  playSuccessMelody();
  getIna219Data();
  delay(2000);  
  playErrorMelody();
  while(1){
   getIna219Data();
   handleButtonPress();
   delay(1000);
  }
}