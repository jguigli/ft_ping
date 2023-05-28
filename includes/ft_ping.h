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
# define BUFFER_SIZE 42 /* Struct ethhdr + struct arphdr + 6 + 4 + 6 + 4 */

/* Variable Global */

extern int sockfd;

/* Déclaration des structures */



/* Prototype des fonctions */



#endif