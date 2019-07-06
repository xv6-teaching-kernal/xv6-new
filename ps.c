#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) {
    struct procps ps_array[MAX_PS_PROCS];
    struct procps *start;
    sysps((unsigned long)MAX_PS_PROCS * sizeof(struct procps),ps_array);
    start = &ps_array[0];
    
        printf (1,"SZ PGDIR STATE PID KILLED CHAN NAME PARENT_PID EDI\n");
    while(start != &ps_array[MAX_PS_PROCS-1] && start->pid != 0){
        printf (1,"%d ", start->sz);
        printf (1,"%p ", start->pgdir);
        switch (start->state)
        {
            case 0:
                printf (1,"UNUSED   ");
                break;
            case 1:
                printf (1,"EMBRYO   ");
                break;
            case 2:
                printf (1,"SLEEPING ");
                break;
            case 3:
                printf (1,"RUNNABLE ");
                break;
            case 4:
                printf (1,"RUNNING  ");
                break;
            case 5:
                printf (1,"ZOMBIE   ");
                break;
            default:
                break;
        }
        printf (1,"%d ", start->pid);
        if(start->killed < 0){
            printf (1,"KILLED ");
        } else {
            printf (1,"ALIVE  ");
        }
    
        printf (1,"%d ", start->chan);
        printf (1,start->name);
        printf (1," %d ", start->parent_pid);
        printf (1," %d ", (int)start->edi);
        printf (1,"\n");
        start++;
    }
    exit();
        
}