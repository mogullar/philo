include "philo.h"

int	check_good(t_status *status)
{
	pthread_mutex_lock(&status->m_good);
	if (!status->good)
	{
		pthread_mutex_unlock(&status->m_good);
		return (1);
	}
	pthread_mutex_unlock(&status->m_good);
	return (0);
}

void struct_init(t_status *status, char *argv[])
{
	status->philo_n = ft_atoi(argv[1]);
	status->ttd = ft_atoi(argv[2]);
	status->tte = ft_atoi(argv[3]);
	status->tts = ft_atoi(argv[4]);
	status.eat_n = -1;
}