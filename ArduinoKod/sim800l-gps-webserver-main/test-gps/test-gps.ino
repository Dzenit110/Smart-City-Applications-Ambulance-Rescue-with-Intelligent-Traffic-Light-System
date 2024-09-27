#include <SoftwareSerial.h> // Gereken Kütüpahen tanımlamak

#define rxPin 9
#define txPin 8 // Gereken Pinleri tanımalamk, tx-transmitter; rx-receiver
SoftwareSerial gpsSerial(rxPin,txPin); 

void setup()
{
  //Arduino ve Arduino IDE (Serial Monitor) ile seri iletişimi başlatsın (Serial Monitor)
  Serial.begin(115200);
  
  // Arduino ve Ublox NEO 6M Modül arasında seri iletişim, genel GPS için hızı 9600 baud 
  gpsSerial.begin(9600);

  Serial.println("Başlatılıyor...");
  delay(1000); // 1 saniye yavaşlatma
}

void loop()
{
  while (gpsSerial.available() > 0) // İletişimde gelen byte var mı diye kontrol etmektedir
    Serial.write(gpsSerial.read()); // Gelen bilgi seri monitöründe göstermektedir
}
