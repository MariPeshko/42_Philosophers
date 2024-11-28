/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:34:14 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/28 17:42:35 by mpeshko          ###   ########.fr       */
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
	while(argv[i])
	{
		if (ft_isdigit(argv[i]))
			i++;
		else
		{
			printf("Please avoid using letters of the alphabet\n");
			printf("'%c' is not a number.\n", argv[i]);
			printf("The program accepts positive numbers only.\n");
			exit(EXIT_FAILURE);
		}
	}
}

void	analys_args(char **argv)
{
	int	nmb;
	is_digit_check(argv[1]);
	is_digit_check(argv[2]);
	is_digit_check(argv[3]);
	is_digit_check(argv[4]);

	nmb = ft_atoi(argv[1]);
	printf("number_of_philosophers: %d\n", nmb);
	//analys_nmb_ph(nmb);
	if (nmb < 0)
	{
		printf("Please enter a positive number of philosophers.\n");
		exit(EXIT_FAILURE);
	}
	if (nmb == 0)
	{
		printf("The table is empty. Where are the philosophers?\n");
		exit(EXIT_FAILURE);
	}

	int	time_to_die;
	time_to_die = ft_atoi(argv[2]);
	printf("time_to_die: %d\n", time_to_die);
	
	int	time_to_eat;
	time_to_eat = ft_atoi(argv[3]);
	printf("time_to_eat: %d\n", time_to_eat);
	
	int	time_to_sleep;
	time_to_sleep = ft_atoi(argv[4]);
	printf("time_to_sleep: %d\n", time_to_sleep);
}