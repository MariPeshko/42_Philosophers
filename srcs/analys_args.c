/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analys_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 19:12:39 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/07 14:42:58 by mpeshko          ###   ########.fr       */
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

int	analys_args(char **argv)
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