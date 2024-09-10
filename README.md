# Philosophers

This project is an implementation of the classic **Dining Philosophers Problem**, featuring both a basic solution and a more advanced solution in the **bonus** section. It demonstrates the use of multi-threading, synchronization, and handling concurrency issues such as deadlock, race conditions, and starvation using mutexes and semaphores.

## Table of Contents

- [Introduction](#introduction)
- [Philosophers Problem](#philosophers-problem)
- [How It Works](#how-it-works)
- [Installation](#installation)
- [Usage](#usage)
- [Bonus Part](#bonus-part)

## Introduction

The Dining Philosophers Problem is a classic synchronization problem where philosophers sit around a table and alternate between eating and thinking. The challenge is to manage resource sharing (forks) such that no philosopher starves or gets into a deadlock. This project provides a solution using threads and mutexes in C, as well as an advanced version using semaphores in the **bonus** section.

## Philosophers Problem

In this problem, a certain number of philosophers sit at a round table. There is a fork between each pair of philosophers. Philosophers alternate between thinking and eating. However, to eat, each philosopher needs to pick up both the fork to their left and the fork to their right. Philosophers must avoid deadlock (where everyone is holding one fork but waiting for another) and starvation (where a philosopher never gets to eat).

## How It Works

- Each philosopher is represented by a separate thread.
- Forks are shared resources, represented by mutexes.
- Philosophers follow this pattern:
  1. Think for a certain time.
  2. Wait for both forks (left and right).
  3. Eat for a certain time.
  4. Release both forks.
  5. Sleep for a certain time.
  6. Repeat.

The solution ensures no philosopher will starve and avoids deadlock through proper synchronization techniques.

### Key Concepts Used:

- **Multithreading**: Each philosopher is a thread.
- **Mutexes**: To control access to shared resources (forks).
- **Synchronization**: Proper handling of shared resources to avoid race conditions and deadlocks.

## Installation

To compile and run the project, follow these steps:

1. Clone the repository:

    ```bash
    git clone https://github.com/ddavlet/Philosophers.git
    cd Philosophers/philo
    ```

2. Compile the code:

    ```bash
    make
    ```

## Usage

After compiling, you can run the program with the following command:

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> <number_of_meals>
```

<number_of_philosophers>: The number of philosophers sitting at the table.
<time_to_die>: The maximum time (in milliseconds) a philosopher can go without eating before dying.
<time_to_eat>: The time (in milliseconds) a philosopher spends eating.
<time_to_sleep>: The time (in milliseconds) a philosopher spends sleeping.
[<number_of_meals>] (optional): The number of meals each philosopher must eat before the simulation ends. If not provided, the simulation will run indefinitely.
Example:

```bash
./philo 5 800 200 200
```

This command simulates 5 philosophers who:

Must eat before 800 milliseconds pass.
Spend 200 milliseconds eating.
Spend 200 milliseconds sleeping.

## Bonus Part

In the bonus part of the project, an enhanced version of the solution is implemented. Instead of using mutexes, semaphores are used to manage resource sharing and synchronization. This provides a different method to ensure thread-safe operations and handle concurrency issues.

### Key Differences in the Bonus:

Semaphore-Based Solution: Instead of using a mutex per fork, semaphores are used to manage the shared resources and control access more efficiently.
Process-Based Implementation: Each philosopher is forked as a separate process instead of using threads. This allows handling synchronization at a process level rather than thread level.
Improved Deadlock Prevention: The bonus version provides enhanced prevention mechanisms for avoiding deadlock and starvation through the use of semaphores.
Compiling the Bonus Version:
To compile the bonus version, use the following command:

```bash
cd philo_bonus
make
```

Running the Bonus Version:
The command to run the bonus version is the same as the basic version:

```bash
./philo_bonus <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [<number_of_meals>]
```

This will start the bonus version of the dining philosophers problem using semaphores.
