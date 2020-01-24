#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char const *argv[])
{
    int fileDesc[2];
    pid_t processId;

    pipe(fileDesc);
    processId=fork();

    if (processId == 0){
        int mapperOutput = open("output.txt",O_WRONLY | O_APPEND);
        dup2(fileDesc[1],mapperOutput);
        close(fileDesc[0]);
        execlp("./mapper","./mapper",NULL);
    }
    else if(processId == -1)
        printf("Unable to fork");

    else {
        processId=fork();

        if (processId == 0){
            dup2(fileDesc[0],0);
            close(fileDesc[1]);
            execlp("./reducer","./reducer",NULL);
        }     else if(processId == -1)
            printf("Unable to fork");
        else {
            close(fileDesc[0]);
            close(fileDesc[1]);
            wait(NULL);
            wait(NULL);
        }

    }

    return 0;
}
