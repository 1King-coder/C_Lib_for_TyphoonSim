// generated using template: cop_main.template---------------------------------------------
/******************************************************************************************
**
**  Module Name: cop_main.c
**  NOTE: Automatically generated file. DO NOT MODIFY!
**  Description:
**            Main file
**
******************************************************************************************/
// generated using template: arm/custom_include.template-----------------------------------


#ifdef __cplusplus
#include <limits>

extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <complex.h>
#include <time.h>
#include <stdarg.h>

// x86 libraries:
#include "../include/sp_functions_dev0.h"


#ifdef __cplusplus
}
#endif


// ----------------------------------------------------------------------------------------                // generated using template:generic_macros.template-----------------------------------------
/*********************** Macros (Inline Functions) Definitions ***************************/

// ----------------------------------------------------------------------------------------

#ifndef MAX
#define MAX(value, limit) (((value) > (limit)) ? (value) : (limit))
#endif
#ifndef MIN
#define MIN(value, limit) (((value) < (limit)) ? (value) : (limit))
#endif

// generated using template: VirtualHIL/custom_defines.template----------------------------

typedef unsigned char X_UnInt8;
typedef char X_Int8;
typedef signed short X_Int16;
typedef unsigned short X_UnInt16;
typedef int X_Int32;
typedef unsigned int X_UnInt32;
typedef unsigned int uint;
typedef double real;

// ----------------------------------------------------------------------------------------
// generated using template: custom_consts.template----------------------------------------

// arithmetic constants
#define C_SQRT_2                    1.4142135623730950488016887242097f
#define C_SQRT_3                    1.7320508075688772935274463415059f
#define C_PI                        3.1415926535897932384626433832795f
#define C_E                         2.7182818284590452353602874713527f
#define C_2PI                       6.283185307179586476925286766559f

//@cmp.def.start
//component defines


//@cmp.def.end


//-----------------------------------------------------------------------------------------
// generated using template: common_variables.template-------------------------------------
// true global variables





// const variables
static const int _bldc3_machine_wrapper1__n_mch_ao_baseaddr = 65536;
static const int _bldc3_machine_wrapper1__n_mch_page_size = 262144;
static const int _bldc3_machine_wrapper1__n_ml_baseaddr = 8388608;
static const int _bldc3_machine_wrapper1__n_rd_as = 13107200;
static const int _bldc3_machine_wrapper1__n_sp_out_indices[6] = {8, 10, 11, 0, 1, 2};
static const int _bldc3_machine_wrapper1__n_vars_per_mch = 16;
static const char* _bldc3_machine_wrapper1__p_enb_sig_out = "True";
static const char* _bldc3_machine_wrapper1__p_ext_mdl_load_type = "torque";
static const char* _bldc3_machine_wrapper1__p_load_src = "SCADA / external";
static const unsigned int _bldc3_machine_wrapper1__p_machine_id = 0;
static const int _bldc3_machine_wrapper1__p_pms = 10;

static const int _bus_split6__n_num_of_outputs = 6;
static const int _bus_split6__n_prev_len[6] = {0, 1, 2, 3, 4, 5};



//@cmp.var.start
// variables
real _bldc3_machine_wrapper1__out[6];
static real _bus_split6__out;
static real _bus_split6__out1;
static real _bus_split6__out2;
static real _bus_split6__out3;
static real _bus_split6__out4;
static real _bus_split6__out5;
//@cmp.var.end

//@cmp.svar.start
// state variables
real _bldc3_machine_wrapper1__model_load;





//@cmp.svar.end

// IO shared variables

//
// Tunable parameters
//
static struct Tunable_params {
} __attribute__((__packed__)) tunable_params;

void *tunable_params_dev0_cpu0_ptr = &tunable_params;

// Dll function pointers
#if defined(_WIN64)
#else
// Define handles for loading dlls
#endif





// generated using template: \templates\virtual_hil\fmi_custom_logger_fncs.template---------------------------------
#include <stdarg.h>



//
// DMA buffers
//













// generated using template: virtual_hil/custom_functions.template---------------------------------
void ReInit_user_sp_cpu0_dev0() {
#if DEBUG_MODE
    printf("\n\rReInitTimer");
#endif
    //@cmp.init.block.start
    {
        _bldc3_machine_wrapper1__model_load = 0;
    }
    //@cmp.init.block.end
}


