#include "../includes/ft_ping.h"


double custom_sqrt(double x)
{
    if (x < 0)
	{
        // Gestion des valeurs négatives (retourne NaN)
        return 0.0 / 0.0; // Division par zéro génère NaN
    }

    double estimate = x;
    double previous = 0.0;

    while (estimate != previous)
	{
        previous = estimate;
        estimate = 0.5 * (estimate + x / estimate);
    }

    return estimate;
}