
#ifndef MINISHELL_H
# define MINISHELL_H

//libraries//

//--readline--//
# include <stdio.h> //can we use this idk??

//--malloc, free--//
# include <stdlib.h>
# include "../libft/libft.h"

#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

//--defining macros for errors--//
# define ERROR_MALLOC "Error: couldn't memory allocate"
# define ERROR_CMDS "Error: couldn't find the command"
# define ERROR_FREE "Error: couldn't free successfully"
# define ERROR_READLINE "Error: couldn't read the input"
# define ERROR_ARGC "Error: incorrect amount of arguments input"
# define ERROR_INPUT "Error: ur input sucks u dull brained dirtsquirt"
# define ERROR_SYNTAX "Error: syntax is tricky... for u anyway it seems"
# define ERROR_VARIABLE "Error: variable is invalid or couldn't be found"

//--variable to contain all info for creating the program--//
typedef	struct s_concept {
	struct s_token	*token; //this will be a linked list that contains all the cmds;
	char 			**paths; //put the PATH envp str here maybe;
	char			*input;
	struct s_var	*var;
}					t_concept;

typedef	struct	s_var {
	char			*var_name;
	char			*var_str;
	int				start;
	int				new_len;
	char			*frankenstein;
}					t_var;

typedef struct s_token
{
	char			*str; //whats actually in it
	int				type; //DEFAULT< SQUOTE< DQUOTE;
	struct s_token  *prev;
	struct s_token	*nxt;
}					t_token;

enum e_type { //figure out how enum stuff works
	DEFAULT = 1, //this is for a regular word;
	SQUOTE,
	DQUOTE,
	BUILTIN,
	CMD,
	QUOTE, //wait do i still need this one then;
	VAR,
	VARQUOTE,
	SPACES,
	PIPE,
	INPUT,
	HEREDOC,
	TRUNCATE,
	APPEND,
	END
};


//--minishell.c--//


//--initialise.c--//
t_concept	*initialise(t_concept *info, char **envp);

//oid	initialise(t_concept *info, int argc, char **argv);

//--build_n_edit_list.c--//
void		add_node(t_concept *info, t_token **first, char *str);
void		del_node(t_concept *info, t_token **sacrifice);

//===== LEXER ======//

//--lexer.c--//
void 		lexer(t_concept *info);

//--quotes.c--//
int			store_quotes(t_concept *info, int *i);

//--tokenisation.c--//
int			tokenisation(t_concept *info, char *input, int *i, int start);

//--find_cmd.c--//
void		find_commands(t_concept *info);

//--syntax.c--//

void 		syntax_chk(t_concept *info, t_token *token);


//--execute_cmds.c--//
//void 	execute_cmds(char *argv, char **envp);
//char 	*get_cmd_path(char **paths, char *cmd);
//char 	*find_path(char **envp);

//--clean.c--//
//int		msg_variable(char *err, char *entered);
void		error(t_concept *info, char *errorcode);cd
//void	free_list(t_input *input);
void		clean_loop(t_concept *info);
void		clean_end(t_concept *info);


//--syntax.c--//
int	syntax_chk_consecutive_ops(t_concept *info, t_token **token, t_token **end);

#endif