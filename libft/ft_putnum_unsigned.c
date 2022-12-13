/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnum_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoore <imoore@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:35:18 by imoore            #+#    #+#             */
/*   Updated: 2022/10/17 19:55:25 by imoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putcharuns(int c, char *i)
{
	write(1, &c, 1);
	i[0]++;
}

void	ft_recursive_print(unsigned int num, char *i)
{
	if (num >= 10)
	{
		ft_recursive_print(num / 10, i);
		ft_recursive_print(num % 10, i);
	}
	else
		ft_putcharuns(num + '0', i);
}

int	ft_putnum_unsigned(unsigned int num)
{
	int		total_leng;
	char	*i;

	total_leng = 0;
	i = malloc(1);
	i[0] = 0;
	if (num == 0)
	{
		free (i);
		return (write(1, "0", 1));
	}
	else
		ft_recursive_print(num, i);
	total_leng += i[0];
	free (i);
	return (total_leng);
}
