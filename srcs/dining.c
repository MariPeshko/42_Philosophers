/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:02:54 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/03 14:55:18 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * Routine is neverending loop if every philosopher is alive.
 * If someone is dead, then bool dead is true, and this even break the circle.
*/
static void *routine(void *arg) // void *arg
{
	int		i;
	t_philo	*philo;

	i = 2;
	philo = (t_philo *)arg;
	while (i >= 1)
	{
		pthread_mutex_lock(philo->left_f);
		pthread_mutex_lock(philo->right_f);
		printf("%i has taken a fork\n", philo->philo_id);
		philo->status = EATING;
		printf("%i is eating\n", philo->philo_id);
		usleep(philo->tbl->time_eat * 1000);
		if (philo->tbl->dead == true)
		{
			int *result = malloc(sizeof(int));
			*result = -1;
			return ((void *)result);
		}
		philo->status = SLEEPING;
		printf("%i is sleeping\n", philo->philo_id);
		pthread_mutex_unlock(philo->left_f);
		pthread_mutex_unlock(philo->right_f);
		usleep(philo->tbl->time_sleep * 1000);
		i--;
	}
	int *result = malloc(sizeof(int));
	*result = philo->philo_id;
	return ((void *)result);
}

void	start_time(long *start_time)
{
	struct timeval current_time;
	long	value;
	
	gettimeofday(&current_time, NULL);
	value = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	*start_time = value;
}

/**
 * Init start_time.
 * 
*/
int start_dining(t_table *table)
{
    printf("dining\n");
	start_time(&table->start_time);
	
    int i = 0;
	t_philo	*ph;
	
	//pthread_mutex_lock(&table->mtx_create);
	while (i < table->total_nmb)
	{
		ph = table->philos[i];
		if (pthread_create(&ph->thread_t, NULL, &routine, ph) != 0) 
			return (i + 1);
		i++;
	}
	//pthread_mutex_unlock(&table->mtx_create);
	
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
