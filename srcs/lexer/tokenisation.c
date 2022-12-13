/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 09:55:44 by isobelmoore       #+#    #+#             */
/*   Updated: 2022/12/07 09:47:02 by isobelmoore      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//try to only use a pointer to keep track of i because its alot more swish and compact;

#include "../includes/minishell.h"

static int	get_type(char *input, int i);
static int	store_word(t_concept *info, int i, int start, char *input);
static int	store_ops(t_concept *info, char *input, int start, int type);

int	tokenisation(t_concept *info, char *input, int *i, int start)
{
	int type;

	type = get_type(input, (*i)); // i is always going to be the last thing just before a space?? maybe - probs need some kind of clarification on this point because im an imbicile;
	while (type == DEFAULT)
	{ 
		(*i)++;
		type = get_type(input, (*i));
	}
	if (type != DEFAULT) //ie while its not a word; so will do this when it gets to a space or something else - but like also what if its like echo hey| how is that going to understadn the word next ot hte pipe - will look into this later i suppose; okay this us actually fine dont worry about it;
	{

		if ((*i) != 0 && get_type(input, (*i) - 1) == DEFAULT) //this will check if the previous thing was a word. - checks for anything space or not;
		{
			start = store_word(info, (*i), start, input);
			if (type == SPACES)
				(*i)++;
		}
		else if (type == APPEND || type == HEREDOC || type == PIPE
			|| type == INPUT || type == TRUNCATE || type == END)
		{
			start = store_ops(info, input, (*i), type); //(&data->token, str, (*i), type);
			if (type == APPEND || type == HEREDOC)
				(*i)++;
			(*i)++;
		}
		else if (type == SPACES)
			(*i)++;
	}
	return (start); //this should return the thing right after the thing finishes; - which should finish at the length of the string;
}

static int	get_type(char *input, int i)
{
	if ((input[i] > 8 && input[i] < 14 ) || input[i] == 32)
		return (SPACES);
	else if (input[i] == '|')
		return (PIPE);
	else if (input[i] == '<' && input[i + 1] == '<')
		return (HEREDOC);
	else if (input[i] == '<')
		return (INPUT);
	else if (input[i] == '>' && input[i + 1] == '>')
		return (APPEND);
	else if (input[i] == '>')
		return (TRUNCATE);
	else if (input[i] == '\0')
		return (END);
	else if (input[i] == '\'' || input[i] == '\"')
		return (QUOTE);
	else
		return (DEFAULT); //it will only do this if its a word;
}

static int	store_word(t_concept *info, int i, int start, char *input) //dont need to plus i cos its already gone past it;
{
	int j;
	char *str;

	str = malloc(sizeof(*str) * (i - start) + 1);
	if (str == NULL)
		printf("fail");
	j = 0;
	while (start < i)
	{	
		if (get_type(input, start) == SPACES || get_type(input, start) == END)
			start++;
		str[j] = input[start];
		j++;
		start++;
	}
	str[j] = '\0';
	add_node(info, &info->token, ft_strdup(str)); //this will stay as default so dont need to change it;
	free(str);
	str = NULL;
	return (start + 1); //returns the location after the word;
}

static int	store_ops(t_concept *info, char *input, int start, int type)
{
	int j;
	char *str;

	j = 0;
	if (type == APPEND || type == HEREDOC)
	{
		str = malloc(sizeof(*str) * (3)); //okay so without it being like another thing longer is has a little tanty;
		if (!str)
			error(info, ERROR_MALLOC);
		while (j < 2)
		{
			str[j] = input[start];
			j++;
			start++;
		}
		str[j] = '\0';
	}
	else
	{
		str = (char *)malloc(sizeof(*str) * (2));
		if (!str)
			error(info, ERROR_MALLOC);
		str[j] = input[start];
		str[j + 1] = '\0';
		start++;
	}
	add_node(info, &info->token, ft_strdup(str)); //this will stay as default so dont need to change it;
	free(str);
	str = NULL;
	info->token->prev->type = type;
	/*if (info->token->prev->type == END)
	{
		printf("it the type");
		info->token->type = type;
	}
	info->token->prev->type = type;*/
	return (start);
}