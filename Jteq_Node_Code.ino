/**************
 * By- Veral Agarwal
 */
 #include<ESP8266WiFi.h>
 //#include<WiFi.h> // uncomment this for ESP32 and comment ESP8266WiFI.h
 #include<Wire.h>
 #include<PubSubClient.h> //Library for MQTT

 #define LED 2 //In built LED
 #define PIR 5 //Node mcu pin D1

 //Entering SSID and Password of your Hotspot
 const char* ssid= "YOUR_SSID";
 const char* password="YOUR_PASSWORD";

// Enter the ip adress of MQTT broker
const char* mqtt_server="MQTT_SERVER"; 
const char* mqttuser="USER_MQTT"; //If Enabled
const char* mqttpass="MQTT_PASSWORD";

char* deviceID ="DEVICE_ID";


 //Making Unique topic for Publishing and Subscribing  
String deviceID1 = String(deviceID) + "/command";
const char* device_IDx = deviceID1.c_str(); //Converting from String to char
String deviceID2 = String(deviceID) + "/status"; 
const char* device_IDy = deviceID2.c_str();

//Print both the topics
Serial.println(device_IDx);
Serial.println(device_IDy);

//Wifi Client espClient
WiFiClient espClient;
PubSubClient client(espClient); //(deviceid/command)
char msg[50];
long lastmsg=0;
char led_status[5];
int value=0;
  

void setup()
{
  Serial.begin(9600);
  delay(500);
 
  //------Defining the PIR Mode as INPUT-------------- 
  pinMode(PIR,INPUT);
  
  
  wificonnect();
  client.setServer(mqtt_server,1889); //change the port to 1883 if not working on 1889
  client.setCallback(callback);
 
  pinMode(LED,OUTPUT);
  digitalWrite(LED,LOW);
  
}

//--------Connecting to the WIFI-----------------

void wificonnect()
{
  Serial.println();
  Serial.print("Connecting to...");
  Serial.println(ssid);
  WiFi.begin(ssid,password);

  while(WiFi.status() !=WL_CONNECTED)
  {
    delay(500);
    Serial.println(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

//--------------------MQTT Message-----------------------

void callback(char* topic,byte* message, unsigned int length){
  Serial.print("Message arrived on topic:");
  Serial.println(topic);
  Serial.print(".Message:");
  String messageTemp;

  for(int i=0;i<length;i++)
  {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
       
  if(String(topic) == device_IDx)  // if topic is deviceID/command     
  {
    if(messageTemp=="1")
    {
      Serial.println("Received 1");
      led_status[0] = 'O';
      led_status[1] = 'N';
      Serial.println("LED ON"); // showing the status in Serial Monitor
      digitalWrite(LED,HIGH);
      loop();
      }
      else if(messageTemp =="0")
      {
        Serial.println("Received 0");
        led_status[0]='O';
        led_status[1]='F';
        led_status[2]='F';
        Serial.println("LED OFF"); //showing the Status in Serial Monitor
        digitalWrite(LED,LOW);
        loop();
      }
  }
}

//----------Connecting to the MQTT Server------------

void reconnect()
  {
    while(!client.connected())
    {
      Serial.println("Attempting MQTT Connection");
      
      if(client.connect(deviceID))
    {
      Serial.println("Connection Established");
       client.subscribe(device_IDx); //Subscribe to the topic deviceID/command
      
    } else {
      Serial.print("failed,rc=");
      Serial.print(client.state());
      Serial.println("Retrying in 5 seconds...");
      delay(5000);
    }
  }
}

//--------------PIR (Motion Sensor)---------------
void Pir()
{
long state=digitalRead(PIR);
  if(state==HIGH){
    delay(7000);
    Serial.println("Motion Sensor HIGH");
    client.publish(device_IDy,"1"); //publish "1" when th PIR sensor is HIGH to the topic deviceID/status
  }
  else { 
    delay(7000);
    Serial.println("Motion Sensor LOW");
    client.publish(device_IDy,"0"); //publish "0" When the PIR sensor is LOW to the topic deviceID/status
  }
}

void loop()
{
  Pir();
  
  if(!client.connected())
  {
    reconnect();
  }
  client.loop();
}
