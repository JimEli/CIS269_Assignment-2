/*************************************************************************
* Title: Templated Singly Linked List
* File: list.h
* Author: James Eli
* Date: 9/24/2018
*
* Minimal Singly Linked List Class. Far from complete.
*
* Singly linked list constructed of a private node structure. Each node
* contains two fields (data and next). The data element is templated to
* be of any type. The list maintinas a head and tail pointer. List member
* functions (only) include:
*   back()      // Returns element at tail of list.
*   empty()     // Returns true if list is empty.
*	push_back() // Adds new node to tail of list.
*	pop_front() // Removes front element from list.
*	clear()     // Clears list of all elements.
*   remove()    // Remove element from list.
*	operator<<  // Overloaded << operator prints list contents.
*   iterator incorporates only needed functionality for the demo.
*
* Notes:
*  (1) Compiled/tested with MS Visual Studio 2017 Community (v141), and
*      Windows SDK version 10.0.17134.0
*  (2) Compiled/tested with Eclipse Oxygen.3a Release (4.7.3a), using
*      CDT 9.4.3 and MinGw gcc-g++ (6.3.0-1).
*
* Submitted in partial fulfillment of the requirements of PCC CIS-269.
*************************************************************************
* Change Log:
*   09/24/2018: Initial release. JME
*   09/29/2018: Added remove function. JME
*   09/29/2018: Added very basic iterator support. JME
*************************************************************************/
#pragma once
#ifndef _LIST_H_
#define _LIST_H_

#include <iostream> // cout for print functionality.

namespace myList
{

	// Result (return) of remove function.
	constexpr auto DELETE_SUCCESS = 0;
	constexpr auto DELETE_FAIL = -1;

	// Individual list node.
	template <typename T>
	struct Node
	{
		Node() { next = nullptr; }
		~Node() { }

		T element;                  // Data.
		Node<T>* next;              // Link to next node.
	};

	template <typename T>
	class list
	{
	private:
		Node<T>* head;	            // list head node pointer.
		Node<T>* tail;	            // list tail node pointer.
		std::size_t count;          // Count of nodes in list.

	public:
		// Ctor.
		list() : head(nullptr), tail(nullptr), count(0) { }
		// Dtor.
		~list() { clear(); }

		// Returns true if list is empty.
		bool empty() const { return this->count == 0; }

		// Return tail element.
		T& back() const { return this->tail->element; }

		// Adds new node to tail of list.
		void push_back(const T& e)
		{
			// Delete(s) matching this new are in pop_front/remove.
			Node<T>* newNode = new Node<T>;

			newNode->element = e;
			newNode->next = nullptr;

			if (this->tail)
				this->tail->next = newNode;
			this->tail = newNode;

			if (this->head == nullptr)
				this->head = newNode;

			this->count++;
		}

		// Removes node from head of list.
		void pop_front()
		{
			if (empty())
				return;

			Node<T>* temp = head;
			head = head->next;

			if (tail == temp)
				tail = nullptr;

			delete temp;
			count--;
		}

		// Clears list of all elements.
		void clear()
		{
			while (!this->empty())
				pop_front();
			this->head = this->tail = nullptr;
			this->count = 0;
		}

		// Overloaded output operator to display list contents.
		friend std::ostream& operator<< (std::ostream& os, const list<T>& list)
		{
			for (const Node<T> *node = list.head; node; node = node->next)
				os << node->element;
			return os << std::endl;
		}

		// Find and return node.
		Node<T>* find(const T& e)
		{
			if (this->empty())         // Can't find in empty list.
				return nullptr;

			Node<T>* node = this->head;

			// Walk list looking for node match.
			do {
				if (node->element == e)
					return node;       // Found it!

				node = node->next;

			} while (node);

			return nullptr;            // Failed to find node.
		}

		// Remove first occurance of element from list.
		int remove(T e)
		{
			if (this->empty())
				return DELETE_FAIL;

			Node<T> *node = this->head, *prev = node;

			do {
				if (node->element == e)
				{
					// Decrement count, check if empty?
					if (!--count)
					{
						delete node;
						this->head = nullptr;
						this->tail = nullptr;
						return DELETE_SUCCESS;
					}
					// Removing head node?
					if (node == this->head)
					{
						this->head = node->next;
						delete node;
						return DELETE_SUCCESS;
					}
					// Removing tail node?
					else if (node == this->tail)
					{
						this->tail = prev;
						prev->next = nullptr;
						delete node;
						return DELETE_SUCCESS;
					}
					else
					{
						prev->next = node->next;
						delete node;
						return DELETE_SUCCESS;
					}
				}

				prev = node;
				node = node->next;

			} while (node);

			return DELETE_FAIL;
		}

		//
		// Inner iterator class. Member typedefs provided through inheritance from std::iterator.
		//class iterator : public std::iterator<std::forward_iterator_tag, T, ptrdiff_t, T*, T&>
		class iterator : public std::iterator<std::forward_iterator_tag, T>
		{
		private:
			Node<T> *pNode;

			// Ctor is private, so only friends can create instances.
			iterator(Node<T> *n) : pNode(n) { }
			iterator() : pNode(nullptr) { }

			friend class list;

		public:
			// Dtor.
			~iterator() { }

			// Overload comparison operators.
			bool operator== (const iterator& it) const { return pNode == it.pNode; }
			bool operator!= (const iterator& it) const { return pNode != it.pNode; }

			// Overload dereference and pointer operators.
			T& operator* () { return pNode->element; }
			T* operator-> () { return &pNode->element; }

			// Overload prefix increment operator.
			iterator& operator++ ()
			{
				pNode = pNode->next;
				return *this;
			}
		}; // End iterator inner class.

		// Begin and end iterators.
		iterator begin() const { return iterator(head); }
		//iterator end() const { return iterator(tail); }
		iterator end() const { return iterator(tail->next); }
	};
}
#endif
