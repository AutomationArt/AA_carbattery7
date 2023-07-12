## CarBat (for Automation.art)

- Case - case for 3D printing for this device
- Code - code examples  
- Docs - documents for chips
- Image - photo of the ready device
- Pcb - all files for the pcb making

#### Right away about bugs that were fixed in the scheme after the first prototype

!Voltage divider of 10k and 37k on DCDC feedback (were both 37)
!PH and BOOT  - Changing the capacitor connection

###  How does it work?
You just connect the device to the battery and get the result on the screen/browser (in development)

### Main features

- Voltage measurement range 7-36 volts
- LED indicator 3 pieces (3 different colors)
- Display for information output (optional)
- Load connection and power measurement (2A max, optional)
- Audible indicator for warning
- Temperature sensor connection (optional)
- User button for your functions
- External antenna connection for long-distance Wifi/Bluetooth
- Possibility to connect sensors via UART

### Examples of use
- Measuring vehicle battery voltage
- Measurement of any battery voltage
- understanding the rate of discharge or charge of batteries by voltage
- DC low voltage measurement
- Measurement of consumption of a load connected to the device
- audible alarm of the set parameters of accumulator or DC network voltage
- others        

### Current PCB release
[![carbat](/Image/3_13.png "carbat")](/Image/3_13.png "carbat")
[![carbat_aelmaker](/Image/1_13.png "carbat_aelmaker")](/Image/1_13.png "carbat_aelmaker")
[![carbat_aelmaker](/Image/2_13.png "carbat_aelmaker")](/Image/2_13.png "carbat_aelmaker")

### Manufactured device

[![carbat](/Image/2_1.png "carbat")](/Image/2_1.png "carbat")
[![carbat](/Image/2_3.png "carbat")](/Image/2_3.png "carbat")

### Case

in progress

### Specifications

| Name | Justification |
| ------------ | ------------ |
| esp32-c3-u2 | cheap energy efficient controller |
| TPS54240DGQR | wide power range device |
| AP2112K-3.3TRG1 | time and experience proven voltage regulator |
| MLT-7525 | easy to use booster |
| INA219AIDR | wide range voltage meter
| LED x3 | indicators
| Oled 0.91 | small, not expensive screen |  
| Ds18b20 | accurate temperature sensor (optional)|
