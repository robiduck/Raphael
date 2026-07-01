  Raphael Robot Kontrol Kartı Kütüphanesi 
  
  
  Raphael v1, ATmega328PB mikrodenetleyici mimarisine sahip, mini sumo ve çizgi izleyen robot projeleri için optimize edilmiş yüksek performanslı bir robot kontrol kartıdır. Bu kütüphane; kart üzerindeki motor sürücü, sensörler, buzzer, kullanıcı butonu, harici kesme (interrupt) pinleri ve batarya voltaj okuma gibi tüm donanım bileşenlerini en yüksek hızda ve en basit fonksiyon çağrılarıyla kontrol etmenizi sağlar.
  
  
  📚 Fonksiyon Sözlüğü 
  Kütüphane içindeki tüm fonksiyonların detaylı açıklamaları, parametreleri ve örnek kullanım senaryoları aşağıda listelenmiştir.
  
  
  1. Başlatma ve Temel Arayüz Fonksiyonları
     
  🔹 begin() : Kart üzerindeki tüm giriş/output (I/O) pinlerini, motor sürücü frekans hatlarını ve kütüphane altyapısını başlatır. setup() fonksiyonunun içinde mutlaka bir kez çağrılmalıdır.
    
     robot.begin();
  
  🔹 ledYak() / ledSondur() : Kart üzerinde bulunan sistem durum LED'ini (Flaşör) doğrudan kontrol eder.
  
    robot.ledYak();    // Durum LED'ini aktif eder  
    robot.ledSondur(); // Durum LED'ini kapatır
  
  🔹 butonBasildiMi() : Kart üzerindeki kullanıcı butonunun (A1 pini) durumunu sorgular. Butona basıldığında true döndürür.
  
    while(!robot.butonBasildiMi()) { /* Butona basılana kadar bekle */ }
  
  🔹 buzzerCal(uint16_t frekans, uint32_t sure) : Kart üzerindeki piezo buzzer vasıtasıyla belirtilen frekansta (Hz) ve süre boyunca (ms) ses üretir.
  
    robot.buzzerCal(2000, 150);
  
 
  2. Sensör ve Giriş Okuma Fonksiyonları
     
  🔹 bataryaVoltaj(): Kartın beslendiği LiPo bataryanın anlık voltaj değerini analog hattan okur, kalibre eder ve float olarak döndürür.
  
    float voltaj = robot.bataryaVoltaj();
  
  🔹 taktikOku(): Kart üzerinde bulunan çok konumlu Rotary Switch (Taktik Anahtarı) değerini okur. Seçilen taktik numarasını uint8_t olarak döndürür.
  
     uint8_t secilenTaktik = robot.taktikOku();
  
  🔹 dijitalSensorOku(SensorName sensor): Karta bağlı olan dijital rakip mesafe, çizgi veya 12V endüstriyel NPN sensörlerini lojik olarak sorgular.Parametreler: Kütüphane içinde tanımlı olan Raphael::SENS1 ile Raphael::NPN2 arasındaki sabitler kullanılır.
  
    bool onSolRadar = robot.dijitalSensorOku(Raphael::SENS1); yanNPN1 = robot.dijitalSensorOku(Raphael::NPN1);   // D pini
  
  
   3.Motor Sürücü Kontrol Fonksiyonları
     
  🔹 setMotor(int16_t solHiz, int16_t sagHiz): Çift kanallı motor sürücü entegresine doğrudan yön ve PWM hız komutu gönderir. -255 ile 255 arasında değer alır.
  
    robot.setMotor(255, 255); // %100 güç ileri
  
  🔹 dur(): Motorlara giden tüm enerjiyi keser. Motorlar kendi ataletleriyle serbest duruşa (coasting) geçer.
  
    robot.dur();
  
  🔹 fren(): Motor sürücü çıkışlarını donanımsal olarak kısa devre eder. Robotun zınk diye durmasını sağlayan aktif elektronik frenleme uygular.
  
    robot.fren();


  
