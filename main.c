#include "main.h"

int main(int argc, char *argv[]){
    __pid_t ch_pid;
    while(1){
        printf(":>");
        char buf[256];
        char *cargv[32];
        int iter = 0;
        for(int i = 0; i < 32; i++){
            cargv[i] = 0;
        }
        while(iter < 256){
            buf[iter] = fgetc(stdin);
            if(buf[iter] == '\n') {
                buf[iter] = 0;
                break;
            }
            iter++;
        }
        char tmpstr[256] = {'.','/', 0};
        cargv[0] = strcat(tmpstr, strtok(buf, " "));
        for(int i = 1; i < 32; i++){
            cargv[i] = strtok(NULL, " "); 
        }
        if(!strcmp("cd", buf)){
            chdir(cargv[1]);
            continue;
        } 
        if(!strcmp("quit", buf)) 
            exit(0);
        ch_pid = fork();
        if(!ch_pid){
            if(execvp(buf, cargv) == -1) 
                printf("cant start\n");
            exit(0);
        }
        int status;
        __pid_t tmpid = wait(&status);
        while(tmpid != ch_pid){
            printf("some another(%d) process was closed. Status %d \n", tmpid, status);
            //tmpid = wait(status);
            kill(ch_pid, SIGKILL);
        }
    }
    return 0;
}