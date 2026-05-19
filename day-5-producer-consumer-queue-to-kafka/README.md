## Beyond the Kernel | Modern C++ & Linux | Day 5 - From Producer Consumer Queues to Kafka

### Recap from Day 4

In my last post, I wrote about producer consumer pattern using a bounded queue. At a basic level the idea was simple:
 - A producer creates task
 - A consumer process task
 - A queue sits between them

### From One Application to Distributed Systems
This pattern is not limited to threads inside one process or application.
In real real distributed systems, the problem becomes much bigger. That is why systems like Kafka are very important.

### What is Kafka?
Kafka is an distributed event streaming platform. It allows applications to publish, store, and consume streams of records.
 - A Producer publishes an event to Kafka Topic
 - A Consumer reads and process an event from Kafka Topic
 - A Kafka Topic sits between them

### What is a Kafka Topic?
A Topic is a named stream of records. Think of it as a notice board in an apartment building:
 - The building manager puts a notice, Water will be turned off on Sunday at 10 AM.
 - Anyone can read the same notice, residents, cleaners, security, maintenance etc.
 - Each person uses this notice differently, residents store water, cleaners change their schedule, security answers questions and maintenance does the repair.

### Kafka Topic in Simple Terms
In Kafka terms:
 - The building manager is the producer
 - The notice board is the Kafka topic
 - The people reading the notice are consumers

So a Kafka Topic is a common place where messages or events are posted and many interested systems can read them.

### Kafka Topics, Partitions, and Offsets
Kafka Topics
 - Retain Messages based on retention policy such as time.
 - Divided into one or more partitions
 - Each partition have messages or events
 - Each message or event have an position called an offset, which consumers use to track how far they have read.

### Consumer Groups

Kafka also supports consumer groups. In a consumer group a set of multiple consumers can share the same type of work, where one event is processed by one consumer only, that is one partition is read by one consumer only, within that consumer group.

### From Basic Pattern to Scale

So now basic

Producer -> Task -> Consumer

has evolved at scale to

Many Producers -> Many Topics and Partitions -> Many Consumers

### Where Kafka is Used

Kafka is commonly used for event driven systems, log aggregation, data pipelines, stream processing, and communication between services.

### Final Thought

Modern technologies may look complex from the outside, but many of them are built on foundational ideas.
That is why learning the fundamentals first makes advanced technologies much simpler to understand.
