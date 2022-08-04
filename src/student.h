#pragma once
#include <iostream>
#include <string>
struct student
{
	std::string name;
	std::string section;
	int age;

	student(std::string name, std::string section, int age) {
		this->name = name;
		this->section = section;
		this->age = age;
	}
};

/*
	Motivazione di questa strategia:
		Quando stavo calcolando quanto tempo aveva bisogno la lista per contenere una grande quantità di numeri,
		ho notato che quando chiamavo costantemente il print, il terminale spendeva troppo tempo per stampare dei valori
		quindi ho cercato di creare un print (in arrayList) dove esiste un contenitore che tiene tutti i dati in una stringa
		e dopo aver preso il tutto, li stampasse sul terminale.

		Dato che stampare non necissita di un tipo di dato specifico, usufruisco della libreria string per immagazzinare
		il tutto in una grande stringa usando .append.

		Perciò ho voluto che dato un determinato pointer di una struttura dati complessa,
		ti restituisca il valore in stringa, utilizzandolo come function
		pointer in print per stampare il tutto, invece che passare un function pointer che chiami il print
		ogni volta per ogni elemento nella lista.

		Dato che la linked list è un 'vettore dinamico' io non posso conoscere quanto grande sarà perciò
		per evitare che chiamo costantemente il print per n volte, ho cercato di ottimizzarlo.

		Se vedi che sto scrivendo in modo logorroico è perché sono le 03:12 nel mentre che ti sto scrivendo. 
		passo la notte cosi ^^

*/

std::string getStudentToString(student* student) {
	return student->name + " " + std::to_string(student->age) + " " + student->section;
}