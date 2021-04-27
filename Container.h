#pragma once
#include <cassert>


template<typename T> class Container {
public:

	Container() {
		m_first = nullptr;
		m_last = nullptr;
		m_current = nullptr;
		m_size = 0;
	}

	~Container() {
		clear();
	}

	void addFirst(const T& data) {
		Node* node = new Node(data, m_first, nullptr);

		if (m_first != nullptr) {
			m_first->m_prev = node;
		}
		else {
			assert(m_last == nullptr);
			m_last = node;
		}

		m_first = node;
		m_size++;
	}

	void addLast(const T& data) {
		Node* node = new Node(data, nullptr, m_last);
		
		if (m_last != nullptr) {
			m_last->m_next = node;
		}
		else {
			assert(m_first == nullptr);
			m_first = node;
		}

		m_last = node;
		m_size++;
	}

	void removeFirst() {
		if (isEmpty()) {
			return;
		}

		Node* node = m_first;
		m_first = m_first->m_next;
		if (m_first == nullptr) {
			m_last = nullptr;
		}
		delete node;
		m_size--;
	}

	void removeLast() {
		if (isEmpty()) {
			return;
		}

		Node* node = m_last;
		m_last = m_last->m_prev;
		if (m_last == nullptr) {
			m_first = nullptr;
		}
		delete node;
		m_size--;
	}

	T& getFirst() const {
		if (isEmpty()) {
			throw std::runtime_error("Nothing to get");
		}

		return m_first->m_data;
	}

	T& getLast() const {
		if (isEmpty()) {
			throw std::runtime_error("Nothing to get");
		}

		return m_last->m_data;
	}

	int getSize() const {
		return m_size;
	}

	bool isEmpty() const {
		return getSize() == 0;
	}

	void exchange(Container<T>& other) {
		Node* first = m_first;
		Node* last = m_last;

		this.m_first = other.m_first;
		this.m_first = other.m_last;

		other.m_first = first;
		other.m_last = last;
	}

	void reverse() {
		Node* oldLast = m_last;
		Node* oldFirst = m_first;

		Node* node = m_first;
		while (node != nullptr) {
			Node* next = node->m_next;
			node->m_next = node->m_prev;
			node->m_prev = next;
			node = next;
		}

		m_first = oldLast;
		m_last = oldFirst;
	}

	void clear() {
		while (!isEmpty()) {
			removeLast();
		}
		assert(m_size == 0);
	}

	void resetIterator() {
		m_current = m_first;
	}

	bool hasNext() {
		return m_current != nullptr;
	}

	T& getNext() {
		if (m_current == nullptr) {
			throw std::runtime_error("Nothing to get");
		}

		T& data = m_current->m_data;
		m_current = m_current->m_next;
		return data;
	}

private:

	struct Node {
		Node(const T& data, Node* next, Node* prev) : m_data(data), m_next(next), m_prev(prev)  {}
		T m_data;
		Node* m_next;
		Node* m_prev;
	};

	Node* m_first;
	Node* m_last;
	Node* m_current;
	int m_size;
};