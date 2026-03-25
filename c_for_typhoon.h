#ifndef C_FOR_TYPHOON_LIBRARY_H
#define C_FOR_TYPHOON_LIBRARY_H
#include <stdint.h>

typedef struct {
    uint8_t Sa_top;
    uint8_t Sa_bot;
    uint8_t Sb_top;
    uint8_t Sb_bot;
    uint8_t Sc_top;
    uint8_t Sc_bot;
} INVERSOR_SWITCHES;

typedef struct {
    uint8_t HallA;
    uint8_t HallB;
    uint8_t HallC;
} HALL_INPUTS;

typedef enum  {
    CLOCKWISE,
    COUNTER_CLOCKWISE,
} Rotation_Direction;


void bldcHallSensorComLogic (
    INVERSOR_SWITCHES* switches,
    HALL_INPUTS hallInputs,
    Rotation_Direction direction
);

#endif // C_FOR_TYPHOON_LIBRARY_H