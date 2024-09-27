
// RemoteXY bağlantı modunu seçip kütüphane eklemektedir
#define REMOTEXY_MODE__ESP8266_SOFTSERIAL_POINT
#include <SoftwareSerial.h>

#include <RemoteXY.h>

//RemoteXY bağlantı ayarları
#define REMOTEXY_SERIAL_RX 10
#define REMOTEXY_SERIAL_TX 11
#define REMOTEXY_SERIAL_SPEED 9600
#define REMOTEXY_WIFI_SSID "Git_Wifi"
#define REMOTEXY_WIFI_PASSWORD "123456789"
#define REMOTEXY_SERVER_PORT 6377


// RemoteXY ayarlanması 
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 29 bytes
  { 255,1,0,0,0,22,0,16,21,1,2,1,21,35,22,11,1,26,31,31, // Bellekte hizalanması ve genellikle daha iyi performans ve bellek kullanımı sağlamak amacıyla 
  65,99,0,75,97,112,97,116,0 };
  
// Struct yapı kontrol arayüzünüzün tüm değişkenlerini bulunmaktadır
struct {

    // giriş değişkenleri
  uint8_t Acik; // =1 eğer tıkladıyasa "ON" yoksa  =0 "OFF" şekilde olmaktadır 

    // other variable
  uint8_t connect_flag;  // =1 eğer bağlantı ise , yoksa  =0 şekilfe flag olmaktadır

} RemoteXY;
#pragma pack(pop)


// #define PIN_ACIK 5 // 5 pin şekilde ayarlanması


void setup() 
{
 
  RemoteXY_Init (); // kütüphanesi çağırmaktadıri, belirli arayüzü bir uzaktan kontrol etmek
  
}

void loop() 
{ 
  RemoteXY_Handler ();
  
   // Eğer RemoteXY.Acik değeri 0 ise, PIN_ACIK pinini "LOW" olcak şekilde, aksi halde "HIGH" olacak
  if (RemoteXY.Acik == 0) {

    // Burada eğer button tıklamadıysa ambulans için GPS çalışma prensibi bulunamaktadır...
  
   // Burada GPS için daha önce açıkalan kodlar eklemesi gerekmektedir...
   
  } 
  
  else {

      // Burada eğer button tıkladıysa trafik sistemine ait olan RF Transmitter için çalışma prensibi bulunamaktadır....

    
  }

}
