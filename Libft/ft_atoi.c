/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbertin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:42:08 by jbertin           #+#    #+#             */
/*   Updated: 2022/11/07 12:42:16 by jbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	check_sp_signs(int *ptr_i, const char *str, int *ptr_minus)
{
	int	minus;
	int	i;

	i = 0;
	minus = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	if ((str[i] == 43 || str[i] == 45)
		&& (str[i + 1] == 43 || str[i + 1] == 45))
		return (9);
	while (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
		{
			minus++;
			i++;
		}
		else
			i++;
	}
	*ptr_i = i;
	*ptr_minus = minus;
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	nb;
	int	minus;

	i = 0;
	nb = 0;
	minus = 0;
	if (check_sp_signs(&i, str, &minus) == 9)
		return (0);
	while (str[i] && (str[i] > 47 && str[i] < 58))
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	if (minus % 2 == 1)
		nb = -nb;
	return (nb);
}
