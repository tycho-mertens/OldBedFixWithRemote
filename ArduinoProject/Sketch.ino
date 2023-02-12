#include "includes.h"

#define LEGS_UP 9
#define LEGS_DOWN 10
#define HEAD_UP 11
#define HEAD_DOWN 12


char ssid[] = "YourWifiNetwork";  // Put your own Wifi name in here
char pass[] = "YourPassword";     // Put your own Wifi password in here
IPAddress ip(10, 0, 0, 102);      // Assign static ip (this ip is also staticly set in the android app)

WiFiServer server(7700);
int status = WL_IDLE_STATUS;

void setup() {

  pinMode(LEGS_UP, OUTPUT);
  pinMode(LEGS_DOWN, OUTPUT);
  pinMode(HEAD_UP, OUTPUT);
  pinMode(HEAD_DOWN, OUTPUT);
  
  Serial.begin(9600);
  while(!Serial){}
  WiFi.config(ip);
  connectToAP();  
  printWifiStatus();
  server.begin();
}

void printWifiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void connectToAP() {
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);

    delay(1000);
    Serial.println("Connected...");
  }
}


void loop() {
  if(status != WL_CONNECTED) return;  //Check if we're connected to AP
  
  WiFiClient c = server.available();
  Communications coms(&c);
  TelnetConsole tc(&coms);
  if(!c) return; // Continue if there is no client

  while(1){
    String req = coms.recv();
    
    SimplePacket p(req);
    p.printInfo();
    if(p.isEmpty()) break;

    String type = p.actionType;
    if(type.equals("CMD")){
      String cmd = p.message;
      cmd.trim();

      //Switch statements won't work here with arduino String objects,
      //There is also a better way to do this, but this works
      if(cmd.equals("legsUp")){
        tc.println("Operation: Legs UP");
        execute(LEGS_UP, p.param);
      }else if(cmd.equals("legsDown")){
        tc.println("Operation: Legs DOWN");
        execute(LEGS_DOWN, p.param);
      }else if(cmd.equals("headUp")){
        tc.println("Operation: Head UP");
        execute(HEAD_UP, p.param);
      }else if(cmd.equals("headDown")){
        tc.println("Operation: Head DOWN");
        execute(HEAD_DOWN, p.param);
      }else if(cmd.equals("bothUp")){
        tc.println("Operation: Both UP");
        executeBoth(HEAD_UP, LEGS_UP, p.param);
      }else if(cmd.equals("bothDown")){
        tc.println("Operation: Both DOWN");
        executeBoth(HEAD_DOWN, LEGS_DOWN, p.param);
      }
    }else if(type.equals("MSG")){
      //This is merely to test the connection
      String msg = p.message;
      msg.trim();
      if(msg.equals("hello")){
        //Join command
        coms.send("HELLO");
        tc.println("Client connected!");
      }else if(msg.equals("quit")){
        //Quit command
        coms.send("GOODBYE");
        c.stop();
        tc.println("Client disconnected!");
      }else if(msg.equals("ping")){
        //Ping pong command
        tc.println("Received 'ping', sending 'pong'");
        coms.send("PONG");
      }
    }
  }
}

void execute(int pin, int param){
  if(param == -1) return;
  digitalWrite(pin, param == 0 ? LOW : HIGH);
}

void executeBoth(int pinOne, int pinTwo, int param){
  if(param == -1) return;
  digitalWrite(pinOne, param == 0 ? LOW : HIGH);
  digitalWrite(pinTwo, param == 0 ? LOW : HIGH);
}
