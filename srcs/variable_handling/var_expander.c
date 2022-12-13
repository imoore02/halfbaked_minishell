/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:25:48 by isobelmoore       #+#    #+#             */
/*   Updated: 2022/12/13 11:44:13 by isobelmoore      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	var_expand_util(t_token *token, t_var *var);

void	var_expander(t_concept *info, t_token *token, t_var *var)
{
	t_token *end;

	end = token->prev;
	while (token)
	{
		if (token->type == VAR)
			var_expand_util(token, var);
		if (token == end)
			break;
		token = token->next;
	}
}

static void	var_expand_util(t_token *token, t_var *var)
{
	int i;

	i = 0;
	while (token->str)
	{
		if (token->str[i] == '$'
				&& is_next_char_a_sep(token->str[i + 1]) == 0
					&& var_between_quotes(token->str, i) == 0)
					{ 
						var->start = i;
						find_var_str(info, token, var);
						replace_var(info, token, var); //find_var_str will return the var_str represented by the var_name;
					}
		else
			i++;
	}
}

static int	is_next_char_a_sep(char c)
{
	if (c == '$' || c == ' ' || c == '=' || c == '\0')
		return (1);
	else
		return (0);
}

static int	var_between_quotes(char *str, int i)
{
	if (i > 0)
	{
		if (str[i - 1] == '\"' && str[i + 1] == '\"')
			return (1);
		else
			return (0);
	}
	return (0);
}


/* var_expander_heredoc:
*	Heredoc variant of var_expander. Replaces a string containing an
*	environment variable, like $USER with its corresponding value.
*	Returns the replaced string. May return NULL on error.

char	*var_expander_heredoc(t_data *data, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$'
			&& is_next_char_a_sep(str[i + 1]) == false
			&& var_between_quotes(str, i) == false)
			str = replace_str_heredoc(str, recover_val(NULL, str + i, data), i);
		else
			i++;
	}
	return (str);
}
*/