#pragma once
#include <string>
#include <functional>
template<class T>
class arrayList
{
private:
	struct dataStruct
	{
		T value = value;
		dataStruct* next = nullptr;
	};
public:

	arrayList() {
		this->head = nullptr;
		this->size = 0;
	}

	arrayList(arrayList& other) {
		// Deep copy
		for (int i = 0; i < other.getSize(); i++)
		{
			this->add(*other.get(i));
		}
	}

	arrayList(arrayList&& other) noexcept{
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
	
		arrayList::dataStruct* oldHead = head;
		head = new arrayList::dataStruct;
		head->value = value;
		head->next = oldHead;
		
		this->size++;
	}

	void modify(unsigned int pos, T value) {
		int i = this->size - pos;
		arrayList::dataStruct* tmp = head;
		while (tmp)
		{
			if (i == 1) {
				tmp->value = value;
			}
			else
			{
				tmp = tmp->next;
			}
			i--;
		}
	}

	bool modifyWithRecursion(unsigned int pos, const T& value)
	{
		pos = this->getSize() - pos;
		return modifyRecursive_Aux(pos, value, head);
	}
private:
	bool modifyRecursive_Aux(unsigned int pos, const T& value, arrayList::dataStruct* currentNode) {
		if (currentNode == nullptr) return false;

		if (pos == 1)
		{
			currentNode->value = value;
			return true;
		}

		pos--;
		return modifyRecursive_Aux(pos, value, currentNode->next);
	}
public:
	bool remove(unsigned int pos) {
		int i = 0;
		bool hasBeenDeleted = false;
		arrayList::dataStruct** list = &head;
		while (*list)
		{
			if (i == pos) {
				arrayList::dataStruct* ptrToDelete = *list;
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
		// per trovare ciò che hai inserito in modo user-friendly.
		// Se so che la logica è "firts-in last-out" allora devo fare così
		// int i = 0  
		int i = this->size - pos;
		arrayList::dataStruct* tmp = head;
		
		while (tmp)
		{
			if (i ==  1) {
				return &tmp->value;
			}
			else
			{
				tmp = tmp->next;
			}
			i--;
		}
	

		return nullptr;
	}

	T* getRecursive(unsigned int pos, arrayList::dataStruct* start = nullptr) {
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
		arrayList::dataStruct* tmp = this->head;
		std::string output;

		while (tmp)
		{
			output.append(std::to_string(tmp->value) + '\n');
			tmp = tmp->next;
		}
		std::cout << output << std::endl;
	}

	void printList(std::string(*getData)(const T&)) {
		// read student.h 
		std::string output;
		arrayList::dataStruct* tmp = this->head;
		while (tmp)
		{
			output.append(getData(tmp->value) + '\n');
			tmp = tmp->next;
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
	void sort(int (*criteria)(const T&,const T&), bool ascension = false) {
		// n = size of the list
		int ascendValue = -1;
		if (ascension)
		{
			ascendValue = 1;
		}

		for (int i = 0; i < this->size; i++)
		{
			for (int j = 0; j < this->size - i - 1; j++) {

				T* selectNode = this->get(j);
				T* nextNode = this->get(j + 1);
				if (criteria(*selectNode, *nextNode) == ascendValue) {
				
					T tmpNode = *selectNode;
					*selectNode = *nextNode;
					*nextNode = tmpNode;
				}
			}
		}
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

		for (int i = 0; i < this->size; i++)
		{
			for (int j = 0; j < this->size - i - 1; j++) {
				if (lambdaCriteria(*this->get(j), *this->get(j + 1)) == ascendValue) {

					auto tmpValue = *this->get(j);
					this->modify(j, *this->get(j + 1));
					this->modify(j + 1, tmpValue);
				}
			}
		}
	}

	private:
		arrayList::dataStruct* head;
		unsigned int size;
};



