

//these are just all the functions i made in the process of trial and error that turned out to not be completely useless but may or may not have potential future use//

int count_single_quotes(char *input, t_lexer *lexer)
{
	int i;
	int j;
	int counter;
	int len;

	len = ft_strlen(input);
	i = 0;
	counter = 0;
	while (i < len)
	{
		if (input[i] == '/''') //how do you signify this;
		{
			lexer->singles_location[j] = i;
			counter++;
			j++;
		}
		i++;
	}
	if (counter % 2 = 0)
		return (counter / 2);
	else
		return (-1);
}

int count_double_quotes(char *input, t_lexer *lexer)
{
	int i;
	int j;
	int counter;
	int len;

	len = ft_strlen(input);
	i = 0;
	counter = 0;
	while (i < len)
	{
		if (input[i] == '/"') //how do you signify this;
		{
			lexer->doubles_location[j] = i;
			counter++;
			j++;
		}
		i++;
	}
	if (counter % 2 = 0)
		return (counter / 2);
	else
		return (-1);
}

int order_quote_locations(t_concept *info, t_lexer *lexer)
{
	int i;
	int j;
	int k;
	int singles;
	int doubles

	if (ft_strlen(lexer->singles_location) == 1)
		return (2); //this allows you to just use this instead;
	else if (ft_strlen(lexer->doubles_location) == 1)
		return (1); //this allows you to just use this instead;
	singles = ft_strlen(lexer->singles_location) / 2;
	doubles = ft_strlen(lexer->doubles_location) / 2;
	i = 0;
	j = 0;
	k = 0;
	while (k < (2 * (singles + doubles))) //this means if there are any quotes alone they will be ignored;
	{
		if (lexer->singles_location[i] < lexer->doubles_location[j])
		{
			lexer->quote_location[k] = lexer->singles_location[i];
			lexer->quote_location[k + 1] = lexer->singles_location[i + 1];
			i++;
		}
		else if (lexer->singles_location[i] > lexer->doubles_location[j])
		{
			lexer->quote_location[k] = lexer->doubles_location[j];
			lexer->quote_location[k + 1] = lexer->doubles_location[j + 1];
			j++;
		}
		k++;
	}
	return (0);
}

char **minishell_split(t_concept *info) //will hopefully return a double array of the input split up properly;
{
	t_lexer *lexer;
	int len;

	info->lexer = lexer; //is the right way to do this thing?
	init_lexer(); //do all memory allocation here; - will use a lot of ft_strlen to set stuff;
	find_quotes(info, lexer);
	if (ft_strlen(lexer->q_location) == 0)// - is this gonna register a null term?? what if there is nothign in it?
		info->input_arr = ft_split(info->input_str, ' ');
	else
		info->input_arr = split_by_quotes(info, lexer); //will need to split it even further after this - will have to do this by seeing which ones begin and end in double or single quotes; - and not splitting those ones;
}

char  **split_at_quoutes(t_lexer *lexer, char *input)
{
	int i;
	int j;
	
	counter = lexer->q_location[lexer->k]; //init this to 0; (somewhere else)
	while (i < lexer->len)
	{
		if (i >= lexer->q_location[lexer->k] && i <= lexer->q_location[lexer->k + 1])
		{
			lexer->input_arr[arr_counter][j] = input
		}
		else ()
		i++;
	}
	split_conditions(lexer);
}

void split_conditions(t_lexer *lexer)
{
	if (lexer->q_location[0] == 0 && lexer->q_location[1] != ft_strlen(input)) // 2
		lexer->arr_counter += 1;
	else if (lexer->q_location[0] != 0 && lexer->q_location[1] == ft_strlen(input)) //2
	else if (lexer->q_location[0] == 0 && lexer->q_location[1] == ft_strlen(input)) //none
	else (lexer->q_location[0] != 0 && lexer->q_location[1] != ft_strlen(input)) // 3
		lexer->arr_counter += 2;
}

//--takes input from above function (read_input)--//
void lexer(t_concept *info, const char *input)
{
	char **input_split;
	int i;

	//find number of tokens that exists//
	info->len = ft_countwords(input);//find a way to split them// - for now just by spaces but im sure that will be insufficient due to quotes being a thing;
	input_split_into_tokens = (t_token *)malloc(sizeof(t_token * len)); //okay no this is wrong - do it for the number of tokens not number of characters
	if (!input_into_token)
		error(info, ERROR_MALLOC_TOKENS);
	input_split = minishell_split(input);
	while (i < info->len)
	{
		add_node(info, &info->token, input_split[i]); //this mallocs and stuff//
		i++;
	}
}

