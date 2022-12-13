/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:51:38 by isobelmoore       #+#    #+#             */
/*   Updated: 2022/12/06 13:57:03 by isobelmoore      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//____CLEANS UP: PRINTS ERRORS(if any), FREES AND EXITS PROGRAM/EXECUTION_____//

static void	free_list(t_token *token);

void	error(t_concept *info, char *errorcode)
{
	ft_putstr(errorcode);
	clean_end(info);
	exit(-1); //not quite sure what this means
}

void	clean_end(t_concept *info)
{
	if (info)
	{
		if (info->paths)
		{
			free(info->paths);
			info->paths = NULL;
		}
		if (info->input)
		{
			free(info->input);
			info->input = NULL;
		}
		if (info->token)
		{
			free_list(info->token);
			info->token = NULL;
		}
		free (info);
	}
}

//will clean up the input/reset it for each loop re-run ->but will not destory envp **paths variable which is valuable; (dunno if you can retrive it more than once so ill jsut grab it at the very start);
void	clean_loop(t_concept *info)
{
	if (info)
	{
		if (info->input)
		{
			free(info->input);
			info->input = NULL;
		}
		if (info->token)
		{
			free_list(info->token);
			info->token = NULL;
		}
	}
}

/*/---IDK WHAT THERE IS REALLY TO CLEAN UP YET--/*/
static void	free_list(t_token *token)
{
	t_token	*current;
	t_token	*sacrifice;

	if (token)
	{
		current = token->nxt;
		while (current != token)
		{
			sacrifice = current;
			current = current->nxt;
			free(sacrifice);
		}
		free(current);
	}
}