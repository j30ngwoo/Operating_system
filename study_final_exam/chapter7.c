// 1. bounded-buffer (producer-consumer) problem
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

// 2. readers-writers problem


// 3. dining philosophers problem

