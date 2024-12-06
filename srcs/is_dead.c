/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dead.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:48:56 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/06 16:32:33 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	temp_print(t_philo **philosophers, int total_nmb)
{
	int	i;
	
    i = 0;
	while (i < total_nmb)
	{
		if (philosophers[i]->status == EATING)
		{
			printf("%i EATING\n", philosophers[i]->philo_id);
		}
		i++;
	}
	return (0);
}


int is_dead_monitor(t_philo *philo)
{
    long diff;
    
    diff = 0;
    if (philo->tbl->dead == true)
        return (0);
    pthread_mutex_lock(&philo->lock);
    diff = (curr_time()) - philo->time_last_meal;
    pthread_mutex_unlock(&philo->lock);
    //printf("%li %i %li ms without meal monitor\n", curr_time(), philo->philo_id, diff);
	if (diff >= philo->tbl->time_die || philo->tbl->time_die == 0)
    {
		pthread_mutex_lock(&philo->tbl->mtx_dead);
        philo->tbl->dead = true;
        pthread_mutex_lock(&philo->tbl->mtx_msg);
        printf("%li %i died\n", curr_time(), philo->philo_id);
        pthread_mutex_unlock(&philo->tbl->mtx_msg);
		pthread_mutex_unlock(&philo->tbl->mtx_dead);
        return (1);
    }
    else
        return (0);
}

int is_dead(t_philo *philo)
{
    long diff;
    
    diff = 0;
    pthread_mutex_lock(&philo->tbl->mtx_dead);
    if (philo->tbl->dead == true)
    {
        pthread_mutex_unlock(&philo->tbl->mtx_dead);
        return (1);
    }
    else
    {
        pthread_mutex_lock(&philo->lock);
        diff = (curr_time()) - philo->time_last_meal;
        pthread_mutex_unlock(&philo->lock);
		//printf("%li %i %li ms without meal\n", curr_time(), philo->philo_id, diff);
        if (diff >= philo->tbl->time_die || philo->tbl->time_die == 0)
        {
            philo->tbl->dead = true;
            pthread_mutex_lock(&philo->tbl->mtx_msg);
            printf("%li %i died\n", curr_time(), philo->philo_id);
            pthread_mutex_unlock(&philo->tbl->mtx_msg);
            pthread_mutex_unlock(&philo->tbl->mtx_dead);
            return (1);
        }
        else
        {
            pthread_mutex_unlock(&philo->tbl->mtx_dead);
            return (0);
        }
    }
}
		