#include <stdlib.h>
#include <stddef.h>
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

// Color scape secuences: thanks to javi
#define  BLACK   "\e[0;30m"
#define  RED     "\e[0;31m"
#define  GREEN   "\e[0;32m"
#define  YELLOW  "\e[0;33m"
#define  BLUE    "\e[0;34m"
#define  PURPLE  "\e[0;35m"
#define  CYAN    "\e[0;36m"
#define  WHITE   "\e[0;37m"
#define  RESET   "\x1b[0m"

#define ANNOUNCE_FORK CYAN"has taken a fork"WHITE
#define ANNOUNCE_EAT GREEN"is eating"WHITE
#define ANNOUNCE_SLEEP BLUE"is sleeping"WHITE
#define ANNOUNCE_THINK YELLOW"is thinking"WHITE
#define ANNOUNCE_DEATH RED"died"WHITE

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
    struct timeval last_m;
    struct timeval time_s;
    struct s_prompt *prompt;
    int count_m;
} t_philo;

typedef struct s_prompt
{
    int someone_has_died;
    struct s_params *params;
    struct s_philo **table;
    pthread_t orchttr;
    pthread_mutex_t print_mutex;
} t_prompt;

void create_threads(t_prompt *prompt);
void jointhreads(t_prompt *prompt);
// Routine
void *routine(void *);
int action_take_forks(t_philo *philo);
int action_eat(t_philo *philo);
int action_sleep(t_philo *philo);
int action_think(t_philo *philo);

// Control
void *control(void *p);

//Initializations
void init_prompt(t_prompt *prompt, t_params *params, t_philo **table);
void set_params(t_params *params, int argc, char **argv);
void init_table(t_prompt *prompt, t_philo *philos, pthread_mutex_t *forks);
void init_philo(t_prompt *prompt, t_philo *philo, pthread_mutex_t *forks);
void build_table(t_prompt *prompt, t_philo *philos);

// Error handling
void exit_on_error(t_prompt *prompt, char *s);
void cleanup(t_prompt *prompt);
void free_table(t_philo **head);

// Utils libft
size_t	ft_strlen(const char *str);
int	ft_isdigit(int c);
void	ft_putstr_fd(char *s, int fd);
int	ft_abs(int i);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int	ft_atoi(const char *nptr);

// Utils
unsigned long get_time_in_microseconds(struct timeval tv);
void Announce(t_philo *philo, char *s);

// Debug
void ft_printphilosopher(t_philo *p);
void ft_printtable(t_philo **head);
void ft_printparams(t_params *params);
