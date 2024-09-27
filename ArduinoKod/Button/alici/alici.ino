#include <VirtualWire.h>

char *mesaj;
int ledPin=3; // ÇIKIŞ 

void setup() {
 pinMode(ledPin,OUTPUT);

 Serial.begin(9600);
 vw_set_ptt_inverted(true);
 vw_set_rx_pin(8); // RF ALICI'DEN GIRIŞ SİNYALİ
 vw_setup(4000);
 vw_rx_start();
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN]; // Bu dizi, VirtualWire kütüphanesi aracılığıyla alınan mesajları depolamak için kullanmaktadır
  uint8_t buflen=VW_MAX_MESSAGE_LEN; // Dizisinin içindeki verilerin uzunluğunu tutar

if(vw_get_message(buf, &buflen))
{
  if(buf[0] == '0'){
    Serial.println(buf[0]);
    digitalWrite(ledPin, LOW);
    }

if(buf[0] == '1'){
    Serial.println(buf[1]);
    digitalWrite(ledPin, HIGH);
    }

  }


}
