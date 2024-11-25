/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:26:15 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/24 19:32:08 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int x = 2;

void* routine2()
{
	x += 4;
	printf("Process id: %d\n", getpid());
    printf("Hello from threads\n");
	printf("The value of x is: %d\n", x);
    sleep(2);
    printf("Ending thread\n");
	return (0);
}

void* routine()
{
	x += 1;
	printf("Process id: %d\n", getpid());
    printf("Hello from threads\n");
	printf("The value of x is: %d\n", x);
    sleep(2);
    printf("Ending thread\n");
	return (0);
}

int	main(void)
{
	pthread_t	t1, t2;
	
	printf("The value of x is: %d\n", x);
	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
	{
		return (1);
	}
	if (pthread_create(&t2, NULL, &routine2, NULL) != 0)
	{
		return (2);
	}
	 if (pthread_join(t1, NULL) != 0)
	 {
        return (3);
    }
    if (pthread_join(t2, NULL) != 0)
	{
        return (4);
    }
	return (0);
}