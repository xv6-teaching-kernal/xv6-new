// The system calls provided by the VM Manager

#include "types.h"
#include "stat.h"
#include "user.h"

#include "guestSysCalls.h"

int
gsys_date()
{
    return 27;
}

int
gsys_month()
{
    return 5;
}

int
gsys_year()
{
   return 2016;
}

int
gtrap(int sys_call_num)
{
    int val = 0;
    // printf(1, "Working \n");
    switch(sys_call_num)
    {
        case 1:
            val = gsys_date();
            break;

        case 2:
            val = gsys_month();
            break;

        case 3:
            val = gsys_year();
            break;
        default:
            val = 0;
    }

   return val;
}
