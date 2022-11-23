#ifndef FOC_FOCCONVERTER_H_
#define FOC_FOCCONVERTER_H_

#include "Pid.h"

class FocConverter {
public:
	FocConverter();
	virtual ~FocConverter();

	float Ia, Ib, Ic;
	float Ialpha, Ibeta;
	float Id, Iq;
	float Ualpha, Ubeta;
	float Ud, Uq;

	float Theta;

	float Um; //最大电压 Udc * SQRT3_3

	Pid PidD, PidQ;

	void Clarke(float iA, float iB, float iC);
	void Clarke(void);
	void Park(float iAlpha, float iBeta, float theta);
	void Park(void);
	void RevPark(float uD, float uQ, float theta);
	void RevPark(void);


};

#endif /* FOC_FOCCONVERTER_H_ */
