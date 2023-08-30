# ft_ping

gettimeofday.
exit.
inet_ntop. / inet_pton.
signal / alarm / usleep.
socket / setsockopt.
sendto / recvmsg.
getpid / getuid.
getaddrinfo / getnameinfo / freeaddrinfo.
strerror / gai_strerror.
printf and its family.


MAN PING :
http://www.man-linux-magique.net/man8/ping.html  
https://www.geeksforgeeks.org/ping-in-c/  

La commande ping requiert  la capacité CAP_NET_RAWIO  pour pouvoir être exécutée. Elle peut être utilisée via set-uid root. 

TODO :

- resolving dns a gerer (voir sujet)

- Il me faudrait acceder a l'ipheader pour indiquer le verbose mode unreachable, mais j'automatise l'envoi de ce header sans setsockopt
- faire mode verbeux la ou il faut
- tester le verbose du host unreachable -> manque ip dr dump (normalement c'est bon pour ip et icmp header)

JSP :
- Comment gerer les bytes recu (difference avec le vrai ping)
- des fois c'est 64 des fois c'est 56 bytes

- Rajouter le timestamp dans le packet ????
- reception d'un 999999 ms en time parfois
- Gerer la bonne address pour host unreachable (c a d mon adresse) avec getnameinfo
- gerer les differents type de code pour le type unreachable

OK :
- le vrai PING continue a envoye des paquets si il ne recoit pas de paquets REPLY (ce qui est pas notre cas)
- check le bon ordre dans seq (wireshark) -> htons(seq)
- Gerer la sortie avec signal si possible
- unknown host 1.

POINT :
Je ne comprend pas trop la taille du paquet ICMP cense etre 56 et 64 avec ICMPHDR et 84 avec IPHDR
La data est de 56 dans mon paquet contre 48 dans le vrai paquet ping
pourtant j'ai la mm length de 98 bytes analyse par wireshark (pour le paquet complet)

Il faut que je trouve comment envoyer le paquet avec l'IPHDR






PRINTF AUTRE PAQUET :
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