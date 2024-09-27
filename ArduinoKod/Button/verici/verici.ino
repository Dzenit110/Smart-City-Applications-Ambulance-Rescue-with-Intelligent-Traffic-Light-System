#include <VirtualWire.h> // Gereken kütüphane tanımlanmak

char *mesaj;
int buttonPin=6; // Burada şu Remotexy &  ESP8266 için pin tanımlanmaktadır
int buttonDurum;


void setup() {
Serial.begin(9600); // Serial Monitor çalışmasına başlasın
pinMode(buttonPin,INPUT); // Pin giriş olarak tanımlanmak

vw_set_ptt_inverted(true);
vw_set_tx_pin(6);
vw_setup(4000); // Kütüphanden gelen komutlar

}

void loop() {

 buttonDurum=digitalRead(buttonPin); // 1 ya da 0 değeri gelmektedir

 if(buttonDurum == HIGH) // Gelen değeri 1 iste 
 { 
  mesaj="1";
  }
else{
  mesaj="0";
  }

  Serial.println(mesaj);
  vw_send((uint8_t *)mesaj,strlen(mesaj));
  vw_wait_tx();
  delay(100);

  
}
