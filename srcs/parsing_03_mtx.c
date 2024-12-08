/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_03_mtx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:59:04 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/08 22:08:44 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_mtx(t_table *table)
{
	if (pthread_mutex_init(&table->mtx_time, NULL) != 0)
	{
		write(2, "mutex init failed", 17);
		return (FAILURE);
	}
	if (pthread_mutex_init(&table->mtx_dead, NULL) != 0)
	{
		write(2, "mutex init failed", 17);
		return (FAILURE);
	}
	if (pthread_mutex_init(&table->mtx_msg, NULL) != 0)
	{
		write(2, "mutex init failed", 17);
		return (FAILURE);
	}
	return (SUCCESS);
}
