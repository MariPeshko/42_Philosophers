/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_nmb_argc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:10:40 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/08 19:01:00 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int    check_number_arg(int argc)
{
    if (argc < 5 || argc > 6)
	{
		if (argc < 5)
			printf("[Error] Please, give me more argument(s).\n");
		if (argc > 6)
			printf("[Error] Oops!.. Too many arguments.\n");
		printf("The program input:\n");
		printf("   ./philosophers\n   [number_of_philosophers]\n");
		printf("   [time_to_die]\n   [time_to_eat]\n");
		printf("   [time_to_sleep]\n");
		printf("   [number_of_times_each_philosopher_must_eat] ");
		printf("(optional argument)\n");
		return (FAILURE);
	}
	return (SUCCESS);
}
