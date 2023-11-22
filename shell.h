#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/*  "environment" that points to arrays */
extern char **env;


/**
 * struct dt - contains most of the data
 * @av: arg vec
 * @inpt: comd written by the user
 * @as: tks of cmd line
 * @status: end status of shll
 * @count: program that counts lines
 * @_environ: env var
 * @pid: process ID of the shell
 */
typedef struct dt
{
	char **av;
	char *inpt;
	char **as;
	int status;
	int count;
	char **_environ;
	char *pid;
} dt_shell;

/**
 * struct sepa_list_s - slt
 * @septr: ; | &
 * @next: next node
 * Description: slt to store separaptrs
 */
typedef struct sepa_list_s
{
	char septr;
	struct sepa_list_s *next;
} sepa_list;

/**
 * struct line_list_s - slt
 * @line: cmd 
 * @next: nn
 * Description: slt to cmd
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - slt
 * @lens_var: length of var
 * @val: val of the var
 * @len_val: lens of the val
 * @next: next node
 * Description: slt to store val
 */
typedef struct r_var_list
{
	int lens_var;
	char *val;
	int lens_val;
	struct r_var_list *next;
} rvar;

/**
 * struct builtin_s - Builtin struct for command argurments
 * @name: The name of the cmd builtin i.e cd, exit, env
 * @f: data type ptr func.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(dt_shell *dtsh);
} builtin_t;

/* linked lists.c */
sepa_list *add_sep_nod_end(sepa_list **hd, char sep);
void free_sepa_list(sepa_list **hd);
line_list *add_line_nod_end(line_list **hd, char *line);
void free_line_lt(line_list **hd);

/*inked lists2.c */
rvar *add_rvar_node(rvar **hd, int lvar, char *var, int lval);
void free_rvar_lt(rvar **hd);

/* string functions */
char *_stct(char *d, const char *s);
char *_stcp(char *d, char *s);
int _stcmp(char *s1, char *s2);
char *_stchr(char *s, char c);
int _stpn(char *s, char *accept);

/* memm.c for memory managements*/
void _memcp(void *nptr, const void *ptr, unsigned int s);
void *_reloc(void *ptr, unsigned int o_s, unsigned int ne);
char **_relocdp(char **ptr, unsigned int o_s, unsigned int ne);


/* au_st2.c */
char *_stdp(const char *a);
int _stlen(const char *a);
int cm_char(char str[], const char *dm);
char *_sttk(char str[], const char *dem);
int _isdigit(const char *s);

/* string functions au_st3.c */
void rev_str(char *a);

/* for checking syntax errors */
int rep_char(char *ipt, int i);
int err_sep_op(char *ipt, int i, char l);
int ft_char(char *ipt, int *i);
void pt_syn_err(dt_shell *dtsh, char *ipt, int i, int b);
int check_syn_err(dt_shell *dtsh, char *ipt);

/* standard library functions */
int gt_lens(int a);
char *au_itoa(int a);
int _atoi(char *a);

/* func that gets sig */
void gt_sig(int s);

/* func for getting lines */
void bg_line(char **lptr, size_t *a, char *b, size_t s);
ssize_t gt_line(char **lptr, size_t *a, FILE *stm);/* split.c */

/*func fr splitting commandss */
char *sp_char(char *ipt, int b);
void add_nod(sepa_list **h_s, line_list **h_l, char *ipt);
void go_nt(sepa_list **lt_s, line_list **lt_l, dt_shell *dtsh);
int spt_cms(dt_shell *dtsh, char *ipt);
char **st_line(char *ipt);

/*func for env1.c */
int cp_env_nm(const char *n_env, const char *nm);
char *getenv(const char *nm, char **_env);


/* func for env2.c */
char *cp_info(char *nm, char *val);
void st_env(char *nm, char *val, dt_shell *dtsh);
int _setenv(dt_shell *dtsh);
int _unsetenv(dt_shell *dtsh);


/* func that gets builtin */
int (*gt_builtin(char *cmd))(dt_shell *dtsh);

/* func that loops shell */
char *wt_comm(char *in);
void shell_lp(dt_shell *dtsh);

/* func that changes directory */
void cd_dt(dt_shell *dtsh);
void cd_to(dt_shell *dtsh);
void cd_prev(dt_shell *dtsh);
void cd_t_hom(dt_shell *dtsh);

/* changes directory of the shell */
int cd_sh(dt_shell *dtsh);

/* func that gets error */
int get_err(dt_shell *dtsh, int ev);

/*func that solves error */
char *stct_cd(dt_shell *, char *, char *, char *);
char *err_not_fd(dt_shell *dtsh);
char *err_gt_cd(dt_shell *dtsh);
char *err_exit_shell(dt_shell *dtsh);

/* erro2 */
char *err_gt_alias(char **as);
char *err_env(dt_shell *dtsh);
char *err_syn(char **as);
char *err_perm(char **as);
char *err_pt(dt_shell *dtsh);

#endif
