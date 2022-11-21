#pragma once
#pragma once
#include <string>
#include <functional>
#include <vector>

template<class T>
/*
	Premessa: 
		Questa classe ottimizza certi passaggi e non sostituisce completamente
		la logica di una linked list

*/

class optimazedArrayList
{
public:
	struct dataStruct
	{
		T value = T();
		dataStruct* next = nullptr;
	};
public:

	optimazedArrayList() {
		this->head = nullptr;
		this->valueArray = nullptr;
		this->size = 0;
		this->auxilaryArray;
	}

	optimazedArrayList(optimazedArrayList& other) {
		// Deep copy
		for (unsigned int i = 0; i < other.getSize(); i++)
		{
			this->add(*other.get(i));
		}
	}

	optimazedArrayList(optimazedArrayList&& other) noexcept {
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

		optimazedArrayList::dataStruct* oldHead = head;
		head = new optimazedArrayList::dataStruct();
		head->value = value;
		head->next = oldHead;
		auxilaryArray.add(value);

		this->size++;
	}

	void modify(unsigned int pos, T value) {
		this->auxilaryArray.modify(pos, auxilaryArray.get(pos));
	}

public:
	bool remove(unsigned int pos) {
		int i = 0;
		bool hasBeenDeleted = false;
		optimazedArrayList::dataStruct** list = &head;
		while (*list)
		{
			if (i == pos) {
				optimazedArrayList::dataStruct* ptrToDelete = *list;
				*list = ptrToDelete->next;
				delete ptrToDelete;
				this->size--;
				this->auxilaryArray.remove(i);
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
		// per trovare ciò che hai inserito in modo user-friendly.
		// Se so che la logica è "firts-in last-out" allora devo fare così
		// int i = 0  
		if (this->auxilaryArray.getSize() > pos)
		{
			return this->auxilaryArray.get(pos);
		}

		return nullptr;
	}

	T* getRecursive(unsigned int pos, optimazedArrayList::dataStruct* start = nullptr) {
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
		optimazedArrayList::dataStruct* tmp = this->head;
		std::string output;

		this->auxilaryArray.printAsBasicDataType();
	}

	void printList(std::string(*getData)(const T&)) {
		// read student.h 
		this->auxilaryArray.printList(getData);
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
	optimazedArrayList::dataStruct* head;
	DynamicArray<T> auxilaryArray;
	unsigned int size;
};