#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

int 
xargs(int argc, char* argv[]){
  int i, ret;
  char arg[MAXARG];
  char c, *cmd;

  cmd = argv[1];
  for(i = 0; i < argc - 1; ++i)
    argv[i] = argv[i + 1];

  while(1){
    i = 0;
    memset(arg, 0, strlen(arg));
    while(1){
      ret = read(0, &c, 1);
      if(ret == 0 || c == '\n') break;
      arg[i++] = c;
    }

    if(i == 0)
      break;

    if((ret = fork()) > 0){
      wait(0);
    }else if(ret == 0){
      argv[argc - 1] = arg;
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
