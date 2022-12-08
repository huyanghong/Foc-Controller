#include "main.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task.h"
#include "SimpleFOC.h"
#include "sensors/MagneticSensorSPI.h"
#include "spi.h"

BLDCMotor motor = BLDCMotor(7);
BLDCDriver3PWM driver = BLDCDriver3PWM(Gpio_pin2Index(GPIOA, GPIO_PIN_8), Gpio_pin2Index(GPIOA, GPIO_PIN_9),Gpio_pin2Index(GPIOA, GPIO_PIN_10), Gpio_pin2Index(GPIOC, GPIO_PIN_7));
MagneticSensorSPI sensor = MagneticSensorSPI(AS5147_SPI, Gpio_pin2Index(GPIOA, GPIO_PIN_4));
InlineCurrentSense current_sense = InlineCurrentSense(0.1, 10.0, Gpio_pin2Index(GPIOC, GPIO_PIN_0), Gpio_pin2Index(GPIOC, GPIO_PIN_1),Gpio_pin2Index(GPIOC, GPIO_PIN_2));
Print Serial;

void setupSimpleFOC() {

	vTaskDelay(1000);

	// initialise magnetic sensor hardware
	sensor.init(&hspi1);
	// link the motor to the sensor
	motor.linkSensor(&sensor);

	// driver config
	// power supply voltage [V]
	driver.voltage_power_supply = 12;
	driver.init();
	// link the motor and the driver
	motor.linkDriver(&driver);

	// choose FOC modulation (optional)
	motor.voltage_sensor_align = 1;
	// set control loop type to be used

	motor.torque_controller = TorqueControlType::foc_current;
	motor.controller = MotionControlType::angle;


	// maximal voltage to be set to the motor
	motor.voltage_limit = 6;

	// velocity low pass filtering time constant
	// the lower the less filtered
	motor.LPF_velocity.Tf = 0.01;

	// angle P controller
	motor.P_angle.P = 30;
	// maximal velocity of the position control
	motor.velocity_limit = 12;


	motor.useMonitoring(Serial);
	motor.monitor_downsample = 0; // disable intially
	motor.monitor_variables = _MON_TARGET | _MON_VEL | _MON_ANGLE; // monitor target velocity and angle


	current_sense.init();
	motor.linkCurrentSense(&current_sense);

	// initialize motor
	motor.init();
	// align sensor and start FOC
	motor.initFOC();
}

float target = 1;

void loopSimpleFOC() {
	motor.loopFOC();
	motor.move(target);
	motor.monitor();
}

void disableSimpleFOC(int s) {
	if(s == 1)
		motor.enable();
	else motor.disable();
}
void setTarget(float t){
	target = t;
}
