#include <FOC/FocController.h>

FocController::FocController() {
	// TODO Auto-generated constructor stub
}

FocController::~FocController() {
	// TODO Auto-generated destructor stub
}

void FocController::Init() {
	this->PolePair = 11;
	this->Udc = 12;
	this->Svpwm->Udc = this->Udc;

	this->FocConv->Um = sqrt(3) / 3.0 * this->Udc;

	this->FocConv->PidD.Kp = 2.58;
	this->FocConv->PidD.Ki = 92.25;
	this->FocConv->PidD.Integral_Attenuation = 0.99;
	this->FocConv->PidD.Kd = 0;
	this->FocConv->PidD.Limit_Error = 0.1f;
	this->FocConv->PidD.Limit_Integral = this->FocConv->Um;
	this->FocConv->PidD.Limit_Result = this->FocConv->Um;
	this->FocConv->PidQ.Kp = 2.58;
	this->FocConv->PidQ.Ki = 92.25;
	this->FocConv->PidQ.Integral_Attenuation = 0.99;
	this->FocConv->PidQ.Kd = 0;
	this->FocConv->PidQ.Limit_Error = 0.1f;
	this->FocConv->PidQ.Limit_Integral = this->FocConv->Um;
	this->FocConv->PidQ.Limit_Result = this->FocConv->Um;

	this->PidSpeed.Kp = 6;
	this->PidSpeed.Ki = 12;
	this->PidSpeed.Integral_Attenuation = 0.99;
	this->PidSpeed.Kd = 0;
	this->PidSpeed.Limit_Error = 100;
	this->PidSpeed.Limit_Integral = 1.0;
	this->PidSpeed.Limit_Result = 1.0f;

	this->PidPosition.Kp = 4.25;
	this->PidPosition.Ki = 4.29;
	this->PidPosition.Integral_Attenuation = 1;
	this->PidPosition.Kd = 34;
	this->PidPosition.Limit_Error = 1;
	this->PidPosition.Limit_Integral = 1.0;
	this->PidPosition.Limit_Result = 1.0f;

	this->Adc->Offset(1000);
	this->Adc->Start();

}

