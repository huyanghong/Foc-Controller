#include <FOC/SvPwm.h>

SvPwm::SvPwm() {
	// TODO Auto-generated constructor stub
}

SvPwm::~SvPwm() {
	// TODO Auto-generated destructor stub
}

SvPwm::SvPwm(TIM_HandleTypeDef* tim, int period) {
	// TODO Auto-generated constructor stub
	this->Tim = tim;
	this->PERIOD = period;
	this->PwmOutput(0, 0, 0);
}

void SvPwm::Svpwm(float uAlpha, float uBeta){
	float U1, U2, U3;
	float T1, T2, T3, T4, T5, T6, T7, Ts = 1.0f;

	U1 =  uBeta;
	U2 =  uAlpha * SVPWM_SQRT3_2 - uBeta / 2; // -temp3
	U3 = -uAlpha * SVPWM_SQRT3_2 - uBeta / 2;//-temp2

	uint8_t A = 0, B = 0, C = 0;
	if (U1 > 0) A = 1;
	if (U2 > 0) B = 1;
	if (U3 > 0) C = 1;

	uint8_t N = 4*C + 2*B + A;
	switch (N) {
		case 3: this->Sector = 1; break;
		case 1: this->Sector = 2; break;
		case 5: this->Sector = 3; break;
		case 4: this->Sector = 4; break;
		case 6: this->Sector = 5; break;
		case 2: this->Sector = 6; break;
	}

    switch (this->Sector) {
        case 1:
            T4 = SVPWM_SQRT3 * Ts / this->Udc * U2;
            T6 = SVPWM_SQRT3 * Ts / this->Udc * U1;
            T7 = (Ts - T4 - T6) / 2;
            break;
        case 2:
            T2 = -SVPWM_SQRT3 * Ts / this->Udc * U2;
            T6 = -SVPWM_SQRT3 * Ts / this->Udc * U3;
            T7 = (Ts - T2 - T6) / 2;
            break;
        case 3:
            T2 = SVPWM_SQRT3 * Ts / this->Udc * U1;
            T3 = SVPWM_SQRT3 * Ts / this->Udc * U3;
            T7 = (Ts - T2 - T3) / 2;
            break;
        case 4:
            T1 = -SVPWM_SQRT3 * Ts / this->Udc * U1;
            T3 = -SVPWM_SQRT3 * Ts / this->Udc * U2;
            T7 = (Ts - T1 - T3) / 2;
            break;
        case 5:
            T1 = SVPWM_SQRT3 * Ts / this->Udc * U3;
            T5 = SVPWM_SQRT3 * Ts / this->Udc * U2;
            T7 = (Ts - T1 - T5) / 2;
            break;
        case 6:
            T4 = -SVPWM_SQRT3 * Ts / this->Udc * U3;
            T5 = -SVPWM_SQRT3 * Ts / this->Udc * U1;
            T7 = (Ts - T4 - T5) / 2;
            break;
    }


    float Ta;
    float Tb;
    float Tc;
    switch (this->Sector) {
        case 1:
            Ta = T4 + T6 + T7;
            Tb = T6 + T7;
            Tc = T7;
            break;
        case 2:
            Ta = T6 + T7;
            Tb = T2 + T6 + T7;
            Tc = T7;
            break;
        case 3:
            Ta = T7;
            Tb = T2 + T3 + T7;
            Tc = T3 + T7;
            break;
        case 4:
            Ta = T7;
            Tb = T3 + T7;
            Tc = T1 + T3 + T7;
            break;
        case 5:
            Ta = T5 + T7;
            Tb = T7;
            Tc = T1 + T5 + T7;
            break;
        case 6:
            Ta = T4 + T5 + T7;
            Tb = T7;
            Tc = T5 + T7;
            break;
    }

	this->T1 = (Ta * this->PERIOD);
	if (this->T1 > this->PERIOD)	this->T1 = this->PERIOD;
	if (this->T1 < 0)	this->T1 = 0;

	this->T2 = (Tb * this->PERIOD);
	if (this->T2 > this->PERIOD)	this->T2 = this->PERIOD;
	if (this->T2 < 0)	this->T2 = 0;

	this->T3 = (Tc * this->PERIOD);
	if (this->T3 > this->PERIOD)	this->T3 = this->PERIOD;
	if (this->T3 < 0)	this->T3 = 0;
}

