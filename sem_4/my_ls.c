#include <stdio.h>
#include <dirent.h>
#include <string.h>

void Usage() {
    fprintf(stderr, "\nUsage: exec [OPTION]... [DIR]...\n");
    fprintf(stderr, "List DIR's (directory) contents\n");
    fprintf(stderr, "\nOptions\n-R\tlist subdirectories recursively\n");
    return;
}

void RecDir(char * path, int flag) {
    DIR * dp = opendir(path);
    if(!dp) {
        perror(path);
        return;
    }
    struct dirent * ep;
    char newdir[512];
    while((ep = readdir(dp)))
        if(strncmp(ep->d_name, ".", 1))
            printf("%s\t", ep->d_name);
    closedir(dp);
    dp = opendir(path);
    while((ep = readdir(dp))) if(strncmp(ep->d_name, ".", 1)) {
        if(flag && ep->d_type == 4) {
            sprintf(newdir, "%s/%s", path, ep->d_name);
            RecDir(newdir, 1);
        }
    }
    printf("\n");
    closedir(dp);
}

int main(int argc, char ** argv) {
    if (argc <= 1) {
        RecDir(".", 0);
    }
    else {
        RecDir(argv[1], 0);
    }
    /*switch(argc) {
    case 1:
        
    case 2:
        if(strcmp(argv[1], "-R") == 0) Usage();
        else RecDir(argv[1], 0);
        break;
    case 3:
        if(strcmp(argv[1], "-R") == 0) RecDir(argv[2], 1);
        else Usage();
        break;
    default: Usage();
    }*/
    return 0;
}