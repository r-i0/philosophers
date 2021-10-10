#include "philo.h"

bool ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (true);
	else
		return (false);
}

int check_error(long num, const char *str, int negative, int i)
{
	long real_num;

	real_num = num * negative;
	if (!ft_isdigit(str[i])
		|| (negative == 1 && real_num > INT_MAX)
		|| (negative == -1 && real_num < INT_MIN))
		return (-1);
	return (0);
}

int ft_atoi(const char *str, bool *err)
{
	int i;
	int negative;
	long num;

	i = 0;
	num = 0;
	negative = 1;
	if (str[0] == '\0')
		*err = true;
	if (str[i] == '-')
		negative = -1, i++;
	while (str[i] != '\0')
	{
		num *= 10;
		num += str[i] - '0';
		if (check_error(num, str, negative, i) == -1)
			*err = true;
		i++;
	}
	return ((int)num * negative);
}
