## Wiring
![](https://i.imgur.com/lZZITK0.png)  
Then connect the Arduino to your computer open the project on platformIO and click upload 
When you see "Conecting..." on the terminal press the RESET button on back of the ESP32-Cam board   
After that disconnect the IO0 from GND and press the RESET button again    
It's done!

## Settings
__Flash Frequency:__ 40Mhz  
__Flash Mode:__ QIO  
__Partition Scheme:__ Huge APP (3MB No OTA/1MB SPIFFS)  
__Upload Speed:__ 115200  
__Monitor Speed:__ 115200  
Theese are specified in plaftormio.ini
