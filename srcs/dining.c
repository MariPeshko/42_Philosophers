/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:02:54 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/04 18:56:06 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

time_t	curr_time()
{
	struct timeval current_time;
	time_t	value;
	
	gettimeofday(&current_time, NULL);
	value = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (value);
}

/**
 * Routine is neverending loop if every philosopher is alive.
 * If someone is dead, then bool dead is true, and this even break the circle.
*/
static void *routine(void *arg)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->tbl->mtx_dead);
		if (philo->tbl->dead == true)
		{
			pthread_mutex_unlock(&philo->tbl->mtx_dead);
			int *result = malloc(sizeof(int));
			*result = -1;
			return ((void *)result);
		}
		else
		{
			long diff;
			diff = (curr_time()) - philo->time_last_meal;
			printf("%li ms philosopher %i %li ms without meal\n", curr_time(), philo->philo_id, diff);
			if (diff >= philo->tbl->time_die || philo->tbl->time_die == 0)
			{
				philo->tbl->dead = true;
				pthread_mutex_lock(&philo->tbl->mtx_msg);
				printf("%li ms %i died\n", curr_time(), philo->philo_id);
				pthread_mutex_unlock(&philo->tbl->mtx_msg);
				pthread_mutex_unlock(&philo->tbl->mtx_dead);
				int *result = malloc(sizeof(int));
				*result = -1;
				return ((void *)result);
			}
			else
				pthread_mutex_unlock(&philo->tbl->mtx_dead);
		}
		pthread_mutex_lock(philo->left_f);
		pthread_mutex_lock(philo->right_f);
		if (philo->tbl->dead == true)
		{
			int *result = malloc(sizeof(int));
			*result = -1;
			pthread_mutex_unlock(philo->left_f);
			pthread_mutex_unlock(philo->right_f);
			return ((void *)result);
		}
		else
		{
			pthread_mutex_lock(&philo->tbl->mtx_msg);
			printf("%i has taken a fork\n", philo->philo_id);
			pthread_mutex_unlock(&philo->tbl->mtx_msg);
			philo->status = EATING;
			pthread_mutex_lock(&philo->tbl->mtx_msg);
			printf("%i is eating\n", philo->philo_id);
			pthread_mutex_unlock(&philo->tbl->mtx_msg);
			usleep(philo->tbl->time_eat * 1000);
			philo->time_last_meal = curr_time();
			pthread_mutex_unlock(philo->left_f);
			pthread_mutex_unlock(philo->right_f);
		}
		philo->status = SLEEPING;
		if (philo->tbl->dead == true)
		{
			int *result = malloc(sizeof(int));
			*result = -1;
			return ((void *)result);
		}
		pthread_mutex_lock(&philo->tbl->mtx_msg);
		printf("%li ms %i is sleeping\n", curr_time(), philo->philo_id);
		pthread_mutex_unlock(&philo->tbl->mtx_msg);
		usleep(philo->tbl->time_sleep * 1000);
		if (philo->tbl->dead == true)
		{
			int *result = malloc(sizeof(int));
			*result = -1;
			return ((void *)result);
		}
		i++;
	}
	int *result = malloc(sizeof(int));
	*result = philo->philo_id;
	return ((void *)result);
}

/**
 * Init start_time.
 * 
*/
int start_dining(t_table *table)
{
    printf("dining\n");
	table->start_time = curr_time();
	
	printf("start_time: %li\n", table->start_time);

	t_philo	*ph;
    int		i;

	i = 0;
	while (i < table->total_nmb)
	{
		ph = table->philos[i];
		ph->time_last_meal = table->start_time;
		i++;
	}
	i = 0;
	//t_philo	*ph;
	
	// if (table->time_die == 0)
	// {
	// 	table->dead = true;
	// 	printf("Philosopher needs more than 0 ms \n");
	// }
	if (table->total_nmb == 1)
	{
		ph = table->philos[i];
		printf("%li %i died\n", curr_time(), ph->philo_id);
		return (SUCCESS);
	}
	pthread_mutex_lock(&table->mtx_create);
	while (i < table->total_nmb)
	{
		ph = table->philos[i];
		if (pthread_create(&ph->thread_t, NULL, &routine, ph) != 0) 
			return (i + 1);
		i++;
	}
	pthread_mutex_unlock(&table->mtx_create);
	
	printf("Doing other things while the thread runs...\n");
    printf("Waiting for thread to complete...\n");
	i = 0;
	while(i < table->total_nmb)
	{
		ph = table->philos[i];
		void *res;
		if (pthread_join(ph->thread_t, &res) != 0)
		{
			printf("pthread_join returned not 0\n");
			return (i + 1);
		}
		if (res != NULL)
			printf("Thread %d finished!\n", *(int *)res);
		else if (res == NULL)
			printf("res == NULL\n");
		i++;
		free(res);
	}
	return (SUCCESS);
}
