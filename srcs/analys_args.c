/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analys_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 19:12:39 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/01 19:13:14 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_digit_check(char *argv)
{
	int	i;

	i = 0;
	if (argv[i] == '+' || argv[i] == '-')
			i++;
	if (argv[i] == '+' || argv[i] == '-')
	{
		printf("Sorry, there is an extra - or + here. Try again!\n");
		return (1);
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
			return (1);
		}
	}
	return (0);
}

int	analys_args(char **argv)
{
	if (is_digit_check(argv[1]) == 1)
		return (1);
	if (is_digit_check(argv[2]) == 1)
		return (1);
	if (is_digit_check(argv[3]) == 1)
		return (1);
	if (is_digit_check(argv[4]) == 1)
		return (1);
	return (0);
}