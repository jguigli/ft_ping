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

La commande ping requiert  la capacité CAP_NET_RAWIO  pour pouvoir être exécutée. Elle peut être utilisée via set-uid root. 


Logique de la fonction PING :

parser les inputs
gerer 192.1 = 192.0.0.1
si adresse/host -> getaddrinfo ou getnameinfo
getpid() pour identifier le process qui envoi
creation du paquet ICMP

boucle infini :
envoi du paquet ICMP Echo Request
check des erreurs sur l'envoi
attente du paquet reponse ICMP Echo reply
timestamp a la reception
verification du bon paquet retourne
affichage des infos recu
check des erreurs sur la reception

si ctrl/-c fin de la boucle et affichage des infos finals