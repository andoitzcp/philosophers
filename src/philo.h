#include <stdlib.h>
#include <stdio.h>
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
} t_philo;

void ft_printphilosopher(t_philo *p);
void ft_printtable(t_philo **head);
void ft_printparams(t_params *params);
