#ifndef FOC_FOCCONTROLLER_H_
#define FOC_FOCCONTROLLER_H_

#include <FOC/FocConverter.h>
#include <FOC/SvPwm.h>
#include "FOC/MagneticSensorSPI.h"
#include "FOC/IncrementalEncoder.h"
#include "FOC/AdcValue.h"


class FocController {
public:
	FocController();
	virtual ~FocController();
	FocController(FocConverter *foc_Conv, SvPwm *sv_pwm, Encoder *sen, AdcValue *adc){
		this->Adc = adc;
		this->Sensor = sen;
		this->Svpwm = sv_pwm;
		this->FocConv = foc_Conv;
	};


	AdcValue *Adc;
	Encoder *Sensor;
	FocConverter *FocConv;
	SvPwm *Svpwm;

	void Init();
	void Run();

	float DeltaT;
	unsigned long Timestamp;
	float Udc; //电源电压
	int PolePair;
	int RunTime;

	float ElectronicAngle, MechanicalAngle, OffsetAngle;
	float OpenLoopTheta;

	Pid PidSpeed;
	Pid PidPosition;

	enum {CW = -1, CCW = 1} Dir = this->CCW;
	enum {Disable, InjectionVoltage, NoSensorOpenLoopSpeed, NoSensorOpenLoopPosition, CloseLoopCurrent, CloseLoopSpeed, CloseLoopPosition} Mode = this->Disable;


	struct{
		float Theta;
		float Voltage;
	}InjectionVoltageTarget;
	struct{
		float Speed;
		float Voltage;
	}NoSensorOpenLoopSpeedTarget;
	struct{
		float Position;
		float Speed;
		float Voltage;
	}NoSensorOpenLoopPositionTarget;
	struct{
		float Id;
		float Iq;
	}CloseLoopCurrentTarget;
	struct{
		float Speed;
		float Id;
		float Iq;
	}CloseLoopSpeedTarget;
	struct{
		float Position;
		float Id;
		float Iq;
	}CloseLoopPositionTarget;
};

#endif /* FOC_FOCCONTROLLER_H_ */
