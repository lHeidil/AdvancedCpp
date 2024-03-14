#ifndef _TEMPLATES_H_
#define _TEMPLATES_H_

#include <iostream>
#include <iomanip>
#include <typeinfo.h>

//Exo1 A
//version 1
//it may have issues when dealing with floating-point types due to potential precision errors when subtracting
//il a besoin de operator -(TObj, TObj) , bool operator >(TObj, TObj) et TObj(TObj&) ctor copie
//template <typename TObj> 
//TObj MaxVal(TObj o1, TObj o2){
//	if ((o1-o2)>0) return o1;
//	else return o2;
//}
//version 2
//besoin de bool operator >(TObj, TObj) et TObj(TObj&) ctor copie
//template <typename TObj> 
//TObj MaxVal(TObj o1, TObj o2){
//	return o1>o2 ? o1:o2;
//}
//version 3
template <typename TObj> inline 
TObj& MaxVal(TObj& o1, TObj& o2){
	cout<<"MaxVal Non Const\n";
	return o1>o2 ? o1:o2;
}
//version 4
template <typename TObj> inline 
const TObj& MaxVal(const TObj& o1, const TObj& o2){
	cout<<"MaxVal Const\n";
	return o1>o2 ? o1:o2;
}

//Exo2 A
//besoin de operator<<(ostream,TObj) pour chaque type TObj
//passage par pointeur
//Suitable for dynamically allocated arrays where the size is determined at runtime.
template <typename TObj> inline 
void ShowVect(std::ostream& os, const TObj* tab, size_t sz, const char * name=" "){
	os<<"Tableau "<<name<<" de "<<sz<<" elements de type "<<typeid(TObj).name()<<"\n ";
	for (size_t i=0; i<sz; ++i){
		os<<tab[i]<<((i == sz-1)? "\n":", ");
	}
}
//passage par référence
//Suitable for arrays of fixed size known at compile time.
template <typename TObj, const size_t SZ> inline 
void ShowVect(std::ostream& os, const TObj (&tab)[SZ], const char * name=" "){
	os<<"Tableau "<<name<<" de "<<SZ<<" elements de type "<<typeid(TObj).name()<<"\n ";
	for (size_t i=0; i<SZ; ++i){
		os<<tab[i]<<((i == SZ-1)? "\n":", ");
	}
}

//Exo2 B,D,E
//operator += (TObj, TObj)
//TObj(TObj&) ctor copie
//(TObj) ctor à 1 param 
template <typename TObj, const size_t SZ> inline //pas pour les tableau dynamique
TObj VectSomme(const TObj (&tab)[SZ]){
	//TObj S = 0 ;
	TObj S(tab[0]);
	for (size_t i=1; i<SZ; ++i){
		S += tab[i];
	}
	return S;
}
//Exo2 C
template <typename TObj, const size_t SZ> inline
void TestVectSomme(std::ostream& os, const TObj (&tab)[SZ]){
	os<<"Somme du tableau "<<VectSomme(tab)<<"\n ";
}
//Exo2 F
template <typename TObj,size_t SZ> inline
size_t GetSize(const TObj(& o1)[SZ]){ // () o1 pour etre fort que SZ
	return sizeof(o1)/sizeof(o1[0]);
}
//Exo3 A
template <typename TObj> inline
void TriMontant(std::ostream& os, TObj* tab, size_t sz)
{	//bubble sort
    for (size_t i = 0; i < sz - 1; ++i) {
        for (size_t j = 0; j < sz - i - 1; ++j) {
            if (tab[j] > tab[j + 1]) {
				TObj temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;
            }
        }
    }

    for (size_t i = 0; i < sz; ++i) {
        os << tab[i] << ((i == sz - 1) ? "\n" : ", ");
    }
}
//Exo3 B
//bool operator >(TObj, TObj) et TObj(TObj&) ctor copie
#endif