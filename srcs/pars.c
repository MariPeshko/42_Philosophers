/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:34:14 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/02 19:29:15 by mpeshko          ###   ########.fr       */
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

