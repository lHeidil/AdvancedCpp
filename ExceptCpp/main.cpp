#include <iostream>
#include <iomanip>
#include <string>
#include <limits.h>
#include <typeinfo.h> 
#include <math.h>
#include "Fract.h"

using namespace std;

/********************** Gestion des exceptions C++ ***************************************/
// Attention : normalement on ne transmets jamais une exception par référence ou par adresse
// car au moment de l'utilisation dans catch il faut qu'elle existe toujours: donc toujours par copie !!!
// L'exemple du const char* est particulier car dans ce cas (no.2) on transmet une adresse d'une chaine
// constante qui existe toujours dans le segment de données
// Mais les exemples no.7 et no.8 montrent des erreurs de conception car transmission par adresse
// L'exemple no.9 montre la solution correcte si l'on veut transmettre de chaines variable (par copie)

// provoquer une exception C++ non-gérée localement
void test1(unsigned int cas=0)
{
  switch(cas)
  {
  case 0: throw 2.3; // provoquer une exception de type double et valeur 2.3
    break;
  case 1: throw sin(1.0f); // provoquer une exception de type float
    break;
  case 2: throw "Coucou"; // provoquer une exception de type const char*
    break;
  case 3: throw 'A'; // provoquer une exception de type char
    break;
  case 4: throw Fract::CFract(3,4); // provoquer une exception de type CFract
    break;
  case 5: throw "Une autre message"; // provoquer une exception de type const char*
    break;
  case 6: throw 1+5.5; // provoquer une exception de type double
    break;
  case 7:
    {
      char loc[15];
      sprintf(loc,"BlaBla %d !",2022);
      throw loc; // provoquer une exception de type const char* mais dans le catch la tableau loc n'existe plus !!!
      break;
    }
  case 8:
    {
      double v1=3.7;
      throw &v1; // provoquer une exception de type double* mais dans le catch la variable v1 n'existe plus !!!
    }
  case 9:
    string s;
    s="Blabla"; s+=" Coucou";
    throw s; // provoquer une exception de type std::string parfaitement correcte car par copie
  }
}

// provoquer une exception C++ gérée localement
void test2(unsigned int cas=0)
{
  try
  {
    switch(cas)
    {
    case 0: throw 2.3; // provoquer une exception de type double et valeur 2.3
      break;
    case 1: throw sin(1.0f); // provoquer une exception de type float
      break;
    case 2: throw "Coucou"; // provoquer une exception de type const char*
      break;
    case 3: throw 'A'; // provoquer une exception de type char
      break;
    case 4: throw Fract::CFract(3,4); // provoquer une exception de type CFract
      break;
    case 5: throw "Une autre message"; // provoquer une exception de type const char*
      break;
    case 6: throw 1+5.5; // provoquer une exception de type double
      break;
    }
  }
  catch(const char* str)
  {
    cout<<"Une exception de type const char*: "<<str<<"\n";
  }
  catch(double d)
  {
    cout<<"Une exception de type double: "<<d<<"\n";
  }
  catch(Fract::CFract f)
  {
    cout<<"Une exception de type CFract: "<<f<<"\n";
  }
  catch(...)
  {
    cout<<"Une exception d'un autre type non prevu...\n";
  }
  cout<<"Et le programme continue apres catch\n";
}

// surveiller et gérer une exception C++
void test3(unsigned int cas=0)
{
  try
  {
    test1(cas);
  }
  catch(const char* str)
  {
    cout<<"Une exception de type const char*: "<<str<<"\n";
  }
  catch(double d)
  {
    cout<<"Une exception de type double: "<<d<<"\n";
  }
  catch(Fract::CFract f)
  {
    cout<<"Une exception de type CFract: "<<f<<"\n";
  }
  catch(...)
  {
    cout<<"Une exception d'un autre type non prevu...\n";
  }
  cout<<"Et le programme continue apres catch\n";
}

/************************************* exemples factorielle ***************************************/
namespace Fact_V1 {
// fonction qui génère des exceptions si argument négatif ou résultats trop grands
long Fact(long f) //ecrire en version template
{
  if(f<0) throw(int(1));
  if(f==0) return 1;
  long v=Fact(f-1);
  if(LONG_MAX/v < f) throw(int(2)); // f* v > LONG_MAX va etre jamais verifier 3shan lw da 7sl hyb2a fe overflow lkn l mktoba di abl my7sl f b2dr adetect f3ln
  return f*v;
}

// test pour la fonction Fact
void testFact()
{
  cout<<"\nTestFact version 1\n";
  try
  {
    cout<<"6! = "<<Fact(6)<<endl;
    cout<<"8! = "<<Fact(8)<<endl;
    cout<<"10! = "<<Fact(10)<<endl;

    // enlever le commentaire de la ligne suivante pour déclencher une exception type int de valeur 1
    //cout<<"-2! = "<<Fact(-2)<<endl;

    for(long i=0; i<35; i++)
      cout<<i<<"! = "<<Fact(i)<<endl; // il y aura une exception type int valeur 2 pour i=13

    cout<<"-2! = "<<Fact(-2)<<endl; // cette exception ne se declenche pas si i arrive à 13 dans la boucle precedente
  }
  catch(int v) { cout<<"Exception de type int = "<<v<<endl;}
  catch(...) { cout<<"Exception de type inconnu\n";}
}
}

