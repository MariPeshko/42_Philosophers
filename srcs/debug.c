/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 23:13:37 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/03 20:19:06 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    print_tests(t_table *table)
{
    t_philo *p_test;
    
    printf("print_tests\n");
    printf("total number: %i\n", table->total_nmb);
    p_test = table->philos[0];
    printf("t_philo *p_test adress: %p\n", p_test);
    printf("time_last_meal: %li\n", p_test->time_last_meal);
    printf("______________________________________\n");
}
