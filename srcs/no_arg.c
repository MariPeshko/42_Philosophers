/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_arg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:10:40 by mpeshko           #+#    #+#             */
/*   Updated: 2024/11/25 16:11:17 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    no_arg(int argc)
{
    if (argc != 2)
	{
		ft_dprintf("The program input:\n./philosophers [number_of_philosophers]\n");
		exit(EXIT_FAILURE);
	}
}