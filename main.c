#include "philo.h"

void	*philosopher(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->status->eat_n != -1
			&& philo->nbr_eat == philo->status->eat_n)
			return (NULL);
		if (check_good(philo->status))
			return (NULL);
		philo_eat(philo);
		if (check_good(philo->status))
			return (NULL);
		print_message(philo, "is sleeping");
		ft_usleep(philo->status, philo->status->tts);
		if (check_good(philo->status))
			return (NULL);
		print_message(philo, "is thinking");
	}
}

void	ft_clear(t_status *status)
{
	int	i;

	i = -1;
	while (++i < status->philo_n)
		pthread_detach(status->philos[i].thread);
	free(status->philos);
	while (++i < status->philo_n)
		pthread_mutex_destroy(&status->forks[i]);
	free(status->forks);
}

int	create_philo(t_status *status)
{
	int	i;

	status->eat_count = 0;
	status->philos = malloc(sizeof(t_philo) * status->philo_n);
	status->forks = malloc(sizeof(pthread_mutex_t) * status->philo_n);
	pthread_mutex_init(&status->m_print, NULL);
	i = -1;
	while (++i < status->philo_n)
		pthread_mutex_init(&status->forks[i], NULL);
	pthread_mutex_init(&status->m_good, NULL);
	pthread_mutex_init(&status->m_eat_count, NULL);
	status->time = `get_time();
	half_philo(status, 0);
	ft_usleep(status, 10);
	half_philo(status, 1);
	pthread_create(&status->look, NULL, look, status);
	pthread_join(status->look, NULL);
	ft_clear(status);
	return (0);
}

int	check_inputs(t_status *status)
{
	if (!(status->philo_n > 0))
		return (1);
	if (!(status->tte > 0))
		return (1);
	if (!(status->tts > 0))
		return (1);
	if (!(status->ttd > 0))
		return (1);
	if (!(status->eat_n > 0) && status->eat_n != -1)
		return (1);
	return (0);
}

int	main(int argc, char const *argv[])
{
	t_status		status;

	if (argc > 4 && argc <= 6)
	{
		struct_init(&status, argv);
		if (argc == 6)
			status.eat_n = ft_atoi(argv[5]);
		if (check_inputs(&status))
		{
			write(STDERR_FILENO, "Error inputs\n", ft_strlen("Error inputs\n"));
			return (1);
		}
		status.good = 1;
		create_philo(&status);
	}
	else
	{
		write(STDERR_FILENO, "Error inputs\n", ft_strlen("Error inputs\n"));
		return (1);
	}
	return (0);
}
