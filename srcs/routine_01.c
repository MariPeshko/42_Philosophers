/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:29:27 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/09 15:38:46 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * Routine is neverending loop if every philosopher is alive.
 * If someone is dead, then bool dead is true, and this even break the circle.
 * 
 * Even philosophers wait slightly to prevent contention.
*/
void	*routine(void *arg)
{
	t_philo	*philo;
	int		*result;

	philo = (t_philo *)arg;
	result = malloc(sizeof(int));
	*result = philo->philo_id;
	if (philo->philo_id % 2 == 0)
		ft_usleep(5);
	while (1)
	{
		if (!ft_fork(philo))
			return ((void *)result);
		if (!ft_eat(philo))
			return ((void *)result);
		if (!ft_sleep(philo))
			return ((void *)result);
		if (!ft_think(philo))
			return ((void *)result);
	}
}

int	ft_fork(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		if (!routine_even(philo))
			return (0);
	}
	else
	{
		if (!routine_odd(philo))
			return (0);
	}
	if (!ft_msg_second_fork(philo))
		return (0);
	return (1);
}

int	ft_eat(t_philo *philo)
{
	unsigned long	timestamp;

	timestamp = 10000;
	timestamp = ft_timestamp(philo->tbl);
	if (!dead_or_full(philo->tbl))
	{
		pthread_mutex_unlock(philo->left_f);
		pthread_mutex_unlock(philo->right_f);
		return (0);
	}
	ft_msg(philo, timestamp, EATING);
	pthread_mutex_lock(&philo->state_lock);
	philo->time_last_meal = ft_time_last_meal(philo->tbl);
	pthread_mutex_unlock(&philo->state_lock);
	ft_usleep((philo->tbl->time_eat));
	pthread_mutex_lock(&philo->state_lock);
	philo->amount_meal++;
	pthread_mutex_unlock(&philo->state_lock);
	pthread_mutex_unlock(philo->right_f);
	pthread_mutex_unlock(philo->left_f);
	return (1);
}

int	ft_sleep(t_philo *philo)
{
	unsigned long	timestamp;

	timestamp = 7777;
	if (!dead_or_full(philo->tbl))
		return (0);
	timestamp = ft_timestamp(philo->tbl);
	ft_msg(philo, timestamp, SLEEPING);
	if (!dead_or_full(philo->tbl))
		return (0);
	ft_usleep(philo->tbl->time_sleep);
	if (!dead_or_full(philo->tbl))
		return (0);
	else
		return (1);
}

int	ft_think(t_philo *philo)
{
	unsigned long	timestamp;

	timestamp = 7777;
	timestamp = ft_timestamp(philo->tbl);
	ft_msg(philo, timestamp, THINKING);
	usleep(philo->tbl->time_think);
	if (!dead_or_full(philo->tbl))
		return (0);
	else
		return (1);
}
