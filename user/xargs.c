#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

#define MAXBUF 128

int 
xargs(int argc, char* argv[]){
  int i, ret, cnt;
  char *args[MAXARG];
  char c, *cmd, *arg;

  arg = (char *)malloc(MAXBUF);
  memset(arg, 0, strlen(arg));

  i = 0;
  cnt = 0;
  while(read(0, &c, 1) > 0 && cnt < MAXARG){
    if(c != '\n'){
      arg[i++] = c;
    }else{
      args[cnt] = arg;
      arg = (char *)malloc(MAXBUF);
      memset(arg, 0, strlen(arg));
      ++cnt;
      i = 0;
    }    
  }

  cmd = argv[1];
  for(i = 0; i < argc - 1; ++i)
    argv[i] = argv[i + 1];

  for(i = 0; i < cnt; ++i){
    if((ret = fork()) > 0){
      wait(0);
    }else if(ret == 0){
      argv[argc - 1] = args[i];
      exec(cmd, argv); 
    }else{
      fprintf(2, "fork error...\n");
    }
  
  }
     
  return 0;
}

int 
main(int argc, char* argv[]){
  if(argc < 2){
    fprintf(2, "error, Usage: xargs cmd [argv]\n");
    exit(1);
  }

  xargs(argc, argv);
  exit(0);	
}
