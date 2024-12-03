/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 00:50:32 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/03 13:51:27 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_mtx(t_table *table)
{
	//destroy_philo_mtx();
	int	i;
	
	i = 0;
	while(i < table->total_nmb)
	{
		pthread_mutex_destroy(table->f_mtxs[i]);
		free(table->f_mtxs[i]);
		table->f_mtxs[i] = NULL;
		i++;
	}
	free(table->f_mtxs);
	table->dead = NULL;
}