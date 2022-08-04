// Linked_list.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include <iostream>
#include "student.h"
#include "linkedList.h"
#include <chrono>


int main()
{
	printf("velocita' di allocazione");
	std::cin.get();
// Velocità di allocazione
	arrayList<int> list;
	auto start = std::chrono::high_resolution_clock::now();
	int sizeList = 1000;
	for (int i = 0; i < sizeList; i++)
	{
		list.add(new int(i));
	}
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds> (stop - start);
	std::cout << "size " << list.getSize() << std::endl;
	std::cout << "took : " << duration.count() << " ms" << " in seconds : " << duration.count() / 1000000 << std::endl;

	printf("cancellazione delle meta' della lista");
	std::cin.get();
	// Test delle funzionalita

	// cancellazione dell'intera lista
	for (int i = 0; i < sizeList / 2; i++)
	{
		list.remove(0);
	}
	list.printListAsBasicDataType();
	printf("size = %d ", list.getSize());

	printf("modifica degl'elementi in modo standard");
	std::cin.get();
	
// modifica di tutti gli elementu
	// modalità standard
	for (int i = 0; i < list.getSize(); i++)
	{
		list.modify(i, 69);
	}
	list.printListAsBasicDataType();

	printf("modifa degl'elementi in modo ricorsivo");
	std::cin.get();
	// modalità ricorsiva
	for (int i = 0; i < list.getSize(); i++)
	{
		list.modifyRecursive(i, 6969);
	}
	list.printListAsBasicDataType();


	printf("Copia di una lista usando un copy costructor");
	std::cin.get();
// copia di una lista utilizzando ciò che ho capito dei copy costructors


	arrayList<int> newList(list);
	newList.printListAsBasicDataType();

}