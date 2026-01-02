//  Wish shell
//  By: Jason Wolfe

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char **argv){

    char *prompt = "wish> ";
    char *command = NULL;
    size_t size = 0;
    ssize_t nread;

    while(1){
        printf("%s", prompt);
        nread = getline(&command, &size, stdin);
        if(nread == -1){
            printf("\n");
            exit(0);
        }

        if(strcmp(command, "ls\n") == 0){
            //fork and exec in child process
            pid_t pid = fork();
            if(pid == 0){
                //Child process
                char *args[] = {"ls", NULL};
                execvp("ls", args);

                printf("error in child\n");
                exit(1);
            }

            else if(pid < 0){
                printf("fork() error\n");
            }
            else
                wait(NULL);
        }
        else
            printf("%s", command);
    }

    return 0;
}