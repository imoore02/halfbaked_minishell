/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 18:59:09 by isobelmoore       #+#    #+#             */
/*   Updated: 2022/12/13 11:54:34 by isobelmoore      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_var	*init_var_struct(t_var *var);
static char		*get_env_var_str(t_concept *info, t_var *var, char *var_name);

void	*find_var_str(t_concept *info, t_token *token, t_var *var)
{
	char *input;

	input = token->str;
	var->var_name = get_var_name(input);
	if (var->var_name)
		var->var_str = get_env_var_str(info, var, var->var_name);
	if (!var->var_str)
		error(info, ERROR_VARIABLE); //varible doesnt exist??
	else if (var_name && ft_strncmp(var, '?=', 2) == 0)
		var->var_str = ft_itoa(g_last_exit_code); ////need to complete this part; //ALSO will need to do it for the argvs? -> so i should probably number my tokens such that 
	else
		var->var_str = NULL; 
	free(var->var_name);
}

/* checks for the 'var_name' to see if it matches any of the variable names in */
/* the list of environment variables -> if it does returns the var_str refered */
/* to by the var_name; else it returns null if variable is not found */
static char	*get_env_var_str(t_concept *info, t_var *var, char *var_name)
{
	int		i;
	int		len;
	char 	*var_str;

	i = 0;
	len = ft_strlen(var_name);
	var_str = NULL;
	while (info->env[i])
	{
		if (ft_strncmp(info->env[i], var_name, len) == 0)
		{
			var_str = ft_strdup(info->env[i] + len); 
			break ;
		}
		i++;
	}
	return (var_str);
}