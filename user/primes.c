#include "kernel/types.h"
#include "user/user.h"

#define MAX_NUM 35

void 
run_child(int *p){
  int n, prime;
  int ret;
  int childp[2];

  pipe(childp);
  if((ret = read(p[0], &n, sizeof(int))) == 0)
    exit(0);
  else if(ret < 0)
    fprintf(2, "error read...\n");

  fprintf(1, "prime %d\n", n);
  if((ret = fork()) > 0){
    close(childp[0]);
    while(read(p[0], &prime, sizeof(int)) > 0){
      if(prime % n)
        write(childp[1], &prime, sizeof(int));
    }
    close(p[0]);
    close(childp[1]);
    wait(0);
  }else if(ret == 0){
    close(p[0]);
    close(childp[1]);
    run_child(childp);
  }else
    fprintf(2, "error fork...\n");

  exit(0);
}


int
main(){
  int p[2];
  int ret;

  pipe(p);  
  if((ret = fork()) > 0){
    close(p[0]);
    for(int i = 2; i < 35; ++i){
      write(p[1], &i, sizeof(int));
    }
    close(p[1]);
    wait(0);
  }else if(ret == 0){
    close(p[1]);
    run_child(p);
  }else{
    fprintf(2, "error fork...\n");
  }
  exit(0);
}

