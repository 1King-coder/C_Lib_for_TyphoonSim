#ifndef C_FOR_TYPHOON_LIBRARY_H
#define C_FOR_TYPHOON_LIBRARY_H
#include <stdint.h>

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

void rampStep (double gain, double stepTime, double t, double* out);

#endif // C_FOR_TYPHOON_LIBRARY_H