/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_n_edit_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:29:02 by isobelmoore       #+#    #+#             */
/*   Updated: 2022/12/11 16:22:09 by isobelmoore      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

////////////THIS IS FROM MY PUSHSWAP AND HAS NOT YET BEEN ADAPTED?//////
//gotta check that this loigic make sense cos i just deleted a bunch of stuff but sort dnot really look at it at all//

#include "../includes/minishell.h"

//--------creating (initiating and mallocing) doubly( yet to make it doubly but i feel it could be helpful) linked list--------//

static t_token	*init_token(t_concept *info, char *str);

//--adding the new node to the bottom of the list--//
//notes: something will need to be freed but ideally when the list is cleared (end of program) or when a node is deleted
void add_node(t_concept *info, t_token **first, char *str) //returns a pointer to the bottom node? -> adds to the end;
{
	t_token	*new;
	t_token *end;

	if (*first)
	{
		new = (t_token *)malloc(sizeof(t_token));
		if (new == NULL)
			error(info, ERROR_MALLOC); //this still doesnt exist yet
		end = (*first)->prev;
		new->nxt = (*first);
		new->prev = end;
		(*first)->prev = new;
		end->nxt = new;
		new->str = str; //this will need to be malloced at somepoint - it doesnt matter when particularly;
		new->type = DEFAULT; //will have to be changed in SQUOTE and DQUOTE;
	}
	else
		(*first) = init_token(info, str);
}

//--initiating the head pointer of a stack--//
static t_token	*init_token(t_concept *info, char *str)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (new == NULL)
		error(info, ERROR_MALLOC);
	new->nxt = new;
	new->prev = new;
	new->str = str;
	new->type = DEFAULT;
	return (new);
}

//--deletes a node from the top of the list (and sets the nxtnode to be head pointer)--//
void	del_node(t_concept *info, t_token **sacrifice)
{
	t_token		*tmp;

	if (*sacrifice)
	{
		if ((*sacrifice)->nxt == (*sacrifice))
		{
			free(*sacrifice);
			(*sacrifice) = NULL;
			if (*sacrifice)
				error(info, ERROR_FREE);
		}
		else
		{
			tmp = (*sacrifice);
			(*sacrifice) = (*sacrifice)->nxt;
			free(tmp->str);
			tmp->str = NULL;
			free(tmp);
			tmp = NULL;
			if (tmp)
				error(info, ERROR_FREE);
		}
	}
}