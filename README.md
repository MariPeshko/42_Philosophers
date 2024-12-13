
# 42_Philosophers

>"The unexamined life is not worth living."
                                — Socrates

42Berlin school project created by Maryna Peshko (mpeshko) in November of 2024. Studying the basics of multithreading. More details in the topic "Philosophers.subject.pdf"

### The program input:
   `./philo
   [number_of_philosophers]
   [time_to_die]
   [time_to_eat]
   [time_to_sleep]
   (optional argument)
   [number_of_times_each_philosopher_must_eat]`

### Examples

Philosopher should not eat and should die.
<br />`./philo 1 800 200 200`
No Philosopher should die.
-`./philo 5 800 200 200`
No Philosopher should die and the simulation should stop when every philosopher has eaten at least 7 times.
-`./philo 5 800 200 200 3`
No Philosopher should die.
-`./philo 4 410 200 200`
One Philosopher should die.
-`./philo 4 299 200 100`
One Philosopher should die.
-`./philo 10 299 2000 100`
No one should die
-`./philo 10 299 2000 100`
Parsing tests
-`./philo 2 "" "" ""`
-`./philo -2 100 100 100`
-`./philo f 100 100 100`

### How to check for data races 
`valgrind --tool=helgrind`

### How to check used function

`nm -u ./philo`

-(c) Maryna Peshko
-https://www.linkedin.com/in/maryna-peshko/
-email: marunapeshko@gmail.com