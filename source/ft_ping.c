#include "../includes/ft_ping.h"

int setData(t_main *main, char **argv)
{
	(void)main;
	(void)argv;
	int on;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_ICMP)) < 0)
    {
        fprintf(stderr, "%s: socket failed: %s\n", PROGRAM, strerror(errno));
        return -1;
    }

	if (setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on)) < 0) // PAS SUR 
    {
        perror("setsockopt() for IP_HDRINCL error");
        exit(EXIT_FAILURE);
    }

    return 0;
}


int ft_ping(int argc, char **argv)
{
	t_main	main = {0};

	if (handleInput(argc, argv, &main) == -1)
		return 1;
	if (setData(&main, argv) == -1)
		return 1;

	while (1)
	{
		
	}
	
	return 0;
}