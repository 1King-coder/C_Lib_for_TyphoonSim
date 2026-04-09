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

void rampStep (double ref, double startValue, double stepTime, double t, double* out) {
    int8_t sign = ref - startValue > 0 ? 1 : -1;

    *out = *out == 0 ? startValue : *out;

    switch (sign) {
        case 1: {
            *out = *out < ref ? startValue + sign * ref/stepTime * t : ref;
            break;
        }
        case -1: {
            *out = *out > ref ? startValue + sign * ref/stepTime * t : ref;
            break;
        }
        default: {
            *out = 0;
            break;
        }
    }

}

void incrementVar (int* count) {
    *count = *count + 1;
}
void decrementVar (int* count) {
    *count = *count + 1;
}

int getIndex_double (const double* array, double value) {
    size_t size = sizeof(array) / sizeof(*array);
    for (int i = 0; i < size; i++) {
        if (array[i] == value) {
            return i;
        }
    }
    return 0;
}

void rampLayers (double* layersRefs, double startValue, LAYERS_TIMES layersTimes, double t, double* out) {
    size_t numOfLayers = sizeof(layersRefs) / sizeof(*layersRefs);

    if (numOfLayers == 1) {
        rampStep(*layersRefs, startValue, *layersTimes.riseTime, t, out);
    }

    if (t >= *layersTimes.riseTime + *layersTimes.riseTime) {
        if (!getIndex_double(layersRefs, *layersRefs)) {
            *out = *layersRefs;
            return;
        }
        startValue = *layersRefs;
        *layersRefs = *(layersRefs + 1);
        *layersTimes.riseTime = *(layersTimes.riseTime + 1);
        *layersTimes.layerPeriod = *(layersTimes.layerPeriod + 1);
    }
    rampStep(*layersRefs, startValue, *layersTimes.riseTime, t, out);


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