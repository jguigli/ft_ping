#include "../includes/ft_ping.h"

int sendData(t_main *main)
{
	struct sockaddr_in dest_addr;

	memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = 0;
	dest_addr.sin_addr = main->s_address;

	memset(main->packet, 0, PACKET_SIZE);
    struct icmphdr *icmp_header = (struct icmphdr *)main->packet;
    icmp_header->type = ICMP_ECHO;
    icmp_header->code = 0;
    icmp_header->checksum = 0;

	ssize_t bytes_sent = sendto(sockfd, main->packet, PACKET_SIZE, 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
    if (bytes_sent < 0) {
        perror("Erreur lors de l'envoi du paquet ICMP");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("FT_PING %s (%s): %d data bytes\n", main->address, main->newAddress);

    close(sockfd);

	return 0;
}