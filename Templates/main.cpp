#include "Template.h"
#include "Fract.h"
using namespace std;
using namespace Fract;

void test1()
{
	
	cout<<"************ Test 1 *****************\n";
	//Exo1 B
	float f1 = 5.3f, f2 = 4.5f;
	double d1 = 2.25, d2 = -15.4;
	int i1 = 25, i2 = -3;
	CFract fr1(4,2),fr2(8,2);
	cout<<MaxVal(f1, f2)<<endl;
	cout<<MaxVal(d1, d2)<<endl;
	cout<<MaxVal(i1, i2)<<endl;
	cout<<MaxVal(i1, 23)<<endl; //ne fonctionne pas avec la version 3 car une constante ne passe pas par référence. Elle doit passer par référence constante . Voir version 4
	//cout<<MaxVal(i1, f2)<<endl; // ambiguité sur le type TObj car deux chemins possibles. C'est à l'utilisateur de faire le choix
	cout<<MaxVal(i1, (int)f2)<<endl;
	cout<<MaxVal((float)i1, f2)<<endl;
	cout<<MaxVal<float>(i1, f2)<<endl;
	cout<<MaxVal<double>(i1, f2)<<endl;
	MaxVal(i1, i2) = 89; // ne marche pas avec la version 4 à cause du const de la valeur de retour

	//Exo1 C
	/*The implicit requirement is the ability to perform
	the (>) comparison operator, it should be defined for
	the objects of type TObj.*/

	//Exo1 D
	cout<<MaxVal(fr1, fr2)<<endl;
	//cout<<MaxVal<double>(fr1, d1)<<endl; //pas de conversion de CFract a double
	cout<<MaxVal<CFract>(fr1, d1)<<endl; //conversion de double en int to be in CFract puis les comparer

	cout<<"************ Fin de Test 1 *****************\n";
}

void test2()
{
	//Exo2 C
	cout<<"************ Test 2 *****************\n";

	double vd1[] = {2.25, -15.4, 6.6, -6.6};
	//const size_t vd1_sz = sizeof(vd1)/sizeof(vd1[0]);
	const size_t vd1_sz = GetSize(vd1);
	ShowVect(cout, vd1, vd1_sz, "vd1");
	ShowVect(cout, vd1, "vd1");
	TestVectSomme(cout, vd1);

	CFract vf1[]={CFract(7,12),CFract(3),CFract(1,6),CFract(2,13),CFract(2,5)};
	//const size_t vf1_sz = sizeof(vf1)/sizeof(vf1[0]);
	const size_t vf1_sz = GetSize(vf1);
	ShowVect(cout, vf1, vf1_sz, "vf1");
	ShowVect(cout, vf1, "vf1");
	TestVectSomme(cout, vf1);

	size_t tdyn_sz = 5 + (rand()%5);
	int *tdyn = new int[tdyn_sz];
	for (size_t i=0; i<tdyn_sz; ++i) tdyn[i] = int (i*i);
	ShowVect( cout, tdyn, tdyn_sz, "tdyn");
	//ShowVect( cout, tdyn, "tdyn");  // erreur avec le passage par référence car les tableaux dynamiques ne sont pas des tableaux qu'on peut passer par référence : impossible de convertir le paramètre 3 de 'const char [5]' en 'size_t'
	delete[] tdyn;

	cout<<"************ Fin de Test 2 *****************\n";
}


void test3()
{
	//Exo3 C
	cout<<"************ Test 3 *****************\n";
	int vint[] = {5, -2, 250, -250,0};
	//const size_t vint_sz = sizeof(vint)/sizeof(vint[0]);
	const size_t vint_sz = GetSize(vint);
	TriMontant(cout, vint, vint_sz);

	double vd1[] = {2.25, -15.4, 6.6, -6.6};
	//const size_t vd1_sz = sizeof(vd1)/sizeof(vd1[0]);
	const size_t vd1_sz = GetSize(vd1);
	TriMontant(cout, vd1, vd1_sz);

	CFract vf1[]={CFract(7,12),CFract(3),CFract(1,6),CFract(2,13),CFract(2,5)};
	//const size_t vf1_sz = sizeof(vf1)/sizeof(vf1[0]);
	const size_t vf1_sz = GetSize(vf1);
	TriMontant(cout, vf1, vf1_sz);

	cout<<"************ Fin de Test 3 *****************\n";
}

void main()
{
    //test1();
	//test2();
	test3();
}