#include "kernel/types.h"
#include "user/user.h"

#define BUF 5

void 
main(){
  int p[2];
  int ret;
  char buffer[BUF];

  pipe(p);
  if((ret = fork()) == 0){
    if(read(p[0], buffer, sizeof(buffer)) > 0)
      fprintf(1, "%d: received %s\n", getpid(), buffer);

    strcpy(buffer, "pong");
    close(p[0]);
    write(p[1], buffer, sizeof(buffer));
    close(p[1]);
  }else if(ret > 0){
    strcpy(buffer, "ping");
    write(p[1], buffer, sizeof(buffer)); 
    close(p[1]);
    
    wait(0);
    if(read(p[0], buffer, sizeof(buffer)) > 0)
      fprintf(1, "%d: received %s\n", getpid(), buffer);
    close(p[0]);

  }else{
    fprintf(2, "fork fail...\n");
  }
  exit(0);
}
