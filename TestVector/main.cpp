//vector utility string stack sstring ostream nez limit istream algorithm
#include <iostream>
#include <iomanip>
#include <vector>
#include <typeinfo.h> 
#include "Fract.h"

using namespace std;

template<typename T> void ShowVect(ostream& os, const vector<T>& v, size_t idx_max=0, size_t idx_min=0)
{
  os<<"Vecteur de type "<<typeid(T).name()<< ", taille "<<v.size()<<", capacite "<<
    v.capacity()<<", max_size "<<v.max_size()<<endl;
  if(v.empty()) return;
  if(idx_max==0 || idx_max>v.size()) idx_max=v.size();
  if(idx_min>idx_max) idx_min=idx_max;
  // tester et comprenez chaque version !!!
#if 1
  // version 1
  for(size_t i=idx_min; i<idx_max; i++) os<<"  ["<<i<<"] "<<v[i]<<endl;
#endif
#if 0
  // version 2
  const T* p = &v[idx_min];
  for(size_t i=idx_min; i<idx_max; i++) cout<<"  ["<<i<<"] "<< *(p++) <<endl;
#endif
#if 0
  // version 3: elle affiche tout le vecteur
  for(vector<T>::const_iterator i=v.begin(); i!=v.end(); i++) cout<<"  ["<<i-v.begin()<<"] "<< *i <<endl;
#endif
#if 0
  // version 4: elle affiche tout le vecteur en l'ordre inverse
  for(vector<T>::const_reverse_iterator i=v.rbegin(); i!=v.rend(); i++) cout<<"  ["<<v.rend()-i-1<<"] "<< *i <<endl;
#endif
}

template<typename T> inline ostream& operator<<(ostream& os, const vector<T>& v) { ShowVect<T>(os,v); return os; }

template <typename T> T SumVect(const vector<T>& v)
{
  vector<T>::const_iterator p=v.begin();
  T sum=*p;
  while((++p)!=v.end()) sum+= *p;
  return sum;
}

void test1()
{
  cout<<"*********** Test 1 **************\n";
  vector<double> v1; //var dynamique
  ShowVect(cout,v1);
  v1.resize(10,5.7);
  ShowVect(cout,v1,10);
  v1.clear();
  ShowVect(cout,v1);
  v1.reserve(100);
  ShowVect(cout,v1);
  for(int i=0; i<20; i++) v1.push_back(i*i);
  ShowVect(cout,v1,20);
  cout<<"Somme = "<<SumVect(v1)<<endl;
  vector<double> v2;
  cout<<v2;
  // homework: comment transférer efficacement les éléments de v1 vers v2 (qui est vide actuellement) ?
}

void test2()
{
  cout<<"*********** Test 2 **************\n";
  vector<char> v1(5,'*'); ShowVect(cout, v1);
  vector<int> v2; ShowVect(cout, v2);
  vector<double> v3(3,3.3); ShowVect(cout, v3);
  cout<<v1<<v2<<v3;
}

using namespace Fract;
void test3()
{
  cout<<"*********** Test 3 **************\n";
  vector<CFract> vf;
  for(int i=0; i<10; i++) vf.push_back(CFract(1,i+1));
  cout<<vf;
  cout<<"Somme = "<<SumVect(vf)<<endl;
}
void test4()
{
  cout<<"*********** Test 4 **************\n"; //vectors are in the heap because it's dynamique ans strings too
  
  size_t Nr=2+(rand()%5),Nc=6+(rand()%5);
  vector<vector<float>> matf(Nr,vector<float>(Nc,4.4f));
  cout<<matf;
}

#include <algorithm>
#include <math.h> //math
template<typename Type> class MultDivValue // fonctoeur a la place des fonction car on a besoin du memoire dans nos fonction comme mult et div
{
private:
  Type Mult,Div;
public:
  MultDivValue(const Type& _Mult, const Type& _Div=1):Mult(_Mult),Div(_Div){}
  void operator ( ) ( Type& v ) const //car les mult et div ne change pas sauf au debut
   {
     v= (v*Mult/Div);
   }
};
template<typename Type> class SquareRoot 
{
public:
  void operator ( ) ( Type& v ) const { v= (Type)sqrt((double)v); }
};
template<typename Type> struct SquareRoot2 //struct par default public donc on ecrit moins la meme chose
{
  void operator ( ) ( Type& v ) const { v= (Type)sqrt((double)v); }
};
template<typename Type> //fonction generique
  void carre(Type& v) 
  {
   v*=v;
  }
template<typename Type> //fonction generique
  bool LastDigitRise(const Type& v1,const Type& v2)
  {
    return ((v1%10)<(v2%10))? 1:0;
  }
 template<typename Type> //fonction generique
  bool LastDigitFall(const Type& v1,const Type& v2)
  {
    return ((v1%10)>(v2%10))? 1:0;
  }
template<typename Type> //fonction generique
  bool SupIsFirst(const Type& v1,const Type& v2)
  {
    return (v1>v2);
  }

void test5(){
cout << "test 5";
vector<int> vi (20,0);
cout<<vi;
for(vector <int>::iterator p=vi.begin(); p<vi.end();++p) //++P tjr 3shan mtb2ash faute d'optimisation 3shan ymshi m3 el  cfract brdo
{ *p= p-vi.begin(); } //difference entre 2 iterateur just like diff entre 2 pointers and it gives me un int that represents the distance between both of them, and no poiinter + pointer it's not defined
cout<<vi;
//_Func User-defined function object that is applied to each element in the range. 
for_each(vi.begin(),vi.end(),MultDivValue<int>(5)); //lkol element mn vi lmrof n3mlo multiply par 5
cout<<vi;
for_each(vi.begin(),vi.end(),MultDivValue<int>(1,5));
cout<<vi;
for_each(vi.begin(),vi.end(),carre<int>); //fonction(definit par sont nom) not foncteur(definit par son instance) donc je ne donne pas parenthese et () j'ecris juste le nom puis je dois donner que c'est parametre de int
cout<<vi;
for_each(vi.begin(),vi.end(),SquareRoot<int>()); //foncteur(definit par sont nom) not foncteur(definit par son instance) donc je ne donne pas parenthese et () j'ecris juste le nom puis je dois donner que c'est parametre de int
cout<<vi;
}

void test6(){
cout << "test 6\n";
vector<int> vi (10);
cout<<vi;
generate( vi.begin ( ), vi.end ( ) , rand ); //srand pour etre vraiment aleatoire elle met le seed au debut
cout<<vi;
sort( vi.begin( ), vi.end( ) );
cout<<vi;
sort( vi.begin( ), vi.end( ), LastDigitRise<int>);
cout<<vi;
sort( vi.begin( ), vi.end( ), LastDigitFall<int>);
cout<<vi;
sort( vi.begin( ), vi.end( ), SupIsFirst<int>);
cout<<vi;


}
void main()
{
  test1();
  test2();
  test3();
  test4();
  test5();
  test6();
}
