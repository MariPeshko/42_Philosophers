/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:53:08 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/08 18:55:33 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * This function, time_to_think, is calculating the waiting time before 
 * a philosopher starts trying to take the first fork. The purpose is likely 
 * to help avoid situations where a philosopher might immediately grab a 
 * fork after just eating and sleeping, which could lead to starvation of 
 * another philosopher.
 * 
 * Think time for an odd total number of philosophers. If this condition is met, 
 * a delay is introduced.
 */
unsigned long	time_to_think(int t_nmb)
{
	unsigned long rtrn;

	rtrn = 0;	
	if (t_nmb > 1 && (t_nmb % 2 != 0))
	{
		rtrn = 500;
		return (rtrn);
	}
	else
		return (0);
}

unsigned long	curr_time()
{
	struct timeval current_time;
	unsigned long	value;
	
	if (gettimeofday(&current_time, NULL) == -1)
		write(2, "Failed gettimeofday\n", 20);
	value = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (value);
}

int	ft_usleep(unsigned long time)
{
	unsigned long	start;

	start = curr_time();
	while ((curr_time() - start) < time)
		usleep(500);
	return (0);
}