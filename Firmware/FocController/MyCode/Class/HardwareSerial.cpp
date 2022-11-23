#include "HardwareSerial.h"
#include "usart.h"

HardwareSerial::HardwareSerial(USART_TypeDef* UartInstance, int32_t baud) {
	// TODO Auto-generated constructor stub
	this->Instance = UartInstance;
	this->Baud = baud;
	this->Available = 0;
	this->Buffer_Head = 0;
	this->Buffer_Tail = 0;
}

void HardwareSerial::Begin(int baud) {
	this->Huart.Instance = this->Instance;
	this->Huart.Init.BaudRate = baud;
	this->Huart.Init.WordLength = UART_WORDLENGTH_8B;
	this->Huart.Init.StopBits = UART_STOPBITS_1;
	this->Huart.Init.Parity = UART_PARITY_NONE;
	this->Huart.Init.Mode = UART_MODE_TX_RX;
	this->Huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	this->Huart.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&this->Huart) != HAL_OK)
	{
		Error_Handler();
	}
}
void HardwareSerial::Begin(void) {
	this->Huart.Instance = this->Instance;
	this->Huart.Init.BaudRate = this->Baud;
	this->Huart.Init.WordLength = UART_WORDLENGTH_8B;
	this->Huart.Init.StopBits = UART_STOPBITS_1;
	this->Huart.Init.Parity = UART_PARITY_NONE;
	this->Huart.Init.Mode = UART_MODE_TX_RX;
	this->Huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	this->Huart.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&this->Huart) != HAL_OK)
	{
		Error_Handler();
	}
}
int HardwareSerial::Read(uint8_t* dest, int num) {
	if(this->Lock) return 0;
	if(this->Available == 0) return 0;
	if(num > this->Available) num = this->Available;

	if(this->Buffer_Head < this->Buffer_Tail || (this->Buffer_Head+num) <= SERIAL_RX_BUFFER_SIZE){
		memcpy(dest, &this->Rx_Buffer[this->Buffer_Head], num);
		this->Buffer_Head += num;
		if(this->Buffer_Head >= SERIAL_RX_BUFFER_SIZE)
			this->Buffer_Head = 0;
	}else{
		int len = SERIAL_RX_BUFFER_SIZE - this->Buffer_Head;
		memcpy(dest, &this->Rx_Buffer[this->Buffer_Head], len);
		memcpy(&dest[len], this->Rx_Buffer, num - len);
		this->Buffer_Head = num - len;
	}
	this->Available -= num;
	return num;
}

uint8_t HardwareSerial::Read(void) {
	if(this->Lock) return 0;
	if(this->Available > 0){
		char ret = this->Rx_Buffer[this->Buffer_Head];
		this->Available--;
		this->Buffer_Head++;
		if(this->Buffer_Head >= SERIAL_RX_BUFFER_SIZE)
			this->Buffer_Head = 0;
		return ret;
	}
	return 0;
}

int HardwareSerial::Add(uint8_t ch) {
	this->Lock = true;
	this->RxTimeStamp = micros();
	this->Rx_Buffer[this->Buffer_Tail] = ch;
	this->Buffer_Tail++;
	if(this->Buffer_Tail >= SERIAL_RX_BUFFER_SIZE)
		this->Buffer_Tail = 0;

	if(this->Available == SERIAL_RX_BUFFER_SIZE) {
		this->Buffer_Head++;
		if(this->Buffer_Head >= SERIAL_RX_BUFFER_SIZE)
			this->Buffer_Head = 0;
	}else this->Available++;
	this->Lock = false;
	return 1;
}

int HardwareSerial::Add(uint8_t* src, int num) {
	this->Lock = true;
	this->RxTimeStamp = micros();
	if(num > SERIAL_RX_BUFFER_SIZE) num = SERIAL_RX_BUFFER_SIZE;
	if(this->Buffer_Tail + num <= SERIAL_RX_BUFFER_SIZE){
		memcpy(&this->Rx_Buffer[this->Buffer_Tail], src, num);
	}else{
		int len = SERIAL_RX_BUFFER_SIZE - this->Buffer_Tail;
		memcpy(&this->Rx_Buffer[this->Buffer_Tail], src, len);
		memcpy(&this->Rx_Buffer, &src[len], num - len);
	}

	this->Buffer_Tail += num;
	if(this->Buffer_Tail >= SERIAL_RX_BUFFER_SIZE)
		this->Buffer_Tail -= SERIAL_RX_BUFFER_SIZE;
	this->Available += num;
	if(this->Available >= SERIAL_RX_BUFFER_SIZE)
		this->Available = SERIAL_RX_BUFFER_SIZE;
	if(this->Buffer_Tail - this->Available < 0)
		this->Buffer_Head = SERIAL_RX_BUFFER_SIZE + this->Buffer_Tail - this->Available;
	else this->Buffer_Head = this->Buffer_Tail - this->Available;
	this->Lock = false;
	return num;
}

HardwareSerial::~HardwareSerial() {
	// TODO Auto-generated destructor stub
}

//int HardwareSerial::Read(unsigned char* dest, int num) {
//	if(num > this->Available) num = this->Available;
//	memcpy(dest, this->Rx_Buffer, num);
//	this->Available -= num;
//	memcpy(this->Rx_Buffer, &this->Rx_Buffer[num], this->Available);
//	return num;
//}
//
//unsigned char HardwareSerial::Read(void) {
//	if(this->Available > 0){
//		unsigned char ret = this->Rx_Buffer[0];
//		this->Available--;
//		memcpy(this->Rx_Buffer, &this->Rx_Buffer[1], this->Available);
//		return ret;
//	}
//	return 0;
//}
//
//int HardwareSerial::Add(unsigned char ch) {
//	if(this->Available < SERIAL_RX_BUFFER_SIZE) {
//		this->Rx_Buffer[this->Available] = ch;
//		Available++;
//	} else {
//		memcpy(this->Rx_Buffer, &this->Rx_Buffer[1], SERIAL_RX_BUFFER_SIZE - 1);
//		this->Rx_Buffer[SERIAL_RX_BUFFER_SIZE-1] = ch;
//		this->Available = SERIAL_RX_BUFFER_SIZE;
//	}
//	return 1;
//}
//
//int HardwareSerial::Add(unsigned char* src, int num) {
//	if(num > SERIAL_RX_BUFFER_SIZE) num = SERIAL_RX_BUFFER_SIZE;
//	if((this->Available + num) <= SERIAL_RX_BUFFER_SIZE) {
//		memcpy(&this->Rx_Buffer[this->Available], src, num);
//		this->Available += num;
//		return num;
//	} else {
//		int rm = this->Available + num - SERIAL_RX_BUFFER_SIZE;
//		memcpy(this->Rx_Buffer, &this->Rx_Buffer[rm], SERIAL_RX_BUFFER_SIZE - rm);
//		memcpy(&this->Rx_Buffer[SERIAL_RX_BUFFER_SIZE - num], src, num);
//		this->Available = SERIAL_RX_BUFFER_SIZE;
//		return num;
//	}
//}

