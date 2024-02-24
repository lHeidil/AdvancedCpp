#include <iostream>
#include <iomanip>
#include <string>
#include <limits.h>
#include <excpt.h>

using namespace std;

/********************** Gestion des exceptions matérielles ***************************************/
// provoquer une exception matérielle non-gérée localement
void test1()
{
  float *pf1=0;
  pf1[3]=3.3f; // on essaie d'accéder à une adresse invalide
  // si appel du main : cela provoque une exception matérielle 0xC00000005 non-gérée qui va arrêter le programme
  // si appel dans un bloc __try alors on peut capter et traiter l'exception
  cout<<"Cette ligne ne sera jamais exécutée\n";
}

// provoquer une exception matérielle non-gérée localement si l'on ignore avant les exceptions C++ de variable non-initialisée
void test1b()
{
  float *pf1; // pointeur non-initialisé, en Debug elle aura la valeur 0xCCCCCCCC et en Release la valeur de la mémoire avant
  // en Debug tout utilisation d'une variable non-initialisée déclenche une exception C++ spécifique
  // pour exécuter la ligne suivante en Debug il faut choir "Ignorer" dans la MessageBox déclenchée par l'exception C++
  cout<<"Pointeur pf1="<<pf1<<"\n"; 
  // pour exécuter la ligne suivante en Debug il faut choir "Ignorer" dans la MessageBox déclenchée par l'exception C++
  pf1[3]=3.3f; // on essaie d'accéder à une adresse non-initialisée, possiblement invalide
  // si appel du main : cela provoque une exception matérielle 0xC00000005 non-gérée qui va arrêter le programme
  // si appel dans un bloc __try alors on peut capter et traiter l'exception
  cout<<"Cette ligne ne sera jamais executee si pf1 a une adresse invalide\n";
}

// provoquer une exception matérielle gérée localement
void test2()
{
  __try // on surveille les exceptions matérielles
  {
    float *pf1=0;
    pf1[3]=3.3f; // on essaie d'accéder à une adresse invalide,
    // cela provoque une exception materielle 0xC00000005 qui sera gérée par le __except suivant
  }
  __except(EXCEPTION_EXECUTE_HANDLER) // on traite les exceptions matérielles générées
  {
    cout<<"Grosse exception materielle, code "<<hex<<_exception_code()<<" !!!\n";
  }
}

// surveiller des exceptions matérielles dans le code appelé puis les gérer localement
void test3()
{
  __try // on surveille les exceptielles materielles dans le bloc suivant
  {
    test1(); // cette fois-ci test1 n'arrête plus le programme
  }
  __except(EXCEPTION_EXECUTE_HANDLER) // on traite les exceptions materielles générées
  {
    cout<<"Exception materielle dans le code surveillé, code "<<hex<<_exception_code()<<" !!!\n";
  }
}

// Activer un test à la fois, regardez et analyser les résultats obtenus
void main()
{
  //test1();
  //test1b();
  //test2();
  test3();
}
