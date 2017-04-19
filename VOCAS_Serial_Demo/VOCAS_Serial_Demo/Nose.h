/*
  Nose.h - Library for VOCAS Tech sheilds.
  Created by Richard Pape and Adam Emberton, September 25, 2015.
  Released into the public domain.
*/

#ifndef Nose_h
#define Nose_h

#include "Arduino.h"

class Nose
{
  public:
    Nose(int pin1, int pin2, int pin3, int pin4);
    void learn(int scent[4],String id,int smellnum);
    void learnPeak(String id,int smellnum);
    void learnDiff(String id,int smellnum);
    String recognize(int scent[4]);
    String recognizePeak();
    String recognizeDiff();

  private:
    int _pin[4];
    int smell[20][4];
    String smellid[20];
};

#endif