/*
 * Encoder.cpp
 *
 *  Created on: 2022年3月16日
 *      Author: Kepler
 */

#include <FOC/Encoder.h>

Encoder::Encoder() {
	// TODO Auto-generated constructor stub

}

Encoder::~Encoder() {
	// TODO Auto-generated destructor stub
}

void Encoder::Update(){

  float angle_data = GetRawCount();

  float d_angle = angle_data - this->AngleDataPrev;
  // if overflow happened track it as full rotation
  if(abs(d_angle) > (0.8*this->Cpr) ) this->FullRotationOffset += d_angle > 0 ? -_2PI : _2PI;

  // (number of full rotations)*2PI + current sensor angle
  this->CurrentAngle = this->Dir * (this->FullRotationOffset + ( angle_data / (float)this->Cpr) * _2PI);
  this->AngleDataPrev = angle_data;


  // calculate sample time
  unsigned long now_us = micros();
  float Ts = (now_us - this->VelocityCalcTimestamp)*1e-6;
  // quick fix for strange cases (micros overflow)
  if(Ts <= 0 || Ts > 0.5) Ts = 1e-4;

  // velocity calculation
  float vel = (this->CurrentAngle - this->AnglePrev)/Ts;

  this->AnglePrev = this->CurrentAngle;
  this->VelocityCalcTimestamp = now_us;
  this->CurrentVelocity = vel;

}

//  Shaft angle calculation
//  angle is in radians [rad]
float Encoder::GetAngle(){
//  float angle_data = GetRawCount();
//
//  float d_angle = angle_data - this->AngleDataPrev;
//  // if overflow happened track it as full rotation
//  if(abs(d_angle) > (0.8*this->Cpr) ) this->FullRotationOffset += d_angle > 0 ? -_2PI : _2PI;
//
//  this->AngleDataPrev = angle_data;
//
//  // (number of full rotations)*2PI + current sensor angle
//  this->CurrentAngle = this->FullRotationOffset + ( angle_data / (float)this->Cpr) * _2PI;
//  //return full_rotation_offset + ( angle_data / (float)cpr) * _2PI;
//  return this->CurrentAngle;

  return this->CurrentAngle;
}

// Shaft velocity calculation
float Encoder::GetVelocity(){
//  // calculate sample time
//  unsigned long now_us = micros();
//  float Ts = (now_us - this->VelocityCalcTimestamp)*1e-6;
//  // quick fix for strange cases (micros overflow)
//  if(Ts <= 0 || Ts > 0.5) Ts = 1e-3;
//
//  // current angle
//  float angle_c = GetAngle();
//  // velocity calculation
//  float vel = (angle_c - this->AnglePrev)/Ts;
//
//  // save variables for future pass
//  this->AnglePrev = angle_c;
//  this->VelocityCalcTimestamp = now_us;
//  this->CurrentVelocity = vel;
//  return vel;

	return this->CurrentVelocity;
}
