/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_arg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:10:40 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/28 16:32:27 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    check_number_arg(int argc)
{
    if (argc != 5)
	{
		if (argc < 5)
			ft_dprintf("Please, give me more argument(s).\n");
		if (argc > 6)
			ft_dprintf("Oops!.. I'm confused! Too many arguments.\n");
		ft_dprintf("The program input:\n");
		ft_dprintf("./philosophers [number_of_philosophers] [time_to_die] ");
		ft_dprintf("[time_to_eat] [time_to_sleep]\n");
		exit(EXIT_FAILURE);
	}
}