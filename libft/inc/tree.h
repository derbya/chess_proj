/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 13:58:30 by aderby            #+#    #+#             */
/*   Updated: 2019/05/23 16:13:51 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

# include <libft.h>

# define T_DIGIT tree->data->digit
# define T_LEFT tree->left
# define T_RIGHT tree->right


typedef struct			s_data
{
	int					digit;
	char				*string;
	void				*other;
	struct s_data		*next;
}						t_data;

typedef struct			s_tree
{
	t_data				*data;
	struct s_tree		*right;
	struct s_tree		*left;
}						t_tree;

void					print_tree_d(t_tree *tree);
void					print_tree_d_rev(t_tree *tree);
int						place_node(t_tree *tree, t_tree *new, int value);

#endif
