#define MAX 5000

#include <stdio.h>
#include <fcntl.h>
#include "get_next_line/get_next_line.h"
#include "BFL/include/bfl.h"

int	first_last_value(char *line)
{
	int	counter;
	int	result;
	int	number_counter;
	int	last;

	if (!line)
		return (0);
	counter = 0;
	number_counter = 0;
	while (line[counter])
	{
		if (ft_isdigit(line[counter]))
		{
			if (number_counter == 0)
				result = line[counter] - '0';
			last = line[counter] - '0';
			number_counter++;
		}
		counter++;
	}
	result = result * 10 + last;
	return (result);
}

int	main(int argc, char **argv)
{
	char	*line[MAX];
	int		fd;
	int		counter;
	int		sum;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (1);
	counter = 0;
	sum = 0;
	line[counter] = get_next_line(fd);
	while (line[counter] && counter < MAX)
	{
		sum += first_last_value(line[counter]);
		counter++;
		line[counter] = get_next_line(fd);
	}
	printf("The solution is: %d\n", sum);
	while (counter--)
		free(line[counter]);
	return (0);
}
