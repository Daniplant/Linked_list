#pragma once
#include <string>

template<class T>
class DynamicArray
{
public:
	DynamicArray() {
		this->size = 0;
		this->capacity = 1;
		this->ptrToValue = new T*;
		*this->ptrToValue = new T;
		this->growthRate = 2;
	}

	void add(T* value) {
		if (this->capacity == this->size)
		{
			// It growths exponensialy
			changeSize(size * growthRate);
			//for (unsigned int i = 0; i < capacity; i++)
			//{
			//	std::cout << this->ptrToValue[i] << std::endl;
			//}
		}

		this->ptrToValue[size] = value;
		this->size += 1;
	}



	unsigned int getSize() {
		return this->size;
	}

	T* get(unsigned int index) {
		if (index < this->size) {
			return this->ptrToValue[index];
		}
		return nullptr;
	}

	T getValue(unsigned int index) {
		if (index < this->size) {
			return *this->ptrToValue[index];
		}
		return NULL;
	}

	bool remove(unsigned int index) {
		bool isCancelConfirmed = (this->size > index) ? true : false;
		
		for (unsigned int i = index; i < this->size - 1; i++)
		{	
			*this->ptrToValue[i] = *this->ptrToValue[i + 1];
		}

		if (isCancelConfirmed) {
			this->size--;
			if (this->capacity / growthRate > this->size) {
				changeSize(int(this->capacity / 2));
			}
		}

		return isCancelConfirmed;

	}

	bool pop() {
		bool isCancelConfirmed = (this->size > 0) ? true : false;

		if (isCancelConfirmed) {
			this->ptrToValue[size] = nullptr;
			this->size--;
			if (this->capacity / growthRate > this->size) {
				changeSize(int(this->capacity / 2));
			}
		}

		return isCancelConfirmed;

	}

	bool modify(unsigned int index, T value) {
		if (index < this->size) {
			*this->ptrToValue[index] = value;
			return true;
		}
		return false;
	}

	void printAsBasicDataType() {
		std::string output;

		for (unsigned int i = 0; i < this->size; i++)
		{
			output.append(std::to_string(*ptrToValue[i]) + '\n');
		}

		std::cout << output << std::endl;
	}


	void printList(std::string(*getData)(const T&)) {
		std::string output;
		int i = 0;
		for (unsigned int i = 0; i < size; i++)
		{
			output.append(getData(*ptrToValue[i]) + '\n');
		}
		std::cout << output << std::endl;
	}


private:
 	void changeSize(unsigned int fixedSize) {

		// Regola : per ogni new corrisponde ad una delete
		// new[] = delete []
		if (size < 1)
		{
			return;
		}
		// populating the swap space
		T** buffer = new T* [size];
		//*buffer = new T[size];
		for (unsigned int i = 0; i < size; i++)
		{
			buffer[i] = new T;
		}

		// Assign the value to the swapSpace
		for (unsigned int i = 0; i < size; i++)
		{
			buffer[i] = this->ptrToValue[i];
		}

	
		/*
			TODO aiuto : sembra che io non possa liberare
			l'array di puntatori che punta ad altri puntatori perché
			se io rendo tutto nullptr io sto cercando di cancellare qualcosa che è nullo
			quindi da un errore duh.
			Perciò ho 2 soluzioni.
			1 DEVO trovare un modo per fare una delete senza che cancelli la reference della variabile puntata
			2 ...non cancellare ma bensi fare nullptr? sembra che possa leakkare della memoria ma non so cosa fare

		*/ 
		
		for (unsigned int i = 0; i < size; i++)
		{
			ptrToValue[i] = nullptr;
			//delete ptrToValue[i];
		}
		// TODO : c'è qualcosa di storto qui dentro: trova un modo per fixarlo
		//delete[] ptrToValue;

		ptrToValue = new T* [fixedSize];
		// *ptrToValue = new T[fixedSize];
		//for (unsigned int i = 0; i < fixedSize; i++)
		//{
		//	ptrToValue[i] = new T;
		//}

		for (unsigned int i = 0; i < size; i++)
		{
			this->ptrToValue[i] = buffer[i];
		}

		for (unsigned int i = 0; i < size; i++)
		{
			buffer[i] = nullptr;
		}
		delete[] buffer;
		

		this->capacity = fixedSize;
	}

	unsigned int size;
	int capacity;
	T** ptrToValue;
	unsigned int growthRate;
};
