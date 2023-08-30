#include "../includes/ft_ping.h"

int setData(t_main *main)
{
	// int	on = 0;
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
        perror("setsockopt() SO_RCVTIMEO");
        exit(EXIT_FAILURE);
    }

	// if (setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on)) < 0)
    // {
    //     perror("setsockopt() IP_HDRINCL");
    //     exit(EXIT_FAILURE);
    // }

	main->pid = getpid();

	ft_memset(&main->dest_addr, 0, sizeof(main->dest_addr));
    main->dest_addr.sin_family = AF_INET;
	main->dest_addr.sin_addr = main->s_address;


    return 0;
}


int ft_ping(int argc, char **argv)
{
	t_main	main = {0};

	if (handleInput(argc, argv, &main) == -1)
		return 1;
	if (setData(&main) == -1)
		return 1;

	if (main.verbose)
		printf("FT_PING %s (%s): %d data bytes, id 0x%04x = %d\n", main.address, main.newAddress, 56, htons(getpid()), getpid());
	else
		printf("FT_PING %s (%s): %d data bytes\n", main.address, main.newAddress, 56);
	
	while (sockfd)
	{
		sendData(&main);
		if (receiveData(&main) != 1)
		{
			if (sockfd)
				usleep(PING_SLEEP);
		}
	}
	printf("--- %s ping statistics ---\n", main.newAddress);
    printf("%d packets transmitted, %d packets received, %.f%% packet loss\n", main.packet_t, main.packet_r, ((main.packet_t - main.packet_r) / (double)main.packet_t) * 100.0);
	if (main.packet_r > 0)
	{
		double variance = (main.sq_sum / main.packet_r) - ((main.sum / main.packet_r) * (main.sum / main.packet_r));
		main.stddev = custom_sqrt(variance);
		printf("round-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n", main.min, (main.sum / main.packet_r), main.max, main.stddev);
	}
	return 0;
}