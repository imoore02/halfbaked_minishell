/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_chk.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:58:05 by isobelmoore       #+#    #+#             */
/*   Updated: 2022/12/13 11:04:26 by isobelmoore      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

///IT MAY BE UNECESSARY TO DISTINGUISH BETWEEN ALL OF THESE TYPES (DEAUFLY ANF DQUOTE VAR VARQUOTE)

/* checks for any variables in the DEFAULT (word) or DQUOTE token types */
// operation: looks for '$' character -> if found will it set their types to
// either VAR (for DEFAULT) or VARQUOTE (for DQUOTE); 
static void	var_chk(t_concept *info, t_token *token)
{
	t_token	*tmp;
	t_token *end;

	tmp = token;
	end = tmp->prev;
	while (1)
	{
		if (tmp->type == DEFAULT || tmp->type == DQUOTE)
			find_if_var(tmp, end);
		if (tmp == end)
			break ; 
		tmp = tmp->nxt;
	}
}

/* looks for '$' characters in a str; if so changes the token 'type' */
static void	find_if_var(t_token *token, t_token *end)
{
	int	i;

	i = 0;
	while (token->str)
	{
		if (token->str[i] == '$')
		{	
			if (token->prev->type == HEREDOC && token->prev != end) //!= end is checking whether it was the first one in the list;
				break ; ///WHAT IS THIS CIRCUMSTANCE FOR ???
			else if (token->type == DEFAULT || token->type == DQUOTE)
				token->type = VAR;
		}
		i++;
	}
}