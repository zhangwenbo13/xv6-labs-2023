#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "spinlock.h"
#include "proc.h"
#include "defs.h"
#include "elf.h"
#include "sysinfo.h"

int
sysinfo(uint64 addr)
{
  struct proc *p = myproc();
  struct sysinfo s;

  s.freemem = freemem();
  s.nproc = nproc();

  if(copyout(p->pagetable, addr, (char *)&s, sizeof(s)) < 0)
    return -1;
  return 0;
}

