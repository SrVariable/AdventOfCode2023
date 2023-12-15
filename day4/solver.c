#include "../BFL/include/bfl.h"
#include <fcntl.h>

void	free_split(char ***str);
int		get_points(char **winnercard, char **mycard);
int		get_sum(char *line);

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		sum;

	if (argc < 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (2);
	sum = 0;
	line = get_next_line(fd);
	if (!line)
		return (3);
	while (line)
	{
		sum += get_sum(ft_strchr(line, ':') + 1);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	ft_printf("The solution is: %d\n", sum);
	close(fd);
}

void	free_split(char ***str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		free((*str)[i]);
		(*str)[i] = NULL;
		i++;
	}
	free(*str);
	*str = NULL;
	return ;
}

int	get_points(char **winnercard, char **mycard)
{
	int	i;
	int	j;
	int	points;

	i = 0;
	points = 0;
	while (mycard[i])
	{
		j = 0;
		while (winnercard[j])
		{
			if (ft_atoi(mycard[i]) == ft_atoi(winnercard[j]))
			{
				if (points == 0)
					points++;
				else
					points *= 2;
			}
			j++;
		}
		i++;
	}
	return (points);
}

int	get_sum(char *line)
{
	char	**check;
	char	**winnercard;
	char	**mycard;
	int		points;

	check = ft_split(line, '|');
	if (!check)
		return (0);
	winnercard = ft_split(check[0], ' ');
	if (!winnercard)
	{
		free_split(&winnercard);
		return (0);
	}
	mycard = ft_split(check[1], ' ');
	if (!mycard)
	{
		free_split(&mycard);
		return (0);
	}
	points = get_points(winnercard, mycard);
	free_split(&winnercard);
	free_split(&mycard);
	return (points);
}
