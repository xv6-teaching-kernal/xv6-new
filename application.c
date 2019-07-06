// A simple user program which will be running under the VM control

#include "types.h"
#include "stat.h"
#include "user.h"

int gdate()
{
    return vmtrap(1);
}

int gmonth()
{
    return vmtrap(2);
}

int gyear()
{
    return vmtrap(3);
}

int
main()
{
    printf(1, "this is the application program...\n");
    printf(1, "date = %d\n", gdate());
    printf(1, "month = %d\n", gmonth());
    printf(1, "year = %d\n", gyear());
    exit();
}
