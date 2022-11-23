#ifndef FOC_INCREMENTALENCODER_H_
#define FOC_INCREMENTALENCODER_H_

#include <FOC/Encoder.h>

class IncrementalEncoder: public Encoder {
public:
	IncrementalEncoder();
	virtual ~IncrementalEncoder();

	IncrementalEncoder(TIM_HandleTypeDef* tim, int cpr, DIR dir = DIR::CCW);

	virtual void Init(TIM_HandleTypeDef* tim, int cpr, DIR dir = DIR::CCW);
	virtual void Init(){};

	virtual int GetRawCount();


	TIM_HandleTypeDef* Tim;
};

#endif /* FOC_INCREMENTALENCODER_H_ */
