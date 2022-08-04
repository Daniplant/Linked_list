// Linked_list.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include <iostream>
#include "arrayList.h"
#include "student.h"
#include <chrono>

int main()
{

    arrayList<int> list;
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 100000; i++)
	{
		list.add(new int(i));
	}

	/*
		senza tail : 6 sec
		con tail   : < 0 sec
	*/

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds> (stop - start);
	//list.printListAsBasicDataType();
	std::cout << "size " << list.getSize() << std::endl;
	std::cout << "took : " << duration.count() << " ms" << " in seconds : " << duration.count() / 1000000 << std::endl;

	arrayList<student> listTest;
	listTest.add(new student("dani", "4C", 18));
	listTest.add(new student("test", "", 10));



	//listTest.printList(&getStudentToString);
}