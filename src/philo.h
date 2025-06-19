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

#define MAX_PHILO_NUMBER 200

#define EXIT_MODE_PUTSTR 0
#define EXIT_MODE_PERROR 1

#define ERROR_STR_01 "philosophers: main: incorrect number of arguments\n"
#define ERROR_STR_02 "philosophers: main: not valid input parameters\n"
#define ERROR_STR_03 "philosophers: main: number of philosophers exceeded maximum\n"
#define ERROR_STR_04 "philosophers: main: number of philosophers must be a positive integer\n"
#define ERROR_STR_05 "philosophers: main: parameters must be a positive integer\n"



// TS: Time Stamp
//      F: Fork, M: Meal, S: Sleep T: Think
//enum {TSF,     TSM,     TSS,     TST};

typedef struct s_params
{
    int nop;
    int ttd;
    int tte;
    int tts;
    int nme;
} t_params;

typedef struct s_tstamp
{
    struct timeval tv;
    pthread_mutex_t mtx;
    unsigned long usecs;
} t_tstamp;

typedef struct s_philo
{
    int nbr;
    pthread_t thr;
    pthread_mutex_t *lfm;
    pthread_mutex_t *rfm;
    pthread_mutex_t mcm;
    struct s_philo *lpn;
    struct s_philo *rpn;
    struct s_tstamp tsf;
    struct s_tstamp tsm;
    struct s_tstamp tss;
    struct s_tstamp tst;
    struct s_tstamp tsd;
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
    pthread_mutex_t death_mutex;
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
int is_alive_philo(t_philo *philo);
int is_philo_finished_eating(t_prompt *prompt, t_philo *philo);
int all_have_eaten(t_prompt *prompt);

//Initializations
void init_prompt(t_prompt *prompt, t_params *params, t_philo **table);
void set_params(t_params *params, int argc, char **argv);
void init_table(t_prompt *prompt, t_philo *philos, pthread_mutex_t *forks);
void init_philo(t_prompt *prompt, t_philo *philo, pthread_mutex_t *forks);
void build_table(t_prompt *prompt, t_philo *philos);

// Error handling
void exit_on_error(char *s, int exit_mode);
void check_input_params(t_params *params);
int is_valid_input_args(char **argv);
int is_number(char *s);

// Utils libft
size_t	ft_strlen(const char *str);
int	ft_isdigit(int c);
void	ft_putstr_fd(char *s, int fd);
int	ft_abs(int i);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int	ft_atoi(const char *nptr);

// Utils
unsigned long get_time_in_microseconds(struct timeval tv);
void Announce(t_philo *philo, char *s, t_tstamp *ts);
void init_tstamp(t_tstamp *tstamp);
void update_tstamp(t_tstamp *tstamp);
unsigned long get_tstamp_usecs(t_tstamp *tstamp);
void set_death_flag(t_prompt *prompt, int val);
int get_death_flag(t_prompt *prompt);

// Debug
void ft_printphilosopher(t_philo *p);
void ft_printtable(t_philo **head);
void ft_printparams(t_params *params);
