/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:56:28 by ahsadik           #+#    #+#             */
/*   Updated: 2024/07/12 15:09:21 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_tokens
{
	char				*token;
	int					type;
	struct s_tokens		*next;
}	t_tokens;

typedef struct s_sp
{
	char	**res;
	int		s_counter;
	int		res_count;
	int		start;
	int		s_len;
}	t_sp;

int			ft_isalpha(int c);
int			ft_isdigit(int d);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_isalnum(int c);
size_t		ft_strlen(const char *str);
int			ft_toupper(int c);
int			ft_tolower(int c);
void		ft_bzero(void *s, size_t n);
char		*ft_strdup(const char *source );
char		*ft_strchr(const char *str, int c);
char		*ft_strrchr(const char *str, int c);
void		*ft_calloc( size_t count, size_t size );
char		*ft_itoa(int n);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
char		**ft_split(char const *s, char sep);
int			ft_lstsize(t_tokens *lst);
t_tokens	*ft_lstnew(void *token, int type);
t_tokens	*ft_lstlast(t_tokens *lst);
void		ft_lstiter(t_tokens *lst, void (*f)(void *));
void		ft_lstdelone(t_tokens *lst, void (*del)(void *));
void		ft_lstclear(t_tokens **lst);
void		ft_lstadd_back(t_tokens **lst, t_tokens *new);
void		ft_lstadd_front(t_tokens **lst, t_tokens *new);
t_tokens	*ft_lstmap(t_tokens *lst, void *(*f)(void *), void (*del)(void *));
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strjoin(char *s1, char *s2, int free);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
char		*ft_strmapi(char const *s, char (*f)(unsigned	int, char));
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memcpy(void *dest, const void *src, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memset( void *pointer, int value, size_t count );
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
void		*ft_memchr( const void *m_block, int chr, size_t size );
char		*ft_strnstr(const char *str, const char *word, size_t len);
int			ft_atoi(const char *str);
#endif
