/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strjoin.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ahsadik <ahsadik@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/11/05 12:00:26 by ahsadik		   #+#	#+#			 */
/*   Updated: 2023/11/05 12:41:54 by ahsadik		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*checknull(char *s1, char *s2, int free)
{
	char	*tmp;

	tmp = NULL;
	if (!s1 && !s2)
		return (NULL);
	if (s1 == NULL)
	{
		tmp = ft_strdup(s2);
		if (free == 2 || free == 3)
			s2 = ft_free(s2);
	}
	else
	{
		tmp = ft_strdup(s1);
		if (free == 1 || free == 3)
			s1 = ft_free(s1);
	}
	return (tmp);
}

char	*ft_strjoin(char *s1, char *s2, int free)
{
	size_t	tlen;
	char	*s;

	if (s1 == NULL || s2 == NULL)
		return (checknull(s1, s2, free));
	tlen = ft_strlen(s1) + ft_strlen(s2) +1;
	s = (char *) malloc (tlen);
	if (s == NULL)
		return (NULL);
	ft_strlcpy(s, s1, tlen);
	ft_strlcpy(s + ft_strlen(s1), s2, tlen);
	if (free == 1 || free == 3)
		s1 = ft_free(s1);
	if (free == 2 || free == 3)
		s2 = ft_free(s2);
	return (s);
}
