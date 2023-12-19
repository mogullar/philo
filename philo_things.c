#include "philo.h"

void	print_message(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->status->m_print);
	if (philo->status->good == 1)
	{
		printf("%lld %d %s\n", get_time() - philo->status->time,
			philo->id + 1, str);
	}
	pthread_mutex_unlock(&philo->status->m_print);
}

void	find_forks(t_status *status, int id)
{
	status->philos[id].l_fork = &status->forks[id];
	if (id + 1 >= status->philo_n)
		status->philos[id].r_fork = &status->forks[0];
	else
		status->philos[id].r_fork = &status->forks[id + 1];
}

void	half_philo(t_status *status, int i)
{
	while (i < status->philo_n)
	{
		status->philos[i].status = status;
		status->philos[i].id = i;
		status->philos[i].last_eat = status->time;
		status->philos[i].limit_eat = status->time + status->ttd;
		status->philos[i].nbr_eat = 0;
		find_forks(status, i);
		pthread_mutex_init(&status->philos[i].m_eating, NULL);
		pthread_create(&status->philos[i].thread, NULL, philosopher,
			&status->philos[i]);
		i += 2;
	}
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(philo->r_fork);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(&philo->m_eating);
	print_message(philo, "is eating");
	philo->last_eat = get_time();
	philo->limit_eat = philo->last_eat + philo->status->ttd;
	pthread_mutex_unlock(&philo->m_eating);
	ft_usleep(philo->status, philo->status->tte);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	if (philo->status->eat_n != -1)
	{
		pthread_mutex_lock(&philo->status->m_eat_count);
		philo->nbr_eat += 1;
		philo->status->eat_count += 1;
		pthread_mutex_unlock(&philo->status->m_eat_count);
	}
}
