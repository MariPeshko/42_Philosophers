/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:34:14 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/02 15:53:25 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	pars_num_of_phil(char *str_nmb_of_phil, int *int_from_big_struct)
{
	int	phs;

	phs = ft_atoi(str_nmb_of_phil);
	printf("number_of_philosophers: %d\n", phs);
	if (phs < 0)
	{
		printf("Please enter a positive number of philosophers.\n");
		return(1);
	}
	if (phs == 0)
	{
		printf("The table is empty. Where are the philosophers?\n");
		return(1);
	}
	*int_from_big_struct = phs;
	return (0);
}

static int	pars_timing(char *str_time_to_do, long *timing)
{
	long	time_to_do;

	time_to_do = ft_atoi(str_time_to_do);
	if (time_to_do < 0)
	{
		printf("Please enter a positive number of time_to_do.\n");
		return(1);
	}
	if (time_to_do == 0)
	{
		printf("time_to_do is 0. What am I doing?\n");
		return(0);
	}
	*timing = time_to_do;
	return (0);
	
}

int	init_tmp(t_data *tmp, t_data *base, int i)
{
	//pthread_t *th;
	
	tmp->total_nmb = base->total_nmb;
	tmp->forks = tmp->total_nmb;
	tmp->time_to_die = base->time_to_die;
	tmp->time_to_eat = base->time_to_eat;
	tmp->time_to_sleep = base->time_to_sleep;
	//tmp->thread = th;
	tmp->thread_id = i;
	printf("thread_id: %d\n", tmp->thread_id);
	return (0);
}

int	init_base_data(char **argv, t_data *tmp)
{
	
	
	printf("time_to_die: %d milliseconds\n", tmp->time_to_die);
	if (pars_timing(argv[3], &(tmp->time_to_eat)) != 0)
		return (1);
	printf("time_to_eat: %d milliseconds\n", tmp->time_to_eat);
	if (pars_timing(argv[4], &(tmp->time_to_sleep)) != 0)
		return (1);
	printf("time_to_sleep: %d milliseconds\n", tmp->time_to_sleep);
	return (0);
}

/**
 * Initialization of total number of philosophers, timing
 * for eating, dying, sleeping, and setting dead bool to false.
*/
int	init_table(char **argv, t_table *table)
{
	if (pars_num_of_phil(argv[1], &(table->total_nmb)) != 0)
		return (1);
	if (pars_timing(argv[2], &(table->time_die)) != 0)
		return (1);
	if (pars_timing(argv[3], &(table->time_eat)) != 0)
		return (1);
	if (pars_timing(argv[4], &(table->time_sleep)) != 0)
		return (1);
	//if (ac == 6)
	table->dead = false;
	return (0);
}

