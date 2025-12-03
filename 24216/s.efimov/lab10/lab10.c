#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    if (argc < 2){
        perror("Few arguments\n");
        exit(EXIT_FAILURE);
    }

    int status;
    pid_t parent = fork();

    switch (parent){
        case -1: 
            perror("Failed to fork process\n");
            exit(EXIT_FAILURE);
        case 0 :
            execvp(argv[1], &argv[1]);
            perror("Failed execvp\n");
            exit(EXIT_FAILURE);

        default:
            pid_t child = wait(&status);
            if (child == -1) {
                perror("Failed to wait\n");
                exit(EXIT_FAILURE);
            }
            if(WIFEXITED(status)){
                printf("process ended with code %d\n", WEXITSTATUS(status));
            }
            else{
                printf("process ended with code %d\n", WTERMSIG(status));
            }
    }
    exit(EXIT_SUCCESS);
}