#ifndef FT_PING_H
# define FT_PING_H

/* Inclusion des dépendances */

#define _GNU_SOURCE

# include <sys/time.h> 
# include <stdlib.h>
# include <stdio.h>
# include <arpa/inet.h>
# include <signal.h>
# include <unistd.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>
# include <netdb.h>
# include <string.h>
# include <errno.h>

# include "../libft/libft.h"


/* Définition des constantes */

# define PROGRAM "ft_ping"
# define PACKET_SIZE 64 // taille paquet IP HDR + ICMP

/* Message erreur */
# define HOST_OP "Missing host operand"
# define PING_HELP "Try 'ping -?' for more information"

/* Variable Global */

extern int sockfd;

/* Déclaration des structures */

typedef struct s_main
{
	char			*address; // nom du host ou adresse
	char			newAddress[16]; // adresse ip finale
	struct in_addr 	s_address; // adresse ip apres inet_pton
	int				verbose; // option -v
	char			packet[IP_MAXPACKET]; // paquet d'emvoi
	int				packet_t; // nonmbre paquet transmis
	int				packet_r; // nonmbre paquet recu
	int				ttl; // Changer le type time to live
	int				time; // Changer le type temps reception apres envoi
} t_main;

/* Prototype des fonctions */

int handleInput(int argc, char **argv, t_main *main);
void handleCtrlC(int sig);
int ft_ping(int argc, char **argv);
int sendData(t_main *main);
int receiveData(t_main *main);



#endif