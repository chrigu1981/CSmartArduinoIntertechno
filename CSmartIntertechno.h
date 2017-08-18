/*
  CSmartIntertechno.h - Library for controlling Intertechno Devices.
  Created by Christian Steck on 10.11.2016
  Released into the public domain.
*/
#ifndef CSmartIntertechno_h
#define CSmartIntertechno_h

#include "Arduino.h"
#include "CSmartIntertechno.h"

class CSmartIntertechno{
  public:
    CSmartIntertechno(int pin);
    void turnOn(int id, int unit, int repeat=6);
    void turnOff(int id, int unit, int repeat=6);
    void dim(int id, int unit, float value, int repeat=6);
  private:
    int _pin;
    int speedInt = 95;
    int start = 25;
    int _short = 2;
    int _long = 12; 
    int endInt = 100;
    String decToBin(int number);
    void sendStart();
    void sendPulse0();
    void sendPulse1();
    void sendPulseHigh();
    void sendPulseLow();
    void sendPulseOn();
    void sendPulseDim();
    void sendPulseOff();
    void sendPulseAll();
    void sendPulseSingle();
    void sendUniqueId(int id);
    void sendUnitCode(int code);
    void sendDim(int code);
    void sendEnd();
};

#endif
