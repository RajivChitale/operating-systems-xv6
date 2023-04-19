#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"


//#include "lapic.c"

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
sys_date(void)
{
  struct rtcdate* rptr;
  if(argptr(0, (void*) &rptr, sizeof(rptr)) < 0)
    return -1;
  cmostime(rptr);
  return 0;
}

// int
// sys_trail(void)
// {
//   int mode;
//   if(argint(0, &mode) < 0)
//     return -1;
//   if(mode == 0) cprintf("No system calls logged\n");
//   else if(mode== 1) cprintf("System calls logged, ignoring write\n");
//   else if(mode== 2) cprintf("All system calls logged\n");
//   return mode;
// }

int
sys_settings(void)
{
  int setting;
  int value;
  if(argint(0, &setting) < 0)
    return -1;
  if(argint(1, &value) < 0)
    return -1;


  if(setting == DEBUG_INFO){
    if(value==0) cprintf("Debug information hidden\n");
    else if(value==1)  cprintf("Debug information shown\n");
    else cprintf("Value must be from 0, 1\n");
  }

  else if(setting == DEMAND_PAGING){
    if(value==0) cprintf("Demand paging off\n");
    else if(value==1)  cprintf("Demand paging on\n");
    else cprintf("Value must be from 0, 1\n");
  }

  else if(setting == SYSCALL_TRAIL){
    if(value==0) cprintf("No system calls logged\n");
    else if(value==1) cprintf("System calls logged, ignoring write\n");
    else if(value==2) cprintf("All system calls logged\n");
    else cprintf("Value must be from 0, 1, 2\n");
  }

  else{ 
    cprintf("Invalid setting. Choose from d (demand paging), i (info), s (syscall trail)\n");
    return -1; 
  }

  configuration[setting] = value;

  return value;
}