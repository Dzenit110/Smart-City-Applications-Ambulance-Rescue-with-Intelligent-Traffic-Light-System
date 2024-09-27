#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <AltSoftSerial.h>  // Kütüphaneler tanımlamak

#define rxPin 2
#define txPin 3 // Pinler tanımlamak
SoftwareSerial sim800L(rxPin,txPin); 

//GPS Module RX pin 9
//GPS Module TX pin 8 burada Ublox NEO 6M Modül için GPS 
AltSoftSerial neogps;

TinyGPSPlus gps; // GPS verilerini işlemek için kütüphanesi

unsigned long previousMillis = 0;
long interval = 60000; // zamanlayici ve kodun belirli bir aralıkta çalışıyor


void setup()
{
  //Seri iletişim  Arduino (Serial Monitor)
  Serial.begin(115200);
  
  //Seri iletişim, Arduino ve SIM800L Modül arasında
  sim800L.begin(9600);
  neogps.begin(9600);

  Serial.println("Başlatılıyor...");
  //delay(10000);

  //Modemin iletişimini test etmek için Serial Monitor'da iletişim
  sendATcommand("AT", "OK", 2000); // Burada 2 saniye bekleyip "OK" cevap alıyorsa işlem başarılıdır
  sendATcommand("AT+CMGF=1", "OK", 2000);
  //sim800L.print("AT+CMGR=40\r");
  
}

void loop()
{
  while(sim800L.available()){
    Serial.println(sim800L.readString());  // Seri Monitor'da veri modülden okuyabildiği sürece devam etsin
  }
  while(Serial.available())  {
    sim800L.println(Serial.readString());
  }

    unsigned long currentMillis = millis();  // Çalışma süresini milisaniye olarak atıyor
    if(currentMillis - previousMillis > interval) { // Belirli bir aralıkta bir eylemin gerçekleştirilip gerçekleştirilmeyeceğini kontrol eden bir koşul
       previousMillis = currentMillis; //  Belirli aralık geçmişse, şu anki zamana atıp, bir sonraki kontrolde kullanılmak üzere bir sonraki geçerli zamanı saklamak
       sendGpsToServer(); // GPS verilerini bir sunucuya göndermek
    }
}

