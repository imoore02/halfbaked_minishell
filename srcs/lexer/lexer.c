/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:37:00 by isobelmoore       #+#    #+#             */
/*   Updated: 2022/12/13 15:17:50 by isobelmoore      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//--LEXICAL ANALYSER--//
//operation: takes the input characters and puts them together into 'tokens';

int			var_chk(t_concept *info, t_token **token);
static void	variable_chk(t_token **token, t_token **end);

//notes: the store functions will have to move i foward; -> so will have to pass a pointer into it so that it can alter the postion; - and then return the starting position;
void lexer(t_concept *info) //need input and tokens -> or at least 1st pointer? -> also need to be able to pass the whole thing into the error function;
{
	int i;
	int start;

	i = 0;
	start = 0;
	///STATUS I NEED TO DO SOMETHING TO MAKE THIS IGNORE THE SPACES;
	//check if input is just spaces -> do this in readline;
	while (i < ft_strlen(info->input))
	{
		if (info->input[i] == '\'' || info->input[i] == '\"')
			start = store_quotes(info, &i); //this returns the location of the thing AFTER the quote;
		else
			start = tokenisation(info, info->input, &i, start); //(same thing into a dll but need to tokenise as we go);
	}
	printf ("input %s\n", info->input);
	syntax_chk_consecutive_ops(info, info->token)
	var_handling(info);
	find_commands(info);

	
	///THIS IS JUST PROOF OF OUTPUT;
	i = 0;
	while(i < 10) //i made it doubly circular beause im lazy and its the easiest way to quickly find the end/add something to the end/access the last node.
	{
		printf("%s + %d\n", info->token->str, info->token->type);
		info->token = info->token->nxt;
		i++;
	}
}