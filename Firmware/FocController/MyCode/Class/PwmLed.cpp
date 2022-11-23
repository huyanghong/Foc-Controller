#include "PwmLed.h"

PwmLed::PwmLed() {
	// TODO Auto-generated constructor stub
	this->Status = this->OFF;

}
PwmLed::PwmLed(TIM_HandleTypeDef* p, int chan, int t) {
	this->Handle_Tim = p;
	this->Channel = chan;
	this->Status = this->OFF;
	if(t > 100) this->Base_Time = 100;
	else if(t < 10) this->Base_Time = 10;
	else this->Base_Time = t;
	//__HAL_TIM_SetCompare(&htim12, TIM_CHANNEL_1, 300);
}

void PwmLed::SetPwm(int pwm) {
	__HAL_TIM_SetCompare((TIM_HandleTypeDef*)this->Handle_Tim, this->Channel, pwm);
}

void PwmLed::Run(void) {
	this->Inc_Time += this->Base_Time;

	switch(this->Status){
		case this->BREATHING:
			if(this->Dir) this->Pwm += this->Base_Time / 10;
			else this->Pwm -= this->Base_Time / 10;
			if(this->Pwm > 100 && this->Dir) this->Dir = 0; /** 呼吸灯的亮度从5~100，太亮看不出区别，没有呼吸效果*/
			else if(this->Pwm < 5 && !this->Dir)	this->Dir = 1;
			break;
		case this->OFF: this->Pwm = 0; break;
		case this->ON : this->Pwm = this->High; break;
		case this->FLASHING:
			if((this->Inc_Time % (500/this->Freq)) < this->Base_Time){ /** 计算频率间隔时间，取模小于一个周期反转状态*/
				if(this->Pwm > this->High/2) this->Pwm = 0;
				else this->Pwm = this->High;
				this->Inc_Time = 0;
			}
			break;
	}
	this->SetPwm(this->Pwm);
}

void PwmLed::SetOn(void) {
	this->Status = this->ON;
}

void PwmLed::SetOff(void) {
	this->Status = this->OFF;
}

void PwmLed::SetBreathing(void) {
	this->Status = this->BREATHING;
}

void PwmLed::SetFlashing(int freq) {
	this->Status = this->FLASHING;
	if(freq > 10) freq = 10;
	if(freq > 0) this->Freq = freq;
	else this->Status = this->OFF;
}

int PwmLed::SetToggle(void) {
	if(this->Status == this->ON)
		this->Status = this->OFF;
	else if(this->Status == this->OFF)
		this->Status = this->ON;

	if(this->Status == this->ON || this->Status == this->OFF) return 1;
	else return 0;
}

PwmLed::~PwmLed() {
	// TODO Auto-generated destructor stub
}

