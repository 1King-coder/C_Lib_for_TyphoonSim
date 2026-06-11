#include "c_for_typhoon.h"
#include <math.h>
#include <stdio.h>



void rampStep (double ref, double startValue, double stepTime, double t, double* out) {
    int8_t sign = ref - startValue >= 0 ? 1 : -1;

    switch (sign) {
        case 1: {
            *out = (*out < ref) ? startValue + (ref-startValue)/stepTime * t : ref;
            break;
        }
        case -1: {

            *out = (*out > ref) ? startValue + (ref-startValue)/stepTime * t : ref;
            break;
        }
        default: {
            *out = 0;
            break;
        }
    }

}

int getIndex_double (const double* array, double value, int size) {
    for (int i = 0; i < size; i++) {
        if (array[i] == value) {
            return i;
        }
    }
    return 0;
}


void rampStepLayers (
    double* layersRefs,
    double startValue,
    int numOfLayers,
    LAYERS_TIMES layersTimes,
    double t,
    double* out
) {

    if (numOfLayers == 1) {
        rampStep(*layersRefs, startValue, *layersTimes.riseTime, t, out);
        return;
    }

    if (rampStepLayersIndex+1 == numOfLayers) {
        startValue = *(layersRefs + rampStepLayersIndex - 1);

        rampStep(
            *(layersRefs + rampStepLayersIndex),
            startValue,
            *(layersTimes.riseTime + rampStepLayersIndex),
            t - rampStepLayersTimeAcc,
            out
        );
        return;
    }
    if (t - rampStepLayersTimeAcc >= *(layersTimes.riseTime + rampStepLayersIndex) + *(layersTimes.layerPeriod + rampStepLayersIndex)) {
        rampStepLayersTimeAcc += *(layersTimes.riseTime + rampStepLayersIndex) + *(layersTimes.layerPeriod + rampStepLayersIndex);
        rampStepLayersIndex++;
    }

    startValue = rampStepLayersTimeAcc != 0 ? *(layersRefs + rampStepLayersIndex - 1) : startValue;

    rampStep(
        *(layersRefs + rampStepLayersIndex),
        startValue,
        *(layersTimes.riseTime + rampStepLayersIndex),
        t - rampStepLayersTimeAcc,
        out
    );
}

void torque_motor_ebike (double omega, double omega_b, double omega_max, double *out) {
    double T_max = 9.545;

    if (omega < 0) {
        *out = 0;
        return;
    };
    if (omega >= 0 && omega <= omega_b) {
        *out = T_max;
        return;
    };
    if (omega_b < omega && omega <= omega_max) {
        *out = T_max * (omega_max - omega) / (omega_max - omega_b);

        return;
    };

    *out = 0;
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