namespace Fact_V2 {
// On veut une gestion des exceptions de Fract qui puissent garder les informations essentielles au delenchement
// de l'exception et pouvoir les afficher(ou utiliser) dans la gestion de catch
// On conçoit alors une exception plus spécifique, avec un numéro d'exception et un message :
class MyExcept
{
public:
  int numb;
  string msg;
  MyExcept(int _numb, const char* _msg): numb(_numb), msg(_msg) {}
  ostream& Show(ostream& os) const
  {
    return os<<"Erreur #"<<numb<<" : "<<msg<<endl;
  }
};

// fonction qui génère des exceptions si argument négatif ou résultats trop grands
long Fact(long f)
{
  if(f<0) throw(MyExcept(1,"Factorielle d'une valeur negative"));
  if(f==0) return 1;
  long v=Fact(f-1);
  if(LONG_MAX/v < f) throw(MyExcept(2,"Depassement de la plage admissible"));
  return f*v;
}

inline ostream& operator<<(ostream& os, const MyExcept& e) { return e.Show(os); }

void testFact()
{
  cout<<"\nTestFact version 2\n";
  try
  {
    cout<<"6! = "<<Fact(6)<<endl;
    cout<<"8! = "<<Fact(8)<<endl;
    cout<<"10! = "<<Fact(10)<<endl;
    for(long i=0; i<35; i++)
      cout<<i<<"! = "<<Fact(i)<<endl;
    cout<<"-2! = "<<Fact(-2)<<endl;
  }
  //catch(MyExcept e) { cout<<"Erreur #"<<e.numb<<" : "<<e.msg<<endl;}
  catch(MyExcept e) { cout<<e; } // cette solution est plus elegante que la ligne precedente
  catch(...) { cout<<"Exception de type inconnu\n";}
}
}

// encore un autre exemple, on essaie de plonger tout dans un template Fact_V3
// le type de retour de la factorielle est le paramètre générique
// l'exception est une classe imbriquée dans le template, elle est encore plus particuliere
//   elle ne gère que la limite de calcul (car l'argument de Fact est size_t maintenant)
//   et elle mémorise à quelle limite elle s'est arretée
template <typename TElem> class Fact_V3
{
public:
  static TElem Fact(size_t f)
  {
    if(f==0) return (TElem)1;
    TElem v=Fact(f-1);
    TElem v2=f*v;
    if(v2/f != v) throw FactExcept(f); // when overflow divise donc ca va etre jamais v donc on le detecte sans detecter l'overflow elle meme
    return v2;
  }
  
  static void testFact()
  {
    cout<<"\nTestFact version 3 (template) pour "<<typeid(TElem).name()<<"\n";
    try
    {
      for(size_t i=0; i<100; i++)
        cout<<i<<"! = "<<Fact(i)<<endl;
    }
    //catch(FactExcept e) { e.Show(cout); }
    catch(FactExcept e) { cout<<e; }
    catch(...) { cout<<"Exception de type inconnu\n";}
  }
  class FactExcept
  {
  public:
    size_t numb;
    FactExcept(size_t _numb): numb(_numb) {}
    ostream& Show(ostream& os) const
    {
      return os<<"Exception pour la calcul de la factorielle de "<<numb<<" en tant que "<<typeid(typename TElem).name()<<endl;
    }
  };
};
// VS2008 a des problèmes à compiler l'opérateur << pour la classe FactExcept imbriquée dans le template Fact_V3
//template <typename T> ostream& operator<<(ostream& os, const Fact_V3<T>::FactExcept& e) { return e.Show(os); }
// solution de contournement qui marche seulement pour le type unsigned _int64 utilisé dans main
ostream& operator<<(ostream& os, const Fact_V3<unsigned _int64>::FactExcept& e) { return e.Show(os); }
//sinon il faut sortir la classe du template ou pas d'opérateur << mais utiliser Show ...

/********************************** exemple de tests sur CFract avec exceptions *************************/
//#include "FractExcept.h"
//// on peut aussi plonger le test dans le même namespace au lieu de casser le namespace FractExcept
//namespace FractExcept {
//void test4()
//{
//  cout<<"\nTest4\n";
//  CFract f1(4,7), ftab[]={CFract(2), CFract(0,2), CFract(12,5)};
//  cout<<"f1="<<f1<<" ftab[0]="<<ftab[0]<<endl;
//  try
//  {
//    cout<<"f1+ftab[0]="<<f1+ftab[0]<<endl;
//    CFract f2(12,0); // ceci va provoquer une exception
//  }
//  catch(Except e)
//  {
//    cout<<e;
//  }
//  try
//  {
//    cout<<"f1/ftab[2]="<<f1/ftab[2]<<endl; // ceci fonctionne
//    cout<<"f1/ftab[1]="<<f1/ftab[1]<<endl; // ceci va provoquer une exception
//  }
//  catch(Except e)
//  {
//    cout<<e;
//  }
//}
//}

// Activer un ou plusieurs tests à la fois, regardez et analyser les résultats obtenus
void main()
{
  test1(0); // provoquer des exceptions non-gérées
  test1(1); // provoquer des exceptions non-gérées
  test1(4); // provoquer des exceptions non-gérées
  test2();
  test2(4);
  test2(2);
  test3(3);
  test3(0);
  Fact_V1::testFact();
  Fact_V2::testFact();
  Fact_V3<unsigned __int64>::testFact();
  FractExcept::test4();
}