#ifndef FOC_PID_H_
#define FOC_PID_H_

class Pid {
public:
	Pid();
	virtual ~Pid();

	float    DeltaT;
	float    Target;
	float    Actual;

	float    Kp;
	float    Ki;
	float    Integral_Attenuation; // range[0, 1]
	unsigned int    Kd;
	float    Error;
	float    ErrorPrev;
	float    Integral;
	float    D_Error;

	float 	Limit_Error;
	float 	Limit_Integral;//积分项下限
	float 	Limit_Result;  //总输出下限

	float   Result;

	void PidProcess(void);
	void PidProcess(float t);
};

#endif /* FOC_PID_H_ */
