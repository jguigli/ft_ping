#include "../includes/ft_ping.h"

int receiveData(t_main *main)
{
	char packet[PACKET_SIZE];
    memset(packet, 0, PACKET_SIZE);

    struct iovec iov;
    iov.iov_base = packet;
    iov.iov_len = sizeof(packet);

    struct sockaddr_in sender_addr;
	sender_addr.sin_addr = main->s_address;

    struct msghdr msg;
    msg.msg_name = &sender_addr;
    msg.msg_namelen = sizeof(sender_addr);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = NULL;
    msg.msg_controllen = 0;
    msg.msg_flags = 0;

    ssize_t packet_len = recvmsg(sockfd, &msg, 0);
    if (packet_len == -1) {
        perror("recvmsg");
        return 1;
    }
    struct ip *ip_header = (struct ip *)packet;
    struct icmphdr *icmp_header = (struct icmphdr *)(packet + (ip_header->ip_hl * 4)); // Skip IP header

    if (icmp_header->type == ICMP_ECHOREPLY)
	{
		main->packet_r++;
        printf("Received ICMP Echo Reply\n");
        printf("Source IP: %s\n", inet_ntoa(ip_header->ip_src));
        printf("Destination IP: %s\n", inet_ntoa(ip_header->ip_dst));
        printf("Identifier: %d\n", ntohs(icmp_header->un.echo.id));
        printf("Sequence: %d\n", ntohs(icmp_header->un.echo.sequence));
    } else {
        printf("Received ICMP packet, but not an Echo Reply\n");

		printf("ip_header->ip_hl: %d\n", ip_header->ip_hl);
		printf("ip_header->ip_v: %d\n", ip_header->ip_v);
		printf("ip_header->ip_tos: %d\n", ip_header->ip_tos);
		printf("ip_header->ip_len: %d\n", ip_header->ip_len);
		printf("ip_header->ip_id: %d\n", ntohs(ip_header->ip_id));
		printf("ip_header->ip_off: %d\n", ip_header->ip_off);
		printf("ip_header->ip_ttl: %d\n", ip_header->ip_ttl);
		printf("ip_header->ip_p: %d\n", ip_header->ip_p);
		printf("ip_header->ip_src: %s\n", inet_ntoa(ip_header->ip_src));
		printf("ip_header->ip_dst: %s\n", inet_ntoa(ip_header->ip_dst));
		
		printf("icmp_header->type: %d\n", icmp_header->type);
		printf("icmp_header->code: %d\n", icmp_header->code);
		printf("icmp_header->un->echo->id: %d\n", ntohs(icmp_header->un.echo.id));
		printf("icmp_header->un->echo->sequence: %d\n", icmp_header->un.echo.sequence);
		printf("icmp_header->checksum: %d\n", icmp_header->checksum);
    }

    // printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%d ms\n", main->address, main->newAddress, 56);


	return 0;
}