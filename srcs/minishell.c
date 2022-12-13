/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:44:27 by isobelmoore       #+#    #+#             */
/*   Updated: 2022/12/11 14:24:42 by isobelmoore      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
# include <stdlib.h>
# include "../libft/libft.h"

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>

static void minishell_running(t_concept *info);
static void read_input(t_concept *info);
static int	check_if_input_is_just_spaces(char *input);

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f')
		return (1);
	return (0);
}

int main(int argc, char **argv, char **envp) //int argc, char **argv, char **envp
{
	t_concept *info;

	info = NULL;
	if (argc != 1 && argc != 3)
		error(info, ERROR_ARGC); 
   	info = initialise(info, envp);
	if (argc == 3 && ft_strncmp(argv[1], "-c", 2) == 0) //can i just compress this into a double character check???
	{
		printf("stagnant");//minishell_stagnant(info, argc, argv);
		argv = NULL;
	}
	else
		minishell_running(info);
	//clean_end(info);// this will free again when it has already been freed;
	return (0);
}

static void minishell_running(t_concept *info)
{
	//set_signals();
	//signal(SIG_INT, something) //will manipulate 'Crtl-C'
   // signal(SIGQUIT, SIG_INT); // make 'Ctrl-D' do what 'Crtl-C' usually does which is to exit the program/ simulates quiting the shell/closing the termihnal;
   // signal(SIGQUIT, SIG_IGN); // ignores "Ctrl-\"
	while (1)
	{
		read_input(info);
		lexer(info);
		//execute(); //executes the commands found;
		//if (crtl D will exit the stuff so this is the things that will break the prog if we want it to mimik the shell)
		// break;
		//clean_loop(info);
		break ;
	}
}

/* Read a string, and return a pointer to it.  Returns NULL on EOF. */
static void read_input(t_concept *info)
{
	if (info->input)
	{
		free(info->input);
		info->input = NULL;
	}
	info->input = readline("$>"); //so if u compile it with the flag -lreadline
	if (!info->input || info->input[0] == '\0' 
		|| check_if_input_is_just_spaces(info->input) == 0) //i should put a condition for if its empty as well (ie. jsut spaces) - also will need a condition for if its invalid but that will be implementable later on presumably in the parser;
		error(info, ERROR_INPUT); //this will only be the case if it is the EOF in which case do i need to do someething?? im not usre.
	add_history(info->input);
}

static int	check_if_input_is_just_spaces(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_isspace(input[i]))
			return (1);
		i++;
	}
	return (0);
}