/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:34:14 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/28 23:33:47 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// static int	ft_isdigit(int c)
// {
// 	if (c >= 48 && c <= 57)
// 		return (1);
// 	else
// 		return (0);
// }

static void	is_digit_check(char *argv)
{
	int	i;

	i = 0;
	if (argv[i] == '+' || argv[i] == '-')
			i++;
	if (argv[i] == '+' || argv[i] == '-')
	{
		printf("Sorry, there is an extra - or + here. Try again!\n");
		exit(EXIT_FAILURE);
	}
	while(argv[i])
	{
		if (ft_isdigit(argv[i]))
			i++;
		else
		{
			printf("'%c' is not a digit.\n", argv[i]);
			printf("Please avoid using letters or \n");
			printf("special characters.\n");
			exit(EXIT_FAILURE);
		}
	}
}

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

static int	pars_timing(char *str_time_to_do, int *int_from_big_struct)
{
	int	time_to_do;

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
	*int_from_big_struct = time_to_do;
	return (0);
	
}

void	analys_args_exit(char **argv)
{
	is_digit_check(argv[1]);
	is_digit_check(argv[2]);
	is_digit_check(argv[3]);
	is_digit_check(argv[4]);
}

int	init_big_struct(char **argv, t_big *big)
{
	analys_args_exit(argv);
	if (pars_num_of_phil(argv[1], &(big->nmb_of_ph)) != 0)
		return (1);
	if (pars_timing(argv[2], &(big->time_to_die)) != 0)
		return (1);
	printf("time_to_die: %d\n", big->time_to_die);
	if (pars_timing(argv[3], &(big->time_to_eat)) != 0)
		return (1);
	printf("time_to_eat: %d\n", big->time_to_eat);
	if (pars_timing(argv[4], &(big->time_to_sleep)) != 0)
		return (1);
	printf("time_to_sleep: %d\n", big->time_to_sleep);
	return (0);
}