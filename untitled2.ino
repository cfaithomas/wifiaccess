
#include <SoftwareSerial.h>



SoftwareSerial softSerial(10, 11); // RX, TX
String SSID = "HOTSPOT-PFIT";  // SSID du réseau Wi-Fi
String PASS = ""; // Mot de passe Wi-Fi





void setup()

{
    Serial.begin(9600);
    softSerial.begin(115200); // baudrate par défaut de l'ESP8266
    delay(100);
    sendValue();

}
void loop() {

}

void receiveValue(const int timeout)
{
    String reponse = "";
    long int time = millis();
    while( (time+timeout) > millis())
    {
        while(softSerial.available())
        {
            char c = softSerial.read();
            reponse+=c;
        }
    }
    Serial.print(reponse);
}

void sendValue() {

    // on va se connecter à un réseau existant, donc on passe en mode station
    softSerial.println("AT+CWMODE=1");
    receiveValue(1000);
    delay(1000);
    // on se connecte au réseau
    softSerial.println("AT+CWJAP=\""+SSID+"\",\""+PASS+"\"");
    receiveValue(1000);
    delay(5000);
    // mode "connexions multiples"
    softSerial.println("AT+CIPMUX=1");
    receiveValue(1000);
    delay(1000);

}