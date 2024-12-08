/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:10:40 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/08 22:01:32 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	arg_valid_check(char *argv, int nbr)
{
	int	i;

	i = 0;
	if (argv[i] == '+' || argv[i] == '-')
			i++;
	if (!*argv)
	{
		printf("Argument %i is an empty string\n", nbr);
		return (1);
	}
	if (argv[i] == '+' || argv[i] == '-')
	{
		printf("Sorry, there is an extra - or + ");
		printf("in argument %i.\nTry again!\n", nbr);
		return (1);
	}
	while(argv[i])
	{
		if (ft_isdigit(argv[i]))
			i++;
		else
		{
			printf("'%c' is not a digit in argument %i.\n", argv[i], nbr);
			printf("Please avoid using letters or ");
			printf("special characters.\n");
			return (1);
		}
	}
	return (0);
}

int	check_args(char **argv)
{
	if (argv[1] && arg_valid_check(argv[1], 1) == 1)
		return (1);
	if (argv[2] && arg_valid_check(argv[2], 2) == 1)
		return (1);
	if (argv[3] && arg_valid_check(argv[3], 3) == 1)
		return (1);
	if (argv[4] && arg_valid_check(argv[4], 4) == 1)
		return (1);
	if (argv[5] && arg_valid_check(argv[5], 5) == 1)
		return (1);
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
		printf("   ./philosophers\n   [number_of_philosophers]\n");
		printf("   [time_to_die]\n   [time_to_eat]\n");
		printf("   [time_to_sleep]\n");
		printf("   [number_of_times_each_philosopher_must_eat] ");
		printf("(optional argument)\n");
		return (FAILURE);
	}
	return (SUCCESS);
}
