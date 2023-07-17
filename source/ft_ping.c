#include "../includes/ft_ping.h"

int ft_ping(int argc, char **argv)
{
	t_main	main = {0};


	if (handleErrorInput(argc, argv, &main))
		return 1;
	
	return 0;
}