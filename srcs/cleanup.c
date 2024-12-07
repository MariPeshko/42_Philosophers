/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 00:50:32 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/07 19:47:13 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_philos(t_philo **philos, int total_nmb)
{
	int	i;
	t_philo	*ph;

	i = 0;
	while (i < total_nmb)
	{
		ph = philos[i];
		free(ph);
		ph = NULL;
		i++;
	}
	free(philos);
}

void	destroy_mtx(t_table *table)
{
	//destroy_philo_mtx();
	int	i;
	
	i = 0;
	while(i < table->total_nmb)
	{
		pthread_mutex_destroy(table->f_mtxs[i]);
		free(table->f_mtxs[i]);
		table->f_mtxs[i] = NULL;
		i++;
	}
	pthread_mutex_destroy(&table->mtx_time);
	pthread_mutex_destroy(&table->mtx_dead);
	pthread_mutex_destroy(&table->mtx_msg);
	
	free(table->f_mtxs);
	table->dead = NULL;
}