/*.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo. */
/*                                                                                      */
/*   Nom du fichier : main.c                                                            */
/*      Type du fichier : ASCII text                                                    */
/*                                                                                      */
/*   By: Jo                                                                             */
/*                                                                                      */
/*  Created: 14/05/2023                                                                 */
/*  Updated: 14/05/2023                                                                 */
/*                                                                                      */
/*.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo.oOo. */
#include "../includes/ft_ping.h"

int sockfd = 0;

int main (int argc, char **argv)
{
    // if (getuid() != 0)
    // {
    //     fprintf(stderr, "%s: This program requires superuser privileges.\n", PROGRAM);
    //     return 1;
    // }
    
    if (ft_ping(argc, argv) == -1)
        return 1;

    return 0;
}
