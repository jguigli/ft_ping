#include "../includes/ft_ping.h"

void displayHelp()
{
	fprintf(stderr, "%s: Usage: ping [OPTION...] HOST ...\n", PROGRAM);
	fprintf(stderr, "Send ICMP ECHO_REQUEST packets to network hosts.\n");
	fprintf(stderr, "Options valid:\n\n");
	fprintf(stderr, "-v, --verbose              verbose output\n");
	fprintf(stderr, "-?, --help                 give this help list\n");
}

int checkOption(int argc, char **argv, t_main *main)
{
	int	address = 0;

	for (int i = 1; argv[i]; i++) 
	{
		if (ft_strncmp(argv[i], "-", 1) == 0 && argv[i][1] != '\0')
		{
			if (ft_strcmp(argv[i], "-v") == 0)
			{
				if (argc > 2)
					main->verbose = 1;
				else
				{
					fprintf(stderr, "%s: %s\n", PROGRAM, HOST_OP);
					fprintf(stderr, "%s\n", PING_HELP);
					return 1;
				}
					
			}
			else if (ft_strcmp(argv[i], "-?") == 0)
			{
				displayHelp();
				return 1;
			}
			else
			{
				fprintf(stderr, "%s: Option invalid: %s\n", PROGRAM, argv[i]);
				return 1;
			}
		}
		else
		{
			if (address)
				return 0;
			main->address = argv[i];
			address++;
		}
    }
	return 0;
}

int		checkHostAdress(t_main *main)
{
	if (inet_pton(AF_INET, main->address, &main->s_address) == 0)
	{
		struct addrinfo hints, *result;
		memset(&hints, 0, sizeof(struct addrinfo));
		hints.ai_family = AF_UNSPEC;    // Pour IPv4 et IPv6
		hints.ai_socktype = SOCK_DGRAM; // Type de socket : SOCK_STREAM pour TCP

		int status = getaddrinfo(main->address, NULL, &hints, &result);
		if (status != 0)
		{
			fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
			return -1;
		}

		// Parcourez les résultats pour obtenir les adresses IP
		struct addrinfo* rp;
		for (rp = result; rp != NULL; rp = rp->ai_next)
		{
			void* addr;
        	char ip_str[INET_ADDRSTRLEN];
			// Utilisez rp->ai_addr pour accéder à la structure d'adresse
			if (rp->ai_family == AF_INET)
			{
				struct sockaddr_in* ipv4_addr = (struct sockaddr_in*)rp->ai_addr;
				addr = &(ipv4_addr->sin_addr);
				inet_ntop(rp->ai_family, addr, ip_str, sizeof(ip_str));
				ft_strlcpy(main->newAddress, ip_str, ft_strlen(ip_str) + 1);
				inet_pton(AF_INET, main->newAddress, &main->s_address);
        		printf("Adresse IP trouvée: %s\n", ip_str);
				freeaddrinfo(result);
				return 0;
        	}
		}
		freeaddrinfo(result);
		fprintf(stderr, "%s: unknown host\n", PROGRAM);
		return -1;
	}
	ft_strlcpy(main->newAddress, main->address, ft_strlen(main->address) + 1);
	return 0;
}

int handleInput(int argc, char **argv, t_main *main)
{
    if (argc < 2)
    {
        fprintf(stderr, "%s: %s\n", PROGRAM, HOST_OP);
		fprintf(stderr, "%s\n", PING_HELP);
        return -1;
    }

	if (checkOption(argc, argv, main))
		return -1;
	
	/* Check si c'est un host ou une adresse, rajouter les octets manquants comme ping */
	if (checkHostAdress(main)) 
		return -1;
	
    return 0;
}