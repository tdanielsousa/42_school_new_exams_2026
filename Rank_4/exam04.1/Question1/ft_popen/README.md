# Process

## Process ID and Parent Process ID

ID (PID), a positive integer that uniquely identifies the process on the system. Process IDs are used and returned by a variety of system calls. For example, the kill() system call (Section 20.5) allows the caller to send a signal to a process with a specific process ID.

Use /proc/sys/kernel/pid_max file - to find the max number of processes.

Each process has a parent—the process that created it. A process can find out the process ID of its parent using the getppid() system call. The parent of each process has its own parent, and so on, going all the way back to process 1, init, the ancestor of all processes. Use command pstree - to see processes tree.
If a child process becomes orphaned because its “birth” parent terminates, then the child is adopted by the init process, and subsequent calls to getppid() in the child return 1.

## Memory Layout of a Process

The **text segment** contains the machine-language instructions of the program run by the process.
The **initialized data segment** contains global and static variables that are explicitly initialized.
The **uninitialized data segment** (zero-initialized data segment) contains global and static variables that are not explicitly initialized. Before starting the program, the system initializes all memory in this segment to 0.
The **stack** is a dynamically growing and shrinking segment containing stack frames. One stack frame is allocated for each currently called function.
The **heap** is an area from which memory (for variables) can be dynamically allocated at run time. The top end of the heap is called the **program break.**

### **Virtual memory Management**

Like most modern kernels, Linux employs a technique known as virtual memory management. The aim of this technique is to make efficient use of both the CPU and RAM (physical memory) by exploiting a property that is typical of most programs:
locality of reference.

Locality of reference is a principle in computer science stating that data items accessed together in time tend to be located close together in memory. Spatial locality is the tendency of a program to reference memory addresses that are near those that were recently accessed (because of sequential processing of instructions, and, sometimes, sequential processing of data structures). Temporal locality is the tendency of a program to access the same memory addresses in the near future that it accessed in the recent past (because of loops).

![screenshot.png](https://prod-files-secure.s3.us-west-2.amazonaws.com/691c7232-2274-4418-afd9-98a004db7e97/fd8e6eae-6820-48d7-b1b3-99d0fa2ed502/%D0%A1%D0%BD%D0%B8%D0%BC%D0%BE%D0%BA_%D1%8D%D0%BA%D1%80%D0%B0%D0%BD%D0%B0_%D0%BE%D1%82_2024-04-06_09-10-46.png)

The upshot of locality of reference is that it is possible to execute a program while maintaining only part of its address space in RAM. A virtual memory scheme splits the memory used by each program into small, fixed-size units called **pages**. Correspondingly, RAM is divided into a series of page frames of the same size. These pages form r**esident set**: this refers to the pages of a program that are currently loaded into physical memory (RAM)

**Swap Area** is a reserved space on the hard disk used as an extension of RAM. When physical memory (RAM) is full, pages that are not currently needed are stored in the swap area to free up space in RAM.

In order to support this organization, the kernel maintains a page table for each process. The page table describes the location of each page in the process’s virtual address space (the set of all virtual memory pages available to the process).
When a process references a page that is not currently resident in physical memory, a page fault occurs, at which point the kernel suspends execution of the process while the page is loaded from disk into memory.

If a process tries to access an address for which there is no corresponding page-table entry, it receives a **SIGSEGV signal**.

### HOW TO IMPLEMENT 42'S ft_popen

#### Functions to maintain exam: pipe(), fork(), waitpid(), close(), dup(), dup2()

1. `pipe(fd)`takes a single argument, which is an array of two integers, and if successful, the array will contain two new file descriptors to be used for the pipeline. Remember that an array name in C *decays* into a pointer to its first member.  So, fd is equivalent to &fd[0].
`fd[0] is set up for reading, fd[1] is set up for writing`
2. `fork` creates the child process. In the parent process, `fork` returns the process ID of the newly created child process.
In the child process, `fork` returns `0`. A new child process is an exact copy of the parent process (except for a few differences like the return value of `fork` and the process ID). In the parent process, `pid1` is set to the process ID of the child process returned by `fork`. Hence, `pid1` represents the child process. In the child process, `pid1` remains unset (since it only happens in the parent process). Instead, `pid1` is `0`, which indicates that it's the child process.
Once the pipeline has been established, the file descriptors may be treated like descriptors to normal files.
3. `close()` frees up system resources associated with the file and informs the operating system that you no longer need access to the file. After that the freed resources can be reused.
If the parent wants to receive data from the child, it should close fd1, and the child should close fd0. If the parent wants to send data to the child, it should close fd0, and the child should close fd1. Since descriptors are shared between the parent and child, we should always be sure to close the end of pipe we aren't concerned with. On a technical note, the EOF will never be returned if the unnecessary ends of the pipe are not explicitly closed.
4. The  dup()  system  call  allocates a new file descriptor that refers to the same open file description as the descriptor oldfd. (For an explanation of open file descriptions, see open(2).)  The new file descriptor number is guaranteed to be the lowest-numbered file descriptor  that  was  unused  in  the  calling process. After a successful return, the old and new file descriptors may be used interchangeably.  Since the two file descriptors refer to the same open file description,  they share file offset and file status flags; For example, `dup(fd[0])` duplicates `fd[0]`, which is the read end of the pipe. `stdin` (file descriptor 0) should be previously closed, then the next available lowest-numbered file descriptor will be `0`. As a result, `fd[0]` takes over the role of `stdin`. Any read operations on `stdin` (`0`) will now be directed to the pipe instead of the original standard input (e.g., keyboard input).
5. `waitpid(pid1, NULL, 0)` waiting for the child process (identified by `pid1`) to terminate, not the parent process. The `waitpid` function waits for the process specified by the first argument (in this case, the child process) to change state.
6. `dup2` system call performs the same task as dup(), but instead of using the lowest-numbered unused file descriptor, it uses the file descriptor number specified in newfd. In other words, the file descriptor newfd is adjusted so that it now refers to the same open file description as oldfd. If the file descriptor newfd was previously open, it is closed before being reused; the close is performed silently (i.e., any errors during  the  close are not reported by dup2()).

The steps of closing and reusing the file descriptor newfd are performed atomically. dup2() doesn't switch the file descriptors, it makes them equivalent. After `dup2(f1, 0)`, whatever file was opened on descriptor `f1` is now also opened (with the same mode and position) on descriptor 0, i.e. on standard input.

### INTER-PROCESS COMMUNICATION

Two types are specified - read and write.

	In child process type == 'r' means that the parent wants to read from the child process's output. In other words:
	The child will run a program that writes to stdout
	The parent will receive that output through a pipe

	So we want to connect the child’s stdout to the pipe, and have the parent read from it.

	type 'w' means that parent process wants to write to a child process's input.
	In other words:
	The child will run a program that read from stdin
	The parent will send the input to stdin throught a pipe


