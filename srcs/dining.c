/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:02:54 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/14 01:14:54 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * All the magic starts here!
 * 
 * The monitor is a separate thread that constantly (in a loop) checks whether 
 * any of the philosophers died and whether all philosophers have eaten 
 * enough times (an optional program argument).
 * 
 * `routine_one` - for case when there is only one philosopher.
 * `routine` - two and more philosophers.
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
/**
 * Threads when finished return their own id number and pthread_join() gets
 * this number. It's a draft for check it. We don't need it for the program's
 * purpose. It's just my styding notes.
 * // if (res != NULL)
 * // printf("Thread %d finished!\n", *(int *)res);
 * // else if (res == NULL)
 * // printf("res == NULL\n");
 */
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
