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

Okay so I've been checking for each command manually by comparing the first token with each of the commands I was going to do.
But I'm thinking now that I can allow the shell to execute almost any command by only checking for built in commands and if it's
not one of those then I just exec() whatever it might be. exec() will handle all that and print errors to if the command doesn't exist.
Then I only need to check for a smaller subset of built ins and not branch for all commands.

Ok I want to work on the path command. So I'm going to keep a fixed length array of like 50 char *'s and use that to store the strings for paths.
I'll init the shell on start with just /bin. Then I'll add a built in command for "path" that assigns new path variables to the path.
I can check that the hard cap isn't hit and just set a new string equal to the input and set that into the array.

I'll loop through the strings in the path array and pass them to access() and check for execute permissions with the X_OK flag.

Now for the redirection functionality. I think it should be easy. I can think of it as at the moment the output for the shell is just stdout.
But I can change that to whatever FILE* I want. I just need to detect the '>'. So I'll parse the arg's array and look for the '>' and
while I'm at it I know I'll also need to look for the '&' for the parallel commands. 