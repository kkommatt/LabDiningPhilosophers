#include <time.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define COUNT 5
#define MAX_MEAL 2

pthread_t philosophers[COUNT];
pthread_mutex_t forks[COUNT];

// Simulates the activity of a philosopherBehave, which can be either thinking or eating.
// This function prints a message indicating the philosopherBehave's number and the action they are performing,
// and then waits for a random time to simulate the duration of the activity.
void simulatePhilosopherActivity(int number, const char *action)
{
    printf("Philosopher %d %s.\n", number, action);
    sleep(1 + rand() % 2);
}

// Simulates the philosopherBehave thinking.
void think(int number)
{
    simulatePhilosopherActivity(number, "is thinking");
}

// Simulates the philosopherBehave eating.
void eat(int number)
{
    simulatePhilosopherActivity(number, "is eating");
}

// Tries to pick up the forks for eating. 1 if both forks are successfully picked up, 0 otherwise.
int pickupForks(int number, int first_fork, int second_fork)
{
    pthread_mutex_lock(&forks[first_fork]);
    printf("Philosopher %d picked up fork %d.\n", number, first_fork);

    if (pthread_mutex_trylock(&forks[second_fork]) == 0)
    {
        printf("Philosopher %d picked up fork %d and starts eating.\n", number, second_fork);
        return 1;
    }
    else
    {
        printf("Philosopher %d couldn't pick up fork %d and continues thinking.\n", number, second_fork);
        pthread_mutex_unlock(&forks[first_fork]);
        printf("Philosopher %d put down fork %d.\n", number, first_fork);
        return 0;
    }
}

// Releases the forks after eating
void releaseForks(int number, int first_fork, int second_fork)
{
    pthread_mutex_unlock(&forks[first_fork]); // Release the first fork
    printf("Philosopher %d put down fork %d.\n", number, first_fork);

    pthread_mutex_unlock(&forks[second_fork]); // Release the second fork
    printf("Philosopher %d put down fork %d.\n", number, second_fork);
}

// Simulates the behavior of a philosopher
void *philosopherBehave(void *num)
{
    int number = *(int *)num;
    int eaten = 0;

    while (eaten < MAX_MEAL)
    {
        think(number);

        int first_fork = number;
        int second_fork = (number + 1) % COUNT;

        if (pickupForks(number, first_fork, second_fork))
        {
            eat(number);
            eaten++;
            releaseForks(number, first_fork, second_fork);
        }
    }

    printf("Philosopher %d finished all meals and leaves the table.\n", number);

    return NULL;
}

// The main function initializes mutexes, creates philosopher threads, and waits for them to finish.
int main()
{
    int i, numbers[COUNT];

    srand(time(NULL));

    for (i = 0; i < COUNT; i++)
    {
        pthread_mutex_init(&forks[i], NULL);
    }

    for (i = 0; i < COUNT; i++)
    {
        numbers[i] = i;
        if (pthread_create(&philosophers[i], NULL, philosopherBehave, &numbers[i]))
        {
            fprintf(stderr, "Error creating thread\n");
            return 1;
        }
    }

    for (i = 0; i < COUNT; i++)
    {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}
