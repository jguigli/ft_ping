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
    
    struct in_addr  test;

    inet_pton(AF_INET, "127.0.0.1", &test);

    struct ip *ip_header = (struct ip *)main->packet;
    struct icmphdr *icmp_header = (struct icmphdr *)(main->packet + sizeof(struct ip));

    ip_header->ip_hl = 5;
    ip_header->ip_v = 4;
    ip_header->ip_tos = 0;
    ip_header->ip_len = sizeof(struct ip) + sizeof(struct icmphdr);
    ip_header->ip_id = htons(pid_nb);
    ip_header->ip_off = 0;
    ip_header->ip_ttl = 64;
    ip_header->ip_p = IPPROTO_ICMP;
    ip_header->ip_sum = 0;
    ip_header->ip_src = test;
    ip_header->ip_dst = main->s_address;

    icmp_header->type = 8;
    icmp_header->code = 0;
    icmp_header->un.echo.id = htons(pid_nb);
    icmp_header->un.echo.sequence = 0;
    icmp_header->checksum = calculate_checksum((unsigned short *)icmp_header, sizeof(struct icmphdr));

	ssize_t bytes_sent = sendto(sockfd, main->packet, PACKET_SIZE, 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
    if (bytes_sent < 0)
    {
        perror("Erreur lors de l'envoi du paquet ICMP");
        return -1;
    }
    main->packet_t++;

    printf("FT_PING %s (%s): %d data bytes\n", main->address, main->newAddress, 56);

	return 0;
}