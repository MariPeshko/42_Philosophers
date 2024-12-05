/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:02:54 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/05 02:39:24 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * Routine is neverending loop if every philosopher is alive.
 * If someone is dead, then bool dead is true, and this even break the circle.
*/
static void *routine(void *arg)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)arg;
	int *result = malloc(sizeof(int));
	*result = -1;
	while (1)
	{
		if (is_dead(philo) == 1)
		{
			return ((void *)result);
		}
		if (philo->philo_id % 2 == 0)
		{
		// check availabilty of both - how?
		pthread_mutex_lock(philo->left_f);
		if (philo->tbl->dead == true)
		{
			pthread_mutex_unlock(philo->left_f);
			return ((void *)result);
		}
		pthread_mutex_lock(&philo->tbl->mtx_msg);
		printf("%li %i has taken a fork\n", curr_time(), philo->philo_id);
		pthread_mutex_unlock(&philo->tbl->mtx_msg);
		// check availabilty of both - how?
		pthread_mutex_lock(philo->right_f);
		if (philo->tbl->dead == true)
		{
			pthread_mutex_unlock(philo->right_f);
			return ((void *)result);
		}
		}
		else
		{
			pthread_mutex_lock(philo->right_f);
			if (philo->tbl->dead == true)
			{
				pthread_mutex_unlock(philo->right_f);
				return ((void *)result);
			}
			pthread_mutex_lock(&philo->tbl->mtx_msg);
			
			printf("%li %i has taken a fork\n", curr_time(), philo->philo_id);
			pthread_mutex_unlock(&philo->tbl->mtx_msg);
			pthread_mutex_lock(philo->left_f);
			if (philo->tbl->dead == true)
			{
				pthread_mutex_unlock(philo->left_f);
				return ((void *)result);
			}
		}
		pthread_mutex_lock(&philo->tbl->mtx_msg);
		printf("%li %i has taken a fork\n", curr_time(), philo->philo_id);
		pthread_mutex_unlock(&philo->tbl->mtx_msg);
		if (philo->tbl->dead == true)
		{
			pthread_mutex_unlock(philo->left_f);
			pthread_mutex_unlock(philo->right_f);
			return ((void *)result);
		}
		else if (is_dead(philo) == 1)
		{
			pthread_mutex_unlock(philo->left_f);
			pthread_mutex_unlock(philo->right_f);
			return ((void *)result);
		}
		else
		{
			philo->status = EATING;
			pthread_mutex_lock(&philo->tbl->mtx_msg);
			printf("%li %i is eating\n", curr_time(), philo->philo_id);
			pthread_mutex_unlock(&philo->tbl->mtx_msg);
			usleep(philo->tbl->time_eat * 1000);
			pthread_mutex_lock(&philo->lock);
			philo->time_last_meal = curr_time();
			pthread_mutex_unlock(&philo->lock);
			
			pthread_mutex_unlock(philo->left_f);
			pthread_mutex_unlock(philo->right_f);
		}
		philo->status = SLEEPING;
		pthread_mutex_lock(&philo->tbl->mtx_msg);
		if (philo->tbl->dead == true)
		{
			pthread_mutex_unlock(&philo->tbl->mtx_msg);
			return ((void *)result);
		}
		printf("%li %i is sleeping\n", curr_time(), philo->philo_id);
		pthread_mutex_unlock(&philo->tbl->mtx_msg);
		usleep(philo->tbl->time_sleep * 1000);
		if (philo->tbl->dead == true)
			return ((void *)result);
		pthread_mutex_lock(&philo->tbl->mtx_msg);
		printf("%li %i is thinking\n", curr_time(), philo->philo_id);
		pthread_mutex_unlock(&philo->tbl->mtx_msg);
		i++;
	}
	return ((void *)result);
}

static void	*routine_loop(void *arg)
{
	t_table *table;
	t_philo	**philosophers;
	int		i;

	table = (t_table *)arg;
	philosophers = table->philos;
	i = 0;
	int *result;
	int x;
	x = 1;
	result = &x;
	while (1)
	{
		i = 0;
		usleep(80);
		while (i < table->total_nmb)
		{
			if (philosophers[i]->status != EATING)
			{
				if (is_dead_monitor(philosophers[i]) == 1)
				{
					pthread_mutex_lock(&table->mtx_dead);
					table->dead = true;
					printf("actual death of %i philosopher\n", i + 1);
					detach_all(philosophers, table->total_nmb);
					pthread_mutex_unlock(&table->mtx_dead);
					return ((void *)result);
				}
			}
			if (table->dead == true)
				return ((void *)result);
			i++;
		}
		if (table->dead == true)
			return ((void *)result);
	}
}

/**
 * Init start_time.
 * 
*/
int start_dining(t_table *table)
{
	t_philo	*ph;
    int		i;

	i = 0;
	table->start_time = curr_time();
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
	pthread_create(&table->loop_thread, NULL, &routine_loop, table);
	//pthread_mutex_lock(&table->mtx_create);
	while (i < table->total_nmb)
	{
		ph = table->philos[i];
		if (pthread_create(&ph->thread_t, NULL, &routine, ph) != 0) 
			return (i + 1);
		i++;
	}
	//pthread_mutex_unlock(&table->mtx_create);
	
	i = 0;
	
	while (i < table->total_nmb)
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
	if (pthread_join(table->loop_thread, NULL) != 0)
		return (i + 1);
	return (SUCCESS);
}
