/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:34:14 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/14 00:56:59 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	pars_num_of_phil(char *str_nmb_of_phil, int *int_from_big_struct)
{
	int	phs;

	phs = ft_atoi(str_nmb_of_phil);
	if (phs < 0)
	{
		printf("Please enter a positive number of philosophers.\n");
		return (1);
	}
	if (phs == 0)
	{
		printf("The table is empty. Where are the philosophers?\n");
		return (1);
	}
	*int_from_big_struct = phs;
	return (0);
}

static int	pars_timing(char *str_time_to_do, unsigned long *timing)
{
	long	time_to_do;

	time_to_do = ft_atoi(str_time_to_do);
	if (time_to_do < 0)
	{
		printf("Please enter a positive number.\n");
		return (1);
	}
	*timing = time_to_do;
	return (0);
}

static void	print_zero_meal(void)
{
	printf("Philosophers have to eat 0 times.\n");
	printf("Simulation wasn't inisialized.\n");
}

/**
 * Initialization of total number of philosophers, timing
 * for eating, dying, sleeping, thinking (if needed) and setting 
 * dead bool to false.
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
	if (argv[5] && *argv[5])
	{
		if (pars_timing(argv[5], &(table->minimum_meal)) != 0)
			return (1);
		if (table->minimum_meal == 0)
		{
			print_zero_meal();
			return (1);
		}
	}
	else
		table->minimum_meal = 2147483647;
	table->dead = false;
	table->start_time = 0;
	table->time_think = time_to_think(table->total_nmb);
	table->all_full = false;
	return (0);
}

int	check_number_arg(int argc)
{
	if (argc < 5 || argc > 6)
	{
		if (argc < 5)
			printf("[Error] Please, give me more argument(s).\n");
		if (argc > 6)
			printf("[Error] Oops!.. Too many arguments.\n");
		printf("The program input:\n");
		printf("   ./philo\n   [number_of_philosophers]\n");
		printf("   [time_to_die]\n   [time_to_eat]\n");
		printf("   [time_to_sleep]\n");
		printf("   [number_of_times_each_philosopher_must_eat] ");
		printf("(optional argument)\n");
		return (FAILURE);
	}
	return (SUCCESS);
}
