#include "philosopher.h"

int get_full(t_rules *rules)
{
	int full;
	pthread_mutex_lock(&rules->done_lock);
	full = rules->full;
	pthread_mutex_unlock(&rules->done_lock);
	return full;
}

void set_full(t_rules *rules)
{
	pthread_mutex_lock(&rules->done_lock);
	rules->full = 1;
	pthread_mutex_unlock(&rules->done_lock);
}

void *dinning(void *arg)
{
	t_rules *rules;
	int	completed;
	int i;

	rules = (t_rules *)arg;
	while (!get_stop(rules) && !get_full(rules))
	{
		i = 0;
		completed = 0;
		while(i < rules->nb_philo)
		{
			pthread_mutex_lock(&rules->philos[i].meal_lock);
			if (rules->philos[i].meals_eaten == rules->must_eat)
				completed++;
			pthread_mutex_unlock(&rules->philos[i].meal_lock);
			i++;
		}
		if (rules->must_eat != -1 && completed == rules->nb_philo)
			set_full(rules);
	}
	return NULL;
}