int sendGpsToServer()
{
    
    boolean newData = false;
    for (unsigned long start = millis(); millis() - start < 2000;){
      while (neogps.available()){
        if (gps.encode(neogps.read())){
          newData = true; // Yeni bilgi aldığı zaman 
          break;
        }
      }
    }  // Bu fonksiyonun amacı, GPS verilerini alınıp alınmadığını kontrol etmek için kullanmakta, 2 saniye olarak çalışıyor 
       // Bu süre içinde GPS verilerinin okunması ve işlenmesi gerçekleştirilir. Başarılı okuyorsa true olarak dönmektedir
  
    //
    if(true){
      newData = false; // yeni bilgi değil, onu daha sonra gösterecek, hangi enlem ve boylam
      
      String enlem, boylam;
      float rakim;
      unsigned long date, time, speed, satellites;
  
      enlem = String(gps.location.lat(), 6); //  enlem -> derece 
      boylam = String(gps.location.lng(), 6); // Boylam -> derece
     rakim = gps.altitude.meters(); // Yükseklik  metre şekilde 
      date = gps.date.value(); // Tarih şekilde değeri atmak
      time = gps.time.value(); // Saat şekilde değeri atmak
      speed = gps.speed.kmph(); 
      
      Serial.print("Enlem= ");  // Serial Monitor'de Enlem ve Boylam yazılıyor
      Serial.print(enlem);
      Serial.print("Boylam= "); 
      Serial.println(boylam);
  
     
      
      String url, temp;
      url = "BURADA WEB SITESI YAZMASI GEREKMEKTEDIR";
      url += enlem;
      url += "&lng=";
      url += boylam;  //  Burada bir web sitesine konum bilgisini göndermek, enlem ve boylam parametre olarak göndermektedir

      

      Serial.println(url);    
      delay(300);  // Burada url değişkeni Serial Monitor'de yazdırmak, kontrol amaçlı ve geçikme 0,3 saniye
          
    sendATcommand("AT+CFUN=1", "OK", 2000);
    //AT+CGATT = 1 Bağlantı modemi bir ağa GPRS'e bağlanır.. AT+CGATT = 0, ise modem bir ağa bağlı GPRS'e bağlı değildir
    sendATcommand("AT+CGATT=1", "OK", 2000);
    sendATcommand("AT+SAPBR=3,1,\"Contype\",\"GPRS\"", "OK", 2000); // ağlantı tipini GPRS olarak ayarlar. Yine, "OK" yanıtının belirli bir süre içinde alınması beklenir..
    sendATcommand("AT+SAPBR=3,1,\"APN\",\"internet\"", "OK", 2000); // APN olarak ayarlanırı belirlemek
    sendATcommand("AT+SAPBR=1,1", "OK", 2000); // PRS bağlantısını başlatmak için kullanılır, bağlantı varsa "OK" cevap veriliyor
    
    sendATcommand("AT+HTTPINIT", "OK", 2000);  // HTTP hizmeti başlatmak için kullanılır
    sendATcommand("AT+HTTPPARA=\"CID\",1", "OK", 1000); // GTTP bağlantısı için bağlantı kimliğini belirlenir
    sim800L.print("AT+HTTPPARA=\"URL\",\""); //  SIM800L modülüna belirtilen URL'ye göndermektedir
    sim800L.print(url); // Url yazdırsın
    sendATcommand("\"", "OK", 1000); // OK cevap verisn yazdırsa
    sendATcommand("AT+HTTPACTION=0", "0,200", 1000); //  HTTP isteğinin başarıyla tamamlandığını göstermektedir
    sendATcommand("AT+HTTPTERM", "OK", 1000); // HTTP servisini sonlandırmak için kullanılır
    sendATcommand("AT+CIPSHUT", "SHUT OK", 1000); //  GPRS bağlantısının başarıyla kapatıldığını göstermektedir

  }
  return 1;    
}

int8_t sendATcommand(char* ATcommand, char* beklenen_cevap, unsigned int timeout){
 //  Burada fonksiyon olarak SIM800L modülüne  AT komutları göndermeyi amaçlıyor. char* ATcommand: Gönderilmek istenen AT komutunu içeren karakter dizisi.
 // char* beklenen_cevap: Beklenen yanıtın karakter dizisi
 // unsigned int timeout: Beklenen yanıtın gelmesi için maksimum beklenen süre.
 
    uint8_t x=0,  cevap=0; // x --> döngü içinde kullanılacak bir sayacı temsil ederken, cevap --> beklenen yanıt 
    char yanit[100]; // Bir karakter dizisi tanımlamak, max 100 karakter 
    unsigned long onceki_bilgi; // Bu dizi, AT komutlarına verilen yanıtları tutmak için kullanılmaktadır

    
    memset(yanit, '\0', 100); // Diziyi temizler ve 0 atar
    delay(100);
   
    while( sim800L.available() > 0) sim800L.read(); // Burada daha önce gelen verileri okur ve atar
    
    if (ATcommand[0] != '\0'){ // eğer AT komut boş değilse, komutu SIM800L modülüne gönderilir
      sim800L.println(ATcommand);
    }

    x = 0;
    onceki_bilgi = millis();

    // Bu döngü, belirli bir süre boyunca cevap beklerout
    do{
        //Giriş tamponunda veri varsa, bu veriyi okur ve işlem yapar
        if(sim800L.available() != 0){
            yanit[x] = sim800L.read(); // Okunan veriyi diziye  atar 
           
            x++;
            // SIM800L modül için  yanıtında istenen yanıtın (OK) olup olmadığını kontrol etmek, varsa cevap olarak 1 atar
            if(strstr(cevap, beklenen_cevap) != NULL){
                cevap = 1;
            }
        } //Eğer belirli bir süre içinde beklenen cevap alındıysa, bu değer 1 olacaktır; aksi takdirde 0 olacaktır
    }while((cevap == 0) && ((millis() - onceki_bilgi) < timeout)); 

  Serial.println(cevap); // cevap olarak  Serial Monitorda yazılıyor
  return cevap;
}
