/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_var_handling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 11:16:01 by isobelmoore       #+#    #+#             */
/*   Updated: 2022/12/13 14:55:24 by isobelmoore      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_var	*init_var_struct(t_var *var);
static void		 free_var_struct(t_var *var);

int var_handling(t_concept *info)
{
	t_var *var;

	info->var = init_var_struct(var);
	var_chk(info, info->token); //(1) will move through the token string and change the 'types' to suit whether a variable is detected or not;
	var_expander(info, info->token); //(2) if a variable is found it will expand it;
	free_var_struct(var);
}

static t_var	*init_var_struct(t_var *var)
{
	var = (t_var *)malloc(sizeof(t_var));
	if (!var)
		error(info, ERROR_MALLOC);
	var->var_name = NULL;
	var->var_str = NULL;
	var->start = 0;
	var->new_len = 0;
	return (var);
}

//i suppose this is how this works but i would rather just free as i go along but this is easier to keep track of;
static void	free_var_struct(t_var *var)
{
	if (var)
	{
		free(var->var_name);
		var->var_name = NULL;
		free(var->var_str);
		var->var_str = NULL;
		free(var->frankstein);
		var->frankenstein;
	}
}
