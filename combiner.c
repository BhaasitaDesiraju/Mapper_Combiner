//#include <stdio.h>
//#include <stdlib.h>
//#include <fcntl.h>
//
//#include <sys/types.h>
//#include <sys/wait.h>
//
//
//int main(int argc, char const *argv[])
//{
//    int pipefd[2];
//    pid_t pid;
//
//    pipe(pipefd);
//
//
//    pid=fork();
//
//    if (pid == 0){
//        dup2(pipefd[1],1);
//        close(pipefd[0]);
//        execlp("./mapper","./mapper",NULL);
//    }
//    else if(pid == -1) printf("Fork Failed");
//
//    else {
//
//        // printf("Started Child: %d\n",pid);
//        pid=fork();
//
//        if (pid == 0){
//            dup2(pipefd[0],0);
//            close(pipefd[1]);
//            execlp("./reducer","./reducer",NULL);
//        } 	else if(pid == -1) printf("Fork Failed");
//        else {
//            close(pipefd[0]);
//            close(pipefd[1]);
//            wait(NULL);
//            wait(NULL);
//        }
//
//    }
//
//    return 0;
//}