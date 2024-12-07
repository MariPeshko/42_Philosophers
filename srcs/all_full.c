/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_full.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 16:15:28 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/07 18:24:02 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	all_full(t_table *table)
{
	int		i;
	t_philo *ph;
	unsigned long	philo_meal_n;
	

	i = 0;
	ph = table->philos[i];
	pthread_mutex_lock(&table->mtx_dead);
	while (i < table->total_nmb)
	{
		ph = table->philos[i];
		pthread_mutex_lock(&ph->lock);
		philo_meal_n = ph->amount_meal;
		pthread_mutex_unlock(&ph->lock);
		if (philo_meal_n >= table->minimum_meal)
			i++;
		else
		{
			pthread_mutex_unlock(&table->mtx_dead);
			return (1);
		}
	}
	table->all_full = true;
	pthread_mutex_unlock(&table->mtx_dead);
	return (0);
}