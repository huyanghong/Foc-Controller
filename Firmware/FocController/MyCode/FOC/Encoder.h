/*
 * Encoder.h
 *
 *  Created on: 2022年3月16日
 *      Author: Kepler
 */

#ifndef FOC_ENCODER_H_
#define FOC_ENCODER_H_

#include "main.h"
#include "math.h"

#ifndef _2PI
#define _2PI 6.2831852
#endif
#ifndef _PI
#define _PI  3.1415926
#endif

class Encoder {
public:
	Encoder();
	virtual ~Encoder();

    /** sensor initialise pins */
	virtual void Init() = 0;

    /**
     * Function getting current angle register value
     * it uses angle_register variable
     */
    virtual int GetRawCount() = 0;

    // implementation of abstract functions of the Sensor class
    void Update();
    /** get current angle (rad) */
    float GetAngle();
    /** get current angular velocity (rad/s) **/
    float GetVelocity();

    /** Stop communication */
    void Close();

    void ZeroProcess(){};

public:
    enum DIR {CW = -1, CCW = 1} Dir = this->CCW;
    float Cpr; //!< Maximum range of the sensor

    // total angle tracking variables
    float FullRotationOffset; //!<number of full rotations made
    float AngleDataPrev; //!< angle in previous position calculation step

    // velocity calculation variables
    float AnglePrev; //!< angle in previous velocity calculation step
    long VelocityCalcTimestamp; //!< last velocity calculation timestamp

  public:
    float CurrentAngle, CurrentVelocity;

};

#endif /* FOC_ENCODER_H_ */
