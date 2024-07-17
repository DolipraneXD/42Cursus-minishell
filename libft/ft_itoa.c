/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:57:32 by ahsadik           #+#    #+#             */
/*   Updated: 2023/11/17 13:22:44 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	len(int nb)
{
	int	c;

	c = 0;
	if (nb < 0)
	{
		nb *= -1;
		c++;
	}
	while (nb > 0)
	{
		nb /= 10;
		c++;
	}
	return (c);
}

char	*ft_itoa(int n)
{
	int		count;
	char	*mem;

	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	count = len(n);
	mem = malloc((count + 1) * sizeof(char));
	if (!mem)
		return (0);
	mem[count--] = '\0';
	if (n < 0)
	{
		mem[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		mem[count--] = (n % 10) + 48;
		n /= 10;
	}
	return (mem);
}
