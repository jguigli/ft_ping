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

void handleAlarm(int sig)
{
    if (sig == SIGALRM)
    {
        alarm(0);
    }
    return;
}