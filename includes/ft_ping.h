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
# include <netinet/in.h>
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>
# include <linux/filter.h>
# include <netdb.h>
# include <string.h>
# include <errno.h>

# include "../libft/libft.h"


/* Définition des constantes */

# define PROGRAM "ft_ping"
# define PACKET_SIZE 64 // taille paquet ICMP + payload
# define PAYLOAD 56
# define IPHDR_SIZE 20
# define ICMPHDR_SIZE 8
# define RECV_TIMEOUT 1
# define PING_SLEEP 1000000

/* Message erreur */
# define HOST_OP "Missing host operand"
# define PING_HELP "Try 'ping -?' for more information"

/* Variable Global */

extern int sockfd;

/* Déclaration des structures */
typedef struct s_ping
{
	struct icmphdr icmp;
	struct ip ip;
} t_ping;
typedef struct s_main
{
	char				*address; // nom du host ou adresse
	char				*myDns;
	char				newAddress[16]; // adresse ip finale
	char				buffersprint[8][1000];
	struct in_addr 		s_address; // adresse ip apres inet_pton
	struct sockaddr_in  dest_addr;
	int					verbose; // option -v
	char				packet[IP_MAXPACKET]; // paquet d'emvoi
	// t_ping				packet;
	int					packet_t; // nonmbre paquet transmis
	int					packet_r; // nonmbre paquet recu
	pid_t				pid;
	double				min;
	double				max;
	double				sum;
	double				sq_sum;
	double				stddev;
	double				time; // Changer le type temps reception apres envoi
	struct timeval 		start_time;
	struct timeval 		end_time;
} t_main;


/* Prototype des fonctions */

int handleInput(int argc, char **argv, t_main *main);
void handleCtrlC(int sig);
void handleAlarm(int sig);
int ft_ping(int argc, char **argv);
int sendData(t_main *main);
int receiveData(t_main *main);
double custom_sqrt(double x);



#endif