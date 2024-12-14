
# 42_Philosophers

### "The unexamined life is not worth living."
— Socrates

42Berlin school project created by Maryna Peshko (mpeshko) in November of 2024. Studying the basics of multithreading. More details in the topic "Philosophers.subject.pdf"

### Logic

The two most important functions to understand a logic:
* `void	*routine(void *arg)`
* `int	ft_fork(t_philo *philo)`
* `int	ft_think(t_philo *philo)`

<br />`In routine() all even philosophers start later than all odd ones.
`if (philo->philo_id % 2 == 0)
		ft_usleep(5);`
<br />`ft_fork() has diferrent logic in taking forks for even and odd philosophers.
<br />`ft_think()  is used to delay a philosopher before he takes a fork, so that he doesn't get there early and steal it from another philosopher who waited longer. This prevents some philosopher from waiting too long for his fork and dying.

### The program input:
`./philo`
<br />`   [number_of_philosophers]`
<br />`   [time_to_die]`
<br />`   [time_to_eat]`
<br />`   [time_to_sleep]`
<br />`   _(optional argument)`_
<br />`   [number_of_times_each_philosopher_must_eat]`
<br />`  <br />`  According to the subject, all tests are limited to 200 philosophers, and the minimum time is 50 ms.

### Examples

Philosopher should not eat and should die.
<br />`./philo 1 800 200 200`
<br /><br />
No Philosopher should die.
<br />`./philo 5 800 200 200`
<br /><br />
No Philosopher should die and the simulation should stop when every philosopher has eaten at least 7 times.
<br />`./philo 5 800 200 200 3`
<br /><br />
No Philosopher should die.
<br />`./philo 4 410 200 200`
<br /><br />
One Philosopher should die.
<br />`./philo 4 299 200 100`
<br /><br />
One Philosopher should die.
<br />`./philo 10 299 2000 100`
<br /><br />
No one should die
<br />`./philo 10 299 2000 100`
<br /><br />
Parsing tests
<br />`./philo 2 "" "" ""`
<br />`./philo -2 100 100 100`
<br />`./philo f 100 100 100`

### How to check for data races 
`valgrind --tool=helgrind`

### How to check used function

`nm -u ./philo`

### Contacts
<br />https://www.linkedin.com/in/maryna-peshko/
<br />email: marunapeshko@gmail.com

(c) Maryna Peshko