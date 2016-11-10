/*
  CSmartIntertechno.h - Library for controlling Intertechno Devices.
  Created by Christian Steck on 10.11.2016
  Released into the public domain.
*/
#include "Arduino.h"
#include "CSmartIntertechno.h"

CSmartIntertechno::CSmartIntertechno(int pin){
    pinMode(pin, OUTPUT);
    _pin = pin;
}

void CSmartIntertechno::turnOn(int id, int unit, int repeat){
    for(int i=0;i<repeat;i++){
        this->sendStart();
        this->sendUniqueId(id);
        this->sendPulseSingle();
        this->sendPulseOn();
        this->sendUnitCode(unit);
        this->sendEnd();
    }
}

void CSmartIntertechno::turnOff(int id, int unit,int repeat){
    for(int i=0;i<repeat;i++){
        this->sendStart();
        this->sendUniqueId(id);
        this->sendPulseSingle();
        this->sendPulseOff();
        this->sendUnitCode(unit);
        this->sendEnd();
    }
}

void CSmartIntertechno::dim(int id, int unit, float value, int repeat){
    value = (value/100)*15;
    for(int i=0;i<repeat;i++){
        this->sendStart();
        this->sendUniqueId(id);
        this->sendPulseSingle();
        this->sendPulseDim();
        this->sendUnitCode(unit);
        this->sendDim(value);
        this->sendEnd();
    }
}

String CSmartIntertechno::decToBin(int number) {
    if(number == 0) 
    return "0";
    if(number == 1) 
    return "1";

    if(number % 2 == 0)
        return this->decToBin(number / 2) + "0";
    else
        return this->decToBin(number / 2) + "1";
}

void CSmartIntertechno::sendStart() {
  digitalWrite(_pin,1);
  delayMicroseconds((speedInt*_short));
  digitalWrite(_pin,0);
  delayMicroseconds((speedInt*start));
}

void CSmartIntertechno::sendPulse0() {
  digitalWrite(_pin,1);
  delayMicroseconds((speedInt*_short));
  digitalWrite(_pin,0);
  delayMicroseconds((speedInt*_short));
}
void CSmartIntertechno::sendPulse1() {
  digitalWrite(_pin,1);
  delayMicroseconds((speedInt*_short));
  digitalWrite(_pin,0);
  delayMicroseconds((speedInt*_long));
}

void CSmartIntertechno::sendPulseHigh() {
  this->sendPulse0();
  this->sendPulse1();
}

void CSmartIntertechno::sendPulseLow() {
  this->sendPulse1();
  this->sendPulse0();
}

void CSmartIntertechno::sendPulseOn() {
  this->sendPulseLow();
}

void CSmartIntertechno::sendPulseDim() {
  this->sendPulse0();
  this->sendPulse0();
}

void CSmartIntertechno::sendPulseOff() {
  this->sendPulseHigh();
}

void CSmartIntertechno::sendPulseAll() {
  this->sendPulseLow();
}

void CSmartIntertechno::sendPulseSingle() {
  this->sendPulseHigh();
}

void CSmartIntertechno::sendUniqueId(int id) {
  int x = 0;
  int l = 0;
  String c;
  
  c = this->decToBin(id);
  l = (int)c.length();
  for(x=0;x<(26-l);x++) {
    this->sendPulseHigh();
  }
  for(x=0;x<l;x++) {
    if(c[x] == '1')
      this->sendPulseLow();
    else
      this->sendPulseHigh();
  }
}

void CSmartIntertechno::sendUnitCode(int code) {
  int x = 0;
  int l = 0;
  String c;
  
  c = this->decToBin(code);
  l = (int)c.length();
  for(x=0;x<(4-l);x++) {
    this->sendPulseHigh();
  }
  for(x=0;x<l;x++) {
    if(c[x] == '1')
      this->sendPulseLow();
    else
      this->sendPulseHigh();
  }
}

void CSmartIntertechno::sendDim(int code) {
  int x = 0;
  int l = 0;
  String c;
  
  c = this->decToBin(code);
  l = (int)c.length();
  for(x=0;x<(4-l);x++) {
    this->sendPulseHigh();
  }
  for(x=0;x<l;x++) {
    if(c[x] == '1')
      this->sendPulseLow();
    else
      this->sendPulseHigh();
  }
  digitalWrite(_pin,1);
  delayMicroseconds((speedInt*_short));
  digitalWrite(_pin,1);
  delayMicroseconds((speedInt*_short));
}

void CSmartIntertechno::sendEnd() {
  digitalWrite(_pin,1);
  delayMicroseconds((speedInt*_short));
  digitalWrite(_pin,0);
  delayMicroseconds((speedInt*endInt));
}