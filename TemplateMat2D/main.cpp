#include "Mat2D.h"
#include "CFract.h"
using namespace std;
using namespace Fract;

//Exo5 C
void test1()
{
  cout<<"************ Test 1 ***************\n";
  Mat2D<6,4,float> m0, m1(5.5f);
  cout<<m0<<m1;
  m1(2,2)=0;
  //m1(6,1)=2.2f; // erreur ou exception potentielle dans l'opérateur () version non-const !!! //not handled error should be in try block
  cout<<m1;
  Mat2D<6,4,float>::SetW(10); Mat2D<6,4,float>::SetPrec(5);
  cout<<"Apres W<-10 Prec<-5, Affichage de m1 par defaut:\n"<<m1;
  Mat2D<4,6,CFract> mf(CFract(-1,3));

  cout<<"Affichage de mf par defaut:\n"<<mf;
  cout<<"Affichage de mf avec Show(mf,6):\n";
  mf.Show(cout,6);
  const Mat2D<5,2, double> md1(13);
  cout<<md1(0,0)<<endl;
  //cout<<md1(1,100)<<endl; // erreur ou exception potentielle dans l'opérateur () version const !!!
}

void test2()
{
  cout<<"************ Test 2 ***************\n";
  Mat2D<5,7,double> m0(7.5f);
  cout<<m0;
  m0.Rand(-5,5);
  cout<<m0;
  Mat2D<7,5,double> m1(~m0);
  cout<<m1;
  Mat2D<2,3,CFract> mf(CFract(2,3));
  cout<<mf;
  mf.Rand(CFract(-1,10),CFract(1,10));
  cout<<mf;
  Mat2D<4,5,char> mc('A');
  cout<<mc;
  mc.Rand('A','Z');
  cout<<mc;
}
//Exo5 D
void test3()
{
  cout<<"************ Test 3 ***************\n";
  const size_t N1=4, N2=2;
  Mat2D<N1,N2,int> m0(10), m1(-5);
  m1.Rand(0,10);
  cout<<m0<<m1;
  Mat2D<N2,N1,int> m2(33), m3(7);
  m2.Rand(5,10);
  cout<<m2<<m3;
  cout << m0+m1;
  //cout << m0-m1; //it gives me error i should fix it
//  cout << m0+m2; impossible : erreur de compilation !!!
  cout << m0*m2;
//  cout << m0*m1; impossible : erreur de compilation !!!
  m0=0; // ça marche seulement si le ctor n'est pas explicite
  m0=Mat2D<N1,N2,int>(10); // ça marche toujours
  cout<<m0;
 Mat2D<N1,N2,float> mf(12);
 m0=m0+mf;
}
void testMe()
{
	
	cout<<"************ Test Me *****************\n";

	Mat2D<6, 4, float> m0, m1(5.5f);
	try{
	//m1(6,1) =2.2f;
	cout<<m1(1,100)<<endl; // erreur ou exception potentielle dans l'opérateur () version const !!!
	}
	catch(int e) {cout << "exeption = " << e << endl;} //demande un vrai type donc on create les exeption comme classe pas template pour ne pas faire infinite de catch
	catch(const Mat2D_Exception& e) {cout << e;}
	catch(...){}
	Mat2D<6, 4, int> m2(2);
	//Mat2D<6, 4, int> m7=m2; //copy test
	Mat2D<6, 4, int> msum = m2 + m1;
	m0.Rand(1.0f, 10.0f);
    m1(3, 2) = 10.0f;
    cout << m0 << m1 << m2 << msum << endl;

    Mat2D<6, 4, char> m3('A');
    m3.Rand('A', 'Z');
    m3(3, 2) = 'X';
    std::cout << m3 << std::endl;


    std::cout << "Transposed Matrix:\n" << ~m0 << std::endl;
    std::cout << "Sum of Matrices FLOAT:\n" << m0 + m2 << std::endl;
	std::cout << "Sum of Matrices INT:\n" << m2 + m0 << std::endl;
	std::cout << "Sum with 1:\n" << m1 + 1 << std::endl;
	//std::cout << "Product with 2:\n" << m0 * 2 << std::endl; //error
    std::cout << "Product of Matrices:\n" << m0.Transpose() * m1 << std::endl;
  
	cout<<"************ Fin de Test Me *****************\n";

}

void main()
{
	test1();
	test2();
	test3();
	testMe();
}
