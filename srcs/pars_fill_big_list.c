/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_fill_big_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:59:04 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/02 00:55:33 by mpeshko          ###   ########.fr       */
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

int	init_tmp(t_data *tmp, t_data *base, int i)
{
	//pthread_t *th;
	
	tmp->total_nmb = base->total_nmb;
	tmp->forks = tmp->total_nmb;
	tmp->time_to_die = base->time_to_die;
	tmp->time_to_eat = base->time_to_eat;
	tmp->time_to_sleep = base->time_to_sleep;
	//tmp->thread = th;
	tmp->thread_number = i;
	printf("thread_number: %d\n", tmp->thread_number);
	return (0);
}

int	init_base_data(char **argv, t_data *tmp)
{
	if (pars_num_of_phil(argv[1], &(tmp->total_nmb)) != 0)
		return (1);
	tmp->forks = tmp->total_nmb;
	printf("number_of_forks: %d\n", tmp->forks);
	if (pars_timing(argv[2], &(tmp->time_to_die)) != 0)
		return (1);
	printf("time_to_die: %d milliseconds\n", tmp->time_to_die);
	if (pars_timing(argv[3], &(tmp->time_to_eat)) != 0)
		return (1);
	printf("time_to_eat: %d milliseconds\n", tmp->time_to_eat);
	if (pars_timing(argv[4], &(tmp->time_to_sleep)) != 0)
		return (1);
	printf("time_to_sleep: %d milliseconds\n", tmp->time_to_sleep);
	return (0);
}

int	ft_init_list (t_list **linked_list, t_data *base)
{
	t_data	*tmp;
	int		count;
	int		i;
	
	tmp = NULL;
	count = base->total_nmb;
	i = 1;
	while (i <= count)
	{
		tmp = ft_calloc(1, sizeof(t_data));
		if (!tmp)
		{
			ft_putstr_fd("Problems with malloc\n", 2);
			return (1);
		}
		if (init_tmp(tmp, base, i) == 1)
			return (1);
		// тут додаємо новий нод для кожного філософа.
		ft_lstadd_back(linked_list, ft_lstnew(tmp));
		i++;
	}
	return (0);
}

int fill_big_list(char **argv, t_big **big)
{
    t_list	*linked_list;
	t_data *base;
	linked_list = NULL;
	
	base = ft_new_calloc(1, sizeof(t_data));
	if (init_base_data(argv, base) == 1)
	{
		free(base);
		return (1);
	}
    // ЗАПАКУВАТИ СТВОРЕННЯ ЛИСТА У ЦЮ ФУНКЦІЮ
    if (ft_init_list (&linked_list, base) == 1)
	{
		// free all linked_list;
		free(base);
		return (1);
	}
    (*big)->ph_list = linked_list;
	free(base);
	return (0);
}