// Dll function pointers and dll reload function
#if defined(_WIN64)
// Define method for reloading dll functions
void ReloadDllFunctions_user_sp_cpu0_dev0(void) {
    // Load each library and setup function pointers
}

void FreeDllFunctions_user_sp_cpu0_dev0(void) {
}

#else
// Define method for reloading dll functions
void ReloadDllFunctions_user_sp_cpu0_dev0(void) {
    // Load each library and setup function pointers
}

void FreeDllFunctions_user_sp_cpu0_dev0(void) {
}
#endif

void load_fmi_libraries_user_sp_cpu0_dev0(void) {
#if defined(_WIN64)
#else
#endif
}


void ReInit_sp_scope_user_sp_cpu0_dev0() {
    // initialise SP Scope buffer pointer
}


// generated using template: virtual_hil/common_timer_counter_handler.template-------------------------

/*****************************************************************************************/
/**
* This function is the handler which performs processing for the timer counter.
* It is called from an interrupt context such that the amount of processing
* performed should be minimized.  It is called when the timer counter expires
* if interrupts are enabled.
*
*
* @param    None
*
* @return   None
*
* @note     None
*
*****************************************************************************************/

void TimerCounterHandler_0_user_sp_cpu0_dev0() {
#if DEBUG_MODE
    printf("\n\rTimerCounterHandler_0");
#endif
    //////////////////////////////////////////////////////////////////////////
    // Output block
    //////////////////////////////////////////////////////////////////////////
    //@cmp.out.block.start
    // Generated from the component: BLDC3.Machine Wrapper1
    {
        if((0)) {
            HIL_OutFloat(0x800018, _bldc3_machine_wrapper1__model_load);
        }{
            real tac_tmp1;
            tac_tmp1 = HIL_InFloat(0xc90008);
            _bldc3_machine_wrapper1__out[0] = tac_tmp1;
        }{
            real tac_tmp2;
            tac_tmp2 = HIL_InFloat(0xc9000a);
            _bldc3_machine_wrapper1__out[1] = tac_tmp2;
        }{
            real tac_tmp3;
            tac_tmp3 = HIL_InFloat(0xc9000b);
            _bldc3_machine_wrapper1__out[2] = tac_tmp3;
        }{
            real tac_tmp4;
            tac_tmp4 = HIL_InFloat(0xc90000);
            _bldc3_machine_wrapper1__out[3] = tac_tmp4;
        }{
            real tac_tmp5;
            tac_tmp5 = HIL_InFloat(0xc90001);
            _bldc3_machine_wrapper1__out[4] = tac_tmp5;
        }{
            real tac_tmp6;
            tac_tmp6 = HIL_InFloat(0xc90002);
            _bldc3_machine_wrapper1__out[5] = tac_tmp6;
        }
    }
    // Generated from the component: Bus Split6
    {
        {
            _bus_split6__out = _bldc3_machine_wrapper1__out[(_bus_split6__n_prev_len[0] + 0)];
        }{
            _bus_split6__out1 = _bldc3_machine_wrapper1__out[(_bus_split6__n_prev_len[1] + 0)];
        }{
            _bus_split6__out2 = _bldc3_machine_wrapper1__out[(_bus_split6__n_prev_len[2] + 0)];
        }{
            _bus_split6__out3 = _bldc3_machine_wrapper1__out[(_bus_split6__n_prev_len[3] + 0)];
        }{
            _bus_split6__out4 = _bldc3_machine_wrapper1__out[(_bus_split6__n_prev_len[4] + 0)];
        }{
            _bus_split6__out5 = _bldc3_machine_wrapper1__out[(_bus_split6__n_prev_len[5] + 0)];
        }
    }
//@cmp.out.block.end
    //////////////////////////////////////////////////////////////////////////
    // Update block
    //////////////////////////////////////////////////////////////////////////
    //@cmp.update.block.start
    // Generated from the component: BLDC3.Machine Wrapper1
    {
    }
    // Generated from the component: Bus Split6
    //@cmp.update.block.end
}
// ----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------