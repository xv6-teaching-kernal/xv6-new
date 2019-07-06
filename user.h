enum procstate { UNUSED, EMBRYO, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };
struct stat;
struct rtcdate;

#define MAX_PS_PROCS 10

struct procps {
  uint sz;                     // Size of process memory (bytes)
  pde_t* pgdir;                // Page table
//   char *kstack;                // Bottom of kernel stack for this process
  enum procstate state;        // Process state
  volatile int pid;            // Process ID
  // struct trapframe *tf;        // Trap frame for current syscall

  void *chan;                  // If non-zero, sleeping on chan
  int killed;                  // If non-zero, have been killed
//   struct file *ofile[NOFILE];  // Open files
  // struct inode *cwd;           // Current directory
  char name[16];               // Process name (debugging)

  volatile int parent_pid;            // Process ID
    uint edi;

};


// system calls
int fork(void);
int exit(void) __attribute__((noreturn));
int wait(void);
int pipe(int*);
int write(int, const void*, int);
int read(int, void*, int);
int close(int);
int kill(int);
int exec(char*, char**);
int open(const char*, int);
int mknod(const char*, short, short);
int unlink(const char*);
int fstat(int fd, struct stat*);
int link(const char*, const char*);
int mkdir(const char*);
int chdir(const char*);
int dup(int);
int getpid(void);
char* sbrk(int);
int sleep(int);
int uptime(void);
int sysps(unsigned long, struct procps[]);
int vmtrap(int);

// ulib.c
int stat(const char*, struct stat*);
char* strcpy(char*, const char*);
void *memmove(void*, const void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void printf(int, const char*, ...);
char* gets(char*, int max);
uint strlen(const char*);
void* memset(void*, int, uint);
void* malloc(uint);
void free(void*);
int atoi(const char*);
