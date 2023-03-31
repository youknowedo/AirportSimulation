#pragma once

template <class T>
class Queue;

template <class T>
class QItem
{
public:
	QItem(T data, Queue<T> *queue, QItem<T> *next = nullptr, QItem<T> *prev = nullptr) : _data(data), _next(next), _previous(prev), _queue(queue) {}

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
	Queue() : _front(nullptr), _back(nullptr), _size(0){};

	QItem<T> *begin() { return _front; }
	QItem<T> *end() { return _back; }

	bool empty() { return (_front == nullptr); }
	int size() const { return _size; }

	void popFront()
	{
		auto newFront = _front->next();

		if (newFront != nullptr)
			newFront->_previous = nullptr;

		delete _front;
		_front = &(*newFront);
		--_size;
	}
	void popBack()
	{
		auto newBack = _back->prev();

		if (newBack != nullptr)
			newBack->_next = nullptr;

		delete _back;
		_back = &(*newBack);
		--_size;
	}
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
