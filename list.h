/*************************************************************************
* Title: Templated Singly Linked List
* File: list.h
* Author: James Eli
* Date: 9/24/2018
*
* Minimal Singly Linked List Class.
*
* Singly linked list constructed of a private node structure. Each node
* contains two fields (data and next). The data element is templated to
* be of any type. The list maintinas a head and tail pointer.
*
* List member functions (only) include:
*   back()      // Returns element at tail of list.
*   empty()     // Returns true if list is empty.
*   push_back() // Adds new node to tail of list.
*   pop_front() // Removes front element from list.
*   clear()     // Clears list of all elements.
*   operator<<  // Overloaded << operator prints list contents.
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
*************************************************************************/
#pragma once
#ifndef _LIST_H_
#define _LIST_H_

#include <iostream>  // Output stream.

namespace myList
{
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

	};
}
#endif
