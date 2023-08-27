#include "../includes/ft_ping.h"

void handleCtrlC(int sig)
{
    if (sig == SIGINT)
    {
        close(sockfd);
        sockfd = 0;
    }
    return;
}