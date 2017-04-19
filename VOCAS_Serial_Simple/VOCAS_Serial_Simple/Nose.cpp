/*
  Nose.cpp - Library for VOCAS Tech sheilds.
  Created by Richard Pape and Adam Emberton, September 25, 2015.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Nose.h"

Nose::Nose(int pin1, int pin2, int pin3, int pin4)
{
  pinMode(pin1, INPUT);
  pinMode(pin2, INPUT);
  pinMode(pin3, INPUT);
  pinMode(pin4, INPUT);

  _pin[0] = pin1;
  _pin[1] = pin2;
  _pin[2] = pin3;
  _pin[3] = pin4;
}

void Nose::learn(int scent[4],String id,int smellnum)
{
  for(int i=0;i<4;i++){
    smell[smellnum][i]=scent[i];
  }
  smellid[smellnum]=id;
  
}

void Nose::learnPeak(String id,int smellnum)
{
  long time=millis()+10000;
  int peak[4];

  for(int i=0;i<4;i++){
    peak[i]=analogRead(_pin[i]);
  }
  
  while(time>millis()){
    for(int i=0;i<4;i++){
      int tempval=analogRead(_pin[i]);
      tempval=analogRead(_pin[i]);
      if(tempval>peak[i]){
        peak[i]=tempval;
      }
    }
  }
  for(int i=0;i<4;i++){
    smell[smellnum][i]=peak[i];
  }
  smellid[smellnum]=id;
}

void Nose::learnDiff(String id,int smellnum)
{

}

String Nose::recognize(int scent[4])
{
  int pick=0;
  int distnew;
  int dist=sqrt(sq((float)scent[0]-smell[0][0])+sq((float)scent[1]-smell[0][1])+sq((float)scent[2]-smell[0][2])+sq((float)scent[3]-smell[0][3]));
  for(int i=1;i<20;i++){
    int distnew=sqrt(sq((float)scent[0]-smell[i][0])+sq((float)scent[1]-smell[i][1])+sq((float)scent[2]-smell[i][2])+sq((float)scent[3]-smell[i][3]));
    if(distnew<dist){
      dist=distnew;
      pick=i;
    }
  }
  return smellid[pick];
}

String Nose::recognizePeak()
{
  long time=millis()+10000;
  float peak[4];

  for(int i=0;i<4;i++){
    peak[i]=analogRead(_pin[i]);
  }
  
  while(time>millis()){
    for(int i=0;i<4;i++){
      int tempval=analogRead(_pin[i]);
      tempval=analogRead(_pin[i]);
      if(tempval>peak[i]){
        peak[i]=tempval;
      }
    }
  }

  int pick=0;
  int distnew;
  int dist=sqrt(sq(peak[0]-smell[0][0])+sq(peak[1]-smell[0][1])+sq(peak[2]-smell[0][2])+sq(peak[3]-smell[0][3]));
  for(int i=1;i<20;i++){
    int distnew=sqrt(sq(peak[0]-smell[i][0])+sq(peak[1]-smell[i][1])+sq(peak[2]-smell[i][2])+sq(peak[3]-smell[i][3]));
    if(distnew<dist){
      dist=distnew;
      pick=i;
    }
  }
  return smellid[pick];
}

String Nose::recognizeDiff()
{

}
