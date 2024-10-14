#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

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
    pthread_t t;
    char *lf;
    char *rf;
    struct s_philo *lp;
    struct s_philo *rp;
} t_philo;
