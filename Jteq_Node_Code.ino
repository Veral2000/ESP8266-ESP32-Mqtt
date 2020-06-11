/**************
 * By- Veral Agarwal
 */
 #include<ESP8266WiFi.h>
 //#include<WiFi.h> // uncomment this for ESP32
 #include<Wire.h>
 #include<PubSubClient.h> //Library for MQTT

 #define LED 2 
 #define PIR 5 //Node mcu pin D2

 //Entering SSID and Password of your Hotspot
 const char* ssid= "JioFiber-RSBYD";
 const char* password="anilzz123";

// Enter the ip adress of MQTT broker
const char* mqtt_server="192.168.29.221"; 
//const char* mqttuser="root";
//const char* mqttpass="";

char* deviceID ="HELLO";


 
String deviceID1 = String(deviceID) + "/command";
const char* device_IDx = deviceID1.c_str();
String deviceID2 = String(deviceID) + "/status"; 
const char* device_IDy = deviceID2.c_str();


WiFiClient espClient;
PubSubClient client(espClient); //(deviceid/command)
char msg[50];
long lastmsg=0;
char led_status[5];
int value=0;
  

void setup()
{
  //beforesetup();

  
  Serial.begin(9600);
  delay(500);
  //PIR 
  pinMode(PIR,INPUT);
  
  
  wificonnect();
  client.setServer(mqtt_server,1883); //change the port to 1883 if not working on 1889
  client.setCallback(callback);
  pinMode(LED,OUTPUT);
  digitalWrite(LED,LOW);
  
}

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
       
  if(String(topic) == device_IDx)  // deviceid/command     
  {
    if(messageTemp=="1")
    {
      Serial.println("Received 1");
      led_status[0] = 'O';
      led_status[1] = 'N';
      Serial.println("LED ON"); // showing the status in serial monitor
      digitalWrite(LED,HIGH);
      loop();
      }
      else if(messageTemp =="0")
      {
        Serial.println("Received 0");
        led_status[0]='O';
        led_status[1]='F';
        led_status[2]='F';
        Serial.println("LED OFF");
        digitalWrite(LED,LOW);
        loop();
      }
  }
}

void reconnect()
  {
    while(!client.connected())
    {
      Serial.println("Attempting MQTT Connection");
      
      if(client.connect(deviceID))
    {
      Serial.println("Connection Established");

      //For subscribe
      //char* topic2; 
      //deviceID1.toCharArray(topic2,20);
      client.subscribe(device_IDx);
      //client.publish("device_ID/debug","JTEQ SMART SYSTEM");
      
    } else {
      Serial.print("failed,rc=");
      Serial.print(client.state());
      Serial.println("Retrying in 5 seconds...");
      delay(5000);
    }
  }
}

void Pir()
{
  //String deviceID2 = String(deviceID) + "/status"; 
//const char* device_IDy=deviceID2.c_str();

long state=digitalRead(PIR);
  if(state==HIGH){
    delay(7000);
    Serial.println("Motion Sensor HIGH");
    client.publish(device_IDy,"1");
  }
  else { 
    delay(7000);
    Serial.println("Motion Sensor LOW");
    client.publish(device_IDy,"0");
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
