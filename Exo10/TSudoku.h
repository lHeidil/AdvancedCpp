#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <vector>
#include <stdexcept>
#include "TPerm.h"
#include "Mat2D.h"

template<TOrdre ORD>
class TSudoku: public Mat2D<ORD*ORD,ORD*ORD,int> 
{
public:
	TSudoku(const TIndex perm = 0) {
		TIndex permTab[ORD];
		TPerm<ORD>::Idx2Tab(perm,permTab);
		for (size_t r=0; r<ORD*ORD; ++r){ 
			for (size_t c=0; c<ORD*ORD; ++c){
				tab[r][c]= ((c+r*ORD)%(ORD*ORD))+1; //not working well only good with first 3 rows
			}
		}
	}

};