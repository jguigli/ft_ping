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
	memset(&msg, 0, sizeof(struct msghdr));
    msg.msg_name = &sender_addr;
    msg.msg_namelen = sizeof(sender_addr);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = NULL;
    msg.msg_controllen = 0;
    msg.msg_flags = 0;

	while (1)
	{
		if (sockfd == 0)
			return -1;
		recvmsg(sockfd, &msg, 0);
		gettimeofday(&main->end_time, NULL);
		
		struct ip *ip_header = (struct ip *)packet;
		struct icmphdr *icmp_header = (struct icmphdr *)(packet + sizeof(struct ip)); // Skip IP header

		if (icmp_header->type == ICMP_ECHOREPLY && ip_header->ip_src.s_addr == main->s_address.s_addr)
		{
			main->time = ((main->end_time.tv_sec - main->start_time.tv_sec) * 1000000LL + (main->end_time.tv_usec - main->start_time.tv_usec) / 1000.0);
			if (main->packet_r == 0)
			{
				main->min = main->time;
				main->max = main->time;
			}
			if (main->min > main->time)
				main->min = main->time;
			if (main->max < main->time)
				main->max = main->time;
			main->avg += main->time;
			main->packet_r++;
			printf("%d bytes from %s icmp_seq=%d ttl=%d time=%.3f ms\n", PACKET_SIZE, inet_ntoa(ip_header->ip_src), icmp_header->un.echo.sequence, ip_header->ip_ttl, main->time);
			return 0;
		}
		else if (icmp_header->type == ICMP_DEST_UNREACH) 
		{
			printf("%d bytes from %s (%s): Destination Host Unreachable\n",
			92, main->address, main->newAddress);
			return 0;
		}
		// else
		// {
		// 	printf("Received ICMP packet, but not an Echo Reply\n");
		// 	// printf("ip_header->ip_hl: %d\n", ip_header->ip_hl);
		// 	// printf("ip_header->ip_v: %d\n", ip_header->ip_v);
		// 	// printf("ip_header->ip_tos: %d\n", ip_header->ip_tos);
		// 	// printf("ip_header->ip_len: %d\n", ip_header->ip_len);
		// 	// printf("ip_header->ip_id: %d\n", ntohs(ip_header->ip_id));
		// 	// printf("ip_header->ip_off: %d\n", ip_header->ip_off);
		// 	// printf("ip_header->ip_ttl: %d\n", ip_header->ip_ttl);
		// 	// printf("ip_header->ip_p: %d\n", ip_header->ip_p);
		// 	printf("ip_header->ip_src: %s\n", inet_ntoa(ip_header->ip_src));
		// 	printf("ip_header->ip_dst: %s\n", inet_ntoa(ip_header->ip_dst));
			
		// 	printf("icmp_header->type: %d\n", icmp_header->type);
		// 	// printf("icmp_header->code: %d\n", icmp_header->code);
		// 	// printf("icmp_header->un->echo->id: %d\n", ntohs(icmp_header->un.echo.id));
		// 	// printf("icmp_header->un->echo->sequence: %d\n", icmp_header->un.echo.sequence);
		// 	// printf("icmp_header->checksum: %d\n", icmp_header->checksum);
		// }
	}


	return 0;
}