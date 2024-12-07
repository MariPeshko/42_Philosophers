/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:02:54 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/07 18:29:14 by mpeshko          ###   ########.fr       */
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
	unsigned long	timestamp;

	philo = (t_philo *)arg;
	i = 0;
	timestamp = 7777;
	int *result = malloc(sizeof(int));
	*result = philo->philo_id;
	if (philo->philo_id % 2 == 0)
		usleep(30);
	while (1)
	{
		if (philo->philo_id % 2 == 0)
		{
			pthread_mutex_lock(philo->left_f);
			if (philo->tbl->dead == true || philo->tbl->all_full == true)
			{
				pthread_mutex_unlock(philo->left_f);
				return ((void *)result);
			}
			pthread_mutex_lock(&philo->lock);
			timestamp = curr_time() - philo->tbl->start_time;
			pthread_mutex_unlock(&philo->lock);
			
			pthread_mutex_lock(&philo->tbl->mtx_msg);
			printf("%li %i has taken a fork\n", timestamp, philo->philo_id);
			pthread_mutex_unlock(&philo->tbl->mtx_msg);
			pthread_mutex_lock(philo->right_f);
			if (philo->tbl->dead == true || philo->tbl->all_full == true)
			{
				pthread_mutex_unlock(philo->left_f);
				pthread_mutex_unlock(philo->right_f);
				return ((void *)result);
			}
		}
		else
		{
			pthread_mutex_lock(philo->right_f);
			if (philo->tbl->dead == true || philo->tbl->all_full == true)
			{
				pthread_mutex_unlock(philo->right_f);
				return ((void *)result);
			}
			pthread_mutex_lock(&philo->lock);
			timestamp = curr_time() - philo->tbl->start_time;
			pthread_mutex_unlock(&philo->lock);
			
			pthread_mutex_lock(&philo->tbl->mtx_msg);
			printf("%li %i has taken a fork\n", timestamp, philo->philo_id);
			pthread_mutex_unlock(&philo->tbl->mtx_msg);
			pthread_mutex_lock(philo->left_f);
			if (philo->tbl->dead == true || philo->tbl->all_full == true)
			{
				pthread_mutex_unlock(philo->left_f);
				pthread_mutex_unlock(philo->right_f);
				return ((void *)result);
			}
		}
		pthread_mutex_lock(&philo->lock);
		timestamp = curr_time() - philo->tbl->start_time;
		pthread_mutex_unlock(&philo->lock);
		
		pthread_mutex_lock(&philo->tbl->mtx_msg);
		printf("%li %i has taken a fork\n", timestamp, philo->philo_id);
		pthread_mutex_unlock(&philo->tbl->mtx_msg);

		if (philo->tbl->dead == true || philo->tbl->all_full == true)
		{
			pthread_mutex_unlock(philo->left_f);
			pthread_mutex_unlock(philo->right_f);
			return ((void *)result);
		}
		pthread_mutex_lock(&philo->lock);
		timestamp = curr_time() - philo->tbl->start_time;
		pthread_mutex_unlock(&philo->lock);
		
		pthread_mutex_lock(&philo->tbl->mtx_msg);
		philo->status = EATING;
		printf("%li %i is eating\n", timestamp, philo->philo_id);
		pthread_mutex_unlock(&philo->tbl->mtx_msg);
		ft_usleep((philo->tbl->time_eat));
		pthread_mutex_lock(&philo->lock);
		philo->time_last_meal = curr_time();
		philo->amount_meal++;
		pthread_mutex_unlock(&philo->lock);
		
		pthread_mutex_unlock(philo->left_f);
		pthread_mutex_unlock(philo->right_f);
		
		if (philo->tbl->dead == true || philo->tbl->all_full == true)
			return ((void *)result);
		
		pthread_mutex_lock(&philo->lock);
		timestamp = curr_time() - philo->tbl->start_time;
		pthread_mutex_unlock(&philo->lock);
		
		if (philo->tbl->all_full == true && philo->tbl->all_full == true)
			return ((void *)result);
		
		pthread_mutex_lock(&philo->tbl->mtx_msg);
		philo->status = SLEEPING;
		printf("%li %i is sleeping\n", timestamp, philo->philo_id);
		pthread_mutex_unlock(&philo->tbl->mtx_msg);
		ft_usleep(philo->tbl->time_sleep);
		if (philo->tbl->dead == true)
			return ((void *)result);
		
		pthread_mutex_lock(&philo->lock);
		timestamp = curr_time() - philo->tbl->start_time;
		pthread_mutex_unlock(&philo->lock);
		
		if (philo->tbl->all_full == true)
			return ((void *)result);
		
		pthread_mutex_lock(&philo->tbl->mtx_msg);
		philo->status = THINKING;
		printf("%li %i is thinking\n", timestamp, philo->philo_id);
		pthread_mutex_unlock(&philo->tbl->mtx_msg);
		i++;
	}
	return ((void *)result);
}

// printf("Monitor: all full\n");
static void	*routine_loop(void *arg)
{
	t_table *table;
	t_philo	**philosophers;
	int		i;
	int *result;
	int x;

	table = (t_table *)arg;
	philosophers = table->philos;
	i = 0;
	x = 1001;
	result = &x;
	while (1)
	{
		usleep(100);
		if (!all_full(table))
			return ((void *)result);
		i = 0;
		while (i < table->total_nmb)
		{
			if (philosophers[i]->status != EATING)
			{
				if (is_dead_monitor(philosophers[i]) == 1)
				{
					pthread_mutex_lock(&table->mtx_dead);
					table->dead = true;
					pthread_mutex_unlock(&table->mtx_dead);
					return ((void *)result);
				}
			}
			i++;
		}
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
	pthread_create(&table->loop_thread, NULL, &routine_loop, table);
	if (table->total_nmb == 1)
	{
		ph = table->philos[i];
		if (pthread_create(&ph->thread_t, NULL, &routine_one, ph) != 0) 
			return (-1);
	}
	else if (table->total_nmb > 1)
	{
		while (i < table->total_nmb)
		{
			ph = table->philos[i];
			if (pthread_create(&ph->thread_t, NULL, &routine, ph) != 0) 
				return (i * -1);
			i++;
		}
	}
	
	i = 0;
	if (pthread_join(table->loop_thread, NULL) != 0)
		return (-2);
	while (i < table->total_nmb)
	{
		ph = table->philos[i];
		void *res;
		if (pthread_join(ph->thread_t, &res) != 0)
		{
			printf("pthread_join returned not 0\n");
			return (i + 1);
		}
		// if (res != NULL)
		// 	printf("Thread %d finished!\n", *(int *)res);
		// else if (res == NULL)
		// 	printf("res == NULL\n");
		i++;
		free(res);
	}
	
	return (SUCCESS);
}
