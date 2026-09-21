#include "inc/rtos.h"

// This is the command line interface (CLI)
// You must have a Serial Terminal running (eg TeraTerm) to diaply and pass keypresses to this function
// A readln() helper function is availble to read the keypresses into a buffer and return when teh Enter key is pressed.
//		void readln(char *line, int size)  line is the buufer, size ensures that you do not overrun past the size of your buffer

//-------------------VARIBALES------------------------------------------
#define MAX_LINE 64
#define MAX_TOKENS 4

//COLOURINGGGG
#define PINK       "\x1b[38;5;205m"
#define HOT_PINK   "\x1b[38;5;198m"
#define LIGHT_PINK "\x1b[38;5;217m"
#define ROSE       "\x1b[38;5;211m"
#define MAGENTA    "\x1b[38;5;201m"
#define RESET      "\x1b[0m"

//-------------------HELPER FUNCTIONS------------------------------------------
static void print_menu(void){
    printf(ROSE"-------------------------♡ ALPIE MAIN MENU ♡-------------------------\n"RESET);
    printf(LIGHT_PINK"pt               + Printing the list of tasks\n"RESET);
    printf(HOT_PINK"rt id            + Removing a task}\n"RESET);
    printf(LIGHT_PINK"sd               + SHUT DOWN \n"RESET);
    printf(HOT_PINK"mm               + Pulling Main Menu\n\n"RESET);
    printf(MAGENTA"blink <numflash> <priority>\n"RESET);
    printf(PINK"count <position> <priority>            Suggest pos 0\n"RESET);
    printf(MAGENTA"flash <position> <priority>            Suggest pos 3\n"RESET);
    printf(PINK"hexer <position> <priority>            Suggest pos 4\n"RESET);
    printf(MAGENTA"splat <position> <priority>            Suggest pos 7\n"RESET);
    printf(ROSE"-----------------------------------------------------------\n"RESET);    
}

static void print_task_list(void) {
    printf(ROSE"\n ♡ TASK LIST ♡ \n\n"RESET);
    TCB_t *current = Task_List;
    while(current != NULL) {
        printf(LIGHT_PINK"\tID: %02u\tTASK NAME: %s\tPRIORITY: %u\n", current->id, current->name, current->priority, RESET);
        current = current->next;
    }
    printf(ROSE"-----------------------------------------------------------\n"RESET);  
}

//-------------------MAIN FUNCTION------------------------------------------
void cmdShell(int dummy) {		// the dummy int is to keep consistent with the other tasks
    char line[MAX_LINE];
    char *token[MAX_TOKENS];

    print_menu();

    while(1){
        printf(ROSE"alpie_shell > "RESET);
        readln(line, MAX_LINE);

        //tokening the spaces:
        int n_tok = 0;
        char *tok = strtok(line, " ");
        while (tok != NULL && n_tok < MAX_TOKENS){
            token[n_tok++] = tok;
            tok = strtok(NULL, " ");
        }
        if (n_tok == 0) continue;

        //Priniting the tasks list
        if(strcmp(token[0], "pt") == 0){
            print_task_list();
        }
        //Priniting the main menu
        else if(strcmp(token[0], "mm") == 0){
            print_menu();
        }
        //Removing a task
        else if (strcmp(token[0], "rt") == 0){
            if(n_tok < 2){
                printf("Usage: rt <id> \n");
                continue;
            }
            uint32_t id = (uint32_t)atoi(token[1]); //atoi is coverting char to int
            if(remove_Task(id)){
                printf(LIGHT_PINK"Removed Task:  %u\n", id, RESET);
            }
            else{
                printf(LIGHT_PINK"Task: %u not found...\n", id, RESET);
            }
        }
        //SHUT DOWN
        else if (strcmp(token[0], "sd") == 0){
            printf(ROSE"++++++ SHUT DOWN ++++++\n"RESET);
            //Turning off sev_seg
            display_clear();
            memset(display_buffer, 0x00, 8); //clearing the memory
            DISABLE_INT();
            while(1) {}
        }
        //Adding a task to the list
        else if (strcmp(token[0], "blink") == 0 || strcmp(token[0], "count") == 0 ||
                 strcmp(token[0], "flash") == 0 || strcmp(token[0], "hexer") == 0 ||
                 strcmp(token[0], "splat") == 0) {
            if (n_tok < 3) {
                printf("Usage: %s <arg> <priority>\n", token[0]);
                continue;
            }
            int arg = atoi(token[1]);
            uint8_t priority = (uint8_t)atoi(token[2]);

            if      (strcmp(token[0], "blink") == 0) add_Task(blink, arg, "blink", priority);
            else if (strcmp(token[0], "count") == 0) add_Task(count, arg, "count", priority);
            else if (strcmp(token[0], "flash") == 0) add_Task(flash, arg, "flash", priority);
            else if (strcmp(token[0], "hexer") == 0) add_Task(hexer, arg, "hexer", priority);
            else                                       add_Task(splat, arg, "splat", priority);
        }
        else {
            printf(ROSE"Unknown command '%s' — type mm' for main menu\n", token[0], RESET);
        }
    }
}
