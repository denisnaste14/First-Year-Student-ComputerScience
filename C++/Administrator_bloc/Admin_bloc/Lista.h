#pragma once
#include <cassert>
#include "Locatar.h"

template <typename T>
class vector_dinamic;
//
template <typename T>
class IteratorVD {
private:
	const vector_dinamic<T>& vd;
	int index_curent;
public:
	//constructori
	IteratorVD(const vector_dinamic<T>& vd) noexcept;
	IteratorVD(const vector_dinamic<T>& vd, int index_curent) noexcept;
	//va returna elementul curent
	auto& operator*() const;

	//va trece la urmatorul element
	auto& operator++();

	//verifica daca indexii celor 2 vectori sunt diferiti
	bool operator!=(const IteratorVD& other) noexcept;
};

template <typename T>
class vector_dinamic {
private:
	int cs;		//capacitate de stocare
	int curent;
	T* elems;
public:
	//constructor
	//rule of 3 
	vector_dinamic();
	auto& operator=(const vector_dinamic& other);
	~vector_dinamic();
	//add ca in vector
	void push_back(const T& loc);
	void pop_back();


	friend class IteratorVD<T>;
	//inceput de vector prin iterator
	IteratorVD<T> begin();
	//sfarsit de vector dat prin iterator
	IteratorVD<T> end();
	//nr de elemente din vector
	int size() const;
	//elementul de la pozitia data 
	auto& at(int i) const;
	//elementul de pe utlima pozitie
	auto& back() const;
};

template <typename T>
vector_dinamic<T>::vector_dinamic():cs{ 10 }, curent{ 0 }, elems{ new T[cs] }{
}

template <typename T>
auto& vector_dinamic<T>::operator=(const vector_dinamic& other) {
	cs = other.cs;
	curent = 0;
	T* new_space;
	new_space = new T[other.cs];
	for (int i = 0; i < other.curent; i++)
		new_space[i] = other.elems[i];
	delete[] elems;
	elems = new_space;
	return *this;
}

template <typename T>
void vector_dinamic<T>::push_back(const T& loc) {
	if (cs == curent) {
		//extindere vector dinamic
		cs = cs * 2;
		T* new_elems = new T[cs];
		for (int i = 0; i < curent; i++)
			new_elems[i] = elems[i];
		//sterg ce era inainte in elems
		delete[] elems;
		elems = new_elems;
	}
	elems[curent] = loc;
	curent++;
}

template <typename T>
vector_dinamic<T>::~vector_dinamic() {
	delete[] elems;
}

template <typename T>
auto& vector_dinamic<T>::at(int i) const {
	return elems[i];
}

template <typename T>
auto& vector_dinamic<T>::back() const{
	return elems[curent-1];
}

template <typename T>
int vector_dinamic<T>::size() const{
	return curent;
}

template <typename T>
IteratorVD<T> vector_dinamic<T>::begin() {
	//se va returna u obiect de tip iterator care refera primul element din vectorul dinamic 
	return IteratorVD<T>(*this);
}

template <typename T>
IteratorVD<T> vector_dinamic<T>::end() {
	//se va returna u obiect de tip iterator care refera ultimul element din vectorul dinamic folosind constructorul cu 2 parametrii din clasa iteratorVD
	return IteratorVD<T>(*this, curent);
}

template <typename T>
void vector_dinamic<T>::pop_back() {
	curent--;
}

//
//
//FUNCTII ITERATORVD
//
//
template <typename T>
IteratorVD<T>::IteratorVD(const vector_dinamic<T>& vd, int index_curent) noexcept : index_curent{ index_curent }, vd{ vd }{
}

template <typename T>
IteratorVD<T>::IteratorVD(const vector_dinamic<T>& vd)noexcept : index_curent{ 0 }, vd{ vd }{
}

template <typename T>
auto& IteratorVD<T>::operator*() const {
	return this->vd.elems[index_curent];
}

template <typename T>
bool IteratorVD<T>::operator!=(const IteratorVD& other) noexcept {
	return index_curent != other.index_curent;
}

template <typename T>
auto& IteratorVD<T>::operator++() {
	index_curent++;
	//returnez iteratorul cu indexul modificat
	return *this;
}

//
//
//Teste
//
//
void test_vector_dinamic_iterator();
void range_for_test();