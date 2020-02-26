/*
File Name: Main.cpp
Author: Stanley Huang


*/
// Includes -----------------------------------

#include "IMU.h"
#include "main.h"

// Defines -------------------------------------

#define SERIAL_BAUDRATE 115200

// Public Variables -----------------------------

// Objects --------------------------------------


Imu _MyImu;


// Public Functions -----------------------------

void setup(){
  Serial.begin(SERIAL_BAUDRATE);
  _MyImu.Begin();
  InitVelocityZ();

}
float _LastAccZ = 0;
void loop(){
  float accX, accY, accZ;
  _MyImu.Tick();
  _MyImu.GetFilteredAccData(&accX, &accY, &accZ);

  float diff = accZ  - _LastAccZ;


    Serial.print(diff); Serial.print("\t");
    float velocity = ComputeVelocityZ(diff);
    Serial.println(velocity);
    _LastAccZ = accZ;


}




// void printEvent(sensors_event_t* event) {
//   Serial.println();
//   Serial.print(event->type);
//   double x = -1000000, y = -1000000 , z = -1000000; //dumb values, easy to spot problem
//   if (event->type == SENSOR_TYPE_ACCELEROMETER) {
//     x = event->acceleration.x;
//     y = event->acceleration.y;
//     z = event->acceleration.z;
//   }
//   else if (event->type == SENSOR_TYPE_ORIENTATION) {
//     x = event->orientation.x;
//     y = event->orientation.y;
//     z = event->orientation.z;
//   }
//   else if (event->type == SENSOR_TYPE_MAGNETIC_FIELD) {
//     x = event->magnetic.x;
//     y = event->magnetic.y;
//     z = event->magnetic.z;
//   }
//   else if ((event->type == SENSOR_TYPE_GYROSCOPE) || (event->type == SENSOR_TYPE_ROTATION_VECTOR)) {
//     x = event->gyro.x;
//     y = event->gyro.y;
//     z = event->gyro.z;
//   }

//   Serial.print(": x= ");
//   Serial.print(x);
//   Serial.print(" | y= ");
//   Serial.print(y);
//   Serial.print(" | z= ");
//   Serial.println(z);
// }

