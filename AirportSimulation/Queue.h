/**
 * Did inline definitions for all of the class-functions since having them outside would
 * give an error (LINK2019). It is likely it has something to do with the fact that the
 * classes are using templates.
 * Also had both classes in one file for ease of use when I want to use these classes in
 * the future.
 */
#pragma once

/**
 * Forward-declaring the Queue class because both Queue and QItem depend on each other.
 * Prevents circular class dependency
 */
template <class T>
class Queue;

/// @brief The items in a Queue. Holds the data, and pointers to the next and previous items
/// @tparam T The class of the data that the item holds
template <class T>
class QItem
{
public:
	/// @brief Creates a new instance of the QItem class
	/// @param data The data that the item should hold
	/// @param queue The queue that this item belongs to
	/// @param next A pointer to the next item in the queue
	/// @param prev A pointer to the previous item in the queue
	QItem(T data,
		  Queue<T> *queue,
		  QItem<T> *next = nullptr,
		  QItem<T> *prev = nullptr) : _data(data),
									  _next(next),
									  _previous(prev),
									  _queue(queue) {}

	T data() const { return _data; }
	QItem<T> *next() const { return _next; }
	QItem<T> *prev() const { return _previous; }
	Queue<T> *queue() const { return _queue; }

	T operator*() const { return data(); }
	QItem<T> *operator++() const
	{
		auto newItem = next();
		if (newItem == nullptr)
			return this = nullptr;
		else
			return newItem;
	}
	QItem<T> *operator--() const
	{
		auto newItem = prev();
		if (newItem == nullptr)
			return this = nullptr;
		else
			return newItem;
	}

	friend class Queue<T>;

private:
	T _data;

	QItem<T> *_next;
	QItem<T> *_previous;

	Queue<T> *_queue;
};

template <class T>
class Queue
{
public:
	/// @brief Creates a new instance of the Queue class
	Queue() : _front(nullptr), _back(nullptr), _size(0){};

	QItem<T> *front() { return _front; }
	QItem<T> *back() { return _back; }

	bool empty() { return (_front == nullptr); }
	int size() const { return _size; }

	/// @brief Removes the first item in the queue
	void popFront()
	{
		auto newFront = _front->next();

		if (newFront != nullptr)
			newFront->_previous = nullptr;

		delete _front;
		_front = &(*newFront);
		--_size;
	}
	/// @brief Removes the last item in the queue
	void popBack()
	{
		auto newBack = _back->prev();

		if (newBack != nullptr)
			newBack->_next = nullptr;

		delete _back;
		_back = &(*newBack);
		--_size;
	}
	/// @brief Removes the i:th item in the queue
	/// @param i The index of the item to be removed
	void pop(int i)
	{
		QItem<T> *toDelete = this->operator[](i);
		QItem<T> *next = toDelete->next();
		QItem<T> *prev = toDelete->prev();

		delete toDelete;

		if (next != nullptr)
			next->_previous = prev;
		else
			_back = prev;

		if (prev != nullptr)
			prev->_next = next;
		else
			_front = next;

		--_size;
	}

	/// @brief Adds an item to the front of the queue
	/// @param newData The data of the new item
	void pushFront(T newData)
	{
		if (this->empty())
		{
			auto newFront = new QItem<T>(newData, this, nullptr, nullptr);
			_front = newFront;
			_back = newFront;
		}
		else
		{
			auto oldFront = _front->next();
			auto newFront = new QItem<T>(newData, this, oldFront, nullptr);

			if (oldFront != nullptr)
				oldFront->_previous = newFront;

			_front = newFront;
		}
		++_size;
	}
	/// @brief Adds an item to the last of the queue
	/// @param newData The data of the new item
	void pushBack(T newData)
	{
		if (this->empty())
		{
			auto newFront = new QItem<T>(newData, this, nullptr, nullptr);
			_front = newFront;
			_back = newFront;
		}
		else
		{
			auto oldBack = _back->prev();
			auto newBack = new QItem<T>(newData, this, nullptr, oldBack);

			if (oldBack != nullptr)
				oldBack->_next = newBack;

			_back = newBack;
		}
		++_size;
	}
	/// @brief Adds an item to the last of the queue
	/// @param newData The data of the new item
	/// @param i The index that the new item should have
	void push(T newData, int i)
	{
		if (i == 0)
		{
			pushFront(newData);
			return;
		}

		QItem<T> *next = (*this)[i];

		if (next == nullptr)
		{
			pushBack(newData);
			return;
		}

		QItem<T> *prev = next->_previous;

		QItem<T> *newItem = new QItem<T>(newData, this, next, prev);

		if (next != nullptr)
			next->_previous = newItem;

		if (prev != nullptr)
			prev->_next = newItem;

		++_size;
	}

	/// @brief Indexes the queue by index
	/// @param i The index of the item
	/// @return The i:th item in the queue
	QItem<T> *operator[](int i)
	{
		QItem<T> *returnItem = _front;

		for (int j = 0; j < i; j++)
		{
			++returnItem;
		}

		return returnItem;
	}

	friend class QItem<T>;

private:
	QItem<T> *_front;
	QItem<T> *_back;
	int _size;
};
