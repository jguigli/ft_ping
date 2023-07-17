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
# include <netdb.h>
# include <string.h>

# include "../libft/libft.h"


/* Définition des constantes */

# define PROGRAM "ft_ping"

/* Message erreur */
# define HOST_OP "Missing host operand"
# define PING_HELP "Try 'ping -?' for more information"

/* Variable Global */

extern int sockfd;

/* Déclaration des structures */

typedef struct s_main
{
	char	*adress;
	int		verbose;
} t_main;

/* Prototype des fonctions */

int handleErrorInput(int argc, char **argv, t_main *main);
void handleCtrlC(int sig);
int ft_ping(int argc, char **argv);



#endif