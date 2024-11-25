/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:26:15 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/26 00:11:27 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int mails = 0;
pthread_mutex_t mutex;

// race condition
void* routine(void *arg)
{
	int *result = arg;
    for (int i = 0; i < 1000000; i++)
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
	no_arg(argc);
	pthread_mutex_init(&mutex, NULL);
	
	int	nmb;
	nmb = ft_atoi(argv[1]);
	printf("Integer for number of philosophers is: %d\n", nmb);

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
		printf("Thread %d complete!\n", *(int *)res);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	printf("Number of mails: %d\n", mails);
	return (0);
}