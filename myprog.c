#include "types.h"
#include "stat.h"
#include "user.h"
int
main(void)
{
    printf(1, "Staring rogue sys call \n");
    vmtrap(1);
    printf(1, "Executes rogue sys call !!!\n");
    exit();
}