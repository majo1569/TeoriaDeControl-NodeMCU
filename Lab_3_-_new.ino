#include <ESP8266WiFi.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include <DateTime.h>

String ssid = "wfrre";
String password = "BityAtomo";
WiFiServer server(80);

String json;
DynamicJsonDocument doc(1024);
const byte I2C_SLAVE_ADDR = 0x7f; //cambiar esto

int led1 = D3;
int led2 = D4;
int led3 = D5;
int led4 = D6;
int led5 = D7;
int rele = D8;
int sonido_analogico = A0;
const int sensitivity = -58; //Sensibilidad del microfono  
const int gain = 20;             
const int sampleWindow = 1000;
unsigned int sample;

void setup() {
  //Iniciar Serial
  Serial.begin(9600);
  Serial.println("\n");
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(rele, OUTPUT);

  Wire.begin(I2C_SLAVE_ADDR);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);

  //Conexion WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay (500);
    Serial.print(".");
  }

  Serial.print("\n");
  Serial.println("#######################################################");
  Serial.print("Conectado a la red: ");
  Serial.println(WiFi.SSID());
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("macAdress: ");
  Serial.println(WiFi.macAddress());
  Serial.println("#######################################################");

  server.begin(); //Levantar el server 
  digitalWrite(rele, LOW);
}

  const char ASK_FOR_LENGTH = 'L';
  const char ASK_FOR_DATA = 'D';
  char request = ' ';
  char requestIndex = 0;

  void SerializeObject(JsonArray sensors, JsonArray actuators){
    doc["cotroller_name"] = "NodeMCU-2";
    doc["date"] = DateTime.now();
    doc["actuators"] = actuators;
    doc["sensors"] = sensors;
    serializeJson(doc, json);
  }

  void receiveEvent (int bytes){
      while (Wire.available()){
        request = (char)Wire.read();
      }
  }

  void requestEvent (){
    if (request == ASK_FOR_LENGTH){
      Wire.write(json.length());
      char requestIndex = 0;
    }
    if (request == ASK_FOR_DATA){
      if (requestIndex < (json.length()/32)){
        Wire.write(json.c_str() + requestIndex * 32, 32);
        requestIndex ++;
      }
      else {
        Wire.write(json.c_str() + requestIndex * 32, (json.length() % 32));
        requestIndex = 0;
      }
    }
  }

  void loop() {
    unsigned long startMillis= millis();
    unsigned int peakToPeak = 0; 
    unsigned int signalMax = 0;
    unsigned int signalMin = 1024;
    
    StaticJsonDocument<200> actuator1;
    StaticJsonDocument<200> actuator2;
    StaticJsonDocument<200> actuator3;
    StaticJsonDocument<200> actuator4;
    StaticJsonDocument<200> actuator5;
    StaticJsonDocument<200> actuator6;
    StaticJsonDocument<200> sensor1;
    DynamicJsonDocument docActuators(1024);
    JsonArray arrActuators = docActuators.to<JsonArray>();
    DynamicJsonDocument docSensors(1024);
    JsonArray arrSensors = docSensors.to<JsonArray>();
    actuator1["type"]="led1";
    actuator2["type"]="led2";
    actuator3["type"]="led3";
    actuator4["type"]="led4";
    actuator5["type"]="led5";
    actuator6["type"]="rele";
    sensor1["type"]= "mic";
    actuator6["current_value"] = 0;
  
    int val_analogico = analogRead(sonido_analogico);
    Serial.print("Valor analogico: ");
    Serial.print(val_analogico);
    Serial.print("\t");
    Serial.print("->");
    Serial.print("\t");
  
   while (millis() - startMillis < sampleWindow){
     sample = analogRead(sonido_analogico);
     if (sample < 1024){
      if (sample > signalMax){
       signalMax = sample;
      }
      else if (sample < signalMin){
         signalMin = sample;
      }
     }
    }
    peakToPeak = signalMax - signalMin;
    double volts = ((peakToPeak * 3.3) / 1024)*10;
    double volts_db = 20*log10(volts/0.001259); 
    Serial.print("dB: " + String(volts_db) );
    Serial.print("\n");
    sensor1["current_value"] = volts_db;
    digitalWrite (rele, LOW);
    actuator6["current_value"] = 0;
  
    if (val_analogico < 500){
      digitalWrite (led1, HIGH);
      digitalWrite (led2, HIGH);
      digitalWrite (led3, HIGH);
      digitalWrite (led4, HIGH);
      digitalWrite (led5, HIGH);
      actuator1["current_value"] = 1;
      actuator2["current_value"] = 1;
      actuator3["current_value"] = 1;
      actuator4["current_value"] = 1;
      actuator5["current_value"] = 1;
      digitalWrite (rele, HIGH);
      actuator6["current_value"] = 1;
    }
    else if (val_analogico < 650){
      digitalWrite (led1, HIGH);
      digitalWrite (led2, HIGH);
      digitalWrite (led3, HIGH);
      digitalWrite (led4, HIGH);
      digitalWrite (led5, LOW);
      actuator1["current_value"] = 1;
      actuator2["current_value"] = 1;
      actuator3["current_value"] = 1;
      actuator4["current_value"] = 1;
      actuator5["current_value"] = 0;
    }
    else if (val_analogico < 750){
      digitalWrite (led1, HIGH);
      digitalWrite (led2, HIGH);
      digitalWrite (led3, HIGH);
      digitalWrite (led4, LOW);
      digitalWrite (led5, LOW);
      actuator1["current_value"] = 1;
      actuator2["current_value"] = 1;
      actuator3["current_value"] = 1;
      actuator4["current_value"] = 0;
      actuator5["current_value"] = 0;
    }
    else if (val_analogico < 850){
      digitalWrite (led1, HIGH);
      digitalWrite (led2, HIGH);
      digitalWrite (led3, LOW);
      digitalWrite (led4, LOW);
      digitalWrite (led5, LOW);
      actuator1["current_value"] = 1;
      actuator2["current_value"] = 1;
      actuator3["current_value"] = 0;
      actuator4["current_value"] = 0;
      actuator5["current_value"] = 0;
    }
    else if (val_analogico < 950){
      digitalWrite (led1, HIGH);
      digitalWrite (led2, LOW);
      digitalWrite (led3, LOW);
      digitalWrite (led4, LOW);
      digitalWrite (led5, LOW);
      actuator1["current_value"] = 1;
      actuator2["current_value"] = 0;
      actuator3["current_value"] = 0;
      actuator4["current_value"] = 0;
      actuator5["current_value"] = 0;
    }
    else {
      digitalWrite (led1, LOW);
      digitalWrite (led2, LOW);
      digitalWrite (led3, LOW);
      digitalWrite (led4, LOW);
      digitalWrite (led5, LOW);
      actuator1["current_value"] = 0;
      actuator2["current_value"] = 0;
      actuator3["current_value"] = 0;
      actuator4["current_value"] = 0;
      actuator5["current_value"] = 0;
    }
    arrActuators[0] = actuator1;
    arrActuators[1] = actuator2;
    arrActuators[2] = actuator3;
    arrActuators[3] = actuator4;
    arrActuators[4] = actuator5;
    arrActuators[5] = actuator6;
    arrSensors[0] = sensor1;
    SerializeObject(arrSensors, arrActuators);
    delay(3000);
  }
