#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	m_eating;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	int				id;
	int				nbr_eat;
	long long		last_eat;
	long long		limit_eat;
	struct s_main	*status;
}	t_philo;

typedef struct s_main
{
	t_philo			*philos;
	pthread_t		look;
	pthread_mutex_t	m_eat_count;
	pthread_mutex_t	m_good;
	pthread_mutex_t	*forks;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_dead;
	int				philo_n;
	int				good;
	int				tte;
	int				tts;
	int				ttd;
	int				eat_n;
	int				eat_count;
	long long		time;
}	t_status;

typedef struct s_args
{
	t_status	*status;
	t_philo	*philo;
}	t_args;

void		half_philo(t_status *status, int i);
int			ft_atoi(const char *str);
int			ft_strlen(const char *str);
long long	get_time(void);
int			check_good(t_status *status);
void		philo_eat(t_philo *philo);
void 		struct_init(t_status *status, char *argv[])
void		*look(void *arg);
void		ft_putnbr_fd(int n, int fd);
void		ft_usleep(t_status *status, int stop_ms);
void		print_message(t_philo *philo, char *str);
void		*philosopher(void *arg);

#endif
