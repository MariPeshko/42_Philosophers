/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:26:15 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/25 16:13:05 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int mails = 0;

void* routine()
{
    printf("Hello from threads\n");
    sleep(2);
    printf("Ending thread\n");
	return (0);
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
	i = 0;
	while(i < nmb)
	{
		if (pthread_join(t[i], NULL) != 0)
			return (i + 1);
		i++;
	}
	return (0);
}