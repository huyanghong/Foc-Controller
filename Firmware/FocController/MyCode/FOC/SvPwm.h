#ifndef FOC_SVPWM_H_
#define FOC_SVPWM_H_

#include "tim.h"

#define SVPWM_SQRT3_2 0.8660254f
#define SVPWM_SQRT3   1.7320508f

class SvPwm {
public:
	SvPwm();
	virtual ~SvPwm();

	SvPwm(TIM_HandleTypeDef* tim, int period);

	TIM_HandleTypeDef* Tim;

	int PERIOD = 4200;
	int T1, T2, T3;
	float Udc = 12;
	int Sector;

	void Svpwm(float uAlpha, float uBeta);
	void Svpwm();

	void PwmOutput(int t1, int t2, int t3){
		if(t1 > PERIOD) t1 = PERIOD;
		if(t2 > PERIOD) t2 = PERIOD;
		if(t3 > PERIOD) t3 = PERIOD;
		if(t1 < 0) t1 = 0;
		if(t2 < 0) t2 = 0;
		if(t3 < 0) t3 = 0;
		this->Tim->Instance->CCR1 = t1;
		this->Tim->Instance->CCR2 = t2;
		this->Tim->Instance->CCR3 = t3;
	}
	void PwmOutput(){
		PwmOutput(T1, T2, T3);
	}
};

#endif /* FOC_SVPWM_H_ */
