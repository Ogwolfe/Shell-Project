Ok so first to just get some basic stuff going I want to get it printing the prompt and then just echo any user input until EOF and then exit.
So I'll do a while loop on getline() and printf() then repeat. If getline() sees EOF it returns -1.

Ok so this creates a basic setup of the core loop. Prompt > parse command > execute command > prompt
I'm just echoing the user input right now. So next maybe I'll try to implement the ls command very simply to start.

ls:
    So the ls command just prints the contents of the current directory. For the project they say that I'm not to implement the commands
    myself but just to call them using a sort of path like shells use to find the executable. Unless it's a built in command. But ls is not.

    So user types ls > shell creates a child process to execute command > wait for it to finish > prompt 
    From what I remember the basic pattern is fork() and then exec() the command in the child process.

    It would be good to get down some functionality here to break up the lines I'm grabbing into strings separated by whitespace.
    So if it's ls -a then I can get "ls" and "-a". Basically literally argc and argv for my shell. The project intro recommended checking out strsep()

    Ok I got a basic version of ls working. I just check if the command entered is exactly ls and then I fork and execvp from the child.
    Now I want to get the arguments and pass those. So I need to build a variable array of char *'s. 