/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:21:10 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/08 22:13:51 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *routine_one(void *arg)
{
	t_philo	*philo;
	int		*result;
	long	timestamp;
	
	philo = (t_philo *)arg;
	timestamp = 5555;
	result = malloc(sizeof(int));
	*result = philo->philo_id;
	pthread_mutex_lock(philo->left_f);
	timestamp = curr_time() - philo->tbl->start_time;
	ft_msg(philo, timestamp, FORK);
	while (1)
	{
		usleep(150);
		if (philo->tbl->dead == true)
		{
			pthread_mutex_unlock(philo->left_f);
			return ((void *)result);
		}
	}
}
