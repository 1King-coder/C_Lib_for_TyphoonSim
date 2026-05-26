#ifndef C_FOR_TYPHOON_LIBRARY_H
#define C_FOR_TYPHOON_LIBRARY_H
#include <stdint.h>

#define samp_freq 5e-6

typedef struct {
    unsigned char Sa_top;
    unsigned char Sa_bot;
    unsigned char Sb_top;
    unsigned char Sb_bot;
    unsigned char Sc_top;
    unsigned char Sc_bot;
} INVERSOR_SWITCHES;

typedef struct {
    unsigned char HallA;
    unsigned char HallB;
    unsigned char HallC;
} HALL_INPUTS;

typedef enum  {
    CLOCKWISE,
    COUNTER_CLOCKWISE,
} Rotation_Direction;

void resetSwitches (INVERSOR_SWITCHES* switches);
void updateHallInputs (
    HALL_INPUTS* hallInputs,
    unsigned char hallA,
    unsigned char hallB,
    unsigned char hallC
);

void bldcHallSensor2phComLogic (
    INVERSOR_SWITCHES* switches,
    HALL_INPUTS hallInputs,
    Rotation_Direction direction
);

void rampStep (double ref, double startValue, double stepTime, double t, double* out);

typedef struct {
    double* riseTime;
    double* layerPeriod;
} LAYERS_TIMES;

int rampStepLayersIndex = 0;
double rampStepLayersTimeAcc = 0;

void rampStepLayers (double* layersRefs, double startValue, int numOfLayers, LAYERS_TIMES layersTimes, double t, double* out);

void staircase (double gain, double totalSteps, double riseTime, double t, double* out);

int getIndex_double (const double* array, double value, int size);
void torque_motor_ebike (double omega, double omega_b, double omega_max, double *out);
double P_Controller (double kp, double u);
double I_Controller (double ki, double u, double* u1, double* y1);
double D_Controller (double kd, double u, double* u1, double* y1);

void PID (double kp, double ki, double kd, double* out, double in);

#endif // C_FOR_TYPHOON_LIBRARY_H