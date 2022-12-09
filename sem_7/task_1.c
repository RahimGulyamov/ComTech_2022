#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{

        char *args[]={"./exec", NULL};
        execvp(args[0],args);

        printf("task_1 finished-----");
    	return 0;
}