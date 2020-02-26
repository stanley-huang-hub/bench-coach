/*
File Name: IMU.c
Author: Stanley Huang

*/


// Includes -------------------------
#include "IMU.h"

// Defines --------------------------
#define DEFAULT_SAMPLE_RATE 100

// Objects --------------------------


// Public Variables -----------------


// Public Functions -----------------

Imu::Imu(){
    _MyImu = Adafruit_BNO055(55, 0x28);
    _SampleRate = DEFAULT_SAMPLE_RATE;

}

void Imu::Begin(){
    if(!_MyImu.begin()){
        Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
        while (1);
    }
    delay(1000);
}

void Imu::Tick(){
//    _MyImu.getEvent(&_OrientationData, Adafruit_BNO055::VECTOR_EULER);
    _MyImu.getEvent(&_AngVelocityData, Adafruit_BNO055::VECTOR_GYROSCOPE);
    _MyImu.getEvent(&_LinearAccelData, Adafruit_BNO055::VECTOR_LINEARACCEL);
    delay(_SampleRate);
}

void Imu::GetRawGyroData(float* x, float* y, float* z){
    *x = _AngVelocityData.gyro.x;
    *y = _AngVelocityData.gyro.y;
    *z = _AngVelocityData.gyro.z;
}

void Imu::GetRawAccData(float* x, float* y, float* z){
    *x = _LinearAccelData.acceleration.x;
    *y = _LinearAccelData.acceleration.y;
    *z = _LinearAccelData.acceleration.z;
}

void Imu::GetFilteredGyroData(float* x, float* y, float* z){
    float rawX, rawY, rawZ;
    GetRawGyroData(&rawX, &rawY, &rawZ);

    ButterworthFilter(&rawX);
    ButterworthFilter(&rawY);
    ButterworthFilter(&rawZ);

    *x = rawX;
    *y = rawY;
    *z = rawZ;
}

void Imu::GetFilteredAccData(float* x, float* y, float* z){
    float rawX, rawY, rawZ;
    GetRawAccData(&rawX, &rawY, &rawZ);


    ButterworthFilter(&rawX);
    ButterworthFilter(&rawY);
    ButterworthFilter(&rawZ);



    *x = rawX;
    *y = rawY;
    *z = rawZ;
}




void Imu::ButterworthFilter(float* data){
    float unfiltered = *data;
    *data = _ButterworthFilter.step(unfiltered);
}
