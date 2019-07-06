// A simple VM Manager - it will run a mock user program under its control

#include "types.h"
#include "stat.h"
#include "user.h"

#include "guestSysCalls.h"

char *appargv[] = { "application", 0 };

int
main()
{
    printf(1, "---This is the VM server---\n");

    printf(1, "starting user program() \n");

    int pid = fork();

    if(pid < 0) {
        return 0;
    } else if(pid == 0) {
        exec("application", appargv);
    } else if(pid > 0) {
        wait();
    }

    printf(1, "---Exiting from VM server---. \n");

    exit();
}

