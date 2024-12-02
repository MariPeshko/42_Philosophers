/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:26:15 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/02 15:15:20 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_table *table;
	
	if (check_number_arg(argc) == 1)
		return (FAILURE);
	if (analys_args(argv) == 1)
		return (FAILURE);
	table = ft_new_calloc(1, sizeof(table));
	if (table == NULL)
		return (FAILURE);
	if (init_table(argv, table) == 1)
	{
		free(table);
		return (FAILURE);
	}
	if (init_mtx(&table) == 1)
	{
		free(table);
		return (FAILURE);
	}
	init_philosophers(table);
	//print_tests(table);
	start_dining(table);
	// знищити s_philo	**philos;
	free(table);
	return (SUCCESS);
}
