#ifndef RAPHAEL_H
#define RAPHAEL_H

#include <Arduino.h>

class Raphael {
  public:
    Raphael();

    // Sistemi Başlatma
    void begin();

    // Profesyonel Motor Kontrolü (-255 ile +255 arası değer alır, PID algoritmaları için kusursuzdur)
    void setMotor(int solHiz, int sagHiz); 
    
    // Klasik Motor Fonksiyonları (0 - 255)
    void ileri(uint8_t hiz);
    void geri(uint8_t hiz);
    void solaDon(uint8_t hiz);
    void sagaDon(uint8_t hiz);
    void dur();
    void fren(); // Sürücü çipinin aktif frenlemesi (Pinler HIGH)

    // Arayüz ve Geri Bildirim
    void ledYak();
    void ledSondur();
    void buzzerCal(uint16_t frekans, uint16_t sure);
    bool butonBasildiMi();
    
    // Sensör ve Veri Okuma
    float bataryaVoltaj();
    uint8_t taktikOku(); // 0 ile 15 arası Rotary Switch değerini döner
    bool dijitalSensorOku(uint8_t pin);
    uint16_t analogSensorOku(uint8_t pin);

    // Kullanıcının kodunda kolayca çağırabilmesi için sensör pin referansları
    static const uint8_t SENS1 = 12;
    static const uint8_t SENS2 = 11;
    static const uint8_t SENS3 = 8;
    static const uint8_t SENS4 = 7;
    static const uint8_t SENS5 = A4;
    static const uint8_t SENS6 = A3;
    static const uint8_t NPN1 = D2;
    static const uint8_t NPN2 = D3;


  private:
    // Raphael v1 Donanım Haritası (Kullanıcıdan Gizlenen Kısım)
    const uint8_t _led = 13;
    const uint8_t _buzzer = A2;
    const uint8_t _buton = A1;
    const uint8_t _lipo = A5;
    
    const uint8_t _m1_ina = 5;
    const uint8_t _m1_inb = 6;
    const uint8_t _m2_ina = 9;
    const uint8_t _m2_inb = 10;
    
    const uint8_t _sw1 = 23;
    const uint8_t _sw2 = 26;
    const uint8_t _sw4 = 24;
    const uint8_t _sw8 = 25;

    // Arka plan motor sürme matematiği
    void motorSur(uint8_t pinA, uint8_t pinB, int hiz);
};

#endif