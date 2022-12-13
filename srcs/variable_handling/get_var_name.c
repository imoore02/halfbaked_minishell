/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_name.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:24:19 by isobelmoore       #+#    #+#             */
/*   Updated: 2022/12/13 11:25:08 by isobelmoore      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	var_length(char *input, int i);
static int	is_var_valid(char c);

/* find the variable name after the $ within the input string -> */
/* returns the variable name with a '=' at the end of it */
char	*get_var_name(char *input)
{
	char	*var_name;
	int		start;
	int		len;
	int		i;

	i = 0;
	start = 0;
	while (input) //so finding the start of the variable //
	{
		if (input[i] == '$')
		{
			start = i + 1;
			break ;
		}
		i++;
	}
	len = var_length(input, start);
	var_name = ft_substr(input, start, len);
	if (!var_name)
		error(info, ERROR_VARIABLE);
	var_name = ft_strjoin(var_name, "=");
	return (var_name);
}

/* will return the length of the variables name string */
// operation: if the variable name denotes a positional parameter (e.g. $5 etc)
// or its the exit code variable ($?) it will return -1;
static int	var_length(char *input, int i)
{
	int		i;
	int		count;

	count = 0;
	if ((input[i] >= '0' && input[i] <= '9') || input[i] == '?' // a shell program is restricted to referencing only nine positional parameters
		&& input[i + 1] == '\0')
		return (1);
	else 
	{
		while (input)
		{
			if (is_var_valid(input[i]) == 1)
				break ;
			count++;
			i++;
		}
	}
	return (count);
}

/* checks that each character is valid to appear in a varible name string*/
//notes: valid variable names are only able to contain letters 
//      (upper and lower), numbers, or _ (underscores);
static int	is_var_valid(char c)
{
	if (ft_isalnum(c) == 0 && c != '_')
		return (1);
	else
		return (0);
}