#pragma once


#pragma once
#include <string>
#include <functional>
#include <vector>
#include "dynamicArray.h"

template<class T>
class OptimazedArrayList
{
public:
	struct dataStruct
	{
		T value = T();
		dataStruct* next = nullptr;
	};
public:

	OptimazedArrayList() {
		this->head = nullptr;
		this->valueArray = nullptr;
		this->size = 0;
	}

	OptimazedArrayList(OptimazedArrayList& other) {
		// Deep copy
		for (unsigned int i = 0; i < other.getSize(); i++)
		{
			this->add(*other.get(i));
		}
	}

	OptimazedArrayList(OptimazedArrayList&& other) noexcept {
		// Move costructor
		this->head = other.head;
		this->size = other.size;
		other.head = nullptr;
		other.size = NULL;
	}


	unsigned int getSize() {
		return this->size;
	}

	void add(const T& value) {

		OptimazedArrayList::dataStruct* oldHead = head;
		head = new OptimazedArrayList::dataStruct();
		head->value = value;
		head->next = oldHead;
		this->auxilaryArray.add(&head->value);

		this->size++;
	}

	void add(T* value) {

		OptimazedArrayList::dataStruct* oldHead = head;
		head = new OptimazedArrayList::dataStruct();
		head->value = *value;
		head->next = oldHead;
		this->auxilaryArray.add(value);

		this->size++;
	}

	void modify(unsigned int pos, T value) {
		if (this->size > pos)
		{
			this->auxilaryArray.modify(pos, value);
		}
	}

public:
	bool remove(unsigned int pos) {
		int i = 0;
		bool hasBeenDeleted = false;
		OptimazedArrayList::dataStruct** list = &head;
		while (*list)
		{
			if (i == pos) {
				this->auxilaryArray.remove(pos);
				OptimazedArrayList::dataStruct* ptrToDelete = *list;
				*list = ptrToDelete->next;
				delete ptrToDelete;
				this->size--;
				return true;

			}
			else {
				list = &(*list)->next;
			}
			i++;
		}
		return false;
	}

	T* get(unsigned int pos) {
		return this->auxilaryArray.get(pos);
	}

	T* getRecursive(unsigned int pos, OptimazedArrayList::dataStruct* start = nullptr) {
		start = (start == nullptr) ? this->head : start;
		if (pos == 0)
		{
			return start->value;
		}
		else if (start->next != nullptr)
		{
			pos--;
			getRecursive(pos, start->next);
		}
		else
		{
			return nullptr;
		}
	}

	void printListAsBasicDataType() {
		this->auxilaryArray.printAsBasicDataType();
	}

	void printList(std::string(*getData)(const T&)) {
		// read student.h 
		std::string output;
		OptimazedArrayList::dataStruct* tmp = this->head;
		for (unsigned int i = 0; i < this->auxilaryArray.getSize(); i++)
		{
			output.append(getData(*this->auxilaryArray.get(i)) + '\n');
		}
		std::cout << output << std::endl;
	}

	// default sorting for function pointers
		// Il return type deve rappresentato in questo modo:
			/*
			*  come rappresentare i due elementi nella comparazione
			*  e come identificare chi è quello 'maggiore' oppure nessuno:
			*
			*		  -1		   0		  1
					-------		 ------		------
					sinistra	 uguali		destra

			*/
	void sort(int (*criteria)(const T&, const T&), bool ascension = false) {
		// n = size of the list

		// TODO : ottimizzare la complessita a O(nlog(n))
		int ascendValue = -1;
		if (ascension)
		{
			ascendValue = 1;
		}

		for (unsigned int i = 0; i < this->size; i++)
		{
			for (unsigned int j = 0; j < this->size - i - 1; j++) {

				T* selectNode = this->get(j);
				T* nextNode = this->get(j + 1);
				if (criteria(*selectNode, *nextNode) == ascendValue) {

					T tmpNode = *selectNode;
					*selectNode = *nextNode;
					*nextNode = tmpNode;
				}
			}
		}
		// n * n(n+n) = n^2 * 2 * n = 2* n^3
		// O(n*n(n*n))
		//		n * n (n^2)
		//		2 * n ^ 2
		//		2n^2
		// O(2n^2)
	}

	// sorting by using lambda functions
	void sort(std::function<int(const T&, const T&)> lambdaCriteria, bool ascension = false) {
		int ascendValue = -1;
		if (ascension)
		{
			ascendValue = 1;
		}

		for (unsigned int i = 0; i < this->size; i++)
		{
			for (unsigned int j = 0; j < this->size - i - 1; j++) {
				if (lambdaCriteria(*this->get(j), *this->get(j + 1)) == ascendValue) {

					auto tmpValue = *this->get(j);
					this->modify(j, *this->get(j + 1));
					this->modify(j + 1, tmpValue);
				}
			}
		}
	}

private:
	// TODO : crea un array per accedere ai dati molto più velocemente
	T** valueArray;
	OptimazedArrayList::dataStruct* head;
	DynamicArray<T> auxilaryArray;
	unsigned int size;
};



