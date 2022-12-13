/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:27:54 by isobelmoore       #+#    #+#             */
/*   Updated: 2022/12/09 18:40:17 by isobelmoore      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	find_next_quote(t_concept *info, int i);
static int	find_s_quote(t_concept *info, int i);
static int	find_d_quote(t_concept *info, int i);
static int	store_squote(t_concept *info, char *str, int i);
static int	store_dquote(t_concept *info, char *str, int i);

int	store_quotes(t_concept *info, int *i) /// t_concept *info, //using a pointer for i so that it will move the actual address;
{
	char *str;
	int len;

	(*i)++; //skips first quote;
	len = find_next_quote(info, (*i));
	str = (char *)malloc(sizeof(char) * (len + 1));  //accounts for null term;
	if (!str)
		error(info, ERROR_MALLOC);
	if (info->input[*i - 1] == '\'')
		(*i) = store_squote(info, str, (*i)); //this inputs the thing after hte ' or "";
	else if ((info->input[*i - 1]) == '\"')
		(*i) = store_dquote(info, str, (*i));
	return (*i); //i is at the last ' or " to return it to defautl tyoe; bUT its returbs one after this to start to show where the next thing should look from;
}

static int find_next_quote(t_concept *info, int i) //takes the spot after the first ' or ";
{
	int start;

	start = i;
	if (info->input[i - 1] == '\'') //the thing just skipped over;
		i = find_s_quote(info, i);
	else if (info->input[i - 1] == '\"') //the thing just kipped over; 
		i = find_d_quote(info, i);
	i = i - start; //it will count the last quote - but jsut dont add on for a null term;eg. 5' 6 7 8 9 '10 would return 4;
	return (i); //cuts out both quotes -> doesnt account for null term
}

static int find_s_quote(t_concept *info, int i)
{
	if (info->input[i - 1] == '\'') //the thing just skipped over;
	{
		while (info->input[i] != '\'')
		{
			if (info->input[i] == '\0')
			{
				printf("couldnt find another \'\n"); //create an exit concition of some desciption;
				exit(1);
			}
			i++;
		}
	}
	return (i);
}

static int find_d_quote(t_concept *info, int i)
{
	if (info->input[i - 1] == '\"') //the thing just skipped over;
	{
		while (info->input[i] != '\"')
		{
			if (info->input[i] == '\0')
			{
				printf("couldnt find another \'\n"); //create an exit concition of some desciption;
				exit(1);
			}
			i++;
		}
	}
	return (i);
}

static int store_squote(t_concept *info, char *str, int i)
{
	int j;

	j = 0;
	while (1)
	{
		if (info->input[i] == '\'')
			break ;
		str[j] = info->input[i];
		i++;
		j++;
	}
	str[j] = '\0';
	if (!str)
		error(info, ERROR_MALLOC); //this teh wrinf error - just get it to ingnore it;
	add_node(info, &info->token, str); //dunno how this works but dont worry;
	info->token->prev->type = SQUOTE; //this is how you access the last node in a doubly circular linked list;
	return (i + 1); //returns the spot of ' or ";"
}

static int store_dquote(t_concept *info, char *str, int i)
{
	int j;

	j = 0;
	while (1)
	{
		if (info->input[i] == '\"')
			break ;
		str[j] = info->input[i];
		i++;
		j++;
	}
	str[j] = '\0';
	if (!str)
		error(info, ERROR_MALLOC); //this teh wrinf error - just get it to
	add_node(info, &info->token, str);
	info->token->prev->type = DQUOTE;
	return (i + 1); //retursn teh spot the ' or '';
}