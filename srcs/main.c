/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:26:15 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/01 20:17:22 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// We can have more than one mutex_t
// mutex m1, m2, m3, m4, m5;
// 5 forks are 5 mutexes
pthread_mutex_t mutex;
// additional mutex for proper output
// Allowing only (N - 1) philosophers to attempt picking up forks 
// simultaneously (using a separate mutex or semaphore for this purpose).

static void *routine() // void *arg
{
	printf("routine\n");
	//t_big *big;
	//big = (t_big *)arg;
	//printf("%d has taken a fork\n", big->t_num);
	//printf("%d is eating\n", big->t_num);
	pthread_mutex_lock(&mutex);
	//usleep(big->time_to_eat * 1000);
	int *result = malloc(sizeof(int));
	*result = 14;
    pthread_mutex_unlock(&mutex);
	return ((void *)result);
}



// void* routine(void *arg)
// {
// 	int *result = arg;
//     printf("Hello from threads %d\n", *result);
//     sleep(2);
//     printf("Ending thread %d\n", *result);
// 	return ((void *)result);
// }



int	main(int argc, char **argv)
{
	check_number_arg(argc);
	if (analys_args(argv) == 1)
		return (1);
	pthread_mutex_init(&mutex, NULL);

	t_big *big;
	big = ft_new_calloc(1, sizeof(t_big));
	if (big == NULL)
	{
		ft_putstr_fd("Problems with malloc\n", 2);
		return (1);
	}
	if (init_big_struct(big) == 1)
	{
		printf("init_big_struct returns 1, exit\n");
		free(big);
		return (1);
	}
	fill_big_list(argv, &big);
	
	int	nmb;
	nmb = ((t_data *)(big->ph_list->content))->forks;
	printf("is this norm?\n");
	printf("((t_data *)(big->ph_list->content))->forks %d\n", ((t_data *)(big->ph_list->content))->forks);
	nmb = 1;
	
	struct timeval current_time;
	gettimeofday(&current_time, NULL);
	printf("micro seconds : %ld\n", current_time.tv_usec);
	// Array to store thread IDs
	pthread_t	tt = ((t_data *)(big->ph_list->content))->thread;
	// Array to pass thread numbers as arguments
	//int thread_numbers[nmb];
	
	int	i = 0;
	// Ось тут додам ітерацію по лінкед лісту.
	// Функція pthread_create буде отримувати новий нод
	// для кожного філософа.
	while(i < nmb)
	{
		// 1 for 1t thread, 2 for 2d thread
		if (pthread_create(&tt, NULL, &routine, NULL) != 0) 
			return (i + 1);
		i++;
	}
	printf("Doing other things while the thread runs...\n");
    printf("Waiting for thread to complete...\n");
	i = 0;
	while(i < nmb)
	{
		// void **__thread_return
		void *res;
		if (pthread_join(tt, (void**) &res) != 0)
			return (i + 1);
		if (res != NULL)
			printf("Thread %d died!\n", *(int *)res);
		i++;
		free(res);
	}
	
	pthread_mutex_destroy(&mutex);

	sleep(2);

	// struct timeval current_time_2;
	// gettimeofday(&current_time_2, NULL);
	// // printf("seconds : %ld\nmicro seconds : %ld\n",
	// // 	current_time_2.tv_sec, current_time_2.tv_usec);
	// if (current_time.tv_sec == current_time_2.tv_sec)
	// {
	// 	long	time;
	// 	time = current_time_2.tv_usec - current_time.tv_usec;
	// 	printf("Duration of execution is %ld ms\n", time);
	// }
	// else
	// {
	// 	//printf("More than one second.\n");
	// 	long	time;
	// 	time = 0;
	// 	if ((current_time_2.tv_sec - current_time.tv_sec) > 1)
	// 		time = current_time_2.tv_sec - current_time.tv_sec - 1;
	// 	//printf("%ld full second(s) in between\n", time);
	// 	time *= 1000000;
	// 	time = time + (1000000 - current_time.tv_usec);
	// 	//printf("%ld with a rest from previous second\n", time);
	// 	time += current_time_2.tv_usec;
	// 	printf("Duration of execution is %ld ms\n", time);
	// }
	
	free((t_data *)(big->ph_list->content));
	free(big->ph_list);
	free(big);
	return (0);
}