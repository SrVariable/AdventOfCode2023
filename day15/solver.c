#include "../BFL/include/bfl.h"
#include <fcntl.h>

void	free_split(char ***str);
int		encoder(char *line);
int		get_sum(char **split);

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	char	**split;

	if (argc < 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (2);
	line = get_next_line(fd);
	if (!line)
		return (3);
	split = ft_split(line, ',');
	ft_printf("The solution is: %d\n", get_sum(split));
	free_split(&split);
	free(line);
	return (0);
}

void	free_split(char ***str)
{
	int i;

	i = 0;
	while ((*str)[i])
	{
		free((*str)[i]);
		(*str)[i] = NULL;
		i++;
	}
	free(*str);
	return ;
}

int	encoder(char *line)
{
	int	i;
	int	value;

	i = 0;
	value = 0;
	while (line[i] && line[i] != '\n')
	{
		value += line[i];
		value *= 17;
		value %= 256;
		i++;
	}
	return (value);
}

int	get_sum(char **split)
{
	int	sum;
	int	i;

	sum = 0;
	i = 0;
	while (split[i])
	{
		sum += encoder(split[i]);
		i++;
	}
	return (sum);
}
