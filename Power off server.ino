#include <SPI.h>
#include <Ethernet.h>
const int inputPin = 13;


// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
IPAddress server(10,10,1,31);  // numeric IP for Google (no DNS)
//char server[] = "http://10.10.1.31";    // name address for Google (using DNS)

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(10, 10,1, 18);

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

//Innicial state of the pin
//int buttonState = 0; 

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  pinMode(13, INPUT);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  
 
}

void loop() {   
  delay(1000);
  
  bool buttonState = digitalRead(inputPin);
  
  if( buttonState==1){  
  Serial.println("Power available");
  }else  { Serial.println("Power down!!!!!!!!!!!!!!!!!!!!!");
  }
  
  Serial.println("conneting to the remote server...");
  Serial.println(client.connect(server,3000));
  if(buttonState == 0){
      delay(30000);
    }
  
   //waiting for while to check again
   if(buttonState == 0){
      client.stop();  
      Serial.println("conneting to remote server after delay...");
 
        if(client.connect(server,3000) == true) {
            Serial.println("connected to  remote server after delay...");
            Serial.println("calling machine shut down...");
                   client.print("GET /run");
                   client.println(" HTTP/1.1");                  
                   client.println("User-Agent: Arduino");                            
                   client.println("Accept: text/html");          
                   client.println();                            
            char c = client.read();
            Serial.print(c);
            client.stop();
             Serial.println("Machine shut down executed...");
             Serial.println("--------------------------------------------------------------");
        }
   
      }
 
 else {
    Serial.println("cannot connet to remote server");
    client.stop();
    }
  
}
