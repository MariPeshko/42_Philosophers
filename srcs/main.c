/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:26:15 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/28 17:48:43 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int mails = 0;
// We can have more than one mutex_t
pthread_mutex_t mutex;

// race condition
void* routine(void *arg)
{
	int *result = arg;
	printf("%d has taken a fork\n", *(int *)result);
    for (int i = 0; i < 100000; i++)
	{
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
    }
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
	pthread_mutex_init(&mutex, NULL);

	analys_args(argv);
	int	nmb;
	nmb = ft_atoi(argv[1]);

	struct timeval current_time;
	gettimeofday(&current_time, NULL);
	printf("micro seconds : %ld\n", current_time.tv_usec);
	// Array to store thread IDs
	pthread_t	t[nmb];
	// Array to pass thread numbers as arguments
	int thread_numbers[nmb];
	
	int			i;
	
	i = 0;
	while(i < nmb)
	{
		thread_numbers[i] = i + 1;
		if (pthread_create(&t[i], NULL, &routine, &thread_numbers[i]) != 0)
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
		if (pthread_join(t[i], &res) != 0)
			return (i + 1);
		printf("Thread %d died!\n", *(int *)res);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	printf("Number of mails: %d\n", mails);

	sleep(3);

	struct timeval current_time_2;
	gettimeofday(&current_time_2, NULL);
	// printf("seconds : %ld\nmicro seconds : %ld\n",
	// 	current_time_2.tv_sec, current_time_2.tv_usec);
	if (current_time.tv_sec == current_time_2.tv_sec)
	{
		long	time;
		time = current_time_2.tv_usec - current_time.tv_usec;
		printf("Duration of execution is %ld ms\n", time);
	}
	else
	{
		//printf("More than one second.\n");
		long	time;
		time = 0;
		if ((current_time_2.tv_sec - current_time.tv_sec) > 1)
			time = current_time_2.tv_sec - current_time.tv_sec - 1;
		//printf("%ld full second(s) in between\n", time);
		time *= 1000000;
		time = time + (1000000 - current_time.tv_usec);
		//printf("%ld with a rest from previous second\n", time);
		time += current_time_2.tv_usec;
		printf("Duration of execution is %ld ms\n", time);
	}
	return (0);
}