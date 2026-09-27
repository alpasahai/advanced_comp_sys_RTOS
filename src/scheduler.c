#include "inc/rtos.h"

// (1) Quantum event fires interrupt (Systick interrupt)
// (2)The context switch saves the current processor state to your current TCB
// (3) The context switch calls your scheduler to choose a new task and for you to assign CurrentTCB to the new task
// (4) The context switch load the context of the new task from teh current TCB onto the processor

//volatile TCB_t *CurrentTCB = NULL; //This might already exist in the main.c so if you have compile errors check
static int32_t tick_count = 0; //Ticks left beforre switching


//-------------------MAIN FUNCTIONS------------------------------------------
void scheduler(void) {
//================================NON-PRE-EMPTIVE ROUND ROBIN=======================
    // if(Task_List == NULL) return; //There's nothing to run

    // if(CurrentTCB == NULL || CurrentTCB->next == NULL) {
    //     CurrentTCB = Task_List; //Wrapping to the head
    // }
    // else {
    //     CurrentTCB = (volatile TCB_t *)CurrentTCB->next; //advancing with no priority
    // }
//================================NON-PRE-EMPTIVE ROUND ROBIN=======================

//================================PRE-EMPTIVE SCHEDULER=======================
    if(Task_List == NULL) return; //There's nothing to run

    if(CurrentTCB != NULL && tick_count > 0){
        tick_count--;
        return; //not switching just yet
    }

    //Credits exhausted - the round-robin scheduler will now choose the next task to run based on priority
    if (CurrentTCB == NULL || CurrentTCB->next == NULL) {
        CurrentTCB = Task_List;
    }
    else {
        CurrentTCB = (volatile TCB_t *)CurrentTCB->next;
    }

    //Setting the priority -> Higher priority tasks will get more ticks before switching
    tick_count = (CurrentTCB->priority > 0) ? CurrentTCB->priority : 1; //Ensure at least 1 tick for any task
//================================PRE-EMPTIVE SCHEDULER=======================
}

