#ifndef FOC_MAGNETICSENSORSPI_H_
#define FOC_MAGNETICSENSORSPI_H_

#include <FOC/Encoder.h>
#include "spi.h"

class MagneticSensorSPI: public Encoder {
public:
	MagneticSensorSPI();
	virtual ~MagneticSensorSPI();
	MagneticSensorSPI(SPI_HandleTypeDef* spi, GPIO_TypeDef* chip_select_gpiox, int chip_select_pin, int angle_register, int cpr, DIR dir = DIR::CCW);

	virtual void Init(SPI_HandleTypeDef* spi, GPIO_TypeDef* chip_select_gpiox, int chip_select_pin, int angle_register, int cpr, DIR dir = DIR::CCW);
	virtual void Init(){};
	virtual int GetRawCount();

public:
    SPI_HandleTypeDef* Spi;
    GPIO_TypeDef* ChipSelectGpiox;
    int ChipSelectPin; //!< SPI chip select pin

    int AngleRegister;

	/** Calculate parity value  */
	uint8_t spiCalcEvenParity(uint16_t value);

};

#endif /* FOC_MAGNETICSENSORSPI_H_ */
