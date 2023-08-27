#include "../includes/ft_ping.h"

int setData(t_main *main, char **argv)
{
	(void)argv;
	(void)main;
	struct timeval tv_out;
    tv_out.tv_sec = RECV_TIMEOUT;
    tv_out.tv_usec = 0;

    if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
    {
        fprintf(stderr, "%s: socket failed: %s\n", PROGRAM, strerror(errno));
        return -1;
    }

	if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv_out, sizeof (tv_out)) < 0) // gere le timeout
    {
        perror("setsockopt()");
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

	printf("FT_PING %s (%s): %d data bytes\n", main.address, main.newAddress, 56);
	while (sockfd)
	{
		sendData(&main);
		receiveData(&main);
		usleep(PING_SLEEP); // Changer la valeur
	}
	printf("--- %s ping statistics ---\n", main.newAddress);
    printf("%d packets transmitted, %d packets received, %.f%% packet loss\n", main.packet_t, main.packet_r, ((main.packet_t - main.packet_r)/main.packet_t) * 100.0);
	if (main.packet_r > 0)
		printf("round-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n", main.min, (main.avg / main.packet_r), main.max, main.stddev);
	return 0;
}