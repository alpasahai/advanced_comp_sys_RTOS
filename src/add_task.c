#include "inc/rtos.h"

//Variables
static uint32_t next_task_id = 1; //Simple implementation
//TCB_t *Task_List = NULL; //List of tasks (HEAD) << Removing this cause it's in the main.c

//-------------------MAIN FUNCTION------------------------------------------
int add_Task(void (*Task)(int), uint32_t arg, const char *name, uint8_t priority){
    //Allocating the memeory
    TCB_t *new_task = (TCB_t *)malloc(sizeof(TCB_t));
    if (new_task == NULL) return -1; 

    //Incrementing the unique ID + updating the priority
    new_task->id = next_task_id++;
    new_task-> priority = priority;
    
    //Safety storage for names:
    int i = 0;
    while (name[i] != '\0' && i < 31) {
        new_task->name[i] = name[i];
        i++;
    }
    new_task->name[i] = '\0';

    //Using dummy stack from Appendix B Table 1
    //STACK for TOP-DOWN - PSR is at end of array
    uint32_t *stack_top = &new_task->TCB_Stack[STACK_SIZE - 1];

    stack_top[0] = 0x01000000;
    stack_top[-1] = (uint32_t)Task;
    stack_top[-2] = 0;
    stack_top[-3] = 0;
    stack_top[-4] = 0;
    stack_top[-5] = 0;
    stack_top[-6] = 0;
    stack_top[-7] = arg; //First arg to pass to task
    stack_top[-8] = 0;
    stack_top[-9] = 0;
    stack_top[-10] = 0;
    stack_top[-11] = 0;
    stack_top[-12] = 0;
    stack_top[-13] = 0;
    stack_top[-14] = 0;

    new_task->Stack_Pointer = &stack_top[-15]; //SP must point here

    //Appending to the end of the Linked List
    new_task->next = NULL;
    if (Task_List == NULL) {
        Task_List = new_task; //If list is empty, new task is the head
    } else {
        TCB_t *current = Task_List;
        while (current->next != NULL) {
            current = current->next; //Traverse to the end of the list
        }
        current->next = new_task;
    }
    return new_task->id;
}
