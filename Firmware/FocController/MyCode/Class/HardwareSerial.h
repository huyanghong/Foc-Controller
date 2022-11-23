#ifndef HARDWARESERIAL_H_
#define HARDWARESERIAL_H_

#include "string.h"
#include "stdint.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include <cstdio>
#include "usart.h"
#include <string>
#include <stdarg.h>

#define SERIAL_RX_BUFFER_SIZE 512
#define SERIAL_TX_BUFFER_SIZE 512

class HardwareSerial {
public:
	HardwareSerial(USART_TypeDef* UartInstance, int32_t baud = 115200);
	//HardwareSerial();
	virtual ~HardwareSerial();

//public:
protected:
	UART_HandleTypeDef Huart;
	USART_TypeDef      *Instance;
	int  Baud;

	uint8_t Rx_Buffer[SERIAL_RX_BUFFER_SIZE];
	uint8_t Tx_Buffer[SERIAL_TX_BUFFER_SIZE];
	uint64_t RxTimeStamp;
	unsigned int Buffer_Head = 0, Buffer_Tail = 0; /** head当前位置数据有效，tail位置前一位才是有效数据*/
	int  Available = 0; /** 接收数据可用长度*/
	int  Tx_Len; /** 发送数据长度*/

	bool Lock;

public:
	void Begin(int baud);
	void Begin(void);
    int GetAvailable(void){return Available;}
    uint64_t GetRxTimeStamp(void){return RxTimeStamp;}
    uint8_t Read(void);
    int Read(uint8_t* dest, int num);
    int Add(uint8_t ch);
    int Add(uint8_t* src, int num);
    void (*pOneWrite)(uint8_t ch);
    void (*pWrite)(uint8_t *src, int num);

    void OneWrite(uint8_t ch){
    	while((Instance->SR & 0X40) == 0);
    	Instance->DR = (uint8_t)ch;
    };
    void Write(uint8_t *src, int num){
    	while(num--){
    		this->OneWrite(*src);
    		src++;
    	}
    };

    uint8_t StrBuf[100];
    void printf(char *fmt,...){
        va_list ap;
        va_start(ap, fmt);
        vsprintf((char*)StrBuf, fmt, ap);
        Write(StrBuf, strlen((char*)StrBuf));
        va_end(ap);
    }

    virtual void DoProtocol(void){}

};

#endif /* HARDWARESERIAL_H_ */
