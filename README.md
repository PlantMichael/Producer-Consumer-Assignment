# Producer-Consumer-Assignment
 An assignment for CS 33211

# Problem
The producer generates items and puts items onto the table. The consumer will pick up items. The table can only hold two items at the same time. When the table is complete, the producer will wait. When there are no items, the consumer will wait. We use semaphores to synchronize producer and consumer.  Mutual exclusion should be considered. We use threads in the producer program and consumer program. Shared memory is used for the “table”.

# The Code
Starts by the producer creating a shared memory object with 2 random numbers and puts them into the buffer. The consumer then takes the numbers out and the producer may produce more again.
