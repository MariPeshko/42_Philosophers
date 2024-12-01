/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:26:15 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/02 00:54:43 by mpeshko          ###   ########.fr       */
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
	if (init_big_struct(big) == 1) // argv, 
	{
		printf("init_big_struct returns 1, exit\n");
		free(big);
		return (1);
	}
	if (fill_big_list(argv, &big) == 1)
	{
		printf("fill_big_list returns 1, exit\n");
		free(big);
		return (1);
	}
	print_my_list(big);
	
	struct timeval current_time;
	gettimeofday(&current_time, NULL);
	printf("micro seconds : %ld\n", current_time.tv_usec);
	
	int	i = 0;
	t_list *iter;
	
	iter = ((t_list *)(big->ph_list));
	int n;
	t_data *ddd = (t_data *)(iter->content);
	n = ddd->thread;
	pthread_t	tt[n];
	while (iter)
	//while (i < nmb)
	{
		printf("loop %d\n", i);
		//pthread_t	tt;
		//tt = ((t_data *)((iter)->content))->thread;
		if (pthread_create(&tt[i], NULL, &routine, NULL) != 0) 
			return (i + 1);
		i++;
		iter = iter->next;
	}
	printf("Doing other things while the thread runs...\n");
    printf("Waiting for thread to complete...\n");
	
	int b = 0;
	
	t_list *iter_sec;
	iter_sec = ((t_list *)(big->ph_list));
	if (!iter_sec)
		printf("t_list iter_sec == NULL\n");
	while (iter_sec)
	//while(i < nmb)
	{
		printf("loop_join %d\n", b);
		//pthread_t	ttj;
		//ttj = ((t_data *)((iter_sec)->content))->thread;
		void *res;
		if (pthread_join(tt[b], &res) != 0)
		{
			printf("pthread_join returned not 0\n");
			return (b + 1);
		}
		if (res != NULL)
			printf("Thread %d died!\n", *(int *)res);
		else if (res == NULL)
			printf("res == NULL\n");
		b++;
		free(res);
		iter_sec = iter_sec->next;
	}
	
	sleep(2);
	
	pthread_mutex_destroy(&mutex);

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
	
	ft_free_cl(&(big->ph_list));
	free(big);
	big = NULL;
	return (0);
}