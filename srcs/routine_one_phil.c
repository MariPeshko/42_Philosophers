/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_one_phil.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:21:10 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/09 16:01:51 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine_one(void *arg)
{
	t_philo	*philo;
	int		*result;
	long	timestamp;

	philo = (t_philo *)arg;
	timestamp = 5555;
	result = malloc(sizeof(int));
	*result = philo->philo_id;
	pthread_mutex_lock(philo->left_f);
	pthread_mutex_lock(&philo->time_lock);
	timestamp = curr_time() - philo->tbl->start_time;
	pthread_mutex_unlock(&philo->time_lock);
	ft_msg(philo, timestamp, FORK);
	while (1)
	{
		usleep(150);
		pthread_mutex_lock(&philo->tbl->mtx_dead);
		if (philo->tbl->dead == true)
		{
			pthread_mutex_unlock(philo->left_f);
			pthread_mutex_unlock(&philo->tbl->mtx_dead);
			return ((void *)result);
		}
		pthread_mutex_unlock(&philo->tbl->mtx_dead);
	}
}
