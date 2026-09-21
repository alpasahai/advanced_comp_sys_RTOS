#include "inc/rtos.h"

//Ticks are set in main.c

// returns 0 if the count > 24Bits
//-------------------MAIN FUNCTION------------------------------------------
uint32_t configure_Systick(uint32_t micro_seconds)
{
    //Fixing the Reload situation:
    uint32_t reload = (125 * micro_seconds) - 1; 

    //Error checking for reload:
    if (reload > 0xFFFFFF){
        return 0;
    }

    systick_hw->csr = 0; //Control Status register disabled
    systick_hw->rvr = reload;
    //systick_hw->rvr = (12500 / micro_seconds); //Reload value register for determines the frequency of interrupts
    systick_hw->cvr = 0; //Current value register
    systick_hw->csr = 0x7; //enabling + turning on interpts 

    return systick_hw->rvr; //return reload val
}

// just use the systick to trigger the context switch
// This is also where the Ticks are generated and used to call the scheduler
// The RTOS System Ticks are also managed in this systick handler

// Note that this function is commented out so that it uses the template supplied one.
void isr_systick(void) {
    Ticks++;
    if (Ticks % TICKS_BEFORE_SWAP == 0){
        CONTEXT_SWITCH();    // trigger context switch and calls the scheduler
    }
}

