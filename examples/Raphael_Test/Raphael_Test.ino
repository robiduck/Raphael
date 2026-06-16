// ---------------------------------------------------------
// RAPHAEL v1 - KÜTÜPHANE TABANLI DONANIM TEST KODU
// ---------------------------------------------------------

#include <Raphael.h>

// Kütüphane nesnemizi oluşturuyoruz
Raphael robot;

// Zamanlama kontrolü için değişken
unsigned long sonYazdirmaZamani = 0;

void setup() {
  // Bilgisayar bağlantısını başlatıyoruz
  Serial.begin(115200);
  Serial.println("========================================");
  Serial.println("--- RAPHAEL KÜTÜPHANE TESTI BASLIYOR ---");
  Serial.println("========================================");

  // Raphael kütüphanesini ve donanım pinlerini başlatıyoruz
  robot.begin();

  // Açılış melodisi (Buzzer testi)
  // buzzerCal(frekans, süre_ms)
  robot.buzzerCal(1200, 150);
  delay(200);
  robot.buzzerCal(1800, 300);
  delay(300);

  Serial.println("Sistem Hazır! Canlı veriler akmaya başlıyor...");
  Serial.println("Motorları test etmek için kart üzerindeki BUTONA basın.");
  Serial.println("------------------------------------------------");
}

void loop() {
  // 1. BUTON VE MOTOR TESTİ
  // Kullanıcı butona bastığı an kütüphanenin motor sürme fonksiyonları test edilir
  if (robot.butonBasildiMi()) {
    motorTestGorevi();
  }

  // 2. CANLI VERİ YAZDIRMA (Her 500 milisaniyede bir)
  if (millis() - sonYazdirmaZamani > 500) {
    sonYazdirmaZamani = millis();
    
    // LED'i her döngüde yakıp söndürerek sistemin çalıştığını görelim
    static bool ledDurum = false;
    ledDurum = !ledDurum;
    if (ledDurum) robot.ledYak();
    else robot.ledSondur();

    // Kütüphane fonksiyonları ile verileri çekiyoruz
    float voltaj = robot.bataryaVoltaj();
    uint8_t taktik = robot.taktikOku();

    // Sensörleri kütüphanede tanımladığımız sabit isimlerle okuyoruz
    bool s1 = robot.dijitalSensorOku(Raphael::SENS1); // Pin 12
    bool s2 = robot.dijitalSensorOku(Raphael::SENS2); // Pin 11
    bool s3 = robot.dijitalSensorOku(Raphael::SENS3); // Pin 8
    bool s4 = robot.dijitalSensorOku(Raphael::SENS4); // Pin 7
    
    // Analog pinlerdeki sensörleri ister dijital ister analog okuyabilirsin usta
    int s5_analog = robot.analogSensorOku(Raphael::SENS5); // Pin A4
    int s6_analog = robot.analogSensorOku(Raphael::SENS6); // Pin A3

    // Seri Port Ekranına Yazdırma Şovu
    Serial.print("LİPO: "); Serial.print(voltaj); Serial.print("V");
    Serial.print(" | TAKTİK: "); Serial.print(taktik);
    Serial.print(" | SENSÖRLER (D12,D11,D8,D7,A4,A3): ");
    Serial.print(s1); Serial.print("-");
    Serial.print(s2); Serial.print("-");
    Serial.print(s3); Serial.print("-");
    Serial.print(s4); Serial.print(" | A4_Ham: ");
    Serial.print(s5_analog); Serial.print(" | A3_Ham: ");
    Serial.println(s6_analog);
  }
}

// Motorları sırayla test eden güvenli fonksiyon
void motorTestGorevi() {
  Serial.println("\n*** MOTOR TESTİ BAŞLADI ***");
  robot.buzzerCal(1000, 200);
  delay(300);

  // Sol motor ileri (Tam güç: 255), Sağ motor duruyor
  Serial.println("-> Sol Motor (M1) İLERİ");
  robot.setMotor(255, 0);
  delay(2000);
  robot.dur();
  delay(500);

  // Sağ motor ileri (Tam güç: 255), Sol motor duruyor
  Serial.println("-> Sağ Motor (M2) İLERİ");
  robot.setMotor(0, 255);
  delay(2000);
  robot.dur();
  delay(500);

  // Çift motor geri (%60 güçle geri çekilme)
  Serial.println("-> İki Motor Birden GERİ");
  robot.setMotor(-150, -150);
  delay(2000);

  // Aktif Frenleme Testi (Robotu zınk diye durdurur)
  Serial.println("-> AKTİF FREN YAPILDI!");
  robot.fren();
  robot.buzzerCal(2200, 400);
  delay(1000);

  robot.dur();
  Serial.println("*** MOTOR TESTİ BİTTİ ***\n");
}