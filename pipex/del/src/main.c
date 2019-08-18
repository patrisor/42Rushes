/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 15:14:41 by vbrazas           #+#    #+#             */
/*   Updated: 2019/08/18 13:55:25 by patrisor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

// Prints the usages for you
int				put_usage(const int errnum)
{
	char		*errstr;

	(errnum == 0) ? errstr = strerror(errno) : false;
	(errnum == 1) ? errstr = "Too less arguments" : false;
	(errnum == 2) ? errstr = "Cannot find binary of the given command" : false;
	(errnum == 3) ? errstr = "ft_strjoin fail" : false;
	ft_printf("ERROR: %s\n\n%s\n", errstr, \
	"Usage: ./pipex file1 cmd1 cmd2 file2");
	exit(1);
	return (1);
}

// Dereference every file descriptor AND exit every child process 
static	void	closer(t_pip *p)
{
	// Dereference every file descriptor 
	(close(p->fd[0][0]) == -1) ? put_usage(0) : false;
	(close(p->fd[0][1]) == -1) ? put_usage(0) : false;
	(close(p->fd[1][0]) == -1) ? put_usage(0) : false;
	(close(p->fd[1][1]) == -1) ? put_usage(0) : false;
	// A call to wait() blocks the calling process until one of its child processes exits or a signal is received
	while (wait(NULL) > 0)
		;
}

// Create a fork for each system call, then redirect 2 file descriptors to stdin and stdout (close the opposite 2)
// Execute the system call at the end
static	void	performfork(t_pip *p, int i, char **av, char **env)
{
	static char			**cmd_arr;

	// Creates a command array -> from "ls -l" into ["/usr/bin/ls","-l"]
	cmd_arr = get_cmd_arr(av[2 + i], p);

	// Create a child process based on each individual system command
	((p->pid = fork()) == -1) ? put_usage(0) : false;
	if (p->pid == 0)
	{
		// system call creates a copy of the old file descriptor (p->fd[i][0]) to be
		// the new file descriptor, 0, or stdin. (Redirection)
		(dup2(p->fd[i][0], 0) == -1) ? put_usage(0) : false;
		// system call creates a copy of the old file descriptor to be the new fd, 1, or stdout.
		(dup2(p->fd[i][1], 1) == -1) ? put_usage(0) : false;
		// Close the opposite file descriptors (if i == 0), then close(p->fd[1][0]) is executed
		(close(p->fd[!(i % 2)][0]) == -1) ? put_usage(0) : false;
		(close(p->fd[!(i % 2)][1]) == -1) ? put_usage(0) : false;
		// Executes the forked system command
		(execve(cmd_arr[0], cmd_arr, env) == -1) ? put_usage(0) : false;
	}
}

int				main(int ac, char **av, char **env)
{
	// Create a structure of the pipe
	t_pip			p;

	// If (ac < 5) then prints "Too less arguments"; else return false
	(ac < 5) ? put_usage(1) : false;
	// Pipe function (#unistd.h) creates a pipe, a unidirectional data channel that can be used for interprocess communication
	// https://linux.die.net/man/2/pipe
	// Returns two file descriptors referring to the ends of the pipe. 
	// - pipefd[0] refers to the read end of the pipe. 
	// - pipefd[1] refers to the write end of the pipe
	// If that doesn't work, then it prints error message from errno
	(pipe(p.pair) == -1) ? put_usage(0) : false;
	// STORE 4 file descriptors 
	// First file is a file with bytes already stored inside
	p.fd[0][0] = open(av[1], O_RDONLY);
	// Data written to the write end of the pipe is buffered by the kernel until it is read from the read end of the pipe.
	// Second descriptor is the WRITE-END channel from the pipe
	p.fd[0][1] = p.pair[1];
	// Third Descriptor is the READ-END channel from the pipe
	p.fd[1][0] = p.pair[0];
	// In order to open a new file for writing, you should open it with (O_WRONLY | O_CREAT | O_TRUNC) as the flags argument
	// O_CREATE says to create the file if it doesn't exist already.
	// O_TRUNC say that if the file does exist, to "truncate" it to zero bytes, erasing what was there.
	// 0644 (t_mode) sets the "-rw-r--r--" permissions for the new file
	p.fd[1][1] = open(av[4], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	// If that doesn't work, then it prints error message from errno
	(p.fd[0][0] == -1 || p.fd[1][1] == -1) ? put_usage(0) : false;
	// Grabs list of Environmental Variables and returns the "PATH=" String.
	p.path = get_path(env);
	// Create a fork for each system call, then redirect 2 file descriptors to stdin and stdout, then run
	performfork(&p, 0, av, env);
	// Create a fork for each system call, then redirect 2 file descriptors to stdin and stdout, then run 
	performfork(&p, 1, av, env);
	// Dereference every file descriptor AND exit every child process
	closer(&p);
	return (0);
}
