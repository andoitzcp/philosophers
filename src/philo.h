#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

/*
  Struct s_params
  NoP: Number of Philosophers
  TtD: Time to Die
  TtE: Time to Eat
  TtS: Time to Sleep
  NME: Number of times a philosopher Must Eat
*/

#define ANNOUNCE_FORK "has taken a fork"
#define ANNOUNCE_EAT "is eating"
#define ANNOUNCE_SLEEP "is sleeping"
#define ANNOUNCE_THINK "is thinking"
#define ANNOUNCE_DEATH "died"

typedef struct s_params
{
    int nop;
    int ttd;
    int tte;
    int tts;
    int nme;
} t_params;

typedef struct s_philo
{
    int nbr;
    pthread_t thr;
    pthread_mutex_t *lfm;
    pthread_mutex_t *rfm;
    struct s_philo *lpn;
    struct s_philo *rpn;
    struct timeval *last_m;
    struct timeval *time_s;
    struct s_prompt *prompt;
    int count_m;
} t_philo;

typedef struct s_prompt
{
    struct s_params *params;
    struct s_philo **table;
    pthread_mutex_t *print_mutex;
} t_prompt;

void create_threads(t_prompt *prompt);
void jointhreads(t_prompt *prompt);
void *routine(void *);

//Initializations
t_prompt *init_prompt();
void set_params(t_params *params, int argc, char **argv);
void init_table(t_prompt *prompt);
t_philo *init_philo(t_prompt *prompt, pthread_mutex_t **tmp_forks);
void build_table(t_prompt *prompt, t_philo **tmp_table);
pthread_mutex_t *init_fork(t_prompt *prompt);

// Error handling
void exit_on_error(t_prompt *prompt, char *s);
void cleanup(t_prompt *prompt);
void free_table(t_philo **head);

// Utils
size_t	ft_strlen(const char *str);
int	ft_isdigit(int c);
void	ft_putstr_fd(char *s, int fd);
int	ft_abs(int i);
int	ft_atoi(const char *nptr);

// Debug
void ft_printphilosopher(t_philo *p);
void ft_printtable(t_philo **head);
void ft_printparams(t_params *params);
