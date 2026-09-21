#include "inc/rtos.h"

//-------------------MAIN FUNCTION------------------------------------------
int remove_Task(uint32_t id)
{
    TCB_t *prev = NULL ;
    TCB_t *current = Task_List;
    
    while (current != NULL){
        if (current->id == id){
            //Relink around it
            if (prev == NULL) Task_List = current->next;
            else prev->next = current->next; 

            //Clearing per spec
            current->id = (uint32_t)-1;
            current->priority = 0;
            current->Stack_Pointer = 0;
            for (int i=0; i < STACK_SIZE; i++)
                current->TCB_Stack[i] = 0;
            
            free(current);
            return id;
        }
        prev = current;
        current = current->next;
    }
    return 0; //Not found
}


