/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:26:15 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/02 20:44:31 by mpeshko          ###   ########.fr       */
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
	//printf("test_00\n");
	table = ft_new_calloc(1, sizeof(table));
	if (table == NULL)
		return (FAILURE);
	//printf("test_01\n");
	// ready
	if (init_table(argv, table) == 1)
	{
		free(table);
		return (FAILURE);
	}
	//printf("test_02\n");
	
	// not ready
	if (init_mtx(table) == 1)
	{
		free(table);
		return (FAILURE);
	}
	//printf("test_03\n");
	
	// not ready
	init_philosophers(table);
	//printf("test_04\n");
	print_tests(table);

	//start_dining(table);
	
	// знищити s_philo	**philos;
	free(table);
	return (SUCCESS);
}
