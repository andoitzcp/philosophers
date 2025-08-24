# PHILOSOPHERS

a 42 project

## Test

To test data races:

```
valgrind --tool=helgrind --tool=drd ./philo 200 800 200 200 10
```
