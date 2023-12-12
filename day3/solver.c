#include <stdio.h>
#include <fcntl.h>
#include "BFL/include/bfl.h"
#include "get_next_line/get_next_line.h"

typedef struct s_pos
{
	int	x;
	int	y;
	int	xmax;
	int	ymax;
}		t_pos;

int	check_left(char **block, t_pos *pos)
{
	if (pos->y - 1 >= 0)
		return (ft_isdigit(block[pos->x][pos->y - 1]) != 1
				&& block[pos->x][pos->y - 1] != '.');
	return (0);
}

int	check_right(char **block, t_pos *pos)
{
	if (pos->y + 1 < pos->ymax)
		return (ft_isdigit(block[pos->x][pos->y + 1]) != 1
				&& block[pos->x][pos->y + 1] != '.'
				&& block[pos->x][pos->y + 1] != '\0');
	return (0);
}

int	check_up(char **block, t_pos *pos)
{
	if (pos->x - 1 >= 0)
		return (ft_isdigit(block[pos->x - 1][pos->y]) != 1
				&& block[pos->x - 1][pos->y] != '.');
	return (0);
}

int	check_down(char **block, t_pos *pos)
{
	if (pos->x + 1 < pos->ymax)
		return (ft_isdigit(block[pos->x + 1][pos->y]) != 1
					&& block[pos->x + 1][pos->y] != '.');
	return (0);
}

int	check_diagonal1(char **block, t_pos *pos)
{
	if (pos->x - 1 >= 0 && pos->y - 1 >= 0)
		return (ft_isdigit(block[pos->x - 1][pos->y - 1]) != 1
				&& block[pos->x - 1][pos->y - 1] != '.');
	return (0);
}

int	check_diagonal2(char **block, t_pos *pos)
{
	if (pos->x - 1 >= 0 && pos->y + 1 < pos->ymax)
		return (ft_isdigit(block[pos->x - 1][pos->y + 1]) != 1
				&& block[pos->x - 1][pos->y + 1] != '.'
				&& block[pos->x - 1][pos->y + 1] != '\0');
	return (0);
}

int	check_diagonal3(char **block, t_pos *pos)
{
	if (pos->x + 1 < pos->xmax && pos->y - 1 >= 0)
		return (ft_isdigit(block[pos->x + 1][pos->y - 1]) != 1
				&& block[pos->x + 1][pos->y - 1] != '.');
	return (0);
}

int	check_diagonal4(char **block, t_pos *pos)
{
	if (pos->x + 1 < pos->xmax && pos->y + 1 < pos->ymax)
		return (ft_isdigit(block[pos->x + 1][pos->y + 1]) != 1
				&& block[pos->x + 1][pos->y + 1] != '.'
				&& block[pos->x + 1][pos->y + 1] != '\0');
	return (0);
}

int	check_symbol(char **block, t_pos *pos)
{
	return (check_left(block, pos) || check_right(block, pos)
		|| check_up(block, pos) || check_down(block, pos)
		|| check_diagonal1(block, pos) || check_diagonal2(block, pos)
		|| check_diagonal3(block, pos) || check_diagonal4(block, pos));
}

char	*get_lines(int fd, t_pos *pos)
{
	char	*line;
	char	*buffer;
	char	*temp;
	int		i;

	line = NULL;
	temp = NULL;
	buffer = get_next_line(fd);
	i = 0;
	while (buffer)
	{
		temp = ft_strjoin(line, buffer);
		free(buffer);
		free(line);
		line = NULL;
		line = ft_strjoin(line, temp);
		free(temp);
		buffer = get_next_line(fd);
		i++;
	}
	buffer = NULL;
	temp = NULL;
	pos->xmax = i;
	return (line);
}

void	free_file(char ***file)
{
	int	i;

	i = 0;
	while ((*file)[i])
	{
		free((*file)[i]);
		(*file)[i] = NULL;
		i++;
	}
	free(*file);
	*file = NULL;
	return ;
}

int	get_number(char **file, t_pos *pos)
{
	int	number;
	int	i;

	number = 0;
	i = 0;
	while (pos->y + i >= 0 && ft_isdigit(file[pos->x][pos->y + i]))
		i--;
	i++;
	while (file[pos->x][pos->y + i] && ft_isdigit(file[pos->x][pos->y + i]))
	{
		number = number * 10 + file[pos->x][pos->y + i] - '0';
		i++;
	}
	return (number);
}

void	parse_map(char **file, t_pos *pos)
{
	int	sum;

	sum = 0;
	pos->ymax = ft_strlen(file[0]);
	pos->x = 0;
	while (file[pos->x])
	{
		pos->y = 0;
		while (file[pos->x][pos->y])
		{
			if (ft_isdigit(file[pos->x][pos->y]))
			{
				if (check_symbol(file, pos))
				{
					sum += get_number(file, pos);
					while (file[pos->x][pos->y + 1] != '\0'
							&& ft_isdigit(file[pos->x][pos->y]))
						pos->y++;
					pos->y--;
				}
			}
			pos->y++;
		}
		pos->x++;
	}
	printf("The solution is: %d\n", sum);
}

int	main(int argc, char **argv)
{
	char	*temp;
	char	**file;
	int		fd;
	t_pos	pos;

	if (argc < 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (2);
	temp = get_lines(fd, &pos);
	file = ft_split(temp, '\n');
	free(temp);
	temp = NULL;
	parse_map(file, &pos);
	free_file(&file);
	close(fd);
	return (0);
}
