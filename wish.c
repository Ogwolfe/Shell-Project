//  Wish shell
//  By: Jason Wolfe

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_ARGS 64

int main(int argc, char **argv){

    char *prompt = "wish> ";
    char *line = NULL;
    char *command = NULL;
    size_t size = 0;
    ssize_t nread;

    while(1){
        char *args[MAX_ARGS] = {NULL};
        printf("%s", prompt);
        nread = getline(&line, &size, stdin);
        if(nread == -1){
            printf("\n");
            exit(0);
        }

        //Break up line
        char *token, *line_copy;
        line_copy = line;
        const char *delim = "\t\n\v\f\r ";    //Whitespace characters
        for(int j = 0; token = strsep(&line_copy, delim); j++){
            if(*token != '\0')
                args[j] = token;
        }


        if(strcmp(args[0], "exit") == 0){
            printf("Goodbye!\n");
            exit(0);
        }

        //TO-DO: Don't check for just ls. Break line into tokens and check first token for line and the rest for args.
        if(strcmp(args[0], "ls") == 0){
            //fork and exec in child process
            pid_t pid = fork();
            if(pid == 0){
                //Child process
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
        else{
            for(int i = 0; args[i]; i++){
                printf("%s ", args[i]);
            }
            printf("\n");
        }
    }

    return 0;
}