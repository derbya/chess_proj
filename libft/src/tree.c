/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 18:23:05 by aderby            #+#    #+#             */
/*   Updated: 2019/06/03 19:07:33 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

void	print_tree_d(t_tree *tree)
{
	if (tree)
	{
		if (T_LEFT)
		{
			print_tree_d(T_LEFT);
			ft_printf("tree value:%d\n", T_DIGIT);
		}
		if (T_RIGHT)
		{
			if (!T_LEFT)
				ft_printf("tree value:%d\n", T_DIGIT);
			print_tree_d(T_RIGHT);
		}
		else if (!T_LEFT && !T_RIGHT)
			ft_printf("tree value:%d\n", T_DIGIT);
	}
}

void	print_tree_d_rev(t_tree *tree)
{
	if (tree)
	{
		if (T_RIGHT)
		{
			print_tree_d_rev(T_RIGHT);
			ft_printf("tree value:%d\n", T_DIGIT);
		}
		if (T_LEFT)
		{
			if (!T_RIGHT)
				ft_printf("tree value:%d\n", T_DIGIT);
			print_tree_d_rev(T_LEFT);
		}
		else if (!T_RIGHT && !T_LEFT)
			ft_printf("tree value:%d\n", T_DIGIT);
	}
}

int		place_node(t_tree *tree, t_tree *new, int value)
{
	if (tree)
	{
		if (T_DIGIT >= value)
		{
			if (!T_LEFT)
				T_LEFT = new;
			else
				return (place_node(T_LEFT, new, value));
		}
		else
		{
			if (!T_RIGHT)
				T_RIGHT = new;
			else
				return (place_node(T_RIGHT, new, value));
		}
		return (1);
	}
	return (0);
}
