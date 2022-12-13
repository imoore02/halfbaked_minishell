/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnum.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:33:36 by imoore            #+#    #+#             */
/*   Updated: 2022/10/26 14:27:42 by isobelmoore      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_countstr(char *string)
{
	int	i;

	i = 0;
	while (string[i])
		i++;
	return (i - 1);
}

int	ft_putnum(int str)
{
	int		i;
	char	*new;

	i = 0;
	new = ft_itoa(str);
	ft_countstr(new);
	i = ft_putstr(new);
	free(new);
	return (i);
}
