/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:26:15 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/25 16:24:54 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int mails = 0;

void* routine(void *arg)
{
	int *result = arg;
    printf("Hello from threads %d\n", *result);
    sleep(2);
    printf("Ending thread\n");
	return ((void *)result);
}

int	main(int argc, char **argv)
{
	no_arg(argc);
	
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
	return (0);
}