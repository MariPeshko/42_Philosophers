/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_03_mtx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:59:04 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/14 01:05:36 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * Initializing mutexes that prevent data races and make the program 
 * robust. Each protects the corresponding variables.
 * 
 * When the lock() function is called, only one thread can run 
 * at a time. The other thread, having reached pthread_mutex_lock(), 
 * waits until pthread_mutex_unlock() function is called, and then 
 * it intercepts the mutex and run.
*/
int	init_mtx(t_table *table)
{
	if (pthread_mutex_init(&table->mtx_time, NULL) != 0)
	{
		write(2, "mutex init failed", 17);
		return (FAILURE);
	}
	if (pthread_mutex_init(&table->mtx_dead, NULL) != 0)
	{
		write(2, "mutex init failed", 17);
		return (FAILURE);
	}
	if (pthread_mutex_init(&table->mtx_msg, NULL) != 0)
	{
		write(2, "mutex init failed", 17);
		return (FAILURE);
	}
	return (SUCCESS);
}
