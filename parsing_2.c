/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghbal <aaghbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:55:17 by aaghbal           #+#    #+#             */
/*   Updated: 2023/05/26 18:30:04 by aaghbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	check_quotes(char *tmp, int *i)
{
	char c;
	int	 j;
	char chara;

	c = tmp[*i];
	j = (*i) + 1;
	if (tmp[*i] == '\'')
		chara = '\"';
	else
		chara = '\'';
	while (tmp[j])
	{
		if (tmp[j] == chara)
			tmp[j] = '#';
		if(tmp[j] == c)
		{
			tmp[j] = '#';
			break;
		}
		j++;
	}
	if (tmp[j] != '#')
		return (1);
	return (0);
}

int get_token_pars(char *line)
{
	int i;
	
	if (!line)
		return (0);
	i = 0;
	if (line[i] && (line[i] == '<' || line[i] == '>') 
		&& (line[i + 1] != '<' && line[i + 1] != '>'))
		return (1);
	else if (line[i] && ((line[i] == '<' && line[i + 1] == '<')
	|| (line[i] == '>' && line[i + 1] == '>')))
		return (1);
	return 0;
}

int ft_parsing(char *tmp)
{
	int i;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == '\"' || tmp[i] == '\'')
			if (check_quotes(tmp, &i))
			{
				free(tmp);
				return(1);
			}
		i++;
	}
	free(tmp);
	return (0);
}

int	ft_parsing_2(t_token **token)
{
	t_token *tmp;
	t_token *tmp1;
	t_token *tmp2;

	char *str = NULL;
	tmp = *token;
	tmp1 = *token;
	tmp2 = ft_tokenlast(tmp1);
	int c = 1;
	if (tmp1->cmd != NULL)
	{
		str = get_token(tmp2->cmd);
		if (str)
			return (free(str), 1);
	}
	while (tmp)
	{
		if (!ft_strncmp(tmp->cmd, "|", 1) && c == 1)
		{
			return (1);
		}
		c = 0;
		if (get_token_pars(tmp->cmd)
		&& get_token_pars(tmp->next->cmd))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

