### 1. bounded-buffer (producer-consumer) problem
```cpp
int n;
semaphore mutex = 1;
semaphore empty = n;
semaphore full = 0;

// producer
wait(empty);
wait(mutex);
produce();
signal(mutex);
signal(full);

// consumer
wait(full);
wait(mutex);
consume();
signal(mutex);
signal(empty);
```

### 2. readers-writers problem
```cpp
int read_count;
semaphore mutex = 1;
semaphore wr_mutex = 1;

//writer
wait(wr_mutex);
write();
signal(wr_mutex);

//reader
wait(mutex);
read_count++;
if (read_count == 1)
	wait(wr_mutex);
signal(mutex);

read();

wait(mutex);
read_count--;
if (read_count == 0)
	signal(wr_mutex);
signal(mutex);
```

### 3. dining philosophers problem
```cpp
int i // i번째 철학자
enum state[i] = {thinking, ...} // thinking, eating, hungry
condition self[i];

void philosophers(int i)
{
	pickup(i);
	eating(i);
	pickdown(i);
}

void pickup(int i)
{
	state[i] = hungry;
	test(i);
	if (state[i] != eating)
		self[i].wait();
}

void pickdown(int i)
{
	state[i] = thinking;
	test((i + 4) % 5);
	test((i + 1) % 5);
}

void test(int i)
{
	if (state[i] == hungry && state[(i + 1) % 5] != eating 
		&& state[(i + 4) % 5] != eating)
	{
		state[i] == eating
		self[i].signal();
	}
}
```