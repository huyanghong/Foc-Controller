#include "main.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stdio.h"
#include "usart.h"
#include "tim.h"
#include "can.h"
#include "HardwareCan.h"
#include "Shycom.h"
#include <FOC/FocController.h>

Shycom shycom(UART4, 1500000);
AdcValue *adcValue = new AdcValue(&hadc1, ADC_INJECTED_RANK_1, &hadc1, ADC_INJECTED_RANK_2);
Encoder *sensor = new MagneticSensorSPI(&hspi1, GPIOA, GPIO_PIN_4, 0x3fff, 16384, MagneticSensorSPI::CW);
//Encoder *sensor = new IncrementalEncoder(&htim3, 64000, MagneticSensorSPI::CCW);
SvPwm *svpwm = new SvPwm(&htim1, 4000);
FocConverter *focConv = new FocConverter();
FocController focController(focConv, svpwm, sensor, adcValue);

int AlignmentCnt = 2500;

void StartFocTask(void *argument)
{
	vTaskDelay(1000);
	focController.Init();
	vTaskDelay(1000);

	focController.Mode = FocController::CloseLoopSpeed;
	while(1)
	{
		vTaskDelay(1);
		switch(focController.Mode)
		{
			case FocController::Disable:
				break;
			case FocController::InjectionVoltage:
				focController.InjectionVoltageTarget.Voltage = 5;
				focController.InjectionVoltageTarget.Theta = 0;
				break;
			case FocController::NoSensorOpenLoopSpeed:
				focController.NoSensorOpenLoopSpeedTarget.Voltage = 5;
				focController.NoSensorOpenLoopSpeedTarget.Speed = 3.14;
				vTaskDelay(2000);
				focController.NoSensorOpenLoopSpeedTarget.Speed = -3.14;
				vTaskDelay(2000);
				break;
			case FocController::NoSensorOpenLoopPosition:
				focController.NoSensorOpenLoopPositionTarget.Voltage = 5;
				focController.NoSensorOpenLoopPositionTarget.Speed = 3.14;
				focController.NoSensorOpenLoopPositionTarget.Position = 6.28;
				vTaskDelay(6000);
				focController.NoSensorOpenLoopPositionTarget.Position = -6.28;
				vTaskDelay(6000);
				break;
			case FocController::CloseLoopCurrent:
				while(AlignmentCnt){
					focController.Mode = FocController::InjectionVoltage;
					focController.InjectionVoltageTarget.Voltage = 5;
					focController.InjectionVoltageTarget.Theta = 0;
					AlignmentCnt--;
					vTaskDelay(1);
					focController.OffsetAngle = focController.Sensor->GetAngle();
				}
				focController.Mode = FocController::CloseLoopCurrent;
				focController.CloseLoopCurrentTarget.Id = 0;
				focController.CloseLoopCurrentTarget.Iq = -0.3;
				vTaskDelay(4000);
				focController.CloseLoopCurrentTarget.Iq = 0.3;
				vTaskDelay(4000);
				break;
			case FocController::CloseLoopSpeed:
				while(AlignmentCnt){
					focController.Mode = FocController::InjectionVoltage;
					focController.InjectionVoltageTarget.Voltage = 5;
					focController.InjectionVoltageTarget.Theta = 0;
					AlignmentCnt--;
					vTaskDelay(1);
					focController.OffsetAngle = focController.Sensor->GetAngle();
					focController.CloseLoopSpeedTarget.Speed = 6.28;
				}
				focController.CloseLoopSpeedTarget.Speed *= (-1);
				focController.Mode = FocController::CloseLoopSpeed;
				vTaskDelay(2000);
				break;
			case FocController::CloseLoopPosition:
				while(AlignmentCnt){
					focController.Mode = FocController::InjectionVoltage;
					focController.InjectionVoltageTarget.Voltage = 5;
					focController.InjectionVoltageTarget.Theta = 0;
					AlignmentCnt--;
					vTaskDelay(1);
					focController.OffsetAngle = focController.Sensor->GetAngle();
					focController.CloseLoopPositionTarget.Position = 3.14;
				}
				focController.CloseLoopPositionTarget.Position *= (-1);
				focController.Mode = FocController::CloseLoopPosition;
				vTaskDelay(4000);
				break;
		}
	}
}
void protocolTask(void *argument){
	shycom.Begin();
	while(1){
		vTaskDelay(100);
		if((millis() - shycom.GetRxTimeStamp()) > 500 /*&& shycom.GetAvailable() > 0*/){
			shycom.DoProtocol();
		}
//		float report[10];
//		report[0] = focController.PidPosition.Kp;
//		report[1] = focController.PidPosition.Ki;
//		report[2] = focController.PidPosition.Kd;
//		report[3] = focController.CloseLoopPositionTarget.Position;
//		shycom.ReportCurveValue(report, 4);
	}
}




void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef* AdcHandle)
{
  /* Get the converted value of injected channel */
	if(AdcHandle->Instance == ADC1){
		focController.Run();
	}
}

extern volatile uint8_t Uart4_RxBuffer[1];
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
	if(UartHandle->Instance == UART4){
		shycom.Add(Uart4_RxBuffer[0]);
		HAL_UART_Receive_IT(&huart4, (uint8_t *)Uart4_RxBuffer, 1);
	}
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	uint8_t buf[8];
	CAN_RxHeaderTypeDef CAN_RX_HDR;
	if (hcan->Instance == hcan1.Instance){
		if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &CAN_RX_HDR, buf) == HAL_OK){
			uint32_t p;
			memcpy(&p, buf, 4);
			printf("pending1: %d %d %d %d %d\n", CAN_RX_HDR.DLC,CAN_RX_HDR.StdId,p,buf[0],buf[7]);
			HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING);	// 再次使能FIFO0接收中断
		}
	}
}


