#include <stdio.h>
#include <unistd.h> // dup, dup2
#include <fcntl.h>
/*
 * dup2() more control than dup
 * prototype: int dup2(int oldfd, int newfd);
 * duplicates  oldfd into newfd
 * if newfd is already open, it is closed first
 * if oldfd == newfd, it just returns nrefd
*/
void main()
{
    int fd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    dup2(fd, STDOUT_FILENO);    // Redirect stdout to log.txt
    close(fd); // fd no longer needed

    printf("this msg will print in file.txt because we duplicate the output to it");
}