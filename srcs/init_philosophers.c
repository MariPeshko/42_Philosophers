/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:08:47 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/02 20:44:49 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// tip:
// int pthread_mutex_init(pthread_mutex_t *restrict mutex,
// const pthread_mutexattr_t *restrict attr);
/**
 * If the number of mutexes is dynamic or only known at runtime, allocating 
 * memory for pthread_mutex_t variables dynamically is a good practice.
 * 
 * 1. Allocate memory for the array of pointers. Each element of this array 
 * will point to a pthread_mutex_t.
 * 2. Allocate memory for each individual pthread_mutex_t.
 * 
 * @param f_mtxs is a pointer to an array of pointers. Each element in the 
 * array is a pthread_mutex_t * (a pointer to a pthread_mutex_t).
*/
static int	init_forks(t_table *table)
{
	pthread_mutex_t **mutex_array;
	int	i;
	
	i = 0;
	mutex_array = ft_new_calloc(table->total_nmb, sizeof(pthread_mutex_t *));
	if (!mutex_array)
	{
	//malloc error return (1)
		printf("malloc error\n");
		return (1);
	}
	while(i < table->total_nmb)
	{
		mutex_array[i] = ft_new_calloc(1, sizeof(pthread_mutex_t));
		// if (!table->mtxs[i]) malloc error return (1)
		if (pthread_mutex_init(mutex_array[i], NULL) != 0)
		{
			write(2, "mutex init failed", 17);
			return (1);
		}
		i++;
		
	}
	table->f_mtxs = mutex_array;
	return (0);
}

/**
 * 1. A pointer to a struct table is assigned to "tbl".
 * 2. ID is assign to philo_id variable.
 * 3. Initialization of mutex for ...
 * 4. Assigning a pointer to the left and right forks, which are represented
 *  by mutexes.
 * 
 * @param i is an iterator from a loop, starts from 0, so i = 0 for 
 * 1-st philosopher, i = 1 is for 2-d philosopher.
 * @param tbl - a pointer to a struct table
 * @param philo_id - each philosoph has it's own id number (from 1 to n)
*/
 static int    assign_value_philos(t_table *table, t_philo *philosoph, int i)
 {
    philosoph->tbl = table;
    philosoph->philo_id = i + 1;
    // Initialization of mutex for ...
	if (pthread_mutex_init(&philosoph->lock, NULL) != 0)
	{
		write(2, "mutex init failed", 17);
		return (1);
	}
	// What is right fork?
	if ((i + 1) == table->total_nmb)
		philosoph->right_f = table->f_mtxs[0];
	else
		philosoph->right_f = table->f_mtxs[i + 1];
	philosoph->left_f = table->f_mtxs[i];
    philosoph->status = THINKING;
    return (0);
 }

/**
 * Initialization "total_nmb" of philosophers which represented by
 * struct s_philo.
 * 1. First: allocate memory for the array of pointers.
 * Each element of this array will point to an array of structs.
 * 2. Assigning values for each philosopher.
 * 
 * @param philos is a pointer to a pointer
*/
int	init_philosophers(t_table *table)
{
	printf("init_philosophers\n");
    int	i;
	
	i = 0;
    // Allocate memory for the array of pointers
	table->philos = ft_new_calloc(table->total_nmb, sizeof(t_philo *));
    // if (!table->philos) - malloc error, return failure

    // READY
    if (init_forks(table) == 1)
		return (FAILURE);
	//printf("philo_test_2\n");
	while(i < table->total_nmb)
	{
		table->philos[i] = ft_new_calloc(1,  sizeof(t_philo));
        // if (!table->philos[i]) - malloc error, return failure

        // NOT READY
        assign_value_philos(table, table->philos[i], i);
		i++;
	}
	return (0);
}
