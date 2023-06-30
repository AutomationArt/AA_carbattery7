#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_INA219.h>

#define Pin_i2c_scl 4
#define Pin_i2c_sda 5
#define Pin_buzzer 19
#define Pin_ds18b20 18
#define Pin_LedGreen 1
#define Pin_LedRed 2
#define Pin_LedYellow 3
#define Pin_FreeButton 10

class Equip
{
private:
  int pinBuzzer;
  int pinRedLED;
  int pinYellowLED;
  int pinGreenLED;
  int pinTemperature;
  int pinButton;
  int pinIna219SDA;
  int pinIna219SCL;

  Adafruit_INA219 ina219;

public:
  Equip(int buzzerPin, int redLEDPin, int yellowLEDPin, int greenLEDPin, int temperaturePin,
        int buttonPin, int ina219SDAPin, int ina219SCLPin)
  {
    pinBuzzer = buzzerPin;
    pinRedLED = redLEDPin;
    pinYellowLED = yellowLEDPin;
    pinGreenLED = greenLEDPin;
    pinTemperature = temperaturePin;
    pinButton = buttonPin;
    pinIna219SDA = ina219SDAPin;
    pinIna219SCL = ina219SCLPin;

    pinMode(pinBuzzer, OUTPUT);
    pinMode(pinRedLED, OUTPUT);
    pinMode(pinYellowLED, OUTPUT);
    pinMode(pinGreenLED, OUTPUT);
    pinMode(pinButton, INPUT);

    Wire.begin(pinIna219SDA, pinIna219SCL);

    if (ina219.begin(&Wire))
    { 
      ESP_LOGD("INA219", "Begin - ok");
    }
    else
    {
      ESP_LOGD("INA219", "Begin - error");
    }

  }

  void playMelody(int melody[], int noteDuration)
  {
    for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++)
    {
      tone(pinBuzzer, melody[i], noteDuration);
      delay(noteDuration);
    }
    noTone(pinBuzzer);
  }

  void playSuccessMelody()
  {
    ESP_LOGD("Play", "Success");
    int successMelody[] = {262, 330, 392, 523, 392, 330};
    int noteDuration = 200;
    playMelody(successMelody, noteDuration);
  }

  void playErrorMelody()
  {
    ESP_LOGD("Play", "Error");
    int errorMelody[] = {262, 196, 196, 262};
    int noteDuration = 250;
    playMelody(errorMelody, noteDuration);
  }

  void setLEDState(int pin, bool state)
  {
    digitalWrite(pin, state);
  }



  bool isButtonPressed()
  {
    return digitalRead(pinButton) == LOW;
  }

  float getIna219Voltage()
  {
    return ina219.getBusVoltage_V();
  }

  float getIna219Current()
  {
    return ina219.getCurrent_mA();
  }

  float getIna219Power()
  {
    return ina219.getPower_mW();
  }
};

Equip equipEsp(Pin_buzzer, Pin_LedRed, Pin_LedYellow, Pin_LedGreen, Pin_ds18b20, Pin_FreeButton, Pin_i2c_sda, Pin_i2c_scl);

void setup()
{
  ESP_LOGD("Setup", "130");
}

void loop()
{

  ESP_LOGD("Voltage", "%f", equipEsp.getIna219Voltage()); 
  delay(2000);
}