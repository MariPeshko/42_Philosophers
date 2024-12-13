/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:02:54 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/13 18:30:31 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * 1. Init start_time.
 * 
 * // if (res != NULL)
 * // printf("Thread %d finished!\n", *(int *)res);
 * // else if (res == NULL)
 * // printf("res == NULL\n");
 */
int	start_dining(t_table *table)
{
	t_philo	*ph;
	int		i;

	i = 0;
	set_start_time(table);
	pthread_create(&table->monitor, NULL, &monitor, table);
	if (table->total_nmb == 1)
	{
		ph = table->philos[i];
		if (pthread_create(&ph->thread_t, NULL, &routine_one, ph) != 0)
			return (-1);
	}
	else if (table->total_nmb > 1)
	{
		while (i < table->total_nmb)
		{
			ph = table->philos[i];
			if (pthread_create(&ph->thread_t, NULL, &routine, ph) != 0)
				return (i * -1);
			i++;
		}
	}
	ft_wait(table);
	return (SUCCESS);
}

void	set_start_time(t_table *tbl)
{
	t_philo	*ph;
	int		i;

	i = 0;
	tbl->start_time = curr_time();
	while (i < tbl->total_nmb)
	{
		ph = tbl->philos[i];
		ph->time_last_meal = tbl->start_time;
		i++;
	}
}

int	ft_wait(t_table *tbl)
{
	t_philo	*ph;
	int		i;
	void	*res;

	i = 0;
	if (pthread_join(tbl->monitor, NULL) != 0)
		return (-2);
	while (i < tbl->total_nmb)
	{
		ph = tbl->philos[i];
		if (pthread_join(ph->thread_t, &res) != 0)
		{
			printf("pthread_join returned not 0\n");
			return (i + 1);
		}
		i++;
		free(res);
	}
	return (0);
}
