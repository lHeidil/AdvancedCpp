#include <iomanip>
#include <typeinfo.h> 
#include "Fract.h"
#include "CPolyDyn.h"
#include "CPoly.h"
#include "TPoly.h"
using namespace std;

//void test1()
//{
//  cout<<"********* Test1 **************\n";
//  {
//  TVectPoly<float> pnull, p0(5.5f), p1(1.2f, 2.4f), p2(1.1f, -4.3f, 0.7f), p3(0,12.4f,3.7f,2.44f), p4(0,0,-5.7f,0,8.5f);
//  //cout<<"Ordre de p4:"<<p4.Ordre()<<"\n";
//  cout<<pnull<<p0<<p1<<p2<<p3<<p4;
//  cout<<p0+p3;
//  cout<<p2*p3;
//  cout<<p1*2.0f; // utilisation implicite (automatique) du ctor à 1 paramètre TCoef
//  //cout<<2.0f*p1; // le compilateur essaie de transformer p1 en float et ça ne marche pas
//                 // mais il ne transforme pas automatiquement 2.0f dans un TVectPoly<float>
//  cout<<((TVectPoly<float>)2.0f)*p1; // utilisation explicite du ctor à 1 paramètre TCoef pour 2.0f
//  TVectPoly<int> p11(1,1), ptri(1);
//  for(unsigned deg=1; deg<30; deg++)
//    cout<<"Triangle de Pascal degre "<<deg<<""<<(ptri*=p11);
//  }
//  {
//  TVectPoly<char> pnull, p0(5), p1(2, -4);
//  cout<<pnull<<p0<<p1;
//
//  }
//}
//template<typename TCoef, size_t SZ> void EvalPoly(const TVectPoly<TCoef> (&TabPoly)[SZ], TCoef v)
//{
//  for(size_t i=0; i<SZ; i++) cout<<"P"<<i<<"<"<<typeid(TCoef).name()<<">("<<v<<")="<<TabPoly[i](v)<<"\n";
//}
//
//// la specialisation pour char ne veut pas les arguments explicites <char,SZ>, le compilateur les deduit automatiquement à partir des args TabPoly et v
//template<size_t SZ> void EvalPoly(const TVectPoly<char> (&TabPoly)[SZ], char v)
//{
//  for(size_t i=0; i<SZ; i++) cout<<"P"<<i<<"<"<<typeid(char).name()<<">("<<(short)v<<")="<<(short)(TabPoly[i](v))<<"\n";
//}
//
//template<typename TCoef> void TestEval(TCoef v)
//{
//  TVectPoly<TCoef> poly[]={TVectPoly<TCoef>(5), TVectPoly<TCoef>(1, 2), TVectPoly<TCoef>(1, -4, 1), TVectPoly<TCoef>(0, 12, 3, 2), TVectPoly<TCoef>(0, 0, -5, 0, 8)};
//  EvalPoly(poly,v);
//  cout<<"\n";
//}
//
//void test2()
//{
//  cout<<"********* Test2 **************\n";
//  TestEval<float>(1.0f);
//  TestEval<int>(2);
//  TestEval<double>(3.0);
//  TestEval<char>(1);
//}

void testA()
{
	std::cout << "*********Test A*********"<< std::endl;
	CPoly poly1(1, 2,0,0,5);
	// poly1.Show(std::cout);
    std::cout << poly1 << "Poly val at x=2: " << poly1(2) <<"\n"<< std::endl;

    float coeffs2[] = {2, -1, 0, 3};
    CPoly poly2(3, coeffs2);
    std::cout << poly2 << "Poly val at x=2: " << poly2(2)<<"\n" << std::endl;
	std::cout << poly2+poly1<< std::endl;
	std::cout << poly2*poly1<< std::endl;
	std::cout << poly2+2<< std::endl;
	std::cout << poly2*2<< std::endl;
	std::cout << 2*poly2<< std::endl;
}
template <typename type>
void testfn(TPoly<type> poly1,TPoly<type> poly2)
{
	std::cout << poly1;
	std::cout << poly2;
	std::cout << "Poly2 val at x=2: " << poly2(2)<<"\n" << std::endl;
	std::cout << "poly2+poly1 = " << poly2+poly1<< std::endl;
	std::cout << "poly2*poly1 = " <<poly2*poly1<< std::endl;
	std::cout << "poly2+2 = " <<poly2+2<< std::endl;
	std::cout << "poly2*2 = " <<poly2*2<< std::endl;
	std::cout << "2+poly2 = " <<2*poly2<< std::endl;
}
void testB()
{
	std::cout << "*********Test B*********"<< std::endl;
	using namespace Fract;
	
	unsigned char coeffs1[] = {2, 1, 0, 7};
    TPoly<unsigned char> poly1(3, coeffs1);
	TPoly<unsigned char> poly1B(1, 2, 1);
    float coeffs2[] = {2, -1, 0, 3};
    TPoly<float> poly2(3, coeffs2);
	TPoly<float> poly2B(1, 2, 0, 0, 5);
	TPoly<CFract> poly3(CFract(1,2), CFract(6,2),CFract(3,2));
	TPoly<CFract> poly3B(CFract(7,2), CFract(6,2));
	TPoly<long> poly4(1, 2, 0, 0, 255);
	TPoly<long> poly4B(1, 2, 3);
	TPoly<double> poly5(1, 2, 0.2);
	TPoly<double> poly5B(1, 2.1, 0.2, 0, 5.8);

	//testfn(poly1,poly1B);
	//testfn(poly2,poly2B);
	//testfn(poly3,poly3B);
	//testfn(poly4,poly4B);
	//testfn(poly5,poly5B);
}

void testADyn()
{
	std::cout << "*********Test A Dynamique*********"<< std::endl;
	CPolyDyn poly1(1, 2,0,0,5);
	//poly1.Show(std::cout);
    std::cout << poly1 << "Poly val at x=2: " << poly1(2) <<"\n"<< std::endl;

    float coeffs2[] = {2, -1, 0, 3};
    CPolyDyn poly2(3, coeffs2);
    std::cout << poly2 << "Poly val at x=2: " << poly2(2)<<"\n" << std::endl;
	//std::cout << poly2+poly1<< std::endl;
	//std::cout << poly2*poly1<< std::endl;
	//std::cout << poly2+2<< std::endl;
	//std::cout << poly2*2<< std::endl;
	//std::cout << 2*poly2<< std::endl;
}

void main() {
	testA();
	testADyn();
	//testB();
    //test1();
    //test2();
}
