#### HOW TO IMPLEMENT 42'S PICOSHELL

The **cmds[] array is used to store multiple commands separated by the pipe symbol (|) in the shell command passed to the program.

Example Command:

./picoshell /bin/ls "|" /usr/bin/grep picoshell

1. Parse arguments:

        argc is the number of arguments passed to the program (in this case, 5 arguments).
        argv is an array of strings representing the arguments (in this case, it contains ./picoshell, /bin/ls, "|", /usr/bin/grep, and picoshell).

    1.2. Determine cmds_size:

            The program needs to figure out how many individual commands there are based on the number of pipes (|).
            For each pipe (|) found in argv, the cmds_size is incremented by 1.
            In this case, there's 1 pipe (|), so cmds_size will be 2.

    1.3. Allocate Memory for cmds:

            cmds_size + 1 pointers to char** are allocated using calloc, which means cmds will be an array of pointers to arrays of strings.
            cmds will be used to store individual commands. Each command (e.g., /bin/ls) will be a sub-array of argv.

    1.4.    Initialize cmds[0]:

            cmds[0] = argv + 1; points cmds[0] to argv + 1, which is the first command after the program name (./picoshell).
            So, cmds[0] will point to argv[1] (i.e., /bin/ls), which is the first command.
            Populate cmds for Pipe-Separated Commands:
            The loop goes through argv to check for the pipe symbol (|).
            Whenever it finds a pipe, it splits the commands into different groups by updating the cmds array.
            The array cmds[1] will point to /usr/bin/grep (which follows the pipe |), and cmds[2] will point to picoshell.
            The argv[i] value is set to NULL to terminate the first part of the command (i.e., argv[i] = NULL).

    Visualization of cmds Initialization:

    Given the example ./picoshell /bin/ls "|" /usr/bin/grep picoshell, after execution of the program, the cmds array will look like this:

    cmds[0] -> { "/bin/ls", NULL }
    cmds[1] -> { "/usr/bin/grep", "picoshell", NULL }
    cmds[2] -> { NULL }

2. Count the number of commands

    We already have cmds set up as an array of char **, where:

    cmds[0] is the first command
    cmds[1] is the second, and so on
    cmds[n] == NULL indicates the end

    So we'll first determine how many commands there are by counting until cmds[i] == NULL.

3. Loop through the commands and fork for each command:

    Create a new pipe before forking, except for the last command (it doesn't need to pipe anything out).
    Fork a child process.

4. Duplicate fds to STDIN or STDOUT depends on the number of command.

In each child process:

    If it's not the first command:
        Redirect stdin to read from the previous pipe’s read end.

    If it's not the last command:
        Redirect stdout to write to the current pipe’s write end.

    Close any unused file descriptors.
    Execute commands.

    cmd1:   STDOUT  → fds[0][1]
    cmd2:   STDIN   ← fds[0][0], 
            STDOUT  → fds[1][1]
    cmd3:   STDIN   ← fds[1][0]

5. Close unused pipe file descriptors:

    Close all unused pipe ends.
    Close the original used FD after dup2().
   
6. Execute the commands with execvp:
        Each element in cmds is a char ** — exactly what execvp wants as its second argument.
        So for our commands:
        🔹 First command (cmds[0])

        execvp(cmds[0][0], cmds[0]);
            -> execvp("/bin/ls", (char *[]){ "/bin/ls", NULL });

        🔹 Second command (cmds[1])

        execvp(cmds[1][0], cmds[1]);
            -> execvp("/usr/bin/grep", (char *[]){ "/usr/bin/grep", "picoshell", NULL });

5. In the parent process:

    After forking each child, close the pipe ends that are no longer needed:
    You don’t want to hold on to pipe ends in the parent; it can cause hangs due to open file descriptors.
    Save the read end of the current pipe to use in the next iteration as the previous pipe's read end.
    Optionally store child PIDs to wait() for them later.

5. After the loop:

    In the parent, call wait() for all the child processes to finish.

🧠 Notes:

    You’ll need n - 1 pipes for n commands.
    Only the child processes should call execvp, and only after doing redirection.
    Use dup2() to redirect stdin/stdout to the pipe ends.

#### DEBUGGING

1. Verify open file desriptors with /proc/<pid>/fd on Linux

    Run the program:
    ./pico sort "|" uniq &

    Then find the PID of the parent process:
    ps aux | grep pico

    Then find the PID of the chil process:
    ps --ppid <parent pid>> -o pid,ppid,cmd

    Then:
    ps --ppid <child pid> -o pid,ppid,cmd

    Then:
    ls -l /proc/<child pid>/fd

    Output should look like:
    0 -> /dev/pts/0
    1 -> /dev/pts/0
    2 -> /dev/pts/0
    3 -> pipe:[123456]

    If there is still pipe FDs (3, 4, etc.), something's not closed.

2. Verify zobmy processes:

    Run the program:
    ./pico ls "|" wc -l

    In another terminal, check for zombies with:
    ps -eo pid,ppid,state,cmd | grep pico

    If there is a Z next to one of the processes, it means shell isn’t reaping that child.