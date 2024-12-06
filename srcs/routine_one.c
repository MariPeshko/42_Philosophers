/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:21:10 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/06 16:31:46 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *routine_one(void *arg)
{
	t_philo	*philo;
	int *result;

	philo = (t_philo *)arg;
    result = malloc(sizeof(int));
	*result = philo->philo_id;
    pthread_mutex_lock(philo->right_f);
    pthread_mutex_lock(&philo->tbl->mtx_msg);
    printf("%li %i has taken a fork\n", curr_time(), philo->philo_id);
    pthread_mutex_unlock(&philo->tbl->mtx_msg);
    pthread_mutex_unlock(philo->right_f);
    while (1)
    {
        if (philo->tbl->dead == true)
            return ((void *)result);
    }
}
