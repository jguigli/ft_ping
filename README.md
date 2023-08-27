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
- reception d'un 999999 ms en time parfois
- faire mode verbeux
- Gerer la bonne address pour host unreachable (c a d mon adresse)
- le vrai PING continue a envoye des paquets si il ne recoit pas de paquets REPLY (ce qui est pas notre cas)

JSP :
- Rajouter le timestamp dans le packet ????
- check le bon ordre dans seq (wireshark)

OK :
- Gerer la sortie avec signal si possible
- unknown host 1.
