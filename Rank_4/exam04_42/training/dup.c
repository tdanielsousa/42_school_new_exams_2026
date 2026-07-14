#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

/*
 * dup() is a system call that duplicates a file descriptor
 * prototype: int dup(int oldfd);   
 * it creates a copy of oldfd(like STDIN_FILENO, STDOUT_FILENO, etc)
 * Return: a new fd that refers to the same open file
 * both fds share:
    - the same file ofsset
    - the same file status flags(read/write)
    - they are different  entries in the fd table
*/
int main()
{
    int fd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644); 
    int copy = dup(STDOUT_FILENO);
    int copy_file = dup(fd);
    
    write(STDOUT_FILENO, "hello", 5);
    write(copy, " world\n", 7); // both STDOUT_FILENO and copy point to the same file, so the output witll contain hello world
    close(copy);

    write(fd, "hello", 5);
    write(copy_file, " world\n", 7); // the same like the previous example, here with the fd of file.txt
    close(fd);
    close(copy_file);

    return 0;
}