/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 13:33:08 by isobelmoore       #+#    #+#             */
/*   Updated: 2022/12/12 16:51:02 by isobelmoore      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void syntax_chk(t_concept *info, t_token *token)
{
	t_token	*tmp;
	t_token *end;

	tmp = token;
	end = tmp->prev;
	while (tmp)
	{
		if (tmp->prev != end && tmp->type >= PIPE && tmp->prev->type >= PIPE)
			error(info, ERROR_SYNTAX);
		tmp = tmp->nxt;
	}
	return (0);
}