#include "stdio.h"
void FocController::Run() {
	unsigned long timestamp_us = micros();
	this->DeltaT = (timestamp_us - this->Timestamp) * 1e-6;
	if(this->DeltaT <= 0 || this->DeltaT > 0.5) this->DeltaT = 1e-4;
	this->Timestamp = timestamp_us;

	this->Adc->Update();
	this->Sensor->Update();
	this->MechanicalAngle = this->Sensor->GetAngle();
	this->ElectronicAngle = (this->MechanicalAngle - this->OffsetAngle) * this->PolePair;

	switch(this->Mode){
		case FocController::Disable:
			this->Svpwm->PwmOutput(0, 0, 0);
			break;
		case FocController::InjectionVoltage:
			this->FocConv->Ud = this->InjectionVoltageTarget.Voltage;
			this->OpenLoopTheta = this->InjectionVoltageTarget.Theta;

			this->FocConv->RevPark(this->FocConv->Ud, 0, this->OpenLoopTheta * this->PolePair);
			this->Svpwm->Svpwm(this->FocConv->Ualpha, this->FocConv->Ubeta);
			this->Svpwm->PwmOutput(this->Svpwm->T1, this->Svpwm->T2, this->Svpwm->T3);
			break;
		case FocController::NoSensorOpenLoopSpeed:
			this->OpenLoopTheta += (this->NoSensorOpenLoopSpeedTarget.Speed * this->DeltaT);
			this->FocConv->Ud = this->NoSensorOpenLoopSpeedTarget.Voltage;

			this->FocConv->RevPark(this->FocConv->Ud, 0, this->OpenLoopTheta * this->PolePair);
			this->Svpwm->Svpwm(this->FocConv->Ualpha, this->FocConv->Ubeta);
			this->Svpwm->PwmOutput(this->Svpwm->T1, this->Svpwm->T2, this->Svpwm->T3);
			break;
		case FocController::NoSensorOpenLoopPosition:
			if((this->NoSensorOpenLoopPositionTarget.Position - this->OpenLoopTheta) >  (this->NoSensorOpenLoopPositionTarget.Speed * this->DeltaT)) this->OpenLoopTheta +=   (this->NoSensorOpenLoopPositionTarget.Speed * this->DeltaT);
			else if((this->NoSensorOpenLoopPositionTarget.Position - this->OpenLoopTheta) < - (this->NoSensorOpenLoopPositionTarget.Speed * this->DeltaT)) this->OpenLoopTheta -=   (this->NoSensorOpenLoopPositionTarget.Speed * this->DeltaT);
			this->FocConv->Ud = this->NoSensorOpenLoopPositionTarget.Voltage;

			this->FocConv->RevPark(this->FocConv->Ud, 0, this->OpenLoopTheta * this->PolePair);
			this->Svpwm->Svpwm(this->FocConv->Ualpha, this->FocConv->Ubeta);
			this->Svpwm->PwmOutput(this->Svpwm->T1, this->Svpwm->T2, this->Svpwm->T3);
			break;
		case FocController::CloseLoopCurrent:
			this->FocConv->Clarke(this->Adc->Value.iu, this->Adc->Value.iv, this->Adc->Value.iw);
			this->FocConv->Theta = this->ElectronicAngle;
			this->FocConv->Park();

			this->FocConv->PidD.Target = this->CloseLoopCurrentTarget.Id;
			this->FocConv->PidD.Actual = this->FocConv->Id;
			this->FocConv->PidD.DeltaT = this->DeltaT;
			this->FocConv->PidD.PidProcess();
			this->FocConv->Ud = this->FocConv->PidD.Result;

			this->FocConv->PidQ.Target = this->CloseLoopCurrentTarget.Iq;
			this->FocConv->PidQ.Actual = this->FocConv->Iq;
			this->FocConv->PidQ.DeltaT = this->DeltaT;
			this->FocConv->PidQ.PidProcess();
			this->FocConv->Uq = this->FocConv->PidQ.Result;

			this->FocConv->RevPark();
			this->Svpwm->Svpwm(this->FocConv->Ualpha, this->FocConv->Ubeta);
			this->Svpwm->PwmOutput(this->Svpwm->T1, this->Svpwm->T2, this->Svpwm->T3);
			break;
		case FocController::CloseLoopSpeed:
			this->PidSpeed.Actual = 0.99 * this->PidSpeed.Actual  + 0.01*this->Sensor->GetVelocity();
			this->PidSpeed.DeltaT = this->DeltaT;
			this->PidSpeed.PidProcess(this->CloseLoopSpeedTarget.Speed);
			this->CloseLoopSpeedTarget.Iq = this->PidSpeed.Result;
			this->CloseLoopSpeedTarget.Id = 0;

			this->FocConv->Clarke(this->Adc->Value.iu, this->Adc->Value.iv, this->Adc->Value.iw);
			this->FocConv->Theta = this->ElectronicAngle;
			this->FocConv->Park();

			this->FocConv->PidD.Target = this->CloseLoopSpeedTarget.Id;
			this->FocConv->PidD.Actual = this->FocConv->Id;
			this->FocConv->PidD.DeltaT = this->DeltaT;
			this->FocConv->PidD.PidProcess();
			this->FocConv->Ud = this->FocConv->PidD.Result;

			this->FocConv->PidQ.Target = this->CloseLoopSpeedTarget.Iq;
			this->FocConv->PidQ.Actual = this->FocConv->Iq;
			this->FocConv->PidQ.DeltaT = this->DeltaT;
			this->FocConv->PidQ.PidProcess();
			this->FocConv->Uq = this->FocConv->PidQ.Result;

			this->FocConv->RevPark();
			this->Svpwm->Svpwm(this->FocConv->Ualpha, this->FocConv->Ubeta);
			this->Svpwm->PwmOutput(this->Svpwm->T1, this->Svpwm->T2, this->Svpwm->T3);
			break;
		case FocController::CloseLoopPosition:
			this->PidPosition.Actual = this->MechanicalAngle;
			this->PidPosition.DeltaT = this->DeltaT;
			this->PidPosition.PidProcess(this->CloseLoopPositionTarget.Position);
			this->CloseLoopPositionTarget.Iq = this->PidPosition.Result;
			this->CloseLoopPositionTarget.Id = 0;

			this->FocConv->Clarke(this->Adc->Value.iu, this->Adc->Value.iv, this->Adc->Value.iw);
			this->FocConv->Theta = this->ElectronicAngle;
			this->FocConv->Park();

			this->FocConv->PidD.Target = this->CloseLoopPositionTarget.Id;
			this->FocConv->PidD.Actual = this->FocConv->Id;
			this->FocConv->PidD.DeltaT = this->DeltaT;
			this->FocConv->PidD.PidProcess();
			this->FocConv->Ud = this->FocConv->PidD.Result;

			this->FocConv->PidQ.Target = this->CloseLoopPositionTarget.Iq;
			this->FocConv->PidQ.Actual = this->FocConv->Iq;
			this->FocConv->PidQ.DeltaT = this->DeltaT;
			this->FocConv->PidQ.PidProcess();
			this->FocConv->Uq = this->FocConv->PidQ.Result;

			this->FocConv->RevPark();
			this->Svpwm->Svpwm(this->FocConv->Ualpha, this->FocConv->Ubeta);
			this->Svpwm->PwmOutput(this->Svpwm->T1, this->Svpwm->T2, this->Svpwm->T3);
			break;
	}
	this->RunTime = micros()- timestamp_us;

}
