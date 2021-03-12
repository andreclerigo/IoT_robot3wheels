## Wiring
![](https://i.imgur.com/2zsgfrU.png)  
Then connect the Arduino to your computer and flash upload the code  
When you see "Conecting..." on the terminal press the RESET button on the ESP32-Cam  
After that disconnect the IO0 with GND and press the RESET button on the ESP32-Cam again  
It's done!

## Settings
__Flash Frequency:__ 40Mhz  
__Flash Mode:__ QIO  
__Partition Scheme:__ Huge APP (3MB No OTA/1MB SPIFFS)  
__Upload Speed:__ 115200  
__Monitor Speed:__ 115200  
Theese are specified in plaftormio.ini
