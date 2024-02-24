#include <iostream>
#include <iomanip>
#include <string>
#include <limits.h>
#include <excpt.h>

using namespace std;

/********************** Gestion des exceptions mat�rielles ***************************************/
// provoquer une exception mat�rielle non-g�r�e localement
void test1()
{
  float *pf1=0;
  pf1[3]=3.3f; // on essaie d'acc�der � une adresse invalide
  // si appel du main : cela provoque une exception mat�rielle 0xC00000005 non-g�r�e qui va arr�ter le programme
  // si appel dans un bloc __try alors on peut capter et traiter l'exception
  cout<<"Cette ligne ne sera jamais ex�cut�e\n";
}

// provoquer une exception mat�rielle non-g�r�e localement si l'on ignore avant les exceptions C++ de variable non-initialis�e
void test1b()
{
  float *pf1; // pointeur non-initialis�, en Debug elle aura la valeur 0xCCCCCCCC et en Release la valeur de la m�moire avant
  // en Debug tout utilisation d'une variable non-initialis�e d�clenche une exception C++ sp�cifique
  // pour ex�cuter la ligne suivante en Debug il faut choir "Ignorer" dans la MessageBox d�clench�e par l'exception C++
  cout<<"Pointeur pf1="<<pf1<<"\n"; 
  // pour ex�cuter la ligne suivante en Debug il faut choir "Ignorer" dans la MessageBox d�clench�e par l'exception C++
  pf1[3]=3.3f; // on essaie d'acc�der � une adresse non-initialis�e, possiblement invalide
  // si appel du main : cela provoque une exception mat�rielle 0xC00000005 non-g�r�e qui va arr�ter le programme
  // si appel dans un bloc __try alors on peut capter et traiter l'exception
  cout<<"Cette ligne ne sera jamais executee si pf1 a une adresse invalide\n";
}

// provoquer une exception mat�rielle g�r�e localement
void test2()
{
  __try // on surveille les exceptions mat�rielles
  {
    float *pf1=0;
    pf1[3]=3.3f; // on essaie d'acc�der � une adresse invalide,
    // cela provoque une exception materielle 0xC00000005 qui sera g�r�e par le __except suivant
  }
  __except(EXCEPTION_EXECUTE_HANDLER) // on traite les exceptions mat�rielles g�n�r�es
  {
    cout<<"Grosse exception materielle, code "<<hex<<_exception_code()<<" !!!\n";
  }
}

// surveiller des exceptions mat�rielles dans le code appel� puis les g�rer localement
void test3()
{
  __try // on surveille les exceptielles materielles dans le bloc suivant
  {
    test1(); // cette fois-ci test1 n'arr�te plus le programme
  }
  __except(EXCEPTION_EXECUTE_HANDLER) // on traite les exceptions materielles g�n�r�es
  {
    cout<<"Exception materielle dans le code surveill�, code "<<hex<<_exception_code()<<" !!!\n";
  }
}

// Activer un test � la fois, regardez et analyser les r�sultats obtenus
void main()
{
  //test1();
  //test1b();
  //test2();
  test3();
}
