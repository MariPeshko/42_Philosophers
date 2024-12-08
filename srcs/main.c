/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:26:15 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/08 22:01:35 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//print_tests(table);
int	main(int argc, char **argv)
{
	t_table	*table;

	if (check_number_arg(argc) == 1)
		return (FAILURE);
	if (check_args(argv) == 1)
		return (FAILURE);
	table = ft_new_calloc(1, sizeof(t_table));
	if (table == NULL)
		return (FAILURE);
	if (init_table(argv, table) == 1)
	{
		free(table);
		return (FAILURE);
	}
	if (init_mtx(table) == 1)
	{
		free(table);
		return (FAILURE);
	}
	init_philosophers(table);
	start_dining(table);
	destroy_mtx(table);
	free_philos(table->philos, table->total_nmb);
	free(table);
	return (SUCCESS);
}
