## THE SANDBOX TASK PURPOSE

This task is about creating a sandbox environment to run functions in a controlled way and determining whether the function is "nice" or "bad." The idea is to isolate the function execution so that if it misbehaves (e.g., crashes, times out, or exits with an error), it does not affect the overall system.

### WHAT SANDBOX IS

In the computer field, sandboxing is a security mechanism that isolates running programs, such as untrusted processes or code, to restrict their access permissions. The virtual environment contains some virtual hardware and software resources, such as file systems, networks, and operating systems, to run applications or processes. A sandboxed program can access only the limited number of resources inside the sandbox, without affecting the external application, system, or platform. This prevents the program from permanently changing other programs or data in the computer. In the cybersecurity field, sandboxing isolates malicious files to identify unknown attacks.

Three technologies are involved in sandboxing: virtualization, access control, and anti-evasion.

Different Types of Sandboxing

There are multiple types of sandboxing, depending on the scope and level of isolation:

- Application sandboxing (isolating entire applications from the OS and other apps);
- Process sandboxing (running a single process in a restricted environment);
- Virtualization-based sandboxing	(using a virtual machine to isolate software);
- Malware analysis sandboxing	(running malware in a controlled environment to study its behavior);
- Container sandboxing	(isolating applications using OS-level virtualization).

The assignment of 42's sanbox.c is about process sandboxing. Instead of isolating an entire application, we are isolating a single function (process) inside a controlled environment.

What our sandbox does:

- Runs an unknown function (f()) inside a separate process.
- Monitors if the function crashes, times out, or exits incorrectly.
- Prevents bad functions from affecting the main program.
- Ensures that no zombie processes remain after execution.

This is similar to application sandboxing, but at a smaller scale (process level).

### RESRTRICTED ENVIRONMENT IN SANDOX

Restricted environment means limiting what a process (or function) can do to prevent it from causing harm to the system. This includes restricting its access to system resources, execution time, and interactions with other processes.

A restricted environment imposes rules and limitations on a process. These restrictions prevent the process from:
✅ Crashing the system (e.g., through segmentation faults).
✅ Accessing unauthorized files or memory.
✅ Making dangerous system calls (e.g., deleting files, modifying kernel memory).
✅ Running indefinitely (enforcing a timeout).
✅ Becoming a zombie process (proper cleanup after execution).

### HOW IS A PROCESS RESTRICTED

The function int sandbox() will isolate process and run the untrusted function inside a separate process (child) so it cannot affect the main program. Main program will monitor the run time of the untrusted function and kill the process if it runs too long. Main program will detect crashes if they happen and handle signals (e.g., segmentation faults, illegal instructions). Finally, main program will monitore the exit status of the untrusted function and prevent zombie processes.

### PLAN TO IMPEMENT A 42'S SANDBOX

🔹 Step 1: Process Isolation
    The function f() is executed in a child process (fork()), so if it crashes, it doesn’t affect the parent.

🔹 Step 2: Timeout Mechanism
    If the function runs for too long, alarm(timeout) ensures it is killed after timeout seconds.

🔹 Step 3: Signal Handling (Catching Crashes)
    If f() causes a segfault (SIGSEGV), abort (SIGABRT), or any other signal, the program will detect it using sigaction().

🔹 Step 4: Monitoring Exit Status
    waitpid() helps determine why the function terminated:
        Exited normally? (Nice function ✅)
        Exited with an error code? (Bad function ❌)
        Crashed due to a signal? (Bad function ❌)

🔹 Step 5: Preventing Zombie Processes
    Ensures that no orphaned child processes remain by correctly using waitpid().

#### SIGNALS HANDLING

More detailed information about signals is here: https://github.com/retiukhina/signals

When a process receives a signal, it is stored in the process's pending signal set inside the kernel until it is handled or ignored. The operating system manages signals using a combination of signal masks, pending signals, and process states.

How the Kernel Processes a Signal

    Signal Sent:

        A signal (e.g., SIGALRM) is sent via kill(), alarm(), etc.
        The kernel adds it to the processes's pending signal set in task_struct.
        Pending Signal Set (sigpending). This is a bitmask stored in the process’s 
        kernel structure. Each signal has a specific bit in this set.


    Check Blocked Signals:

        If the signal is blocked (e.g., with sigprocmask()), it stays in pending.
        If it is not blocked, the process handles it immediately.

    Signal is Delivered:

        If a handler exists (sigaction() was set), it executes the function.
        If no handler exists, the default action occurs (terminate, ignore, etc.).

    Signal is Removed from Pending List:

        Once handled, the signal disappears from pending.
        If it was blocked, it stays in pending until unblocked.

Signal sets in 42's sandbox:

1. sa.sa_mask in the sigaction structure:

    Purpose: This is used to specify which signals should be blocked while the signal handler (handle_alarm) is executing. In the case of sa.sa_mask, no signals are blocked during the handler by default, because it is initialized with sigemptyset(&sa.sa_mask).

    Use: When sigaction is called to set up a handler for SIGALRM, sa_mask controls what signals are blocked temporarily while the handler is running. However, in this case, the program doesn't block any signals during the execution of the handle_alarm function because the set is empty.

2. set used with sigprocmask:

    Purpose: This signal set (set) is used to block signals (SIGINT, SIGTERM) while the main program executes critical sections of code, such as managing the child process or performing operations like fork(), waitpid(), etc.

    Use: Specifically, set is used in combination with sigprocmask() to block SIGINT and SIGTERM so that the program doesn’t get interrupted by these signals during the critical section (e.g., child process management). After the critical section is completed, the signals are unblocked using sigprocmask(SIG_UNBLOCK, &set, NULL).

#### GLOBAL VARIABLE static volatile sig_atomic_t timeout_flag 

´static:´ This makes timeout_flag a local static variable, meaning it’s only visible within the file and retains its value across function calls. It's not destroyed when the function scope ends.

´volatile:´ This keyword tells the compiler that the value of timeout_flag can be changed outside the program's control, such as within a signal handler. This ensures that the compiler doesn’t optimize reads or writes to timeout_flag as it could be modified asynchronously by the signal handler.

´sig_atomic_t:´ Reading and writing this data type is guaranteed to happen in a single instruction, so there’s no way for a handler to run “in the middle” of an access. When signals are handled, the program may be interrupted at any point, and the signal handler may access or modify variables. Using sig_atomic_t ensures that modifications to the variable prevent inconsistencies when it is accessed by both the signal handler and the main program.
