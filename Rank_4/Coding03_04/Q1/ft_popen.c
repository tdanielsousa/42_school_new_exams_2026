/* Allowed functions: pipe, fork, dup2, execvp, close, exit

write the following function:
	
	int	ft_popen(const char *file, char *const argv[], char type)

The function must launch the executable file with the arguments argv (using execvp).
If the type is 'r' the function must return a file descriptor connected to the output of the command.
If the type is 'w' the function must return a file descriptor connected to the input of the command.
In case of error or invalid parameter the function must return -1.

example:

int main() {
	int fd = ft_popen("ls", (char *const[]){"ls", NULL}, 'r');

	char *line;
	while(line = get_next_line(fd))
		ft_putstr(line);
}

Hint: Do not leak file descriptors! */

#include <unistd.h>
#include <stdlib.h>

int	ft_popen(const char *file, char *const argv[], char type)
{
	if (!file || !argv || (type != 'r' && type != 'w'))
		return -1;

	int fd[2];
	int status;

	pipe(fd);
	if (type == 'r')
	{
		if (fork() == 0)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			execvp(file, argv);
			exit (-1);
		}
		close(fd[1]);
		return (fd[0]);
	}
	if (type == 'w')
	{
		if (fork() == 0)
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);
			execvp(file, argv);
			exit (-1);
		}
		close(fd[0]);
		return (fd[1]);
	}
	return -1;
}

/*
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

//test type 'r'
int main()
{
	//int fd = open("texte", O_RDONLY);
	int fd = ft_popen("ls", (char *const[]){"ls", NULL}, 'r');

	char buf[1];
	while(read(fd, buf, 1))
		write(1, buf, 1);

	close(fd);
	return (0);
} */

/* 
//test type 'w'
int main()
{
    int fd = ft_popen("wc", (char *const[]){"wc", NULL}, 'w');
	if (fd == -1)
	{
		perror("error ft_popen args");
		return (0);
	}

    char *input = "Hello world\nThis is a test\nthird line mofo\n";
    write(fd, input, strlen(input));
	

    close(fd);
	printf("after test\n");
    return (0);
} */