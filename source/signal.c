#include "../includes/ft_ping.h"

void handleCtrlC(int sig)
{
    printf("\n%s: SIGINT received. Stopping the program.\n", PROGRAM);
    if (sig == SIGINT)
    {
        // free ce qu'il y a a free eventuellement
        // afficher packets transmitted, packets received, % packet loss
        // afficher round-trip min/avg/max/stddev
    }
    return;
}