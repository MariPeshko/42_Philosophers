/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:29:27 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/09 13:51:25 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	routine_even(t_philo *philo)
{
	unsigned long	timestamp;

	timestamp = 8000;
	pthread_mutex_lock(philo->left_f);
	if (!dead_or_full(philo->tbl))
	{
		pthread_mutex_unlock(philo->left_f);
		return (0);
	}
	timestamp = ft_timestamp(philo->tbl);
	ft_msg(philo, timestamp, FORK);
	pthread_mutex_lock(philo->right_f);
	if (!dead_or_full(philo->tbl))
	{
		pthread_mutex_unlock(philo->left_f);
		pthread_mutex_unlock(philo->right_f);
		return (0);
	}
	return (1);
}

int	routine_odd(t_philo *philo)
{
	unsigned long	timestamp;

	timestamp = 7000;
	pthread_mutex_lock(philo->right_f);
	if (!dead_or_full(philo->tbl))
	{
		pthread_mutex_unlock(philo->right_f);
		return (0);
	}
	timestamp = ft_timestamp(philo->tbl);
	ft_msg(philo, timestamp, FORK);
	pthread_mutex_lock(philo->left_f);
	if (!dead_or_full(philo->tbl))
	{
		pthread_mutex_unlock(philo->left_f);
		pthread_mutex_unlock(philo->right_f);
		return (0);
	}
	return (1);
}

int	ft_msg_second_fork(t_philo *philo)
{
	unsigned long	timestamp;

	timestamp = 9000;
	timestamp = ft_timestamp(philo->tbl);
	if (!dead_or_full(philo->tbl))
	{
		pthread_mutex_unlock(philo->left_f);
		pthread_mutex_unlock(philo->right_f);
		return (0);
	}
	ft_msg(philo, timestamp, FORK);
	if (!dead_or_full(philo->tbl))
	{
		pthread_mutex_unlock(philo->left_f);
		pthread_mutex_unlock(philo->right_f);
		return (0);
	}
	return (1);
}
