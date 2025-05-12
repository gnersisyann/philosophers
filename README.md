# 🧠 Philosophers

This repository contains a solution to the classic "Dining Philosophers" problem, developed as part of the 42 school curriculum. The project is split into two parts:

* **Mandatory** (`philo`) — basic implementation using threads and mutexes.
* **Bonus** (`philo_bonus`) — extended version using processes and semaphores.

## 📚 Table of Contents

* [Project Description](#project-description)
* [Implementation Highlights](#implementation-highlights)

  * [Mandatory](#mandatory)
  * [Bonus](#bonus)
* [Build & Run](#build--run)
* [Usage Examples](#usage-examples)
* [Best Practices & Notes](#best-practices--notes)

## 📖 Project Description

The project simulates the behavior of N philosophers sitting at a table and alternating between four states:

1. **Thinking** 🤔
2. **Taking forks** 🍴
3. **Eating** 🍝
4. **Sleeping** 😴

Each philosopher must pick up two forks (shared with their neighbors) before eating. The challenge lies in synchronizing their actions to avoid **deadlocks** and **starvation**.

## 🛠 Implementation Highlights

### ✅ Mandatory

* Uses **threads** (`pthread`) for each philosopher.
* **Mutexes** represent forks (`pthread_mutex_t`).
* Includes monitoring to track the time since last meal.
* Ensures proper thread termination and resource cleanup.

### 🚀 Bonus

* Uses **processes** (`fork`) instead of threads.
* Employs **semaphores** (`sem_open`, `sem_wait`, `sem_post`) for managing forks and output.
* A separate monitor process checks philosopher states.
* Supports an optional argument for the number of meals per philosopher.

## ⚙️ Build & Run

1. Clone the repository:

   ```bash
   git clone https://github.com/gnersisyann/philosophers.git
   cd philosophers
   ```

2. Build both versions:

   ```bash
   make
   ```

3. Run the **mandatory** version:

   ```bash
   ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_must_eat]
   ```

4. Run the **bonus** version:

   ```bash
   ./philo_bonus <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_must_eat]
   ```

**Example:**

```bash
./philo 5 800 200 200 7
```

This will simulate 5 philosophers with:

* 800ms to die
* 200ms to eat
* 200ms to sleep
* each must eat 7 times

## 💻 Usage Examples

```bash
# Mandatory:
./philo 2 410 200 200

# Bonus with meal count:
./philo_bonus 4 410 200 200 5
```

## 💡 Best Practices & Notes

* Robust argument parsing and error handling.
* Modular design for easier maintenance.
* In the bonus version, semaphores ensure consistent console output.
* Clear resource management: mutexes and memory are always freed.
