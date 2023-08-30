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
    ft_memset(&main->packet, 0, PACKET_SIZE);
    // t_ping packet;
    // struct ip *ip_header = (struct ip *)(main->packet);

    // ip_header->ip_v = 4;             // Version IPv4
    // ip_header->ip_hl = 5;            // Longueur de l'en-tête en mots de 32 bits (5 mots = 20 octets)
    // ip_header->ip_tos = 0;           // Type of Service
    // ip_header->ip_len = sizeof(struct ip) + sizeof(struct icmphdr);   // Longueur totale du paquet (entête + données)
    // ip_header->ip_off = 0;           // Flags et offset de fragment (0 par défaut)
    // ip_header->ip_ttl = 64;          // Time to Live
    // ip_header->ip_p = IPPROTO_ICMP;  // Protocole ICMP
    // ip_header->ip_sum = 0;           // Somme de contrôle (sera calculée automatiquement)

    struct icmphdr *icmp_header = (struct icmphdr *)main->packet;

    icmp_header->type = ICMP_ECHO;
    icmp_header->code = 0;
    icmp_header->un.echo.id = htons(main->pid);
    icmp_header->un.echo.sequence = htons(main->packet_t++);
    icmp_header->checksum = 0;
    icmp_header->checksum = calculate_checksum((unsigned short *)icmp_header, sizeof(struct icmphdr));

    // ip_header->ip_sum = calculate_checksum((unsigned short *)ip_header, ip_header->ip_hl * 4);


	ssize_t bytes_sent = sendto(sockfd, &main->packet, PACKET_SIZE, 0, (struct sockaddr *)&main->dest_addr, sizeof(main->dest_addr));
    if (bytes_sent < 0)
    {
        perror("sendto");
        return -1;
    }
    printf("bytes sent = %ld\n", bytes_sent);
    gettimeofday(&main->start_time, NULL);

	return 0;
}