/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:22:51 by isobelmoore       #+#    #+#             */
/*   Updated: 2022/12/12 16:45:57 by isobelmoore      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_if_cmd(t_concept *info, char *cmd);
static int	find_regular(t_concept *info, char *cmd);
static char *get_cmd_path(char **paths, char *cmd);
static int	find_builtin(char *cmd);

void	find_commands(t_concept *info)
{
	t_token *end;

	end = info->token->prev;
	while (1)
	{
		if (info->token->type == DEFAULT)
		{
			if (check_if_cmd(info, info->token->str) == 0)
				info->token->type = CMD;
			else if (check_if_cmd(info, info->token->str) == 1)
				info->token->type = BUILTIN;
		}
		if (info->token == end)
			break ;
		info->token = info->token->nxt;
	}
	info->token = info->token->nxt;
}

static int check_if_cmd(t_concept *info, char *cmd)
{
	if (find_regular(info, cmd) == 0)
		return (0);
	else if (find_builtin(cmd) == 0)
		return (1);
	else
		return (2); //not a commands;
	//execve(cmd_path, cmd_args, envp);
}

static int find_regular(t_concept *info, char *cmd)
{
	char *cmd_path;
	
    cmd_path = get_cmd_path(info->paths, cmd);
    if (!cmd_path) //if its a built in it will skip this
    {
		free(cmd_path);
		//msg_variable("Command not found: ", argv);
		return (1);
    }
	return (0);
}

static char *get_cmd_path(char **paths, char *cmd)
{
    char *temp;
    char *cmd_path;

    while(*paths)
	{
        temp = ft_strjoin(*paths, "/");
        cmd_path = ft_strjoin(temp, cmd);
		free(temp);
        if (access(cmd_path, 0) == 0) //dunno how access works just pulled it from my pipex;
            return (cmd_path);
        free(cmd_path);
        paths++;
	}
    return (NULL);
}

static int	find_builtin(char *cmd)
{
	int res;

	res = ft_strncmp(cmd, "echo", 4);
	if (res == 0)
		return (res);
	res = ft_strncmp(cmd, "cd", 2);
	if (res == 0)
		return (res);
	res = ft_strncmp(cmd, "pwd", 3);
	if (res == 0)
		return (res);
	res = ft_strncmp(cmd, "export", 6);
	if (res == 0)
		return (res);
	res = ft_strncmp(cmd, "unset", 5);
	if (res == 0)
		return (res);
	res = ft_strncmp(cmd, "env", 3);//pretty sure pipex does thsi one - guess i should have ntoed this down hey.
	if (res == 0)
		return (res);
	res = ft_strncmp(cmd, "exit", 4);
	if (res == 0)
		return (res);
	else
		return (1); //not found in the builtins
}