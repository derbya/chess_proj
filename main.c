#include <stdio.h>
#include <libft.h>

char	g_board1[8][8] =
{
	{'R', 'N', 'B', 'K', 'Q', 'B', 'N', 'R'},
	{'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
	{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
	{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
	{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
	{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
	{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
	{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
};

char	g_board2[8][8] =
{
	{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
	{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
	{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
	{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
	{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
	{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
	{'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
	{'R', 'N', 'B', 'K', 'Q', 'B', 'N', 'R'},
};

char	g_board[8][8] =
{
	{'R', 'N', 'B', 'K', 'Q', 'B', 'N', 'R'},
	{'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
	{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
	{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
	{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
	{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'},
	{'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
	{'R', 'N', 'B', 'K', 'Q', 'B', 'N', 'R'},
};

int	check_pawn_move(char *line, int x);
int	check_normal_move(char *line, int x);
int	check_takes_move(char *line, int x);
int	check_queen_castle(char *line, int x);
int	check_promotion(char *line, int x);
int	check_promotion_in_check(char *line, int x);
int	check_promotion_in_checkmate(char *line, int x);
int	null_function(char *line, int x);

int		(*g_function[])(char *, int) =
{
	&null_function,
	&null_function,
	&check_pawn_move,
	&check_normal_move,//this will collide with a king side casle
	&check_takes_move, // this will collide with a check mate if a pawn delivers it. & a promotion
	&check_queen_castle, //collide with a normal move with a king check & some distincive notiation such as Raxc1 exd6+
	&check_promotion, // this will collide with a check mate if a normal move delivers it. exd6++
	&check_promotion_in_check,
	&check_promotion_in_checkmate,
};

int	kingside_castle(char *line, int x);
int	rook_move(char *line, int x);
int	knight_move(char *line, int x);
int bishop_move(char *line, int x);
int	king_move(char *line, int x);
int	queen_move(char *line, int x);

int		(*g_function_normal[])(char *, int) =
{
	&null_function,
	&rook_move,
	&knight_move,
	&bishop_move,
	&king_move,
	&queen_move,
};

# define NUM "hgfedcba"

int	move_piece(int from[2], int to[2], int x);

int	null_function(char *line, int x)
{
	return (0);
}

int	check_pawn_move_2(char *line, int x)
{
	int i;
	int j;
	int from[2];
	int to[2];

	i = ft_strnchr(NUM, line[0]);
	j = ft_atoi(line + 1) - 1;
	to[0] = j;
	to[1] = i - 1;
	if (!i || j > 7 || g_board[j][i] != 'O')
		return (0);
	i--;
	if (j + 2 == 6)
	{
		if (g_board2[j + 2][i] == 'P')
			if (g_board[j + 1][i] == 'O')//I think this needs to be overall board and to check for ANY piece
			{
				from[0] = j + 2;
				from[1] = i;
				return (move_piece(to, from, x));
			}
	}
	if (g_board2[j + 1][i] == 'P')//this is fine but you need to make the move piece function more generic maybe and definitely change both boards as you go.
	{
		from[0] = j + 1;
		from[1] = i;
		return (move_piece(to, from, x));
	}
	return (0);
}

int	check_pawn_move_1(char *line, int x)
{
	int i;
	int j;
	int from[2];
	int to[2];

	i = ft_strnchr(NUM, line[0]);
	j = ft_atoi(line + 1) - 1;
	to[0] = j;
	to[1] = i - 1;
	if (!i || j > 7 || g_board[j][i - 1] != 'O')
		return (0);
	i--;
	if (j - 2 == 1)
	{
		if (g_board1[j - 2][i] == 'P')
			if (g_board[j - 1][i] == 'O')
			{
				from[0] = j - 2;
				from[1] = i;
				return (move_piece(to, from, x));
			}
	}
	if (g_board1[j - 1][i] == 'P')
	{
		from[0] = j - 1;
		from[1] = i;
		return (move_piece(to, from, x));
	}
	return (0);
}

int	pawn_mate(char *line, int x)
{
	return (0);
}

int	check_pawn_move(char *line, int x)
{
	int i;
	int j;

	if (x)
		return (check_pawn_move_2(line, x));
	return (check_pawn_move_1(line, x));
}

# define PIECE "RNBKQ"

int	kingside_castle(char *line, int x)
{
	return (0);
}

int	rook_move(char *line, int x)
{
	return (0);
}

int	knight_move(char *line, int x)
{
	int i;
	int j;
	int	to[2];
	int	from[2];

	i = ft_strnchr(NUM, line[1]);
	j = ft_atoi(line + 2) - 1;
	i--;
	to[0] = j;
	to[1] = i;
	if (!i ||j < 0 || j > 7 || g_board[j][i] != 'O')
		return (0);
	if (g_board[j - 2][i - 1] == 'N' && (from[0] = j - 2) && (from[1] = i - 1))
		return (move_piece(to, from, x));
	if (g_board[j - 2][i + 1] == 'N' && (from[0] = j - 2) && (from[1] = i + 1))
		return (move_piece(to, from, x));
	if (g_board[j - 1][i - 2] == 'N' && (from[0] = j - 1) && (from[1] = i - 2))
		return (move_piece(to, from, x));
	if (g_board[j - 1][i + 2] == 'N' && (from[0] = j - 1) && (from[1] = i + 2))
		return (move_piece(to, from, x));
	if (g_board[j + 1][i + 2] == 'N' && (from[0] = j + 1) && (from[1] = i - 2))
		return (move_piece(to, from, x));
	if (g_board[j + 1][i - 2] == 'N' && (from[0] = j + 1) && (from[1] = i + 2))
		return (move_piece(to, from, x));
	if (g_board[j + 2][i - 1] == 'N' && (from[0] = j + 2) && (from[1] = i - 1))
		return (move_piece(to, from, x));
	if (g_board[j + 2][i + 1] == 'N' && (from[0] = j + 2) && (from[1] = i + 1))
		return (move_piece(to, from, x));
	return (0);
}

int bishop_move(char *line, int x)
{
	return (0);
}

int	king_move(char *line, int x)
{
	return (0);
}

int	queen_move(char *line, int x)
{
	return (0);
}

int	check_normal_move(char *line, int x)
{
	int fun;

	fun = ft_strnchr(PIECE, line[0]);
	if (ft_strchr(line, 'O'))
		return (kingside_castle(line, x));
	if (fun > 5)
		return (0);
	return (g_function_normal[fun](line, x));
}

int	check_takes_move(char *line, int x)
{
	if (line[3] == '+')
		return(pawn_mate(line, x));
	return (4);
}

int	check_queen_castle(char *line, int x)
{
	return (5);
}

int	check_promotion(char *line, int x)
{
	return (6);
}

int	check_promotion_in_check(char *line, int x)
{
	return (7);
}

int	check_promotion_in_checkmate(char *line, int x)
{
	return (8);
}

int	move_piece(int to[2], int from[2], int x)
{
	g_board[to[0]][to[1]] = g_board[from[0]][from[1]];
	g_board[from[0]][from[1]] = 'O';
	if (x)
	{
		g_board2[to[0]][to[1]] = g_board2[from[0]][from[1]];
		g_board2[from[0]][from[1]] = 'O';
		return (1);
	}
	g_board1[to[0]][to[1]] = g_board1[from[0]][from[1]];
	g_board1[from[0]][from[1]] = 'O';
	return (1);
}

void	print_board(void)
{
	int	i = 0;
	int j;
	while (i < 8)
	{
		j = 0;
		while (j < 8)
		{
			printf(" %c ", g_board[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n");
}

void	err_handle(int x)
{
	if (!x)
	{
		ft_putstr("Invalid Move\n");
		exit(0);
	}
}

int	main(void)
{
	int len;
	int	toggle = 1;
	char *line;
	while (1)
	{
		print_board();
		toggle = (toggle) ? 0 : 1;
		get_next_line(0, &line);
		len = ft_strlen(line);
		if (len > 8)
			err_handle(0);
		if (!g_function[len](line, toggle))
			err_handle(0);
	}
	return (0);
}
