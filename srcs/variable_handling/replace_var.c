/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 18:10:57 by isobelmoore       #+#    #+#             */
/*   Updated: 2022/12/13 14:36:58 by isobelmoore      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void		erase(t_concept *info, t_token *token, t_var *var);
static void		replace(t_concept *info, t_token *token, t_var *var);
static void		*get_new_token_string(t_concept *info, t_token *token, t_var *var);
static void		copy_var_value(char *frankenstein, char *var_str, int *j);

/* main replacement: replaces the var_name with the var_str */
// operation: will replace only if the var_str is not NULL;
void	replace_var(t_concept *info, t_token *token, t_var *var)
{
	if (var->var_str == NULL)
		erase(token, token->str, var->start)
		erase(info, token, var);
	else
		replace(info, token, var);
}

/* where the var_str does not exist or is empty rather than replace the */
/* var_name it will simply erase it */
static void	erase(t_concept *info, t_token *token, t_var *var)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = ft_strlen(str) - var_length(str + index);
	var->frankenstein = (char *)malloc(sizeof(char) * len + 1);
	if (!var->frankenstein)
		error(info, ERROR_MALLOC);
	while (token->str)
	{
		if (token->str[i] == '$')
		{
			i = i + ft_strlen()) + 1;
			if (str[i] == '\0')
				break ;
		}
		var->frankenstein[j++] = token->str[i++];
	}
	var->frankenstein[j] = '\0';
	free(token->str);
	token->str = var->frankenstein;
}

/* replaces the var_name with the var_str */
// operation: devises the 'len' (new string length) by taking the length of
// the original string and subtracting the length of the variable name and then
// adding the length of the corresponding variable string;
static void replace(t_concept *info, t_token *token, t_var *var)
{
	char	*newstr;

	var->new_len = (ft_strlen(token->str) - var_length(token->str) + ft_strlen(var->var_str));
	get_new_token_string(info, token, var);
	free(token->str);
	token->str = ft_strdup(var->frankenstein);
	if (!token_str)
		error(info, ERROR_MALLOC);
	free(newstr);
}

/* this creates a string called 'frankenstein' which is a string with the */
/* var_str in the place of the var_name */
static void	*get_new_token_string(t_concept *info, t_token *token, t_var *var)
{
	int		i;
	int		j;

	var->frankenstein = malloc(sizeof(char) * var->new_len + 1); //i think ive probably already malloced this somewher but double check that;
	if (!var->frankenstein)
		error(info, ERROR_MALLOC);
	i = 0;
	j = 0;
	while (token->str)
	{
		if (token->str[i] == '$')
		{
			copy_var_value(var->frankenstein, var->var_str, &j);
			i = i + ft_strlen(var->var_name) + 1; //moves this up only so far as the var_name
			if (token->str[i] == '\0')
				break ;
		}
		var->frankenstein[j++] = token->str[i++];
	}
	var->frankenstein[j] = '\0';
}

static void	copy_var_value(char *frankenstein, char *var_str, int *j)
{
	int	i;

	i = 0;
	while (var_str)
	{
		frankenstein[*j] = var_str[i];
		i++;
		(*j)++;
	}
}