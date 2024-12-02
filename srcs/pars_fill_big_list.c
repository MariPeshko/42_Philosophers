/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_fill_big_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:59:04 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/02 15:16:49 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"



int	init_mtx(t_table *table)
{
    if (pthread_mutex_init(&table->mtx_create, NULL) != 0)
	{
		write(2, "mutex init failed", 17);
		return (FAILURE);
	}
	return (SUCCESS);
}