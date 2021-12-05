#include <pipex.h>

void	heredoc(t_commands *command)
{
	// ./pipex here\_doc LIMITADOR comando comando1 archivo
	//la entrada va a ser stdin, entonces no la cmabiamos
	printf("---> LIMITADOR %s\n", command->argv[2][0]);
}
