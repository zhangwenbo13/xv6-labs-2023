#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    char *p;
    int n;

    if(argc != 2){
        fprintf(2, "Usage: sleep second ...\n");
	exit(1);
    }

    p = argv[1];
    n = atoi(p);
    sleep(n);
    exit(0);
}
