// Linked_list.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include <iostream>
#include "student.h"
#include "linkedList.h"
#include <chrono>

int main()
{
	
	arrayList<int> list;
	auto start = std::chrono::high_resolution_clock::now();
	int sizeList = 100;

	printf("Velocita' di allocazione per %d elementi ", sizeList);
	std::cin.get();


	for (int i = 0; i < sizeList; i++)
	{
		// first in last out (like stack)
		list.add(i);
	}
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds> (stop - start);
	std::cout << "size " << list.getSize() << std::endl;
	std::cout << "took : " << duration.count() << " ms (microseconds)" << " in seconds : " << duration.count() / 1000000 << std::endl;

	printf("Cancellazione della meta' della lista");
	std::cin.get();

	for (int i = 0; i < sizeList / 2; i++)
	{
		list.remove(0);
	}
	list.printListAsBasicDataType();
	printf("size = %d\n ", list.getSize());

	printf("Modifica degl'elementi in modo standard");
	std::cin.get();
	
	// modalità standard
	for (int i = 0; i < list.getSize(); i++)
	{
		list.modify(i, i);
	}
	list.printListAsBasicDataType();

	//printf("Modifa degl'elementi in modo ricorsivo");
	//std::cin.get();
	//// modalità ricorsiva
	//for (int i = 0; i < list.getSize(); i++)
	//{
	//	list.modifyWithRecursion(i, 20);
	//}
	//list.printListAsBasicDataType();


	printf("Copia di una lista usando un copy-costructor");
	std::cin.get();

	arrayList<int> copiedList(list);
	copiedList.printListAsBasicDataType();

	printf("Spostamento di una lista usando un move-costructor");
	std::cin.get();
	arrayList<int> newList(std::move(list));

	newList.printListAsBasicDataType();



	printf("Bubble sort di una lista di interi usando una funzione lambda");
	std::cin.get();

	std::function<int(const int&, const int&)> intSort = [](const int &x,const int &y) {
		if (x < y)
		{
			return -1;
		}
		else if (x > y)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	};

	newList.sort(intSort);
	newList.printListAsBasicDataType();

	printf("Creazione di una lista di studenti");
	std::cin.get();

	arrayList<student> testStruct;
	testStruct.add(student("dani", "4C", 10));
	testStruct.add(student("notDani", "4C", 9));
	testStruct.add(student("Trussardi", "4C", 1));
	testStruct.add(student("Ronaldigno", "4C", 100));
	testStruct.add(student("Binjilin", "4C", 5));

	testStruct.printList(getStudentToString);

	printf("bubble sort di una lista di studenti, basandosi sulla loro eta'");
	std::cin.get();
	testStruct.sort(SortByAge);
	testStruct.printList(getStudentToString);
}