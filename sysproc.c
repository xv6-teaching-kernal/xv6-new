#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "guestSysCalls.h"

void copy_string(char *target, char *source);


int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_sysps(void)
{
  struct proc *ptable;
  struct proc *ptable_start;

  int proc_buffer_size ;
  char *proc_buffer;
  char *proc_buffer_start;
  if((argint(0, &proc_buffer_size)<0) || (argptr(1, &proc_buffer,proc_buffer_size)<0)){
    return -1;
  }
  ptable = get_ptable();
  ptable_start = ptable;
  
  proc_buffer_start = proc_buffer;

  while(proc_buffer + proc_buffer_size > proc_buffer_start){
    *(uint*)proc_buffer_start = ptable_start->sz;
    proc_buffer_start+=sizeof(uint);

    *(pde_t**)proc_buffer_start = ptable_start->pgdir;
    proc_buffer_start+=sizeof(pde_t*);

    *(enum procstate *)proc_buffer_start = ptable_start->state;
    proc_buffer_start+=sizeof(enum procstate);

    *(volatile int *)proc_buffer_start = ptable_start->pid;
    proc_buffer_start+=sizeof(volatile int);

    *(void **)proc_buffer_start = ptable_start->chan;
    proc_buffer_start+=sizeof(void*);

    *(int *)proc_buffer_start = ptable_start->killed;
    proc_buffer_start+=sizeof(int);

    copy_string((char *)proc_buffer_start, ptable_start->name);
    proc_buffer_start+= sizeof(char)*16;

    *(int *)proc_buffer_start = ptable_start->parent->pid;
    proc_buffer_start+=sizeof(int);

    *(unsigned int *)proc_buffer_start = ptable_start->context->edi;
    proc_buffer_start+=sizeof(unsigned int);

    ptable_start++;
  }

   return 1; 
}


void copy_string(char *target, char *source) {
   while (*source) {
      *target = *source;
      source++;
      target++;
   }
   *target = '\0';
}

int sys_vmtrap(void){

  int sys_call;
  if(argint(0, &sys_call) < 0)
    return -1; // return if no system call argument is sent 

  if(myproc()->parent){
    char *name = "guestVM";
    int name_matches = 1;
    for(int i=0; i<8; i++){
      if(myproc()->parent->name[i] != name[i])
        name_matches = 0;
    };

    if(name_matches == 1)
      return gtrap(sys_call);
  }

  kill(myproc()->pid);
  
  return -1;
}