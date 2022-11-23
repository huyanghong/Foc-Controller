#include <FOC/MagneticSensorSPI.h>
#include <spi.h>
#include "stdio.h"
MagneticSensorSPI::MagneticSensorSPI() {
	// TODO Auto-generated constructor stub

}

MagneticSensorSPI::~MagneticSensorSPI() {
	// TODO Auto-generated destructor stub
}

MagneticSensorSPI::MagneticSensorSPI(SPI_HandleTypeDef* spi, GPIO_TypeDef* chip_select_gpiox, int chip_select_pin, int angle_register, int cpr, DIR dir){
	this->Spi = spi;
	this->ChipSelectGpiox = chip_select_gpiox;
	this->ChipSelectPin = chip_select_pin;

	this->AngleRegister = angle_register;
	this->Cpr = cpr;
	this->Dir = dir;

	HAL_GPIO_WritePin(this->ChipSelectGpiox, this->ChipSelectPin, GPIO_PIN_SET);
	// velocity calculation init
	this->AnglePrev = 0;
	this->VelocityCalcTimestamp = micros();

	// full rotations tracking number
	this->FullRotationOffset = 0;
	this->AngleDataPrev = 0;//this->GetRawCount();
}

void MagneticSensorSPI::Init(SPI_HandleTypeDef* spi, GPIO_TypeDef* chip_select_gpiox, int chip_select_pin, int angle_register, int cpr, DIR dir){
	this->Spi = spi;
	this->ChipSelectGpiox = chip_select_gpiox;
	this->ChipSelectPin = chip_select_pin;

	this->AngleRegister = angle_register;
	this->Cpr = cpr;
	this->Dir = dir;

	HAL_GPIO_WritePin(this->ChipSelectGpiox, this->ChipSelectPin, GPIO_PIN_SET);
	// velocity calculation init
	this->AnglePrev = 0;
	this->VelocityCalcTimestamp = micros();

	// full rotations tracking number
	this->FullRotationOffset = 0;
	this->AngleDataPrev = this->GetRawCount();
}

int MagneticSensorSPI::GetRawCount(){

	  uint16_t command = this->AngleRegister | 0xc000;

	  //Send the command
	  HAL_GPIO_WritePin(this->ChipSelectGpiox, this->ChipSelectPin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(this->ChipSelectGpiox, this->ChipSelectPin, GPIO_PIN_RESET);
	  HAL_SPI_Transmit(this->Spi ,(unsigned char *)&command, 1, 100);
	  HAL_GPIO_WritePin(this->ChipSelectGpiox, this->ChipSelectPin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(this->ChipSelectGpiox, this->ChipSelectPin, GPIO_PIN_SET);

	  //Now read the response
	  HAL_GPIO_WritePin(this->ChipSelectGpiox, this->ChipSelectPin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(this->ChipSelectGpiox, this->ChipSelectPin, GPIO_PIN_RESET);
	  uint16_t register_value = 0;
	  HAL_SPI_TransmitReceive(this->Spi ,(unsigned char *)&command, (unsigned char *)&register_value, 1, 100);
	  //HAL_SPI_Receive(this->Spi , (unsigned char *)&register_value, 1, 100);
	  HAL_GPIO_WritePin(this->ChipSelectGpiox, this->ChipSelectPin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(this->ChipSelectGpiox, this->ChipSelectPin, GPIO_PIN_SET);

	  return register_value & 0x3fff;
}



