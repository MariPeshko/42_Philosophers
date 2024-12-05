/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:53:08 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/04 21:53:24 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

time_t	curr_time()
{
	struct timeval current_time;
	time_t	value;
	
	gettimeofday(&current_time, NULL);
	value = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (value);
}