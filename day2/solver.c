#define MAX_RED 12
#define MAX_GREEN 13
#define MAX_BLUE 14

#include <fcntl.h>
#include "../BFL/include/bfl.h"

int		count_draft(char *line);
char	**free_draft(char ***draft, int position);
char	**mem_draft(char *line);
char	**get_draft(char *line);
int		count_cubes(char *draft);
int		valid_draft(char **draft);
int		get_game_id(char *line);

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	char	**draft;
	int		sum;

	if (argc < 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (2);
	line = get_next_line(fd);
	sum = 0;
	while (line)
	{
		draft = get_draft(ft_strchr(line, ':') + 1);
		if (!draft)
			return (4);
		if (valid_draft(draft) == 1)
			sum += get_game_id(line);
		free(line);
		line = get_next_line(fd);
	}
	ft_printf("The solution is: %d\n", sum);
	free(line);
	close(fd);
	return (0);
}

int	count_drafts(char *line)
{
	int	i;
	int	counter;

	i = 0;
	counter = 1;
	while (line[i])
	{
		if (line[i] == ';')
			counter++;
		i++;
	}
	return (counter);
}

char	**free_draft(char ***draft, int position)
{
	while (position--)
	{
		free((*draft)[position]);
		(*draft)[position] = NULL;
	}
	free(*draft);
	*draft = NULL;
	return (NULL);
}

char	**mem_draft(char *line)
{
	char	**draft;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	draft = (char **)malloc((count_drafts(line) + 1) * sizeof(char *));
	if (!draft)
		return (NULL);
	while (line[i])
	{
		if (line[i] == ';' || line[i + 1] == '\0')
		{
			draft[k] = (char *)ft_calloc(j + 1, sizeof(char));
			if (!draft[k])
				return (free_draft(&draft, k));
			k++;
			j = 0;
		}
		else
			j++;
		i++;
	}
	return (draft);
}

char	**get_draft(char *line)
{
	char	**draft;
	int		i;
	int		j;
	int		k;

	draft = mem_draft(line);
	if (!draft)
		return (NULL);
	i = 0;
	j = 0;
	k = 0;
	while (line[i])
	{
		if (line[i] == ';' || line[i + 1] == '\0')
		{
			draft[k][j] = '\0';
			k++;
			j = 0;
		}
		else
		{
			draft[k][j] = line[i];
			j++;
		}
		i++;
	}
	draft[k] = NULL;
	return (draft);
}

int	count_cubes(char *draft)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (draft[i])
	{
		if (ft_strncmp(&draft[i], "red", 3) == 0
			|| ft_strncmp(&draft[i], "green", 5) == 0
			|| ft_strncmp(&draft[i], "blue", 4) == 0)
			counter++;
		i++;
	}
	return (counter);
}

int	valid_draft(char **draft)
{
	int	i;
	int	j;
	int	k;
	int	value;

	k = 0;
	while (draft[k])
	{
		i = 0;
		while (draft[k][i])
		{
			if (ft_isdigit(draft[k][i]))
			{
				value = draft[k][i] - '0';
				if (ft_isdigit(draft[k][i + 1]))
					value = value * 10 + draft[k][i + 1] - '0';
				j = 0;
				while (draft[k][i + j])
				{
					if (ft_strncmp(&draft[k][i + j], "red", 3) == 0)
					{
						if (value > MAX_RED)
							return (0);
						break ;
					}
					else if (ft_strncmp(&draft[k][i + j], "blue", 4) == 0)
					{
						if (value > MAX_BLUE)
							return (0);
						break ;
					}
					else if (ft_strncmp(&draft[k][i + j], "green", 5) == 0)
					{
						if (value > MAX_GREEN)
							return (0);
						break ;
					}
					j++;
				}
				i += j;
			}
			i++;
		}
		k++;
	}
	return (1);
}

int	get_game_id(char *line)
{
	int	i;
	int	id;

	i = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]))
		{
			id = line[i] - '0';
			if (ft_isdigit(line[i + 1]))
			{
				id = id * 10 + line[i + 1] - '0';
				if (ft_isdigit(line[i + 2]))
					id = id * 10 + line[i + 2] - '0';
			}
			break ;
		}
		i++;
	}
	return (id);
}
