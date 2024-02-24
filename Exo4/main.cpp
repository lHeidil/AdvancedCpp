#include "CTriPascal.h"
void main(){

CTriPascal<unsigned long> t1(5);
CTriPascal<unsigned short> t2(5);
CTriPascal<unsigned __int64> t3(5);

t1.Affiche(std::cout);
t2.Affiche(std::cout);
t3.Affiche(std::cout);
}