#include "../includes/ft_ping.h"

void displayHelp()
{
	fprintf(stderr, "%s: Usage: ping [OPTION...] HOST ...\n", PROGRAM);
	fprintf(stderr, "%s: Usage: ping [OPTION...] HOST ...\n", PROGRAM);
	fprintf(stderr, "%s: Usage: ping [OPTION...] HOST ...\n", PROGRAM);
	fprintf(stderr, "%s: Usage: ping [OPTION...] HOST ...\n", PROGRAM);
}

int checkOption(int argc, char **argv)
{
	char *host = NULL;
    int verbose = 0;
	for (int i = 1; argv[i]; i++) 
	{
        if (ft_strcmp(argv[i], "-v") == 0)
		{
            verbose = 1;
            printf("Option verbose spécifiée\n");
        }
		else if (ft_strcmp(argv[i], "-h") == 0 && i + 1 < argc)
		{
            host = argv[i + 1];
            printf("Option host spécifiée avec la valeur : %s\n", host);
            i++;  // Passer à l'argument suivant
        } 
		else if (ft_strcmp(argv[i], "-") == 0)
		{
            fprintf(stderr, "Option invalide : %s\n", argv[i]);
            return 1;
        }
    }
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



int handleErrorInput(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "%s: missing host operand\n", PROGRAM);
		fprintf(stderr, "Try ping -h\n");
        return -1;
    }

	for (int i = 0; argv[i]; i++)
	{
		if (checkOption(argc, argv))
			return -1;
		if (checkHostAdress(argv))
			return -1;
	}

	// if (checkIp(argv[2]) == -1)
	// {
	// 	fprintf(stderr, "%s: Invalid IP adress: %s\n", PROGRAM, argv[i]);
	// 	return -1;
	// }
    return 0;
}