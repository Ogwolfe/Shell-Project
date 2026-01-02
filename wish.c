//  Wish shell
//  By: Jason Wolfe

#include <stdio.h>
#include <stdlib.h>

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
        printf("%s", command);
    }

    return 0;
}