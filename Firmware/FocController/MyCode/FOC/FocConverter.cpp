#include <FOC/FocConverter.h>
#include "math.h"

#define FOC_SQRT_3  1.73205f
#define FOC_ANGLE_TO_RADIN 0.01745f


FocConverter::FocConverter() {
	// TODO Auto-generated constructor stub

}

FocConverter::~FocConverter() {
	// TODO Auto-generated destructor stub
}

void FocConverter::Clarke(void){
	this->Clarke(this->Ia, this->Ib, this->Ic);
}
void FocConverter::Clarke(float iA, float iB, float iC){
	this->Ialpha = iA;
	this->Ibeta = (iA + 2.0f * iB) / FOC_SQRT_3;
}

void FocConverter::Park(void){
	this->Park(this->Ialpha, this->Ibeta, this->Theta);
}

void FocConverter::Park(float iAlpha, float iBeta, float theta){
	float _Cos = cos(theta);
	float _Sin = sin(theta);

	this->Id =  iAlpha * _Cos + iBeta * _Sin;
	this->Iq = -iAlpha * _Sin + iBeta * _Cos;
}
void FocConverter::RevPark(void){
	this->RevPark(this->Ud, this->Uq, this->Theta);
}
void FocConverter::RevPark(float uD, float uQ, float theta){
	float _Cos = cos(theta);
	float _Sin = sin(theta);

	if((uD * uD + uQ * uQ) > (this->Um * this->Um)){
		float temp = sqrt(uD * uD + uQ * uQ);
		uD = this->Um * uD/temp;
		uQ = this->Um * uQ/temp;
	}

	this->Ualpha = uD * _Cos - uQ * _Sin;
	this->Ubeta  = uD * _Sin + uQ * _Cos;
}

