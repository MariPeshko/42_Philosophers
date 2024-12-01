/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_fill_big_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:59:04 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/01 20:14:16 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	pars_num_of_phil(char *str_nmb_of_phil, int *int_from_big_struct)
{
	int	phs;

	phs = ft_atoi(str_nmb_of_phil);
	printf("number_of_philosophers: %d\n", phs);
	if (phs < 0)
	{
		printf("Please enter a positive number of philosophers.\n");
		return(1);
	}
	if (phs == 0)
	{
		printf("The table is empty. Where are the philosophers?\n");
		return(1);
	}
	*int_from_big_struct = phs;
	return (0);
}

static int	pars_timing(char *str_time_to_do, int *int_from_big_struct)
{
	int	time_to_do;

	time_to_do = ft_atoi(str_time_to_do);
	if (time_to_do < 0)
	{
		printf("Please enter a positive number of time_to_do.\n");
		return(1);
	}
	if (time_to_do == 0)
	{
		printf("time_to_do is 0. What am I doing?\n");
		return(0);
	}
	*int_from_big_struct = time_to_do;
	return (0);
	
}

int	init_tmp(char **argv, t_data *tmp)
{
	pthread_t	th;

	th = 0;
	if (pars_num_of_phil(argv[1], &(tmp->total_nmb)) != 0)
		return (1);
	tmp->forks = tmp->total_nmb;
	printf("number of forks: %d\n", tmp->forks);
	if (pars_timing(argv[2], &(tmp->time_to_die)) != 0)
		return (1);
	printf("time_to_die: %d milliseconds\n", tmp->time_to_die);
	if (pars_timing(argv[3], &(tmp->time_to_eat)) != 0)
		return (1);
	printf("time_to_eat: %d milliseconds\n", tmp->time_to_eat);
	if (pars_timing(argv[4], &(tmp->time_to_sleep)) != 0)
		return (1);
	printf("time_to_sleep: %d milliseconds\n", tmp->time_to_sleep);
	tmp->thread = th;
	return (0);
}

int fill_big_list(char **argv, t_big **big)
{
    t_list	*linked_list;
	//t_data	*ph_info;
    t_data	*tmp;

	linked_list = NULL;

    // ЗАПАКУВАТИ СТВОРЕННЯ ЛИСТА У ЦЮ ФУНКЦІЮ
    // ft_init_list
    
    // ph_info = ft_calloc(1, sizeof(t_data));
	// if (!ph_info)
	// {
	// 	ft_putstr_fd("Problems with malloc\n", 2);
	// 	return (1);
	// }
	
	tmp = ft_calloc(1, sizeof(t_data));
	if (!tmp)
	{
		ft_putstr_fd("Problems with malloc\n", 2);
		return (1);
	}
	if (init_tmp(argv, tmp) == 1)
		return (1);
	ft_lstadd_back(&linked_list, ft_lstnew(tmp));
    // тут додаємо новий нод для кожного філософа.
    
    (*big)->ph_list = linked_list;
	return (0);
}