# ESP8266-ESP32-Mqtt
I am working on a project in which i am making the ESP8266/ESP32 a node for the hub and Establish communication between Hub and Nodes via MQTT. In my case i am using Raspberry pie as a HUB and ESP8266 as a Node. In the my node code you can see how I make every node unique with the deviceID and make topic for MQTT for publihing and subscribing.

//---------------------------SEE THE STEPS FOR SETTING THR ARDUINO IDE-------------------------
This file Includes all the Steps Nedded for Uploading and Running the code in the ESP32/ESP8266. 

In Arduino IDE-

Step1- Set Preferances for ESP8266 and ESP32 -

1-Preferances-
ESP32-https://dl.espressif.com/dl/package_esp32_index.json
ESP8266-http://arduino.esp8266.com/stable/package_esp8266com_index.json%22

ArduinoIDE=>File=>Preferances=>Additional Boards Manage URL's=>Paste the Preferances. (Seperate both by Comma)

2-Install Boards- 
Arduino Ide=>Tools=>Boards=>Manage Boards=>Enter ESP32 in the Search field=>Install.
Same for the ESP8266

Step2- Download/Import all the Libraries-
Download -Arduino Ide=>Tools=>Manage Libraries=> Enter the name of the Library in search field=>Install / Select the version=>Install.
Library Required- ESP8266WiFi, WiFi, Pubsubclient,  Wire. (Place all the names in the Search Field and Install them all Respectievely)

Step3- Open the code-
Arduino IDE=>File=>Open=>Select the Jteq_Node_code.ino File.(Extension must be ino or convert if any other)

Step4-Compile and Upload the Code-

1-Select the board on which you want to upload. Arduino IDE=>Tools=>Boards=>NodeMCU 1.0 /ESP32 DEV (Or whatever Model is yours)

2-Compile the code- ArduinoIDE=>Sketch=>Verify/Compile

3-Upload the code- ArduinoIDE=>Sketch=>Upload.

Step5-Open the Serial Monitor.
Arduino IDE=>ctrl+shift+M / Tools=>Serial Monitor (Set the Baud Rate to 9600).



  




