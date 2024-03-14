#include "TMagic.h"
#include "TSudoku.h"
using namespace std;
void testMagic()
{
  cout <<"-------------Test Magic-------------"<<endl;
  const TOrdre ORD1 = 5;
  const TOrdre ORD2 = 4;
  const TOrdre ORD3 = 3;
  TMagic<ORD1> M1;
  cout<<"p1: "<<M1;
  TMagic<ORD2> M2(0,5);
  cout<<"p2: "<<M2;
  TMagic<ORD3> M3(5,0);
  cout<<"p3: "<<M3;
  cout <<"-----------End Test Magic-----------\n"<<endl;
}
void testSudoku()
{
  cout <<"-------------Test Sudoku-------------"<<endl;
  const TOrdre ORD3 = 3;
  TSudoku<ORD3> M1;
  cout<<"p1: "<<M1;
 
  cout <<"-----------End Test Sudoku-----------\n"<<endl;
}
void main()
{
  //testMagic();
  testSudoku();
}