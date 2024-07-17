/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:44:02 by moel-fat          #+#    #+#             */
/*   Updated: 2024/07/12 15:09:05 by ahsadik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <limits.h>
# include <fcntl.h>
# include <termios.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdbool.h>
# include <sys/signal.h>
# include "../libft/libft.h"

typedef struct s_file
{
	char			*filename;
	int				hd_fd;
	bool			is_exp;
	bool			quotes;
	int				index;
	int				type;
	struct s_file	*next;
}	t_file;

//**store cmd and args**//
typedef struct s_cmds
{
	char			*cmd;
	char			**args;
	t_file			*infile;
	t_file			*outfile;
	t_file			*iofiles;
	int				in_red;
	int				out_red;
	struct s_cmds	*next;
}	t_cmds;

// **store env** //
typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

// **store data** //
typedef struct s_data
{
	t_tokens	**tokens;
	t_cmds		**cmds;
	char		*cmd;
	t_env		*env;
	pid_t		pid;
	int			pipes[2];
	int			fd_in;
	int			fd_out;
	int			old_fdin;
	int			old_fdout;
	int			heredoc_fd;
	int			redoc_fd;
	bool		pipe_on;
	int			i;
	int			n;
	int			flag;
	int			status;
	char		*line;
	char		**path;
	char		**env_arry;
}	t_data;

enum e_synerror
{
	AMBGS,
	UQUOTES,
	HSTR,
	UNEXP,
};

enum e_redirect
{
	STDOUT,
	STDIN,
	OUTFILE,
	APPEND,
	INFILE,
	HEREDOC,
};

enum e_token_type
{
	COMMAND,
	FLAG,
	ARGUMENT,
	ASSIGN,
	PIPE,
	RFILE,
	ROUT,
	RAPPEND,
	RIN,
	RHEREDOC,
};

extern int	g_king;

// CHARLIE BRANCH
//	MAIN_UTILS
int		count2d(char **str);
int		just_space(char *str);
void	free_cmds(t_cmds **cmds);
int		parseit(t_tokens **tokens, t_cmds **cmds, t_data **data, char *cmd);

//	SIGNALS
int		signals_hand(void);

//	TOKENIZER_UTILS
void	fexit(t_data **data, int exit_status);
int		synerror(t_data **data, t_tokens *token, int errno);
int		startswith(char *cmd, char character, int i);
int		add_token(t_data **data, char *token, int type);

//	GET TOKENS
int		get_unquoted(char *cmd, int *i);
char	*get_redfile(t_data **data, char *cmd, int *i);
int		get_squoted(char *cmd, int *i);
int		get_dquoted(char *cmd, int *i);

//	TOKENIZER
int		check_filename(char chr, int position);
int		lexer(t_data **data);

//	PARSER
int		parser(t_data **data);
int		join_2d(t_cmds *cmd, char *arg);

//	LINKED_CMDS
t_cmds	*ft_cmdnew(void);
void	ft_cmdadd_back(t_cmds **lst, t_cmds *new);

//	LINKED_FILES
t_file	*ft_filenew(char *file, int type, int arg1null, int rf_index);
void	ft_fileadd_back(t_file **lst, t_file *new);
t_file	*file_copy(t_data **data, t_file *file);
void	ft_fileclear(t_file **lst);

//	EXPANSION_UTILS
char	*get_value(t_data *data, char *str, int var_end);
char	*single_var(t_data *data, char *str, int var_start, int var_end);
char	*get_var_value(char *str, t_data *data, int *i);
char	*ft_getenv(t_env *env, char *var_name);
char	**expand_args(t_data **data, char **args, int i, int is_exp);

//	PARSER_UTILS
int		notempty(char *arg);
char	**split_arg(char **args, int i);
void	*ft_free(void *ptr);
int		skip_quotes(char *str, int *i, int open2quotes);
int		get_red_index(t_tokens *token, int *red_index);

//	REFORM_CMDS
t_cmds	*reform_cmds(t_data **data, t_cmds *tmp_cmds);
char	**reform_args(t_data **data, char **args);
t_file	*reform_redfile(t_data **data, t_file *file);
void	merge_red(t_data **data, int status);
t_file	*merge_io(t_data **data, t_cmds *t_cmds);

