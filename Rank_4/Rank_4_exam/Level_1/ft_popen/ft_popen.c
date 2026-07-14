#include <unistd.h>
#include <stdlib.h>

int	ft_popen(const char *file, char *const argv[], char type)
{
	int		fd[2];
	pid_t	pid;

	if ((type != 'r' && type != 'w') || pipe(fd) == -1)        // we will Read or Write     //     if pipe(fd) isn't successfull --> ERROR
		return (-1);
	pid = fork();             //  create a child 👶        
	if (pid == -1)				// if 👶 isn't successfull --> ERROR
		return (-1);
	if (pid == 0)       // 👶
	{
		if (type == 'r')
		{
			close(fd[0]);
			dup2(fd[1], 1);
		}
		else
		{
			close(fd[1]);
			dup2(fd[0], 0);
		}
		close(fd[0]);
		close(fd[1]);
		execvp(file, argv);
		exit(1);
	}
	if (type == 'r')
	{
		close(fd[1]);
		return (fd[0]);
	}
	close(fd[0]);
	return (fd[1]);
}



// ----------------------------------------------------------------------------
// MAIN for a test:
#include <stdio.h>
int main(void)
{
	int  fd;
	char buf[100];
	int  n;

	fd = ft_popen("echo", (char *[]){"echo", "hello", NULL}, 'r');
	n = read(fd, buf, 99);
	buf[n] = 0;
	printf("%s", buf);
	return 0;
}