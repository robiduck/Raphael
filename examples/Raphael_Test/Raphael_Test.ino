// ---------------------------------------------------------
// RAPHAEL v1 - KÜTÜPHANE TABANLI DONANIM TEST KODU
// ---------------------------------------------------------

#include <Raphael.h>

// Kütüphane nesnesi tanımlanıyor
Raphael robot;

// Zamanlama kontrolü için değişken (milisaniye cinsinden)
unsigned long sonYazdirmaZamani = 0;

void setup() {
  // Seri haberleşme başlatılıyor
  Serial.begin(115200);
  Serial.println("========================================");
  Serial.println("--- RAPHAEL SİSTEM TESTİ BAŞLADI ---");
  Serial.println("========================================");

  // Donanım pinleri ve kütüphane altyapısı başlatılıyor
  robot.begin();

  // Sesli uyarı sistemi (Buzzer) kontrolü
  robot.buzzerCal(1200, 150);
  delay(200);
  robot.buzzerCal(1800, 300);
  delay(300);

  Serial.println("Sistem hazır. Sensör ve donanım verileri okunuyor.");
  Serial.println("Motor testi döngüsü için kullanıcı butonuna (A1) basın.");
  Serial.println("------------------------------------------------");
}

void loop() {
  // 1. KULLANICI BUTONU VE MOTOR TESTİ
  // Butona basıldığında motor test fonksiyonu çalıştırılır
  if (robot.butonBasildiMi()) {
    motorTestGorevi();
  }

  // 2. VERİ OKUMA VE RAPORLAMA (Her 500 milisaniyede bir)
  if (millis() - sonYazdirmaZamani > 500) {
    sonYazdirmaZamani = millis();
    
    // Sistem çalışma durumunu gösteren flaşör LED kontrolü
    static bool ledDurum = false;
    ledDurum = !ledDurum;
    if (ledDurum) robot.ledYak();
    else robot.ledSondur();

    // Batarya voltajı ve Rotary Switch taktik konumu okunuyor
    float voltaj = robot.bataryaVoltaj();
    uint8_t taktik = robot.taktikOku();

    // Tüm sensör girişleri dijital olarak sorgulanıyor
    bool s1 = robot.dijitalSensorOku(Raphael::SENS1); // Pin 12
    bool s2 = robot.dijitalSensorOku(Raphael::SENS2); // Pin 11
    bool s3 = robot.dijitalSensorOku(Raphael::SENS3); // Pin 8
    bool s4 = robot.dijitalSensorOku(Raphael::SENS4); // Pin 7
    bool s5 = robot.dijitalSensorOku(Raphael::SENS5); // Pin A4 (Dijital olarak okunuyor)
    bool s6 = robot.dijitalSensorOku(Raphael::SENS6); // Pin A3 (Dijital olarak okunuyor)
    bool npn1 = robot.dijitalSensorOku(Raphael::NPN1);//12V NPN Sensor //D2
    bool npn2 = robot.dijitalSensorOku(Raphael::NPN2);//12V NPN Sensor //D3

    // Verilerin Seri Port ekranına standart formatta yazdırılması
    Serial.print("LIPO: "); Serial.print(voltaj); Serial.print("V");
    Serial.print(" | TAKTİK: "); Serial.print(taktik);
    Serial.print(" | SENSÖRLER (D12-D11-D8-D7-A4-A3-D2-D3): ");
    Serial.print(s1); Serial.print("-");
    Serial.print(s2); Serial.print("-");
    Serial.print(s3); Serial.print("-");
    Serial.print(s4); Serial.print("-");
    Serial.print(s5); Serial.print("-");
    Serial.print(s6); Serial.print("-");
    Serial.print(npn1); Serial.print("-");
    Serial.println(npn2);
  }
}

// Güvenli motor test rutinini çalıştıran fonksiyon
void motorTestGorevi() {
  Serial.println("\n*** MOTOR SÜRÜCÜ TESTİ AKTİF ***");
  robot.buzzerCal(1000, 200);
  delay(300);

  // Sol motor ileri yönlü tam güç tahriki
  Serial.println("-> Sol Motor (M1) İLERİ (%100 PWM)");
  robot.setMotor(255, 0);
  delay(2000);
  robot.dur();
  delay(500);

  // Sağ motor ileri yönlü tam güç tahriki
  Serial.println("-> Sağ Motor (M2) İLERİ (%100 PWM)");
  robot.setMotor(0, 255);
  delay(2000);
  robot.dur();
  delay(500);

  // Her iki motorun geri yönlü tahriki
  Serial.println("-> Çift Motor GERİ (%60 PWM)");
  robot.setMotor(-150, -150);
  delay(2000);

  // Donanımsal kısa devre frenleme testi
  Serial.println("-> AKTİF ELEKTRONİK FRENLEME UYGULANDI");
  robot.fren();
  robot.buzzerCal(2200, 400);
  delay(1000);

  robot.dur();
  Serial.println("*** MOTOR SÜRÜCÜ TESTİ TAMAMLANDI ***\n");
}