/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akay <akay@student.42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:14:59 by akay              #+#    #+#             */
/*   Updated: 2024/08/28 15:27:38 by akay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	write_error(char *str)
{
	printf("%s\n", str);
	return (1);
}

static int	arg_num_valid(int argc)
{
	if (argc < 5 || argc > 6)
		return (write_error("Wrong number of arguments!!!!!"));
	return (0);
}

static int	arg_big(char *arg)
{
	if (ft_strlen(arg) > 10
		|| (ft_strlen(arg) == 10 && ft_strncmp(arg, "2147483647", 10) == 1))
		return (write_error("Arguments too big!!!!!!"));
	return (0);
}

static int	args_valid(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		if (arg_big(argv[i]))
			return (1);
		j = 0;
		while ((argv[i][j] >= 9 && argv[i][j] <= 13) || argv[i][j] == ' ')
			j++;
		if (argv[i][j] == '+')
		{
			j++;
			if (!(argv[i][j] >= 48 && argv[i][j] <= 57))
				return (write_error("Arguments must be positive integers!!!"));
		}
		while (argv[i][j])
		{
			if (!(argv[i][j] >= 48 && argv[i][j] <= 57))
				return (write_error("Arguments must be positive integers!!!"));
			j++;
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (arg_num_valid(argc))
		return (1);
	if (args_valid(argc, argv))
		return (1);
	if (ft_atoi(argv[1]) == 0 || ft_atoi(argv[2]) == 0 || ft_atoi(argv[3]) == 0
		|| ft_atoi(argv[4]) == 0 || (argc == 6 && ft_atoi(argv[5]) == 0))
	{
		printf("Arguments must be greater than zero!!!!!\n");
		return (1);
	}
	table_init(&table, argc, argv);
	create_philos(&table);
	table_destroy(&table);
}
