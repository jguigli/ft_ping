#include "../includes/ft_ping.h"

unsigned short calculate_checksum(unsigned short *addr, int len) {
    unsigned int sum = 0;
    unsigned short answer = 0;

    while (len > 1) {
        sum += *addr++;
        len -= 2;
    }

    if (len == 1) {
        *(unsigned char *)&answer = *(unsigned char *)addr;
        sum += answer;
    }

    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    answer = ~sum;

    return answer;
}

int sendData(t_main *main)
{
	struct sockaddr_in  dest_addr;
    pid_t               pid_nb = getpid();


	memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
	dest_addr.sin_addr = main->s_address;

	memset(main->packet, 0, PACKET_SIZE);
    struct icmphdr *icmp_header = (struct icmphdr *)(main->packet);

    icmp_header->type = ICMP_ECHO;
    icmp_header->code = 0;
    icmp_header->un.echo.id = htons(pid_nb);
    icmp_header->un.echo.sequence = main->packet_t++;
    icmp_header->checksum = calculate_checksum((unsigned short *)icmp_header, sizeof(struct icmphdr));

    // struct timeval *timestamp = (struct timeval *)(main->packet + sizeof(struct icmphdr));
    // timestamp->tv_sec = main->start_time.tv_sec;
    // timestamp->tv_usec = main->start_time.tv_usec;

	ssize_t bytes_sent = sendto(sockfd, main->packet, PACKET_SIZE, 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
    if (bytes_sent < 0)
    {
        perror("sendto");
        return -1;
    }
    gettimeofday(&main->start_time, NULL);

	return 0;
}