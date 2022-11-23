#include <FOC/Pid.h>

#define   LIMIT(VALUE, MIN, MAX) ((VALUE)<(MIN)? (MIN): ((VALUE)>(MAX)? (MAX): (VALUE)))

Pid::Pid() {
	// TODO Auto-generated constructor stub

}

Pid::~Pid() {
	// TODO Auto-generated destructor stub
}
void Pid::PidProcess(void){
	this->Error = LIMIT(this->Target - this->Actual, -this->Limit_Error, this->Limit_Error);

	this->Integral += this->Ki * this->Error * this->DeltaT;
	this->Integral = LIMIT(this->Integral, -this->Limit_Integral, this->Limit_Integral);

	if(this->Integral * this->Error < 0) this->Integral *= this->Integral_Attenuation;

	if(this->Kd){
		this->D_Error = 0.001 * (this->Error - this->ErrorPrev) / this->DeltaT;
		this->ErrorPrev = this->Error;
		this->Result = this->Kp * this->Error + this->Integral + this->Kd * this->D_Error;
	}else this->Result = this->Kp * this->Error + this->Integral;

	this->Result = LIMIT(this->Result, -this->Limit_Result, this->Limit_Result);
}
void Pid::PidProcess(float t){
	this->Target = t;
	this->PidProcess();
}
