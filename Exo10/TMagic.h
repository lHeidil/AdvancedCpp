#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <vector>
#include <stdexcept>
#include "TPerm.h"
#include "Mat2D.h"

template<TOrdre ORD>
class TMagic: public Mat2D<ORD,ORD,int> 
{
public:
	TMagic(const TIndex rowPerm = 0, const TIndex colPerm = 0) {
		//TPerm<ORD>::Idx2Tab(rowPerm,tab[0]);
		////for (size_t c=0; c<ORD; ++c) tab[0][c]=c+1; //initialize first row to use it later
		//for (size_t r=1; r<ORD; ++r){ 
		//	for (size_t c=1; c<ORD; ++c){
		//		tab[r][c]=tab[r-1][c-1]; //take values from previous row from c-1 to c "shift right" 
		//	}
		//	tab[r][0] = tab[r-1][ORD - 1]; //put the last element in previous row to the first colm
		//}	
		TIndex rTab[ORD],cTab[ORD];
		TPerm<ORD>::Idx2Tab(rowPerm,rTab);
		TPerm<ORD>::Idx2Tab(colPerm,cTab);
		for (size_t r=0; r<ORD; ++r){ 
			for (size_t c=0; c<ORD; ++c){
				tab[rTab[r]][cTab[c]]=((c-r+ORD)%ORD)+1;
			}
		}
	}

};