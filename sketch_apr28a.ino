//#include <DHT.h>
#include "MySQL_Connection.h"
#include "MySQL_Cursor.h"
#include "ESP8266WiFi.h"
#include "WiFiClient.h"

//#define sensorPin2 D2
//#define typeDHT DHT11
//DHT dht(sensorPin1, typeDHT);

char ssid[] = "Inca";                 // Network Name Inca      AndroidAP
char pass[] = "sql75hj8";                 // Network Password sql75hj8            qmnt4010
byte mac[6]; 

WiFiServer server(80);
IPAddress ip(192,168,1,4);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

WiFiClient client;
MySQL_Connection conn((Client *)&client);

char UPDATE_SQL[] = "UPDATE bitirmee.parkbul set durum='%d' where id=2";
//char INSERT_SQL[] = "INSERT INTO officeto_plants.TBL_READINGS(ID_PLANT, AIR_HUMIDITY, AIR_TEMPERATURE, SOIL_MOISTURE_1, SOIL_MOISTURE_2) VALUES (1, NULL, NULL, %d, %d)";
char query[128];

IPAddress server_addr(85,10,205,173);       // MySQL server IP
char user[] = "burakgulec";           // MySQL user
char password[] = "Asdf1234567";       // MySQL password

void setup() {

  
  
  //pinMode(ldr_pin,INPUT);
  
  Serial.begin(9600);

  //pinMode(sensorPin2, INPUT);

  Serial.println("Initialising connection");
  Serial.print(F("Setting static ip to : "));
  Serial.println(ip);

  Serial.println("");
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi Connected");

  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  Serial.print(mac[5], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.println(mac[0], HEX);
  Serial.println("");
  Serial.print("Assigned IP: ");
  Serial.print(WiFi.localIP());
  Serial.println("");

  Serial.println("Connecting to database");

  while (conn.connect(server_addr, 3306, user, password) != true) {
    delay(200);
    Serial.print ( "." );
  }

  Serial.println("");
  Serial.println("Connected to SQL Server!");

}

void loop() {
int konum=digitalRead(D7);
//int konum=200;
 
  //float t = dht.readTemperature();

  //Serial.println(t);

  delay(5000); //10 sec

  
  sprintf(query, UPDATE_SQL,konum);

  Serial.println("Recording data.");
  Serial.println(query);

  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);

  cur_mem->execute(query);

  delete cur_mem;

}

