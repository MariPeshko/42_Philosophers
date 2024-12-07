/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:53:08 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/07 18:20:05 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
