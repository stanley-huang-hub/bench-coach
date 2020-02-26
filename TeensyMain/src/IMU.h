/*
File Name: IMU.h
Author: Stanley Huang

*/

// Include Guard -------------------------
#ifndef _IMU.H_
#define _IMU.H_

// Includes ------------------------------

#include <Wire.h>
#include "Library/Adafruit_Sensor.h"
#include "Library/Adafruit_BNO055.h"


// Defines -------------------------------

#define IMU_ID      55
#define IMU_ADDR    0x28
#define BUFFER_SIZE 10
// Objects -------------------------------

enum dataType_t{
    gyroX = 0,
    gyroY,
    gyroZ,
    accX,
    accY,
    accZ
};

//High pass butterworth filter order=1 alpha1=1 
class  FilterBuHp1
{
	public:
		FilterBuHp1()
		{
			v[0]=0.0;
		}
	private:
		float v[2];
	public:
		float step(float x) //class II 
		{
			v[0] = v[1];
			v[1] = (1.000000000000000000e+0 * x)
				 + (1.00000000000000022204 * v[0]);
			return 
				 (v[1] - v[0]);
		}
};


class Imu{
    public:
        Imu();
        void Begin();
        void Tick();
        
        void GetRawGyroData(float* x, float* y, float* z);
        void GetRawAccData(float* x, float* y, float* z);

        void GetFilteredGyroData(float* x, float* y, float* z);
        void GetFilteredAccData(float* x, float* y, float* z);

        void ButterworthFilter(float* data);

    private:
        Adafruit_BNO055 _MyImu;
        uint16_t _SampleRate;

        FilterBuHp1 _ButterworthFilter;
        
 //       sensors_event_t _OrientationData;
        sensors_event_t _AngVelocityData;
        sensors_event_t _LinearAccelData;

};





#endif