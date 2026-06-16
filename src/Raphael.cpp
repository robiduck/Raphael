#include "Raphael.h"

Raphael::Raphael() {
  // Nesne yaratıldığında boş kalabilir
}

void Raphael::begin() {
  pinMode(_led, OUTPUT);
  pinMode(_buzzer, OUTPUT);
  pinMode(_buton, INPUT_PULLUP);
  
  pinMode(_m1_ina, OUTPUT);
  pinMode(_m1_inb, OUTPUT);
  pinMode(_m2_ina, OUTPUT);
  pinMode(_m2_inb, OUTPUT);
  
  pinMode(_sw1, INPUT_PULLUP);
  pinMode(_sw2, INPUT_PULLUP);
  pinMode(_sw4, INPUT_PULLUP);
  pinMode(_sw8, INPUT_PULLUP);
  
  dur(); // Başlangıçta robot fırlamasın diye motorları kitler
}

// ==========================================
// MOTOR KONTROL SİSTEMİ
// ==========================================
void Raphael::motorSur(uint8_t pinA, uint8_t pinB, int hiz) {
  // Hız sınırlandırması (-255 ile 255 arası koruma)
  if (hiz > 255) hiz = 255;
  if (hiz < -255) hiz = -255;

  if (hiz >= 0) {
    analogWrite(pinA, hiz);
    digitalWrite(pinB, LOW);
  } else {
    digitalWrite(pinA, LOW);
    analogWrite(pinB, abs(hiz));
  }
}

void Raphael::setMotor(int solHiz, int sagHiz) {
  motorSur(_m1_ina, _m1_inb, solHiz);
  motorSur(_m2_ina, _m2_inb, sagHiz);
}

void Raphael::ileri(uint8_t hiz) { setMotor(hiz, hiz); }
void Raphael::geri(uint8_t hiz) { setMotor(-hiz, -hiz); }
void Raphael::solaDon(uint8_t hiz) { setMotor(-hiz, hiz); }
void Raphael::sagaDon(uint8_t hiz) { setMotor(hiz, -hiz); }

void Raphael::dur() {
  digitalWrite(_m1_ina, LOW); digitalWrite(_m1_inb, LOW);
  digitalWrite(_m2_ina, LOW); digitalWrite(_m2_inb, LOW);
}

void Raphael::fren() {
  digitalWrite(_m1_ina, HIGH); digitalWrite(_m1_inb, HIGH);
  digitalWrite(_m2_ina, HIGH); digitalWrite(_m2_inb, HIGH);
}

// ==========================================
// ARAYÜZ VE SENSÖRLER
// ==========================================
void Raphael::ledYak() { digitalWrite(_led, HIGH); }
void Raphael::ledSondur() { digitalWrite(_led, LOW); }

void Raphael::buzzerCal(uint16_t frekans, uint16_t sure) {
  tone(_buzzer, frekans, sure);
}

bool Raphael::butonBasildiMi() {
  return digitalRead(_buton) == LOW; 
}

float Raphael::bataryaVoltaj() {
  int lipoHam = analogRead(_lipo);
  return (lipoHam * 5.0 / 1023.0) * (14.7 / 4.7);
}

uint8_t Raphael::taktikOku() {
  uint8_t swDeger = 0;
  swDeger |= (!digitalRead(_sw1)) << 0;
  swDeger |= (!digitalRead(_sw2)) << 1;
  swDeger |= (!digitalRead(_sw4)) << 2;
  swDeger |= (!digitalRead(_sw8)) << 3;
  return swDeger;
}

bool Raphael::dijitalSensorOku(uint8_t pin) {
  pinMode(pin, INPUT);
  return digitalRead(pin);
}

uint16_t Raphael::analogSensorOku(uint8_t pin) {
  return analogRead(pin);
}