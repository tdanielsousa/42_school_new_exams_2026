#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int ft_popen(const char *file, char *const argv[], char type)
{
	int fd[2];
	pid_t pid;

	if (!file || !argv || (type!='r' && type!='w'))
		return -1;
	if (pipe(fd) ==-1)
		return -1;	
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return -1;
	}
	if (pid==0)
	{
		if (type=='r')
		{
			if (dup2(fd[1],1) = -1)
				exit(1);			
		}
		else
		{
			if (dup2(fd[0],0) = -1)
				exit(1);			
		}
		close(fd[0]);
		close(fd[1]);
		execvp(file,argv);
		exit(1);
	}
	else
	{
		if (type=='r')
		{
			close(fd[1]);
			return(fd[0]);
		}
		else
		{
			close(fd[0]);
			return(fd[1]);
		}
	}
}

#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	int fd;
	char *args_cat[] = {"cat", NULL};

	fd = ft_popen("cat", args_cat, 'w');
	if (fd == -1)
	{
		perror("ft_popen");
		return (1);
	}

	write(fd, "Hello from ft_popen!\n", 22);
	close(fd); // cat EOF alınca çıkar
	return (0);
}