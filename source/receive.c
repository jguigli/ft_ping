#include "../includes/ft_ping.h"

int receiveData(t_main *main)
{
	char packet[IP_MAXPACKET];
    memset(packet, 0, IP_MAXPACKET);

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
		memset(packet, 0, IP_MAXPACKET);
		bytes = recvmsg(sockfd, &msg, 0);
		// printf("receive message: %ld\n", recvmsg(sockfd, &msg, 0));
		if (bytes == -1)
		{
			return 1;
		}
		
		struct ip *ip_header = (struct ip *)packet;
		struct icmphdr *icmp_header = (struct icmphdr *)(packet + sizeof(struct ip)); // Skip IP header

		gettimeofday(&main->end_time, NULL);
		// printf("start = %ld et end = %ld / startu = %ld et endu = %ld\n", main->start_time.tv_sec ,main->end_time.tv_sec, main->start_time.tv_usec ,main->end_time.tv_usec);
		// printf("start = %ld et mend = %ld / startu = %ld et mendu = %ld\n", main->start_time.tv_sec ,end_time.tv_sec, main->start_time.tv_usec ,end_time.tv_usec);
		main->time = ((main->end_time.tv_sec - main->start_time.tv_sec) * 1000000LL + (main->end_time.tv_usec - main->start_time.tv_usec) / 1000.0);
		
		if (icmp_header->type == ICMP_ECHOREPLY && ip_header->ip_src.s_addr == main->s_address.s_addr)
		{
			char src[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, &ip_header->ip_src, src, INET_ADDRSTRLEN);

			if (main->packet_r == 0)
			{
				main->min = main->time;
				main->max = main->time;
			}
			if (main->min > main->time)
				main->min = main->time;
			if (main->max < main->time)
				main->max = main->time;
			main->sum += main->time;
			main->sq_sum += main->time * main->time;
			main->packet_r++;
			printf("%ld bytes from %s icmp_seq=%d ttl=%d time=%.3f ms\n", bytes - IPHDR_SIZE, src, ntohs(icmp_header->un.echo.sequence), ip_header->ip_ttl, main->time);
			return 0;
		}
		else if (icmp_header->type == ICMP_DEST_UNREACH) 
		{
			struct ip *iphdr = (struct ip *)packet;
			struct icmphdr *icmphdr = (struct icmphdr *)(packet + sizeof(struct ip));
			char src[INET_ADDRSTRLEN], dst[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, &iphdr->ip_src, src, INET_ADDRSTRLEN);
			inet_ntop(AF_INET, &main->s_address, dst, INET_ADDRSTRLEN);

			if (main->verbose)
			{
				// getnameinfo();
				printf("%ld bytes from %s: Destination Host Unreachable\n", bytes - IPHDR_SIZE, src);

				printf("IP Hdr Dump:\n");
				printf(" 4500 0054 a244 4000 4001 14fb c0a8 0114 c0a8 0105\n"); // AMODIF
				printf("Vr HL TOS  Len   ID Flg  off TTL Pro  cks  	Src     Dst      Data\n");
				printf(" %i %d  %d %04d %d  2 %04d  %d %d %d  %s  %s\n",
       			iphdr->ip_v, iphdr->ip_hl, iphdr->ip_tos, ntohs(iphdr->ip_len),
       			ntohs(iphdr->ip_id), iphdr->ip_off, iphdr->ip_ttl, iphdr->ip_sum, iphdr->ip_p, src, dst);
				printf("ICMP: type %d, code %d, size %d, id 0x%04x, seq 0x%04d\n",
       			icmphdr->type, icmphdr->code, PACKET_SIZE, main->pid, main->packet_t);
			}
			else
			{
				printf("%ld bytes from %s: Destination Host Unreachable\n", bytes - IPHDR_SIZE, src);
			}

			return 0;
		}
	}


	return 0;
}