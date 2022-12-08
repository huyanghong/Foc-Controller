/*
 * Arduino.h
 *
 *  Created on: 2021年9月1日
 *      Author: tajor
 */

#ifndef SIMPLEFOC_DRIVERS_HARDWARE_SPECIFIC_ARDUINO_H_
#define SIMPLEFOC_DRIVERS_HARDWARE_SPECIFIC_ARDUINO_H_

#include "main.h"
#include "stm32f4xx_hal.h"
#include "tim.h"
#include "math.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "freertos.h"
#include "task.h"


class Print{
    public:
    void print(char* value){
    	printf("%s", value);
    };
    void print(float value){
    	printf("%f", value);
    };
    void print(double value){
    	printf("%f", value);
    };
    void print(int value){
    	printf("%d", value);
    };
    void print(char value){
    	printf("%c", value);
    };
    void println(char* value){
    	printf("%s \n", value);
    };
    void println(float value){
    	printf("%f \n", value);
    };
    void println(double value){
    	printf("%lf \n", value);
    };
    void println(int value){
    	printf("%d \n", value);
    };
    void println(char value){
    	printf("%c \n", value);
    };
    void print(char* value, int len){
    	printf("%s", value);
    };
    void print(float value, int len){
    	printf("%f", value);
    };
    void print(double value, int len){
    	printf("%lf", value);
    };
    void print(int value, int len){
    	printf("%d", value);
    };
    void print(char value, int len){
    	printf("%c", value);
    };
    void println(char* value, int len){
    	printf("%s \n", value);
    };
    void println(float value, int len){
    	printf("%f \n", value);
    };
    void println(double value, int len){
    	printf("%f \n", value);
    };
    void println(int value, int len){
    	printf("%d \n", value);
    };

    void println(void){
    	printf("\n");
    };
};

#ifndef HIGH
#define HIGH 1
#endif
#ifndef LOW
#define LOW  0
#endif
#ifndef INPUT
#define INPUT  0
#endif
#ifndef OUTPUT
#define OUTPUT 1
#endif

#define max(a,b)    (((a) > (b)) ? (a) : (b))
#define min(a,b)    (((a) < (b)) ? (a) : (b))


char *F(char* str);
void delay(int t);
unsigned long micros(void);
GPIO_TypeDef* index2Gpio_x(uint32_t index);
uint16_t index2Pin_x(uint32_t index);
uint32_t Gpio_pin2Index(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void digitalWrite(int ulPin, bool high_or_low);
uint32_t analogRead(int ulPin);
void pinMode(int ulPin, bool in_or_out);


float _readADCVoltage(const int pinA);
void _configureADC(const int pinA,const int pinB,const int pinC);


#endif /* SIMPLEFOC_DRIVERS_HARDWARE_SPECIFIC_ARDUINO_H_ */
