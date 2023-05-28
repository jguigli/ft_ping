#include "../includes/ft_ping.h"

void handleCtrlC(int sig) {
    printf("\n%s: SIGINT received. Stopping the program.\n", PROGRAM);
    if (sig == SIGINT)
    {
        
    }
    return;
}