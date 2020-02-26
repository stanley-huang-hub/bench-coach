/*
File Name: Main.h
Author: Stanley Huang

Note: Created bc VS was throwing a fit

*/
// Includes -----------------------------------
#include <Arduino.h>
// Defines -------------------------------------

#define ACC_THRESHOLD   0.5

// Public Variables -----------------------------

// Objects --------------------------------------

struct Velocity_t{
  float velocity;
  uint32_t lastTime;
};

Velocity_t _VelocityZ;

void InitVelocityZ(){
    _VelocityZ.velocity = 0;
    _VelocityZ.lastTime = 0;
    
}

float _LastVelocity = 0;
uint32_t _LastTime = 0;

float _PrevVelocity = 0;

float ComputeVelocityZ(float acc){
 // if(abs(acc) >= ACC_THRESHOLD){
    float velocity = 0;
    if(_VelocityZ.lastTime == 0) _VelocityZ.lastTime = millis();
    velocity = acc * (millis() - _VelocityZ.lastTime) + _VelocityZ.velocity;
    _VelocityZ.velocity = velocity;
    _VelocityZ.lastTime = millis();

    // float diff = velocity - _PrevVelocity;
    // _PrevVelocity = velocity;

    // float secondVelocity = 0;
    // secondVelocity = diff * (millis() - _LastTime) + _LastVelocity;
    // _LastVelocity = secondVelocity;
    // _LastTime = millis();

    return velocity;
 // }
  _VelocityZ.lastTime = millis();
return _VelocityZ.velocity;

}

