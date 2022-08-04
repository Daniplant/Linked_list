#pragma once
#include <string>
template<class T>
struct dataStruct
{
	T* value = nullptr;
	dataStruct* next = nullptr;
};


template<class T>
class arrayList 
{
private:
	dataStruct<T>* head;
	dataStruct<T>* tail;
	unsigned int size;
	// Implementa una tail

public:

	arrayList() {
		this->head = nullptr;
		this->tail = nullptr;
		this->size = 0;
	}

	unsigned int getSize() {
		return this->size;
	}

	void add(T* value) {
		dataStruct<T>** tmp = &head;

		if (*tmp == nullptr)
		{
			*tmp = new dataStruct<T>;
			(*tmp)->value = value;
			this->tail = *tmp;
		}
		else
		{
			this->tail->next = new dataStruct<T>;
			this->tail->next->value = value;
			this->tail = this->tail->next;
		}
		size++;

		//while (*tmp != nullptr)
		//{
		//	tmp = &(*tmp)->next;
		//}
		//(*tmp) = new dataStruct<T>;
		//(*tmp)->value = object;
		//this->size++;

	}

	void modify(unsigned int pos, T value) {
		int i = 0;
		dataStruct<T>* tmp = head;
		if (this->size != pos)
		{
			while (tmp)
			{
				if (i == pos) {
					tmp->value = value;
				}
				else
				{
					tmp = tmp->next;
				}
			}
		}
		else
		{
			this->tail->value = value;
		}
	}

	bool remove(unsigned int pos) {
		int i = 0;
		bool hasBeenDeleted = false;
		dataStruct<T>** list = &head;
		while (*list)
		{
			dataStruct<T>* ptrToDelete = *list;

			if (i == pos) {
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
		int i = 0;
		dataStruct<T>* tmp = head;
		if (this->size != pos)
		{
			while (tmp)
			{
				if (i == pos) {
					return tmp->value;
				}
				else
				{
					tmp = tmp->next;
				}
				i++;
			}
		}
		else
		{
			return this->tail->value;
		}

		return nullptr;
	}

	void printListAsBasicDataType() {
		dataStruct<T>* tmp = this->head;
		std::string output;

		while (tmp)
		{
			output.append(std::to_string(*tmp->value) + '\n');
			tmp = tmp->next;
		}
		std::cout << output << std::endl;
	}

	void printList(std::string (*getData)(T*)) {
		// read student.h 
		std::string output;
		dataStruct<T>* tmp = this->head;
		while (tmp)
		{
			output.append(getData(tmp->value) + '\n');
			tmp = tmp->next;
		}
		std::cout << output << std::endl;
	}
};

