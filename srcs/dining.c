/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:02:54 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/02 15:43:48 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void *routine() // void *arg
{
	printf("routine\n");
	pthread_mutex_lock(&mutex);
	//usleep(big->time_to_eat * 1000);
	int *result = malloc(sizeof(int));
	*result = 14;
    pthread_mutex_unlock(&mutex);
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
void start_dining(t_table *table)
{
    printf("dining\n");
	start_time(&table->start_time);
	
    int i = 0;
	pthread_mutex_lock(&table->mtx_create);
	while (iter)
	{
		printf("loop %d\n", i);
		if (pthread_create(&tt[i], NULL, &routine, NULL) != 0) 
			return (i + 1);
		i++;
		iter = iter->next;
	}
	pthread_mutex_unlock(&table->mtx_create);
	printf("Doing other things while the thread runs...\n");
    printf("Waiting for thread to complete...\n");
	i = 0;
	while(i < nmb)
	{
		printf("loop_join %d\n", b);
		void *res;
		if (pthread_join(tt[b], &res) != 0)
		{
			printf("pthread_join returned not 0\n");
			return (i + 1);
		}
		if (res != NULL)
			printf("Thread %d died!\n", *(int *)res);
		else if (res == NULL)
			printf("res == NULL\n");
		i++;
		free(res);
	}
}
