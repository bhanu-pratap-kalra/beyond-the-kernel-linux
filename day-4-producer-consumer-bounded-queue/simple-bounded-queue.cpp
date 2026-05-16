#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <optional>
#include <vector>
#include <iostream>

using namespace std;

template<typename T>
class SimpleBoundedQueue
{
	private:
		mutex mMutex;
		condition_variable mItsNotFull;
		condition_variable mItsNotEmpty;
		queue<T> mQueue;
		size_t mSize;
		bool done;
	public:
		explicit SimpleBoundedQueue(size_t queue_size) : mSize(queue_size)
		{
			done = false;
		}

		bool push(T task)
		{
			unique_lock<mutex> lock(mMutex);

			mItsNotFull.wait(lock, [this] { return mQueue.size() < mSize || done; } );

			if (done)
			{
				return false;
			}

			mQueue.push(move(task));

			mItsNotEmpty.notify_one();

			return true;
		}

		optional<T> pop()
		{
			unique_lock<mutex> lock(mMutex);

			mItsNotEmpty.wait(lock, [this] { return !mQueue.empty() || done; } );

			if (mQueue.empty() && done)
			{
				return nullopt;
			}

			T task = move(mQueue.front());
			mQueue.pop();

			mItsNotFull.notify_one();

			return task;
		}

		void mark_done()
		{
			{
				lock_guard<mutex> lock(mMutex);
				done = true;
			}

			mItsNotEmpty.notify_all();
			mItsNotFull.notify_all();
		}
};

void producer(SimpleBoundedQueue<int>& queue, int producer_id, int num_tasks)
{
	for (int i = 0; i < num_tasks; i++)
	{
		int task = producer_id * 10 + i;

		if (!queue.push(task))
		{
			cout << "Producer " << producer_id << ": Done is called\n";
			return;
		}

		cout << "Producer produced task " << task << "\n";
	}
}

void consumer(SimpleBoundedQueue<int>& queue, int consumer_id)
{
	while(true)
	{
		optional<int> task = queue.pop();

		if (!task.has_value())
		{
			cout << "Consumer " << consumer_id << " is stopping as, no task retrived\n";
			break;
		}

		cout << "Consumer retrived task " << *task << "\n";
	}
}

int usage()
{
	cout << "Invalid arguments\n";
	cout << "call ./simple-bounded-queue <number-of-producers> <number-of-consumers> <number-of-task-each-producer-produces> <queue-size>\n";
	return -1;
}

int main (int argc, char* argv[])
{
	if (5 != argc)
	{
		return usage();
	}

	int num_producers = 0;
	int num_consumers = 0;
	int num_task_by_each_producer = 0;
	int queue_size = 0;

	vector<thread> producers;
	vector<thread> consumers;

	try
	{
		num_producers = stoi(argv[1]);
		num_consumers = stoi(argv[2]);
		num_task_by_each_producer = stoi(argv[3]);
		queue_size = stoi(argv[4]);
	}
	catch (...)
	{
		return usage();
	}

	SimpleBoundedQueue<int> queue(queue_size);

	for (int i = 0; i < num_producers; i++)
	{
		producers.emplace_back(thread(producer, ref(queue),i, num_task_by_each_producer));
	}

	for (int i = 0; i < num_consumers; i++)
	{
		consumers.emplace_back(thread(consumer, ref(queue), i));
	}

	for (auto & producer_thread: producers)
	{
		producer_thread.join();
	}

	queue.mark_done();

	for (auto & consumer_thread: consumers)
	{
		consumer_thread.join();
	}

	return 0;
}


