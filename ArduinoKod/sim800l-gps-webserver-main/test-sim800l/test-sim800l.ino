#include <SoftwareSerial.h> // Kütüphane tanımlanmaktadır

#define rxPin 2 // Gereken pinler tanımlamak
#define txPin 3
SoftwareSerial sim800L(rxPin,txPin); 

void setup()
{
  //Arduino ve Arduino IDE (Serial Monitor) ile seri iletişimi başlatmak
  Serial.begin(115200);
  
  // Arduino ve SIM800L Modül arasaında iletişim başlasın
  sim800L.begin(9600);

  Serial.println("Başlatılıyor...");
  delay(1000);
}

void loop()
{
  
  while(sim800L.available()){ // SIM800L modülünden gelen verileri oku ve Arduino Uno'nun ana seri bağlantısı üzerinden yazdırmaktadır
    Serial.println(sim800L.readString());
  }
  while(Serial.available())  { // Arduino Uno'nun ana seri bağlantısından gelen verileri okuyup SIM800L modülüne göndermektedir
    sim800L.println(Serial.readString());
  }
}
