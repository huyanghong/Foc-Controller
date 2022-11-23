#include <FOC/IncrementalEncoder.h>

IncrementalEncoder::IncrementalEncoder() {
	// TODO Auto-generated constructor stub

}

IncrementalEncoder::~IncrementalEncoder() {
	// TODO Auto-generated destructor stub
}

IncrementalEncoder::IncrementalEncoder(TIM_HandleTypeDef* tim, int cpr, DIR dir){
	this->Tim = tim;

	this->Cpr = cpr;
	this->Dir = dir;

	// velocity calculation init
	this->AnglePrev = 0;
	this->VelocityCalcTimestamp = micros();

	// full rotations tracking number
	this->FullRotationOffset = 0;
	this->AngleDataPrev = 0;//this->GetRawCount();
}

void IncrementalEncoder::Init(TIM_HandleTypeDef* tim, int cpr, DIR dir){
	this->Tim = tim;

	this->Cpr = cpr;
	this->Dir = dir;

	// velocity calculation init
	this->AnglePrev = 0;
	this->VelocityCalcTimestamp = micros();

	// full rotations tracking number
	this->FullRotationOffset = 0;
	this->AngleDataPrev = this->GetRawCount();
}

int IncrementalEncoder::GetRawCount(){
	uint16_t count = this->Tim->Instance->CNT;
	return count;
}


