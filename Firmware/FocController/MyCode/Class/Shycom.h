#ifndef CLASS_SHYCOM_H_
#define CLASS_SHYCOM_H_

#include "HardwareSerial.h"

#define PROTOCOL_BUFFER_SIZE  100

class Shycom: public HardwareSerial {
public:
	Shycom(USART_TypeDef* UartInstance, int32_t baud = 115200);
	virtual ~Shycom();

	virtual void DoProtocol();

	uint8_t Param_Len[256];
	int Protocol_Buffer_Len = 0;
	uint8_t Protocol_Buffer[PROTOCOL_BUFFER_SIZE];

	void ReportCurveValue(const float *value, uint8_t len);

};

#endif /* CLASS_SHYCOM_H_ */
