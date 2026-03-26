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
    uint8_t hallA,
    uint8_t hallB,
    uint8_t hallC
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
            if (hallInputs.HallA == 1 && hallInputs.HallB == 0 && hallInputs.HallC == 0) {
                switches->Sa_top = 1;
                switches->Sc_bot = 1;
            }
            if (hallInputs.HallA == 1 && hallInputs.HallB == 1 && hallInputs.HallC == 0) {
                switches->Sb_top = 1;
                switches->Sc_bot = 1;
            }
            if (hallInputs.HallA == 0 && hallInputs.HallB == 1 && hallInputs.HallC == 0) {
                switches->Sb_top = 1;
                switches->Sa_bot = 1;
            }
            if (hallInputs.HallA == 0 && hallInputs.HallB == 1 && hallInputs.HallC == 1) {
                switches->Sc_top = 1;
                switches->Sa_bot = 1;
            }
            if (hallInputs.HallA == 0 && hallInputs.HallB == 0 && hallInputs.HallC == 1) {
                switches->Sc_top = 1;
                switches->Sb_bot = 1;
            }
            if (hallInputs.HallA == 1 && hallInputs.HallB == 0 && hallInputs.HallC == 1) {
                switches->Sa_top = 1;
                switches->Sb_bot = 1;
            }
            break;
        }


        case COUNTER_CLOCKWISE: {
            const uint8_t hallA = hallInputs.HallA;
            hallInputs.HallA = hallInputs.HallC;
            hallInputs.HallC = hallA;
            if (hallInputs.HallA == 1 && hallInputs.HallB == 0 && hallInputs.HallC == 0) {
                switches->Sa_top = 1;
                switches->Sc_bot = 1;
            }
            if (hallInputs.HallA == 1 && hallInputs.HallB == 1 && hallInputs.HallC == 0) {
                switches->Sb_top = 1;
                switches->Sc_bot = 1;
            }
            if (hallInputs.HallA == 0 && hallInputs.HallB == 1 && hallInputs.HallC == 0) {
                switches->Sb_top = 1;
                switches->Sa_bot = 1;
            }
            if (hallInputs.HallA == 0 && hallInputs.HallB == 1 && hallInputs.HallC == 1) {
                switches->Sc_top = 1;
                switches->Sa_bot = 1;
            }
            if (hallInputs.HallA == 0 && hallInputs.HallB == 0 && hallInputs.HallC == 1) {
                switches->Sc_top = 1;
                switches->Sb_bot = 1;
            }
            if (hallInputs.HallA == 1 && hallInputs.HallB == 0 && hallInputs.HallC == 1) {
                switches->Sa_top = 1;
                switches->Sb_bot = 1;
            }
            break;
        }
    }
}