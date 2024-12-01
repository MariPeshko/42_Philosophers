/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:19:15 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/01 19:33:14 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_new_calloc(size_t nmemb, size_t size)
{
	void	*r;

	r = malloc(size * nmemb);
	if (!r)
		return (0);
	memset(r, 0, (nmemb * size));
	return (r);
}

// поверну це, коли видалю libft
// static void	ft_putchar_fd(char c, int fd)
// {
// 	write(fd, &c, 1);
// }

void	ft_new_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}