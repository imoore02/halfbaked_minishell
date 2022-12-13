/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:08:11 by imoore            #+#    #+#             */
/*   Updated: 2022/10/26 16:38:56 by isobelmoore      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//?????///////THIS IS FROM MY PIPEX AND HAS NOT YUET BEEN ADAPTED?????///////

#include "../includes/minishell.h"

char *find_path(char **envp)
{
    while (ft_strncmp("PATH", *envp, 4))
        envp++;
   return (*envp + 5);
}

char *get_cmd_path(char **paths, char *cmd)
{
    char *temp;
    char *cmd_path;

    while(*paths)
	{
        temp = ft_strjoin(*paths, "/");
        cmd_path = ft_strjoin(temp, cmd);
		free(temp);
        if (access(cmd_path, 0) == 0)
            return (cmd_path);
        free(cmd_path);
        paths++;
	}
    return (NULL);
}

void execute_cmds(char *argv, char **envp)
{  
	char **paths;
	char **cmd_args;
	char *cmd_path;

    paths = ft_split((find_path(envp)), ':');
    cmd_args = ft_split(argv, ' ');
    cmd_path = get_cmd_path(paths, cmd_args[0]);
    if (!cmd_path)
    {
		free(cmd_args);
		free(cmd_path);
		msg_variable("Command not found: ", argv);
		exit(EXIT_FAILURE);
    }
	execve(cmd_path, cmd_args, envp);
}

/*

//--executes the command that 'char *argv' specifies--//
void execute_cmds(t_concept *info, int i, char **envp)
{  
	char **paths;
	//char **cmd_args;
	//char *cmd_path;
	
	printf("%d\n", i);
	paths = ft_split((find_path(envp)), ':'); //this returns the stuff thats like 'usr/bin:bash/usr:usr'  etc but as a double array;
	printf("%d\n", i);
	//cmd_args = ft_split(info->argv[i], ' ');
	cmd_path = get_cmd_path(paths, cmd_args[0]); //this was argv[0] in the original
    if (!cmd_path) //this is the part that will sorta loop until it finds the command path that exists
    {
		free(cmd_args);
		free(cmd_path);
		msg_variable("Command not found: ", info->argv[i]);
		printf("put this error in");//error(info, EXIT_CMDS); //need to create the rest of this f(x)
    }
	//free(paths);
	//execve(cmd_path, cmd_args, info->envp); //in this does cmd args contain teh first cmd as well??? cos it seems liike it
}
*/
//for the above function - need to know which one the argv[things] is actually a cmd - strncmp