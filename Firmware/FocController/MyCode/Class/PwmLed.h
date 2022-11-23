#ifndef CLASS_PWMLED_H_
#define CLASS_PWMLED_H_

#include "main.h"

class PwmLed {
public:
	PwmLed();
	PwmLed(TIM_HandleTypeDef* p, int chan, int t = 10 /*ms*/ );
	virtual ~PwmLed();

public:
	TIM_HandleTypeDef *Handle_Tim = 0;
	int Channel;

	unsigned int Inc_Time = 0; /** run函数运行的时基*/
	int Pwm; /** 暂存当前pwm的值 */
	int Freq; /** 闪烁的频率*/
	int Base_Time; /** run函数运行时间间隔,取值10~100ms*/
	int Dir = 0; /** 呼吸灯计算时的方向*/
	int High = 300; /** 最大亮度*/

public:
	enum  {BREATHING = -2, OFF,  ON, FLASHING} Status;

    void SetTime(TIM_HandleTypeDef* p){this->Handle_Tim = p;}
    void SetChannel(int chan){this->Channel = chan;}

    void SetPwm(int pwm);
    void Run(void);

    void SetOn(void);
    void SetOff(void);
    void SetBreathing(void);
    void SetFlashing(int freq);
    void SetBasetime(int t){Base_Time = t;}

    int SetToggle(void);
    int GetStatus(void){return Status;}

};

#endif /* CLASS_PWMLED_H_ */
