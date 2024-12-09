/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:10:40 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/09 14:06:03 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	err_msg_extra_min_plus(int nbr)
{
	printf("Sorry, there is an extra - or + ");
	printf("in argument %i.\nTry again!\n", nbr);
}

static void	err_msg_not_digit(char c, int nbr)
{
	printf("'%c' is not a digit in argument %i.\n", c, nbr);
	printf("Please avoid using letters or ");
	printf("special characters.\n");
}

static int	arg_plus_minus_digit_check(char *argv, int nbr)
{
	int	i;

	i = 0;
	if (argv[i] == '+' || argv[i] == '-')
		i++;
	if (argv[i] == '+' || argv[i] == '-')
	{
		err_msg_extra_min_plus(nbr);
		return (1);
	}
	while (argv[i])
	{
		if (ft_isdigit(argv[i]))
			i++;
		else
		{
			err_msg_not_digit(argv[i], nbr);
			return (1);
		}
	}
	return (0);
}

static int	arg_valid_check(char *argv, int nbr)
{
	if (!*argv)
	{
		printf("Argument %i is an empty string\n", nbr);
		return (1);
	}
	if (arg_plus_minus_digit_check(argv, nbr))
		return (1);
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
