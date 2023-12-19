#include "philo.h"

int	look_eat(t_status *status)
{
	pthread_mutex_lock(&status->m_eat_count);
	if (status->eat_count >= status->philo_n * status->eat_n
		&& status->eat_n != -1)
	{
		pthread_mutex_lock(&status->m_good);
		status->good = 0;
		pthread_mutex_unlock(&status->m_good);
		pthread_mutex_unlock(&status->m_eat_count);
		return (1);
	}
	pthread_mutex_unlock(&status->m_eat_count);
	return (0);
}

int	look_life(t_status *status, int i)
{
	if (get_time() > status->philos[i].limit_eat)
	{
		pthread_mutex_lock(&status->m_print);
		pthread_mutex_lock(&status->m_good);
		status->good = 0;
		pthread_mutex_unlock(&status->m_good);
		printf("%lld %d died\n", get_time() - status->time, i + 1);
		pthread_mutex_unlock(&status->m_print);
		return (1);
	}
	return (0);
}

void	*look(void *arg)
{
	t_status		*status;
	int			i;

	status = (t_status *)arg;
	while (1)
	{
		i = -1;
		while (++i < status->philo_n)
		{
			pthread_mutex_lock(&status->philos[i].m_eating);
			if (look_life(status, i) || look_eat(status))
			{
				pthread_mutex_unlock(&status->philos[i].m_eating);
				return (NULL);
			}
			pthread_mutex_unlock(&status->philos[i].m_eating);
		}
		usleep(100);
	}
}
