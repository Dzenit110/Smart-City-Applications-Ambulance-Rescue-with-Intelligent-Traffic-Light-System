#include <VirtualWire.h> // Gereken kütüphane eklemketedir

char *mesaj; // Gelen mesaj, Serial Monitor'da göstermektedir
int kirmizi1 = 2; //  Pinler Led diyotlar için tanımlanmaktadır
int sari1 = 3; // Doğu - Batı şekilde  Trafik Işıkları için tanımlamaları
int yesil1 = 4;  

int kirmizi2 = 5; 
int sari2 = 6;  // Kuzey - Guney şekilde  Trafik Işıkları için tanımlamaları
int yesil2 = 7;

int delay_yesil = 5000;
int delay_sari = 3000;  // ms olarak trafik lambası ne kadar ışık yansıtacak
int delay_kirmizi=5000;
int delay_blinking_yesil = 500;

int doguBatidurum ; //Değişken  Doğu - Batı  şekilde Trafik Işıkları için kontrol amaçlı tanımlanmaktadır

void setup() {
  
 Serial.begin(9600);  // Serial Monitor hızı
 vw_set_ptt_inverted(true);
 vw_set_rx_pin(8); // RF ALICI'DEN GIRIŞ PIN SİNYALİ
 vw_setup(4000);  // Kütüphaneden  belirli bir bit hızıyla başlatmak için kullanmaktadır
 vw_rx_start(); // Alım modunda başlatmak için 

  
pinMode(kirmizi1, OUTPUT);  // Trafik  ışık bağlanan led diyotlar çıkış olarak tanımlanmaktadır
pinMode(sari1, OUTPUT);
pinMode(yesil1, OUTPUT);

pinMode(kirmizi2, OUTPUT);
pinMode(sari2, OUTPUT);

pinMode(yesil2, OUTPUT);
}

 // Doğu - Batı için trafik ışığı sistemi olarak başlamaktadır, ilk olan yeşil o tarafta olacak

void yesil_isik(){   
  digitalWrite(kirmizi1, LOW);  // HIGH  - "1" anlamına gelmektedir, böylece gereken diyot yanacak
  digitalWrite(sari1, LOW);   // LOW - "0" demektir ve gereken diyot ışık yansıtmayacak
  digitalWrite(yesil1, HIGH);
  
  digitalWrite(sari2, LOW);
  digitalWrite(yesil2, LOW);
  digitalWrite(kirmizi2, HIGH); // Kuzey - Doğu için trafik lambaları kırmızı ışık gösterilmektedir
  doguBatidurum=0; // Kontrol amaçlı şekilde değştirmektedir
  void yesil_blinking(); // Başka bir fonksiyon çağırmaktadır
  delay(delay_yesil); // Birkaç ms şekilde bütün işlem sürecek
  }
  
void sari_isik(){  // Burada sari ışık şekilde fonksiyon tanımlanmaktadır 
  
  digitalWrite(yesil2, HIGH);
  digitalWrite(sari2, LOW);
  digitalWrite(kirmizi2, LOW);
  
  digitalWrite(yesil1, LOW);
  digitalWrite(kirmizi1, HIGH); // Burada Batı- Doğu şekilde sari ışık şekilde yanacak
  digitalWrite(sari1, HIGH);
  doguBatidurum = HIGH; 
  
  void yesil_blinking();
  delay(delay_sari); // Belirli ms olarak bütün işlem olacak
  void yesil_isik(); // Fonksiyonu çağırmaktadır
   
  }

void kirmizi_isik(){
  
  digitalWrite(yesil1, LOW);
  digitalWrite(sari1, LOW);
  digitalWrite(kirmizi1, HIGH); // Burada Doğu - Batı ışıkları kırmızı şekilde yansıtacak
  
  digitalWrite(kirmizi2, LOW);
  digitalWrite(sari2, LOW);
  digitalWrite(yesil2, HIGH); // Burada Kuzey - Güney ışıkları yeşil şekilde yansıtacak
  delay(delay_kirmizi); // ms olarak belirli işlem sürecek
  void sari_isik(); // Başka fonksiyonu çağırmaktadır
  
  }



void yesil_blinking(){ // Yeşil işiklar yanıp sonsun diye amaçlı bir fonksiyonu 

  if(doguBatidurum == HIGH){
     // Burada durum koşulu geçtikten sonra Kuzey - Güney ışıklar için yeşil için bliking sistemi
  for (int i = 0; i < 3; ++i) { // 3 kez tekrarlanır 
    digitalWrite(yesil2, HIGH);
    delay(delay_blinking_yesil);

    digitalWrite(yesil2, LOW);
    delay(delay_blinking_yesil);
  }
 }

else {
  
  for (int i = 0; i < 3; ++i) { 
    digitalWrite(yesil1, HIGH);
    delay(delay_blinking_yesil); 
     // Burada durum koşulu geçtikten sonra Doğu - Bayı ışıklar için yeşil için bliking sistemi
    digitalWrite(yesil1, LOW);
    delay(delay_blinking_yesil);
  }
  
  void kirmizi_isik(); // Fonksiyonu çağırmaktadır ve böylece sistem yeniden başlanmaktadır, bütün sistem tekrarlanmaktadır
  }
  
  }
  

void loop() {
  
  uint8_t buf[VW_MAX_MESSAGE_LEN]; // Bu dizi VirtualWire kütüphanesi aracılığıyla alınan mesajları depolamak için kullanmaktadır
  uint8_t buflen=VW_MAX_MESSAGE_LEN; // Dizisinin içindeki verilerin uzunluğunu tutar


if(vw_get_message(buf, &buflen))
//VirtualWire kütüphanesinde kullanılan bir fonksiyondur ve bu fonksiyon, alınan bir mesajın olup olmadığını kontrol eder.
{

 if(buf[0] == '0'){ // Gelen mesaj yoksa, normal sistem çalışmasına devam etmekte
// Normal çalışma prensibi trafik ışığı sistemi,
Serial.println(buf[0]);
void kirmizi_isik(); // Program burdan çalışmaya başlamaktadır ve böylece "kirmizi_isik" fonksiyonu çağırmaktadır
 
}

if(buf[0] == '1'){ // Gelen mesaj varsa 

Serial.println(buf[1]);
void yesil_isik(); // Gereken acilen yesil_isik fonksiyonu çağırmaktadır


}

}

}
