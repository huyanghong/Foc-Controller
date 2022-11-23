#include <FOC/AdcValue.h>

AdcValue::AdcValue() {
	// TODO Auto-generated constructor stub
}

AdcValue::~AdcValue() {
	// TODO Auto-generated destructor stub
}


void AdcValue::Offset(int cnt){
	unsigned int iu = 0, iv = 0, iw = 0;

	if(this->Adc3){
		HAL_ADC_Start(this->Adc1);
		HAL_ADC_Start(this->Adc2);
		HAL_ADC_Start(this->Adc3);

		for(int i=0; i<cnt; i++){
			iu += HAL_ADCEx_InjectedGetValue(this->Adc1, this->Rank1);
			iv += HAL_ADCEx_InjectedGetValue(this->Adc2, this->Rank2);
			iw += HAL_ADCEx_InjectedGetValue(this->Adc3, this->Rank3);
			HAL_Delay(1);
		}
		this->OffsetValue.iu = (float)iu / cnt * ADC2AMPS;
		this->OffsetValue.iv = (float)iv / cnt * ADC2AMPS;
		this->OffsetValue.iw = (float)iw / cnt * ADC2AMPS;
	}else{
		HAL_ADC_Start(this->Adc1);
		HAL_ADC_Start(this->Adc2);

		for(int i=0; i<cnt; i++){
			iu += HAL_ADCEx_InjectedGetValue(this->Adc1, this->Rank1);
			iv += HAL_ADCEx_InjectedGetValue(this->Adc2, this->Rank2);
			HAL_Delay(1);
		}
		this->OffsetValue.iu = (float)iu / cnt * ADC2AMPS;
		this->OffsetValue.iv = (float)iv / cnt * ADC2AMPS;
		this->OffsetValue.iw = 0;
	}
//	HAL_ADCEx_InjectedStart_IT(&hadc1);
}
#include "stdio.h"
void AdcValue::Update(void){
	unsigned int iu = 0, iv = 0, iw = 0;

	if(this->Adc3){
		iu = HAL_ADCEx_InjectedGetValue(this->Adc1, this->Rank1);
		iv = HAL_ADCEx_InjectedGetValue(this->Adc2, this->Rank2);
		iw = HAL_ADCEx_InjectedGetValue(this->Adc3, this->Rank3);

		this->Value.iu = this->OffsetValue.iu - iu * ADC2AMPS;
		this->Value.iv = this->OffsetValue.iv - iv * ADC2AMPS;
		this->Value.iw = this->OffsetValue.iw - iw * ADC2AMPS;
	}else{
		iu = HAL_ADCEx_InjectedGetValue(this->Adc1, this->Rank1);
		iv = HAL_ADCEx_InjectedGetValue(this->Adc2, this->Rank2);

		this->Value.iu = this->OffsetValue.iu - iu * ADC2AMPS;
		this->Value.iv = this->OffsetValue.iv - iv * ADC2AMPS;
		this->Value.iw = -this->Value.iu - this->Value.iv;
	}
}
