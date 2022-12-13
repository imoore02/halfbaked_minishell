/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:47:39 by isobelmoore       #+#    #+#             */
/*   Updated: 2022/12/13 11:19:02 by isobelmoore      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char *find_path(char **envp);

t_concept	*initialise(t_concept *info, char **envp)
{
	info = (t_concept *)malloc(sizeof(t_concept));
	if (info == NULL)
		error(info, ERROR_MALLOC);
	info->token = NULL; //is this how i should init this?
	info->input = NULL;
	info->paths = ft_split((find_path(envp)), ':'); //ft_split does malloc inside it - therefore free this in teh clean stuff up part.
	info->env = envp;
	info->var = NULL;
	return (info);
}

static char *find_path(char **envp)
{
    while (ft_strncmp("PATH", *envp, 4))
        envp++;
   return (*envp + 5);
}