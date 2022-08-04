#pragma once
#include <string>
#include <functional>
template<class T>
class arrayList
{
public:
	struct dataStruct
	{
		T* value = nullptr;
		dataStruct* next = nullptr;
	};

	arrayList() {
		this->head = nullptr;
		this->tail = nullptr;
		this->size = 0;
	}

	arrayList(arrayList& other) {
		// Deep copy
		for (int i = 0; i < other.getSize(); i++)
		{
			this->add(other.get(i));
		}
	}

	arrayList(arrayList&& other) {
		// Deep copy
		this = std::move(other);
	}

	unsigned int getSize() {
		return this->size;
	}

	void add(T* value) {
		arrayList::dataStruct** tmp = &head;

		if (*tmp == nullptr)
		{
			*tmp = new arrayList::dataStruct;
			(*tmp)->value = value;
			this->tail = *tmp;
		}
		else
		{
			this->tail->next = new arrayList::dataStruct;
			this->tail->next->value = value;
			this->tail = this->tail->next;
		}
		size++;

	}

	void modify(unsigned int pos, T value) {
		int i = 0;
		arrayList::dataStruct* tmp = head;
		if (this->size != pos)
		{
			while (tmp)
			{
				if (i == pos) {
					*tmp->value = value;
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
			*this->tail->value = value;
		}
	}

  	bool modifyRecursive(unsigned int pos, T value, arrayList::dataStruct* start = nullptr) {
		start = (start == nullptr) ? this->head : start;

		if (pos == 0)
		{
			*start->value = value;
			return true;
		}
		else if (start->next!= nullptr)
		{
			pos--;
			this->modifyRecursive(pos, value, start->next);
		}
		else
		{
			return false;
		}
	}

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
		int i = 0;
		arrayList::dataStruct* tmp = head;
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
			output.append(std::to_string(*tmp->value) + '\n');
			tmp = tmp->next;
		}
		std::cout << output << std::endl;
	}

	void printList(std::string(*getData)(T*)) {
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

	private:
		arrayList::dataStruct* head;
		arrayList::dataStruct* tail;
		unsigned int size;
};



