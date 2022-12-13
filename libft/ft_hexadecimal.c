/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexadecimal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoore <imoore@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:32:36 by imoore            #+#    #+#             */
/*   Updated: 2022/10/17 19:55:09 by imoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_hex(int c, char *i)
{
	write(1, &c, 1);
	i[0]++;
}

void	ft_write_hex(unsigned int num, char format, char *i)
{	
	if (num >= 16)
	{
		ft_write_hex(num / 16, format, i);
		ft_write_hex(num % 16, format, i);
	}
	else
	{
		if (num <= 9)
			ft_putchar_hex(num + '0', i);
		else
		{
			if (format == 'x')
				ft_putchar_hex(num - 10 + 'a', i);
			if (format == 'X')
				ft_putchar_hex(num - 10 + 'A', i);
		}
	}
}

int	ft_hexadecimal(unsigned int num, char format)
{
	char	*i;
	int		g;

	i = malloc(1);
	i[0] = 0;
	if (num == 0)
	{
		free (i);
		return (write(1, "0", 1));
	}
	else
		ft_write_hex(num, format, i);
	g = i[0];
	free (i);
	return (g);
}
