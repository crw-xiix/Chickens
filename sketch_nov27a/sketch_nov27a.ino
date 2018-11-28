#include <ESP8266WiFi.h>
#include <Wire.h>
#include "wifi.h"


#define i2cSCL 1
#define i2cSDA 2

#define ledPin 2

WiFiServer server(80);

void setup() {
  // put your setup code here, to run once:

  
  Serial.begin(74880);
  delay(10);

  Wire.begin(1,2);
 
  Serial.println("Connecting to ");
  delay(1000);
  Serial.println("Connecting to ");
  
  
  pinMode(ledPin, OUTPUT);

  WiFi.mode(WIFI_STA);
  
  WiFi.hostname(wifiHostName);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  
  WiFi.begin(wifiNetwork,wifiPassword);
  
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(ledPin, LOW);
    delay(250);
    digitalWrite(ledPin, HIGH);
    delay(250);
    
  }
  
  // Start the server
  server.begin();
  Serial.println("Server started");
  
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  
}

void loop() {
  // Check if a client has connected

  Serial.println("Waiting...");
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");


  while(client.connected() && !client.available())
  {
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Match the request
  int value = LOW;
  if (request.indexOf("/LED=ON") != -1) {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/LED=OFF") != -1) {
    digitalWrite(ledPin, LOW);
    value = LOW;
  }

  // Return the response

  client.println("<!doctype html>");

client.println("<html lang=\"en\">");
  client.println("<head>");
    //<!-- Required meta tags -->
    client.println("<meta charset=\"utf-8\">");
    client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1, shrink-to-fit=no\">");

    //<!-- Bootstrap CSS -->
    client.println("<link rel=\"stylesheet\" href=\"https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css\" integrity=\"sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO\" crossorigin=\"anonymous\">");

    client.println("<title>Hello, world!</title>");
  client.println("</head>");
  client.println("<body>");
    client.println("<div class=\"container\">");
  
    client.println("<div class=\"jumbotron\">");
    client.println("<h1>Hello, world!</h1>");
      client.println("<div class=\"row\">");
      client.println("<div class=\"col\">Temp:  67 F</div>");
      client.println("<div class=\"col\">Water: 12\" </div>");
      client.println("<div class=\"col\">Lights: 54% </div>");
    client.println("</div>");
client.println("</div>");
        
  client.println("<br><br>");
//class=\"btn btn-info\" role=\"button\"
  
  client.println("<div>Toggle the LED</div>");
  client.println("<a class=\"btn btn-success\" role=\"button\"  href=\"/LED=ON\">On</a>");
  client.println("<a class=\"btn btn-dark\" role=\"button\" href=\"/LED=OFF\">Off</a>");
      client.println("<script src=\"https://code.jquery.com/jquery-3.3.1.slim.min.js\" integrity=\"sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo\" crossorigin=\"anonymous\"></script>");
      client.println("<script src=\"https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js\" integrity=\"sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49\" crossorigin=\"anonymous\"></script>");
      client.println("<script src=\"https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js\" integrity=\"sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy\" crossorigin=\"anonymous\"></script>");
  client.println("</div>");  
  client.println("</body>");
  client.println("</html>");

/*
    <!-- Optional JavaScript -->
    <!-- jQuery first, then Popper.js, then Bootstrap JS -->
    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy" crossorigin="anonymous"></script>
    */
  client.println("</body>");
client.println("</html>");




  /*
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); // do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.print("Led pin is now: ");

  if(value == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("Click <a href=\"/LED=ON\">here</a> turn the LED on pin 2 ON<br>");
  client.println("Click <a href=\"/LED=OFF\">here</a> turn the LED on pin 2 OFF<br>");
  client.println("</html>");

  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
  */
}

  
