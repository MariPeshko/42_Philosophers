/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:58:20 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/08 21:27:37 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_msg(t_philo *philo, unsigned long time, t_status st)
{
	pthread_mutex_lock(&philo->tbl->mtx_msg);
	if (st == EATING)
	{
		philo->status = EATING;
		printf("%li %i is eating\n", time, philo->philo_id);
	}
	if (st == FORK)
	{
		philo->status = FORK;
		printf("%li %i has taken a fork\n", time, philo->philo_id);
	}
	if (st == SLEEPING)
	{
		philo->status = SLEEPING;
		printf("%li %i is sleeping\n", time, philo->philo_id);
	}
	if (st == THINKING)
	{
		philo->status = THINKING;
		printf("%li %i is thinking\n", time, philo->philo_id);
	}
	if (st == DEAD)
		printf("%li %i died\n", time, philo->philo_id);
	pthread_mutex_unlock(&philo->tbl->mtx_msg);
}
