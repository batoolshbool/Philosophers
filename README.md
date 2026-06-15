*This project has been created as part of the 42 curriculum by bshbool.*

---

## Description

**Philosophers** is a project designed to simulate the classic *Dining Philosophers Problem*, a famous computer science problem that illustrates the challenges of **concurrency**, **multithreading**, and **process synchronization**.

The core goal of the project is to manage a set of philosophers who sit at a round table with a large bowl of spaghetti. Each philosopher must alternatingly **eat**, **think**, and **sleep**. However, there are only as many forks as there are philosophers, and a philosopher needs **two forks** (left and right) to eat.

### Key Rules & Challenges

* Philosophers do not know if another is about to die, and they cannot speak to one another.
* The main objective is to design an algorithm using threads and mutexes to prevent **starvation** and avoid **deadlocks**.
* The simulation stops the moment a single philosopher dies of starvation.

---

## Instructions

### Prerequisites

To compile and run this project, you need a C compiler (`gcc` or `clang`) and standard POSIX thread libraries, typically found on a **Linux** (e.g., Ubuntu/Xubuntu) or macOS environment.

### Compilation

The project includes a multi-rule `Makefile` located at the root directory. To compile the executable, run the following command in your terminal:

```bash
make

```

This will compile the source files in the `src/` directory (such as `philosophers.c`, `monitor.c`, `simulation.c`, `routine.c`, and `utils.c`) into an executable named `philo`.

**Other Makefile commands:**

* `make clean`: Removes the compiled object files (`.o`).
* `make fclean`: Removes the object files and the `philo` executable.
* `make re`: Forcefully re-compiles the entire project from scratch.

### Execution

Run the compiled executable with the required command-line arguments:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

```

#### Arguments Guide:

1. **`number_of_philosophers`**: The number of philosophers at the table, which also equals the total number of forks.
2. **`time_to_die`** *(in milliseconds)*: If a philosopher doesn't start eating within this timeframe from their last meal (or the start of the simulation), they die.
3. **`time_to_eat`** *(in milliseconds)*: The duration it takes for a philosopher to eat (during which they hold two forks).
4. **`time_to_sleep`** *(in milliseconds)*: The duration a philosopher spends sleeping after finishing a meal.
5. **`[number_of_times_each_philosopher_must_eat]`** *(Optional)*: If all philosophers eat at least this many times, the simulation terminates safely. If not specified, the simulation runs indefinitely until a philosopher dies.

#### Example:

```bash
# 4 philosophers, die if they don't eat within 410ms, take 200ms to eat, and 200ms to sleep.
./philo 4 410 200 200

```

---

## Technical Choices & File Structure

The source structure of the project is divided logically to maintain modularity and clean threading states:

* **`philo.h`**: The central configuration header containing structural layouts (`t_philo`, `t_data`), function definitions, and tracking states.
* **`src/philosophers.c`**: Entry point handling parsing, primary resource allocations, and sequence lifecycles.
* **`src/simulation.c` / `src/simulation2.c**`: Routines managing mutex initializations, thread creations, and resource cleanups.
* **`src/routine.c`**: Contains the core action cycle loop (take forks, eat, sleep, think) executed by each philosopher thread.
* **`src/monitor.c`**: Runs a dedicated monitoring thread responsible for continuously verifying that nobody has crossed the starvation timestamp.
* **`src/utils.c`**: Auxiliary timing tools (e.g., precise custom millisecond sleep tracking) and string formatting tools.

---

## Resources

### Documentation & Reference Materials

* **POSIX Threads:** `man pthread_create`, `man pthread_mutex_init`, and `man pthread_join`.
* **Dining Philosophers Problem:** Overview of synchronization challenges, deadlocks, and solution patterns (e.g., resource hierarchy solutions).
* **Youtube:** Guids from other 42 students. 

### AI Usage Statement

AI tools were utilized during the development of this project to aid in the following areas:

* **Code Optimization.** 
* **Debugging assistance.** 
* **`README.md` Structuring.**