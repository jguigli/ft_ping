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
	(void)argc;
	for (int i = 1; argv[i]; i++) 
	{
		if (ft_strncmp(argv[i], "-", 1) == 0 && argv[i][1] != '\0')
		{
			if (ft_strcmp(argv[i], "-v") == 0)
			{
				if (argv[i + 1])
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
				fprintf(stderr, "Option invalid: %s\n", argv[i]);
				return 1;
			}
		}
    }
	return 0;
}

// int checkHostAdress(char **argv)
// {
// 	char *host = NULL;
//     int verbose = 0;
// 	for (int i = 1; argv[i]; i++) 
// 	{
//         if (ft_strcmp(argv[i], "-v") == 0)
// 		{
//             verbose = 1;
//             printf("Option verbose spécifiée\n");
//         }
// 		else if (ft_strcmp(argv[i], "-h") == 0 && i + 1 < argc)
// 		{
//             host = argv[i + 1];
//             printf("Option host spécifiée avec la valeur : %s\n", host);
//             i++;  // Passer à l'argument suivant
//         } 
// 		else if (ft_strcmp(argv[i], "-") == 0)
// 		{
//             fprintf(stderr, "Option invalide : %s\n", argv[i]);
//             return 1;
//         }
//     }
// }

int checkIp(char *ip)
{
    int i = 0;
    int j = 0;
    int y = 0;
    char *tmp = NULL;
    int byte = 0;
    int nbByte = 0;

    while (ip[i] != '\0')
    {
        j = i;
        y = 0;
        while (ip[j] != '.' && ip[j])
        {
            if (!ft_isdigit(ip[j]))
                return -1;
            ++j;
            ++y;
        }
        if (y > 3 || y == 0)
            return -1;
        ++nbByte;
        tmp = ft_substr(ip, i, y);
        byte = ft_atoi(tmp);
		if (byte == 0 && y != 1)
			return (free(tmp), -1);
        free(tmp);
        if (byte > 255 || byte < 0)
            return -1;
        if (ip[j] == '\0')
            break ;
        else
            i = j + 1;
    }
    if (nbByte != 4)
        return -1;
    return 0;
}





int handleErrorInput(int argc, char **argv, t_main *main)
{
    if (argc < 2)
    {
        fprintf(stderr, "%s: %s\n", PROGRAM, HOST_OP);
		fprintf(stderr, "%s\n", PING_HELP);
        return -1;
    }

	for (int i = 0; argv[i]; i++)
	{
		if (checkOption(argc, argv, main))
			return -1;
		/* Check si c'est un host ou une adresse, rajouter les octets manquants comme ping */
		// if (checkHostAdress(argv)) 
		// 	return -1;
	}
    return 0;
}