//	CHECKER
int		check_syntax(t_data **data, int *is_heredoc, int status);
int		open_read_heredoc(t_data *data, char *delimiter);
int		ft_strnchr(char *str, char c, int n);
int		syntaxerr(t_tokens *tokens);

//	EXPANSION
char	*check_expand(char *str, t_data *data, int *is_exp, int thirdarg);
char	*expand(t_data *data, char *str, int var_start, int var_end);
char	*rm_quotes(char *str, int free);

// AMINE BRANCH

//**BUILTINS**//
void	ft_cd(t_cmds *cmd, t_data *data);
void	ft_setenv(char *name, char *value, t_data *data);
void	ft_exit(t_cmds *cmd, t_data *data);
void	ft_env(t_cmds *cmd, t_env *env, t_data *data);
void	ft_unset(t_cmds *cmd, t_data *data);
void	ft_pwd(t_cmds *cmds, t_data *data);
void	ft_echo(t_cmds *cmd, t_data *data);
void	ft_export(t_cmds *cmds, t_env **env, t_data *data);

//**EXECUTION**//
void	ft_execut(t_cmds *cmds, t_data *data);
// int		check_redirection_in(t_cmds *cmds);
int		check_redirection(t_cmds *cmds);
int		open_outfile(t_file *outfile);
int		open_append(t_file *outfile);
int		open_infile(t_file *infile);
char	**ft_find_path(char **env);
char	**ft_lst_to_array(t_env *env);
int		check_builtins(t_cmds *cmds, t_data *data);
int		access_exev(t_cmds *cmds, t_data *data);
int		access_exev(t_cmds *cmds, t_data *data);
int		check_slash(char **cmd);
t_env	*make_env(t_env **env, char **envp);
t_env	*make_env(t_env **env, char **envp);
void	make_backup_env(t_env **env);
void	add_env_var(t_env **env, const char *name, const char *value);
void	ft_printlist(t_env *env);
void	apply_redirections(t_data *data);
void	reset_redirections(t_cmds *cmd, t_data *data, int or_in, int or_out);
int		handle_red(t_cmds *cmds, t_data *data, int *or_stdin, int *or_stdout);
void	add_last_arg_to_env(t_cmds *cmds, t_data *data, int flag);
char	**remove_empty_args(t_cmds *cmd);
void	setup_environment(t_data *data);
void	cleanup_environment(t_data *data);
void	call_child(t_cmds *cmds, t_data *data, int in_fd, int out_fd);
void	wait_for_children(t_data *data);
void	ft_print_export(t_env *env);
int		ft_isvalid_identifier(char *str);
int		ft_find_plusequal(char *str);
void	ft_execut_multi_helper(t_cmds *cmds, t_data *data, int in_fd);
int		check_ambgred(const char *str);
void	close_heredoc_fds(t_cmds *cmds);
//***ERRORS***//
void	ft_print_cmd_error(char **cmd, t_data *data);
void	ft_error_cmdnotfound(char **cmd, t_data *data);
int		check_point_slash(char **cmd);
void	ft_error_permission_denie(char **cmd, t_data *data);
void	ft_error_is_directory(char **cmd, t_data *data);
void	ft_error_not_directory(char **cmd, t_data *data);
void	ft_error_ambiguous_redirect(char *str);
void	ft_error_identifier(char *str, t_data *data, int flag);
void	remove_quotesfromargs(t_cmds *cmds);
void	ft_error_open(char *file);

//**UTILS**//
void	ft_free_array(char **str);
void	add_last_arg_to_env(t_cmds *cmds, t_data *data, int flag);
int		ft_strcmp(char *s1, char *s2);
void	ft_lstadd_back_mini(t_env **lst, t_env *new);
t_env	*ft_lstnew_mini(char *name, char *value);
void	ft_setenv(char *name, char *value, t_data *data);
void	ft_free_list_env(t_env **env);
void	ft_print_array(char **array);
int		ft_isvalid_identifier(char *str);
void	reset_tty(void);
void	ft_add_env2(char *name, char *value, t_env **env, int flag);
t_data	*data_grep(t_data *data);

#endif