char	**minishell_split(t_lexer *lexer, char *input)
{
	char	**strs;
	int		i;
	int		j;
	int		start; //if i include both start and finish then i can check if they are consecutive to eliminate this because there is nothing to put into it;
	int		finish; //i gotta look into this cos im not sure its gonna work properly but i guess we can find out/ lol;

	if (!input) //already accounted for this before this so really it can probably be taken out?
		return (NULL);
	i = 0;
	find_quotes_n_spaces(lexer, input); //word cpunt will over-count - because usually there is spaces on either side of the quotes;
	strs = (char **)malloc(sizeof(char *) * (lexer->word_count + 1));
	if (!strs)
		return (NULL);
	strs[j] = NULL; //gotta initiate it;
	j = 0;
	while (i < lexer->word_count) //number of words its going to do; not running through the whole thing;
	{
		start = lexer->locations[j];
		finish = lexer->locations[j + 1];
		strs[i] = ft_stralloc(((char *)input), start, finish);
		if (strs[i] == NULL)
		{
			ft_freeup(strs[i]);
		}
		i++;
		j++; //makes the finish the start; - this could potentially fuck everything up but oh well;
	}
	return (strs);
}

//this is going to spit out x2 int arrays - with the locations in the input string of the quotes of double quotes in each;
void find_quotes_n_spaces(t_lexer *lexer, char *input)
{
	int		len;
	char	*temp;

	len = ft_strlen(input);
	lexer->i = 0; //this needs to be traded between function so keep it as a pointer to be passed along but reset here everytime;
	while (lexer->i < len)
	{
		if (input[lexer->i] == '\'')
			find_next_s_quote(lexer, input);
		else if (input[lexer->i] == '\"') //how do you signify this;
			find_next_d_quote(lexer, input);
		else if (input[lexer->i] == ' ') //alter this to account for '\n' etc incase a file is put in as input;
		{
			lexer->locations[lexer->j] = lexer->i;
			lexer->j++;
			lexer->word_count++; //dont forget to initiate this;
		}
		lexer->i++;
	}
}

//do i need to consider a null terminiator at the end of this q_location - how do i allocate this? - i suppose it should be the length of the input - cos thats the longest it could be;

static void find_next_s_quote(t_lexer *lexer, char *input)
{
	int w;
	
	w = lexer->i; //stores the first location - only to be entered into the array if the other one is found;
	while (input[lexer->i] != '\'') //what if it reaches the end of the input without finding it?
		lexer->i++;
	if (input[lexer->i] != '\0' && input[lexer->i] == '\'')
	{
		lexer->locations[lexer->j] = w; //this puts the 2 locations in the thing together;
		lexer->j++; //can i compress this into the above line via [j++ inside the alocation if u know what i mean]??
		lexer->locations[lexer->j] = lexer->i;
		lexer->j++; //does this put it in the correct spot??
		lexer->word_count++;
	}
}

static void find_next_d_quote(t_lexer *lexer, char *input)
{
	int w;
	
	w = lexer->i;
	while (input[lexer->i] != '\"')
		lexer->i++;
	if (input[lexer->i] != '\0' && input[lexer->i] == '\"')
	{
		lexer->locations[lexer->j] = w;
		lexer->j++;
		lexer->locations[lexer->j] = lexer->i;
		lexer->j++;
		lexer->word_count++;
	}
}


//wont do anything if there is 2 of the strings that are being looked for
int	minishell_strnstr(const char *haystack, const char *needle, int n)
{
	int	i;
	int	j;
	int len;

	i = 0;
	j = 0;
	if (needle == NULL || needle[0] == '\0')
		return (-1);
	len = ft_strlen(needle);
	while (haystack[i] != '\0' && i < n)
	{
		if (haystack[i] == needle[j])
		{
			while (haystack[i + j] == needle[j] && i + j < n)
			{
				if (needle[j + 1] == '\0')
					return ((i + j) - (len - 1));
				j++;
			}
			j = 0;
		}	
		i++;
	}
	return (-1);
}

//will need a function to check if the type finishes up on defualt or otherwise ->and accordindly throws an error;
//this very sleek method is stolen straight from your french lady;
int set_type(char c, int type)
{
	if (c == '\'' && type == DEFAULT)
		return (SQUOTE);
	if (c == '\'' && type == SQUOTE)
		return (DEFAULT);
	if (c == '\"' && type == DEFAULT)
		return (DQUOTE);
	if (c == '\"' && type == DQUOTE)
		return (DEFAULT);
	return (0);
}

int	msg_variable(char *err, char *entered)
{ 
	char *temp;
	char *error_terminal;

	temp = ft_strjoin(err, entered);
	error_terminal = ft_strjoin(temp, "\n");
	write(2, error_terminal, ft_strlen(error_terminal));
	return (0);
}
