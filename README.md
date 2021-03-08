# robot3wheels_esp32cam  
A project that will take a simple Arduino project to a controlled robot trough the internet with video feed  
**This project uses VSCode extension [PlatformIO](https://platformio.org/) to program the microcontrollers**

# ESP32-Cam
Flashing with Arduino UNO but you also could use a [FTDI USB to TLL](http://lechacalshop.com/162-large_default/ftdi-usb-to-ttl-serial-converter-adapter-ft232rl.jpg)  
Using an ESP32-Cam with an ESP32-2S chip that is compatible with CAMERA_MODEL_AI_THINKER  

## Flashing code
### Wiring
![](https://i.imgur.com/2zsgfrU.png)  
Then connect the Arduino to your computer and flash upload the code  
When you see "Conecting..." on the terminal press the RESET button on the ESP32-Cam  
After that disconnect the IO0 with GND and presse the RESET button on the ESP32-Cam again  
It's done!

## Settings
__Flash Frequency:__ 40Mhz  
__Flash Mode:__ QIO  
__Partition Scheme:__ Huge APP (3MB No OTA/1MB SPIFFS)  
__Upload Speed:__ 115200  
__Monitor Speed:__ 115200  
Theese are specified in plaftormio.ini
