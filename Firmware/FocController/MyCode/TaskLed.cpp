#include "PwmLed.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"

//extern TIM_HandleTypeDef htim12;
//extern TIM_HandleTypeDef htim14;
//
//PwmLed Red(&htim12, TIM_CHANNEL_1, 50);
//PwmLed Green(&htim12, TIM_CHANNEL_2, 50);
//PwmLed Blue(&htim14, TIM_CHANNEL_1, 50);
//
//void ledTask(void *argument){
//	Red.SetBreathing();
//	Green.SetOff();
//	Blue.SetOff();
//	while(1){
//		vTaskDelay(50);
//		Red.Run();
//		Blue.Run();
//		Green.Run();
//	}
//}



