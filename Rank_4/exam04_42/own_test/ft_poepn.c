# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

int	ft_popen(const char *file, char *const argv[], char type)
{
    int fds[2];
    
    if (!file || !argv || (type != 'w' && type != 'r'))
        return -1;

    pipe(fds);
    if (type == 'r')
    {
        if (fork() == 0)
        {
            close(fds[0]);
            dup2(fds[1], 1);
            close(fds[1]);
            execvp(file, argv);
            exit(-1);
        }
        close(fds[1]);
        return fds[0];
    }
    else {
        if (fork() == 0)
        {
            close(fds[1]);
            dup2(fds[0], 0);
            close(fds[0]);
            execvp(file, argv);
            exit(-1);
        }
        close(fds[0]);
        return fds[1];
    }
}


char	*get_next_line(int fd)
{
	char	*ret = malloc(9999);
	char	c;
	int		i = 0;
	int		cpt = 0;

	if (fd < 0)
		return (NULL);
	while ((cpt = read(fd, &c, 1)) > 0)
	{
		ret[i] = c;
		i++;
		if (c == '\n')
			break ;
	}
	if (i == 0 || cpt < 0)
	{
		free(ret);
		return (NULL);
	}
	ret[i] = '\0';
	return (ret);
}


void ft_putstr(const char *s)
{
	if (!s)
		return;
	while (*s)
		write(STDOUT_FILENO, s++, 1);
}
int main() {
	int fd = ft_popen("ls", (char *const[]){"ls", NULL}, 'r');

	char *line;
	while(line = get_next_line(fd))
		ft_putstr(line);

    int fd2 = ft_popen("cat", (char *const[]){"cat", NULL}, 'w');
    write(fd2, "hello\n", 6);
}