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

	ssize_t bytes = 0;

	while (sockfd)
	{
		bytes = recvmsg(sockfd, &msg, 0);
		// printf("receive message: %ld\n", recvmsg(sockfd, &msg, 0));
		if (packet[0] == '\0' && bytes == -1)
			return 0;
		
		struct ip *ip_header = (struct ip *)packet;
		struct icmphdr *icmp_header = (struct icmphdr *)(packet + sizeof(struct ip)); // Skip IP header

		gettimeofday(&main->end_time, NULL);
		// printf("start = %ld et end = %ld / startu = %ld et endu = %ld\n", main->start_time.tv_sec ,main->end_time.tv_sec, main->start_time.tv_usec ,main->end_time.tv_usec);
		// printf("start = %ld et mend = %ld / startu = %ld et mendu = %ld\n", main->start_time.tv_sec ,end_time.tv_sec, main->start_time.tv_usec ,end_time.tv_usec);
		main->time = ((main->end_time.tv_sec - main->start_time.tv_sec) * 1000000LL + (main->end_time.tv_usec - main->start_time.tv_usec) / 1000.0);
		
		if (icmp_header->type == ICMP_ECHOREPLY && ip_header->ip_src.s_addr == main->s_address.s_addr)
		{
			alarm(0);
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
			printf("%d bytes from %s icmp_seq=%d ttl=%d time=%.3f ms\n", PACKET_SIZE, inet_ntoa(ip_header->ip_src), ntohs(icmp_header->un.echo.sequence), ip_header->ip_ttl, main->time);
			return 0;
		}
		else if (icmp_header->type == ICMP_DEST_UNREACH) 
		{
			alarm(0);
			printf("%d bytes from %s (%s): Destination Host Unreachable\n", 92, main->address, main->newAddress);
			if (main->verbose)
			{
				char src[INET_ADDRSTRLEN], dst[INET_ADDRSTRLEN];
				inet_ntop(AF_INET, &ip_header->ip_src, src, INET_ADDRSTRLEN);
				inet_ntop(AF_INET, &ip_header->ip_dst, dst, INET_ADDRSTRLEN);

				printf("IP Hdr Dump:\n");
				printf(" 4500 0054 a244 4000 4001 14fb c0a8 0114 c0a8 0105\n"); // AMODIF
				printf("Vr HL TOS  Len   ID Flg  off TTL Pro  cks  	Src     Dst      Data\n");
				printf(" %i %d %d %04d %d  2 %04d  %d %d %d  %s  %s\n",
       			ip_header->ip_v, ip_header->ip_hl, ip_header->ip_tos, ip_header->ip_len,
       			ntohs(ip_header->ip_id), ip_header->ip_off, ip_header->ip_ttl, ip_header->ip_sum, ip_header->ip_p, src, dst);
				printf("ICMP: type %d, code %d, size %d, id 0x%04x, seq 0x%d\n",
       			icmp_header->type, icmp_header->code, PACKET_SIZE, icmp_header->un.echo.id, ntohs(icmp_header->un.echo.sequence));
			}
			return 0;
		}
		// else
		// {
		// 	printf("Received ICMP packet, but not an Echo Reply :\n");
		// 	// printf("ip_header->ip_hl: %d\n", ip_header->ip_hl);
		// 	// printf("ip_header->ip_v: %d\n", ip_header->ip_v);
		// 	// printf("ip_header->ip_tos: %d\n", ip_header->ip_tos);
		// 	// printf("ip_header->ip_len: %d\n", ip_header->ip_len);
		// 	// printf("ip_header->ip_id: %d\n", ntohs(ip_header->ip_id));
		// 	// printf("ip_header->ip_off: %d\n", ip_header->ip_off);
		// 	// printf("ip_header->ip_ttl: %d\n", ip_header->ip_ttl);
		// 	// printf("ip_header->ip_p: %d\n", ip_header->ip_p);
		// 	printf("ip_header->ip_src: %s\n", inet_ntop(ip_header->ip_src));
		// 	printf("ip_header->ip_dst: %s\n", inet_ntop(ip_header->ip_dst));
			
		// 	printf("icmp_header->type: %d\n", icmp_header->type);
		// 	// printf("icmp_header->code: %d\n", icmp_header->code);
		// 	// printf("icmp_header->un->echo->id: %d\n", ntohs(icmp_header->un.echo.id));
		// 	// printf("icmp_header->un->echo->sequence: %d\n", icmp_header->un.echo.sequence);
		// 	// printf("icmp_header->checksum: %d\n", icmp_header->checksum);
		// }
	}


	return 0;
}