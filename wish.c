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
    FILE *input = stdin;
    int batch_mode = 0; //Boolean
    
    //Batch mode
    if(argc == 2){
        batch_mode = 1;
        input = fopen(argv[1], "r");

        if(input == NULL){
            fprintf(stderr, "File not found\n");
            exit(1);
        }
    }

    while(1){
        char *args[MAX_ARGS] = {NULL};
        if(!batch_mode){
            printf("%s", prompt);
            fflush(stdout);
        }
        nread = getline(&line, &size, input);
        if(nread == -1){
            exit(0);
        }

        //Break up line
        char *token, *line_copy;
        line_copy = line;
        const char *delim = "\t\n\v\f\r& ";    //Whitespace characters + '&' for special shell stuff
        for(int j = 0; token = strsep(&line_copy, delim);){
            if(*token != '\0'){
                args[j++] = token;  //Increment j here to avoid NULL gaps in the args[] array
            }
        }

        //This is so user can enter nothing and shell will just go to a newline
        if(args[0] == NULL) continue;

        //Check for built in commands first
        if(strcmp(args[0], "exit") == 0){
            printf("Goodbye!\n");
            exit(0);
        }

        else if(strcmp(args[0], "cd") == 0){
            const char *path = (args[1] == NULL || strcmp(args[1], "~") == 0) ? getenv("HOME") : args[1];

            int status = chdir(path);

            if(status == -1) printf("cd error\n");
        }

        //All other commmands
        else{
            //fork and exec in child process
            pid_t pid = fork();
            if(pid == 0){
                //Child process
                execvp(args[0], args);

                printf("error in child\n");
                exit(1);
            }

            else if(pid < 0){
                printf("fork() error\n");
            }
            else
                wait(NULL);
        }
    }

    return 0;
}