/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:24:16 by isobelmoore       #+#    #+#             */
/*   Updated: 2022/12/09 18:35:48 by isobelmoore      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parser(t_concept *info, t_token *first)
{
	t_token *current;
	t_token *end;

	end = info->token->prev; //this will find the last token in the cycle;
	current = find_cmd_unit(first) //returns a string **char that will either output or be piped into the next cmd unit;
	///OPTION 1
	//execute will exclude pipes but will include all the redirection stuff -> at this point can determine if its a valid cmdunit??
	while (current != end)
	{
		execute_n_pipe(info, first, current); //okay have to work out how to store this properly;
		first = current; //not sure when to do this but i thhink i get the gist;
		current = find_cmd_unit(current)
	}
	else
		execute(current); //>> and > cant be used right in front of a pipe? - or maybe this is something that i can build into the execute func. (by like saying if there is NULL output then error) - will do this later -> need to go through errors and fidn out whcih ojnes have consequeences;
}

void execute_n_pipe(t_concept *info, t_token *current)
{
	//1. determine what kind of execution is required -> course of action. ->detect operations??
	//2. perhaps it would be better to first to move through each one finding out what it is and then changing??
	//3. maybe i need a struct to store, first, current and last???
	if (start->type == CMD)
	{
		is_cmd(start);
	}

}

void is_cmd(t_token *start)
{
	find_args()
}


//this will find where (if any) the pipes are; I suppose this is what defines the command units??
t_token *find_cmd_unit(t_token *token)
{
	t_token *token;
	
	while (token->type) != PIPE)
		token = token->nxt;
	return (token);
}

//dont need this function;
static int is_opertation(char *c)
{
	if (get_type(c, 0) == HEREDOC || get_type(c, 0) == APPEND || get_type(c, 0) == INPUT || get_type(c, 0) == TRUNCATE)
		return (1); //if returns one it is an operator;
	else
		return (0);
}




static char **find_args(t_token *token) //creates an argument string for everything starting from token supplied if those thigns are words and not operations;
{
	char **args;
	int i;

	i = 0;
	while (token->type == DEFAULT || token->type == SUOTE 
		|| token->type == DQUOTE || token->type == CMD 
			|| token->type == BUILTIN)
	{
		agrs[i] = ft_strdup(token->str);
		token = token->nxt;
		i++;
	}
	return (args);
}

//create a f(x) that will determine the sequence -> command line -> that will hopefully then determine in which order and what to execute.

