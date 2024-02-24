#include "TPerm.h"

using namespace std;

//template<typename T> void ShowVect(ostream& os, const vector<T>& v, size_t idx_max=0, size_t idx_min=0)
//{
//  os<<"Vecteur de type "<<typeid(T).name()<< ", taille "<<v.size()<<", capacite "<<
//    v.capacity()<<", max_size "<<v.max_size()<<endl;
//  if(v.empty()) return;
//  if(idx_max==0 || idx_max>v.size()) idx_max=v.size();
//  if(idx_min>idx_max) idx_min=idx_max;
//  for(size_t i=idx_min; i<idx_max; i++) os<<"  ["<<i<<"] "<<v[i]<<endl;
//}
//template<typename T> inline ostream& operator<<(ostream& os, const vector<T>& v) { ShowVect<T>(os,v); return os; }
//
//template<typename T, size_t SZ> ostream& ShowTab(ostream& os, const T (&tab)[SZ])
//{
//  os<<"Tableau de type "<<typeid(tab).name()<<" :\n";
//  for(size_t i=0; i<SZ; i++) os<<"  ["<<i<<"]="<<tab[i]<<"\n";
//  return os;
//}
//void test1() // tests divers
//{
//  try
//  {
//    cout<<"==============\n";
//    cout<<"Tests divers :\n";
//    cout<<"==============\n";
//    const TPermBase::TOrdre sz=20;
//    cout<<"MaxIdx("<<sz<<") ="<<TPerm<sz>().MaxIdx()<<endl;
//    TPerm<5> p1;
//    for(TPermBase::TIndex i=0; i<150; i++) cout<<p1++;
//    //TPerm<3> pexept(1000); // ceci provoque une exception, où, comment, à tester
//    // ligne suivante: analyser le code, trouver où et comment l'exception est déclenchée et
//    // pour quoi cette structure try/catch ne peut pas attraper cette exception ?
//    //TPerm<50> pexcept2; // ceci provoque une exception, où, comment, à tester
//    TPerm<10> p2(5000), p3(2);
//    cout<<"p2 : "<<p2;
//    cout<<"p3 : "<<p3;
//    cout<<"p2*p3 : "<<p2*p3;
//    TPermBase::TOrdre tab[4]={0,3,1,2}; //0->0, 1->3, 2->1, 3->2
//    TPerm<4> p4(tab);
//    cout<<"p4 :"<<p4;
//    TPermBase::TOrdre tabinv[4]={0,2,3,1}; //0->0, 1->2, 2->3, 3->1
//    TPerm<4> p4inv(tabinv);
//    cout<<"p4inv :"<<p4inv;
//    cout<<"p4*p4inv : "<<p4*p4inv;
//    cout<<"p4inv*p4 : "<<p4inv*p4;
//    char t1[4]={'A','B','C','D'};
//    ShowTab(cout,t1);
//    PermuteTab(t1,p4);
//    //PermuteVect(vector<float>(10,2.2f),p4); // ceci provoque une exception, où, comment, à tester
//    ShowTab(cout,t1);
//    //PermuteTab(t1,~p4); // à tester après l’implémentation de l'opérateur ~
//  }
//  catch(TPermBase::Except e) {cout<<e;}
//}
//
//void test2() // test de racine de la permutation identite
//{
//  const TPermBase::TOrdre ORD=4;
//  cout<<"===================================================\n";
//  cout<<"Test de racine de la permutation identite (ordre "<<ORD<<")\n";
//  cout<<"===================================================\n";
//  TPerm<ORD> p1;
//  while((++p1).GetIdx())
//  {
//    TPerm<ORD> p2(p1);
//    TPermBase::TIndex pw=1;
//    while(++pw < p1.MaxIdx())
//    {
//      if((p2*=p1).GetIdx()==0)
//      {
//        cout<<p1<<" est une racine d'ordre "<<pw<<endl;
//        break;
//      }
//    }
//  }
//}
//
//template <TPermBase::TOrdre ORD> void test3() // test de permutation
//{
//  cout<<"============================================\n";
//  cout<<"Permutation d'ordre "<<ORD<<" sur un vector<char> :\n";
//  cout<<"============================================\n";
//  vector<char> vstr;
//  for(size_t i=0; i<ORD; i++) vstr.push_back(char('A'+i));
//  cout<<vstr;
//  TPerm<ORD> p(50%TPerm<ORD>::MaxIdx());
//  cout<<p;
//  PermuteVect(vstr,p);
//  cout<<vstr;
//}
void testA()
{
  cout <<"-------------Test A-------------"<<endl;
  const TOrdre ORD1 = 5;
  TIndex Tab[ORD1];
  //TPerm<ORD1>::Idx2Tab(5,Tab);	
  //cout<<TPerm<ORD1>::Tab2Idx(Tab)<<endl;
  TPerm<ORD1> p1;
  p1++;
  ++p1;
  const TOrdre ORD2 = 10;
  TPerm<ORD2> p2(5);
  cout<<"p1: "<<p1;
  cout<<"p2: "<<p2;
  cout <<"-----------End Test A-----------\n"<<endl;
}
void testB()
{
  cout <<"-------------Test B-------------"<<endl;
  const TOrdre ORD = 5;
  TIndex TabL[ORD]={4,2,1,3,0},TabR[ORD]={3,0,1,4,2};
  //cout<<TPerm<ORD>::Tab2Idx(TabL)<<endl;
  //cout<<TPerm<ORD>::Tab2Idx(TabR)<<endl;
  TPerm<ORD> p1(TPerm<ORD>::Tab2Idx(TabL));
  TPerm<ORD> p2(TabR);
  //cout<<p1.GetIdx()<<","<<p2.GetIdx()<<endl;
  cout<<"p1: "<<p1;
  cout<<"p1: "<<p2;
  //p1*=p2;
  p1 = p1*p2;
  cout<<"p1*p2: "<<p1;
  cout <<"-----------End Test B-----------\n"<<endl;
}
void testC()
{
  cout <<"-------------Test C-------------"<<endl;
  const TOrdre ORD3 = 4;
  TIndex Tab[ORD3] = {1, 0, 3, 2};
  TPerm<ORD3> p(Tab);
  const TIndex N = 3;
  cout << "Permutation : " << p;

  if (p.racineID<N>()) {  cout << "La permutation est une racine d'ordre " << N << " de l'id." << endl;  } 
  else {  cout << "La permutation n'est pas une racine d'ordre " << N << " de l'id." << endl; }
  cout <<"-----------End Test C-----------\n"<<endl;
}
//__int64 = long long = 64 bits
//max= fact(ordmax) =(2^64)-1 (unsinged from0 to (2^n)-1)
//ordmax est le nombre qui donne factorial <= (2^64)-1 ???
void main()
{
  testA();
  testB();
  testC();
  //test1();
  //test2();
  //test3<3>();
  //test3<5>();
  //test3<10>();
  //cout<<"Fin des tests\nAppuyer sur entree pour terminer\n";
  //string s;
  //std::getline(cin,s);
}