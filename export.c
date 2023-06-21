/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kach <zel-kach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 04:51:58 by zel-kach          #+#    #+#             */
/*   Updated: 2023/06/14 08:09:04 by zel-kach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	print_epxport(t_list *export_list)
{
	char	*tmp;
	int		i;

	while (export_list)
	{
		printf("declare -x ");
		tmp = ft_strdup(export_list->content);
		i = -1;
		while (tmp[++i])
		{
			if (tmp[i] == '=')
			{
				printf("=\"");
				printf("%s", ft_strchr(export_list->content, '=') + 1);
				printf("\"");
				break ;
			}
			printf("%c", tmp[i]);
		}
		printf("\n");
		free(tmp);
		export_list = export_list->next;
	}
}

void	export_empty(t_list *export_list, t_list *env_list, char *var)
{
	int		i;
	char	*tmp;


	i = 0;
	tmp = ft_strdup(var);
	while (var[++i])
	{
		if (var[i] == '=')
		{
			ft_lstadd_back(&export_list, ft_lstnew(tmp));
			ft_lstadd_back(&env_list, ft_lstnew(tmp));
			return ;
		}
		else if (!var[i + 1])
			ft_lstadd_back(&export_list, ft_lstnew(tmp));
	}
	return ;
}

char	*add_var(t_list *export_list, char *var)
{
	char	**tmp2;
	char	**tmp3;

	tmp3 = ft_split(var, '+');
	while (export_list)
	{
		tmp2 = ft_split(export_list->content, '=');
		if (!ft_strncmp(tmp2[0], tmp3[0], ft_strlen(tmp3[0]))
			&& ft_strlen(tmp3[0]) == ft_strlen(tmp2[0]))
		{
			if (tmp3[1] && tmp3[1][1] != '\0')
			{
				var = ft_strjoin(export_list->content, tmp3[1] + 1);
				free_tabb(tmp2);
				free_tabb(tmp3);
				free (export_list->content);
				return (var);
			}
			char *s = ft_strjoin(tmp3[0], tmp3[1]);
			free_tabb(tmp2);
			free_tabb(tmp3);
			printf("%s\n", s);
			return (s);
		}
		free_tabb(tmp2);
		export_list = export_list->next;
	}
	char *s = ft_strjoin(tmp3[0], tmp3[1]);
	free_tabb(tmp3);
	printf("%s\n", s);
	return (s);
}

int	same_var(t_list *export_list, t_list *env_list, char *var)
{
	t_list	*tmp;
	char	**tmp2;
	char	**tmp3;

	tmp = export_list;
	tmp3 = ft_split(var, '=');
	while (tmp)
	{
		tmp2 = ft_split(tmp->content, '=');
		if (!ft_strncmp(tmp2[0], tmp3[0], ft_strlen(tmp3[0]))
			&& ft_strlen(tmp3[0]) == ft_strlen(tmp2[0]))
		{
			if (!tmp3[1] && var[ft_strlen(var) - 1] != '=')
			{
				free_tabb(tmp2);
				free_tabb(tmp3);
				return (0);
			}
			my_unset(tmp2[0], export_list, env_list);
			free_tabb(tmp2);
			free_tabb(tmp3);
			return (1);
		}
		free_tabb(tmp2);
		tmp = tmp->next;
	}
	free_tabb(tmp3);
	return (1);
}

void	my_export(t_list *export_list, t_list *env_list, char *var)
{
	if (var)
	{
		var = export_pars(export_list, var);
		if (!var)
			return ;
		if (!same_var(export_list, env_list, var))
			return ;
		export_empty(export_list, env_list, var);
		return ;
	}
	else
		print_epxport(export_list);
}
