#include "c_for_typhoon.h"
#include <math.h>


void resetSwitches (INVERSOR_SWITCHES* switches) {
    switches->Sa_top = 0;
    switches->Sa_bot = 0;
    switches->Sb_top = 0;
    switches->Sb_bot = 0;
    switches->Sc_top = 0;
    switches->Sc_bot = 0;
}
void updateHallInputs (
    HALL_INPUTS* hallInputs,
    unsigned char hallA,
    unsigned char hallB,
    unsigned char hallC
) {
    hallInputs->HallA = hallA;
    hallInputs->HallB = hallB;
    hallInputs->HallC = hallC;
}

void bldcHallSensor2phComLogic(
    INVERSOR_SWITCHES* switches,
    HALL_INPUTS hallInputs,
    const Rotation_Direction direction
) {

    switch (direction) {

        case CLOCKWISE: {
            //0 - 60
            if (hallInputs.HallA == 1 && hallInputs.HallB == 0 && hallInputs.HallC == 0) {
                switches->Sc_top = 1;
                switches->Sb_bot = 1;
            }
            // 60 - 120
            if (hallInputs.HallA == 1 && hallInputs.HallB == 1 && hallInputs.HallC == 0) {
                switches->Sa_top = 1;
                switches->Sb_bot = 1;
            }
            // 120 - 180
            if (hallInputs.HallA == 0 && hallInputs.HallB == 1 && hallInputs.HallC == 0) {
                switches->Sa_top = 1;
                switches->Sc_bot = 1;
            }
            // 180 - 240
            if (hallInputs.HallA == 0 && hallInputs.HallB == 1 && hallInputs.HallC == 1) {
                switches->Sb_top = 1;
                switches->Sc_bot = 1;
            }
            // 240 - 300
            if (hallInputs.HallA == 0 && hallInputs.HallB == 0 && hallInputs.HallC == 1) {
                switches->Sb_top = 1;
                switches->Sa_bot = 1;
            }
            // 300 - 360
            if (hallInputs.HallA == 1 && hallInputs.HallB == 0 && hallInputs.HallC == 1) {
                switches->Sc_top = 1;
                switches->Sa_bot = 1;
            }
            break;
        }


        case COUNTER_CLOCKWISE: {

            if (hallInputs.HallA == 1 && hallInputs.HallB == 0 && hallInputs.HallC == 0) {
                switches->Sa_top = 1;
                switches->Sc_bot = 1;
            }
            // 60 - 120
            if (hallInputs.HallA == 1 && hallInputs.HallB == 1 && hallInputs.HallC == 0) {
                switches->Sa_top = 1;
                switches->Sb_bot = 1;
            }
            // 120 - 180
            if (hallInputs.HallA == 0 && hallInputs.HallB == 1 && hallInputs.HallC == 0) {
                switches->Sc_top = 1;
                switches->Sb_bot = 1;
            }
            // 180 - 240
            if (hallInputs.HallA == 0 && hallInputs.HallB == 1 && hallInputs.HallC == 1) {
                switches->Sc_top = 1;
                switches->Sa_bot = 1;
            }
            // 240 - 300
            if (hallInputs.HallA == 0 && hallInputs.HallB == 0 && hallInputs.HallC == 1) {
                switches->Sb_top = 1;
                switches->Sa_bot = 1;
            }
            // 300 - 360
            if (hallInputs.HallA == 1 && hallInputs.HallB == 0 && hallInputs.HallC == 1) {
                switches->Sb_top = 1;
                switches->Sc_bot = 1;
            }
            break;
        }
    }
}

void rampStep (double gain, double stepTime, double t, double* out) {
    *out = fabs(*out) < fabs(gain) ? gain/stepTime * t : gain;
}

void staircase (double gain, double totalSteps, double riseTime, double t, double* out) {
    int step = t / (riseTime / totalSteps);
    *out = fabs(*out) < fabs(gain) ? gain/totalSteps * step : gain;
}

double P_Controller (double kp, double u) {
    return kp*u;
}

double I_Controller (double ki, double u, double* u1, double* y1) {
    double out = 0.5 * (2*ki*samp_freq*(u + *u1) + 2* *y1);
    *u1 = u;
    *y1 = out;
    return out;
}

double D_Controller (double kd, double u, double* u1, double* y1) {
    double out = 1/samp_freq * (2*kd*(u - *u1) - *y1 * samp_freq);
    *u1 = u;
    *y1 = out;
    return out;
}

void PID (double kp, double ki, double kd, double* out, double in) {
    double u1, y1;
    u1 = 0;
    y1 = 0;

    *out = P_Controller (kp, in) + ki !=0 ? I_Controller(ki, in, &u1, &y1) : 0 + kd !=0 ? D_Controller(kd, in, &u1, &y1) : 0;
}