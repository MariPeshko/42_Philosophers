/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:34:14 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/02 00:44:00 by mpeshko          ###   ########.fr       */
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

// static int	retrieve_sizet_nmb(char *str_nmb_of_phil, size_t *nmb)
// {
// 	size_t	phs;
// 	int		tmp;

// 	tmp = ft_atoi(str_nmb_of_phil);
// 	if (tmp < 0)
// 	{
// 		printf("Please enter a positive number of philosophers.\n");
// 		return(1);
// 	}
// 	if (tmp == 0)
// 	{
// 		printf("The table is empty. Where are the philosophers?\n");
// 		return(1);
// 	}
// 	phs = (size_t)tmp;
// 	printf("retrieve_sizet_nmb number_of_philosophers: %ld\n", phs);
// 	*nmb = phs;
// 	return (0);
// }

int	init_big_struct(t_big *big) // char **argv, 
{
	// if (retrieve_sizet_nmb(argv[1], &(big->nmb)) == 1)
	// 	return (1);
	big->ph_list = NULL;
	return (0);
}