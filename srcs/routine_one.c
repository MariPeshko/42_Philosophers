/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:21:10 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/07 15:16:21 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *routine_one(void *arg)
{
	t_philo	*philo;
	int		*result;
	long	timestamp;
	
	timestamp = 5555;
	philo = (t_philo *)arg;
    result = malloc(sizeof(int));
	*result = philo->philo_id;
    pthread_mutex_lock(philo->left_f);
    pthread_mutex_lock(&philo->tbl->mtx_msg);
	timestamp = curr_time() - philo->tbl->start_time;
    printf("%li %i has taken a fork\n", timestamp, philo->philo_id);
    pthread_mutex_unlock(&philo->tbl->mtx_msg);
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
