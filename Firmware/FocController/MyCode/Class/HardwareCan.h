#ifndef CLASS_HARDWARECAN_H_
#define CLASS_HARDWARECAN_H_
#include "main.h"
#include <vector>

typedef struct {
	CAN_RxHeaderTypeDef Header;
	uint8_t  	Data[8];
} CanMessage_t;

class HardwareCan {
public:
	HardwareCan(CAN_HandleTypeDef *hcan):Hcan(hcan){};
	virtual ~HardwareCan();

	CAN_HandleTypeDef *Hcan;

	std::vector<CanMessage_t> TransmitMsg;
	std::vector<CanMessage_t> ReceiveMsg;

	virtual void DoProtocol(void);
};

#endif /* CLASS_HARDWARECAN_H_ */
