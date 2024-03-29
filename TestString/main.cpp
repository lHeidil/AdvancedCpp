#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <typeinfo.h> 
#include <string.h> 
#include <fstream>
#include "ConsoleCP.h"

using namespace std;

ostream& NicePrint(ostream& os, const string& s, const char* name) { return os<<name<<"=\""<<s<<"\"\n"; }
wostream& NicePrint(wostream& os, const wstring& s, const char* name) { return os<<name<<"=\""<<s<<"\"\n"; }

void test1()
{
  cout<<"******** Test1 *************\n";
  string s1, s2("Coucou");
  NicePrint(cout,s1,"s1");
  NicePrint(cout,s2,"s2");
  cout<<"Type de chaine: "<<typeid(s1).name()<<"\n";
  cout<<"Taille d'elements: "<<sizeof(s2[0])<<" octets, Size="<<s2.size()<<", Capacity="<<s2.capacity()<<", StrLen="<<strlen(s2.c_str())<<"\n";
  s1.append("Tout ceci");
  NicePrint(cout,s1,"s1");
  string mot="ce";
  s1.erase(s1.find(mot),mot.size()); // effacer "ce"
  NicePrint(cout,s1,"s1");
  s1.erase();
  NicePrint(cout,s1,"s1"); // effacer tout le reste
  s1="Nouvelle *phrase*";
  s1+=s2;
  NicePrint(cout,s1,"s1");
  s1=s2;
  NicePrint(cout,s1,"s1");
  NicePrint(cout,s2,"s2");
  cout<<"s1 est "<<((s1==s2)?"identique":"differente")<<" a s2\n";
  s1.replace(2,2,"12345");
  NicePrint(cout,s1,"s1");
  NicePrint(cout,s2,"s2");
  cout<<"s1 est "<<((s1==s2)?"identique":"differente")<<" a s2\n";
}

// on mélange à la console seulement cout et wcout mais si vous souhaitez
// n'utiliser que wout alors remplacer toutes les chaines char en w_char
void test2()
{
  cout<<"******** Test2 *************\n";
  wstring s1, s2(L"Coucou à été");
  NicePrint(wcout,s1,"s1");
  NicePrint(wcout,s2,"s2");
  cout<<"Type de chaine: "<<typeid(s1).name()<<"\n";
  cout<<"Taille d'elements: "<<sizeof(s2[0])<<" octets, Size="<<s2.size()<<", Capacity="<<s2.capacity()<<", StrLen="<<wcslen(s2.c_str())<<"\n";
  s1.append(L"Tout ceci");
  NicePrint(wcout,s1,"s1");
  wstring mot=L"ce";
  s1.erase(s1.find(mot),mot.size()); // effacer "ce"
  NicePrint(wcout,s1,"s1");
  s1.erase();
  NicePrint(wcout,s1,"s1"); // effacer tout le reste
  s1=L"Nouvelle *phrase*";
  s1+=s2;
  NicePrint(wcout,s1,"s1");
  s1=s2;
  NicePrint(wcout,s1,"s1");
  NicePrint(wcout,s2,"s2");
  cout<<"s1 est "<<((s1==s2)?"identique":"differente")<<" a s2\n";
  s1.replace(2,2,L"12345");
  NicePrint(wcout,s1,"s1");
  NicePrint(wcout,s2,"s2");
  cout<<"s1 est "<<((s1==s2)?"identique":"differente")<<" a s2\n";
}
void test3(const char* fname){
cout<<"******** Test3 *************\n";
ifstream is(fname);
if (!is) {cout<< "Impossible d'ouvrir le fichier "<< fname<<"\n";return;}
cout<<"Le fichier"<<fname<<"contient les lignes suivants:\n";
size_t idx=0;
while(is)//not for loop to check the boll returned that indicates the status of the file
{
  string line;
  if(getline(is,line))  cout<<"line "<< ++idx <<" : " <<line<<"\n";
}
cout<< "Le fichier a "<< idx <<" lignes\n";
} //fermeture du file

#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <functional>
class MyFile: public vector<std::string>//heritage pour avoir acces a tout ce aui est public
{
public:
  MyFile(const char* fname){
    std::ifstream is(fname);
#if 0
    if(!is) throw invalid_argument("Fichier d'entréé invalide");
#else
    { //pour que oss devient variable locale est ne reste pas dans la pile 
    std::ostringstream oss; //comme sprintf de C 
    oss<<"Le fichier: "<< fname <<" est invalide";
    if(!is) throw invalid_argument(oss.str());
  }
#endif
      cout<<"Le fichier "<<fname<<" contient les lignes suivants:\n";
      size_t idx=0;
      while(is)//not for loop to check the bool returned that indicates the status of the file
      {
        string line;
        if(getline(is,line))  { ++idx; push_back(line);}
      }
  }
  void Show(std::ostream& os)const{ for(size_t i=0;i<size();i++) os<<at(i) <<"\n";} //*this[i] == at(i)
  void Sort(){sort( begin( ), end( ) );}
  template<typename T> void Sort(T& foncteur){sort( begin( ), end( ),foncteur );}
};
void test4(const char* fname){
cout<<"******** Test4 *************\n";
try{
    MyFile file(fname);
    file.Show(cout);cout<<'\n';
    ofstream file2("copie.txt");
    file.Show(file2);
    file.Sort();
    file.Show(cout);cout<<'\n';
    file.Show(ofstream("OrdreAlpha.txt"));cout<<'\n';
    file.Sort(greater<string>()); //string car dans les vvecteur chaque line est un string
    file.Show(cout);cout<<'\n';
    
}
catch (exception&e) //la classe mere de invalid_argument
{
    cerr<<"Exception de type \""<<typeid(e).name()<< e.what()<<"\n"; //recuper cet chaine oss.str()
}
}
template <typename typeClass>
class ParsedFile: public vector<typeClass>//heritage pour avoir acces a tout ce aui est public
{
public:
  ParsedFile(const char* fname){
    std::ifstream is(fname);
    std::ostringstream oss; //comme sprintf de C 
    oss<<"Le fichier: "<< fname <<" est invalide";
    if(!is) throw invalid_argument(oss.str());
    cout<<"Le fichier "<<fname<<" contient les lignes suivants:\n";
    size_t idx=0;
    std::string line;
    while(getline(is,line))
    {
      ++idx;
      try{
        //std::istringstream iss(line);typeClass info(iss); push_back(info); //lmfrod el 3 steps dol aktbhom mra w7da
        //std::istringstream iss(line);push_back(typeClass(iss)); //option tani
        //std::istringstream iss(line);push_back(iss); //conversion par le compilateur automatique
          //push_back(std::istringstream(line)); //ashal w7da klo f line wa7d
          push_back(line); //da constructor eltany bta3 elstrings w da kan explicite f msh byt3ml lw7do
      }
      catch (exception&e) //la classe mere de invalid_argument
      {
        cerr<<"Exception de type \""<<typeid(e).name()<< e.what()<<"a la ligne: "<<idx<<" \n"; //recuper cet chaine oss.str() + quelle ligne
      }

    }
  }
  void Show(std::ostream& os)const{ for(size_t i=0;i<size();i++) os<<at(i) <<"\n";} //*this[i] == at(i)
  void Sort(){sort( begin( ), end( ) );}
  template<typename T> void Sort(T& foncteur){sort( begin( ), end( ),foncteur );}
};
class Formula1
{
public:
  std::string Prenom,Nom,Pays,Ecurie;
  unsigned char Rang,Points,Victoires,Podium;
#if 0
  Formula1(istream& is){
    is>>Rang>>Prenom>>Nom>>Ecurie>>Pays>>Points>>Victoires>>Podium;//chaque element est detecter par un ou plusieur espace
    if(!is) throw std::exception("Erreur de lecture Formula1::Formula1"); //lmfrod a3mlha w7da w7da wlexpection b3dha 3shan a3rf el moshkla fen
  }
#else
  Formula1(istream& is){
    Read(is);
  }
  Formula1(const std::string& s){
    Read(std::istringstream(s));
  }
  void Read(istream& is){
    is>>Rang>>Prenom>>Nom>>Ecurie>>Pays>>Points>>Victoires>>Podium;//chaque element est detecter par un ou plusieur espace
    if(!is) throw std::exception("Erreur de lecture Formula1::Formula1"); //lmfrod a3mlha w7da w7da wlexpection b3dha 3shan a3rf el moshkla fen
  }
#endif
  std::ostream& Show(std::ostream& os)const{ return os<<Rang<<" "<<Nom<<" "<<Pays;} //*this[i] == at(i)

  static bool OrdreByCountry(const Formula1& f1,const Formula1& f2) //methode static 
  {
    return (f1.Pays>f2.Pays);
  }
};
inline std::ostream& operator<<(std::ostream& os,const Formula1& f1){ return f1.Show(os);}



void test5(const char* fname){
cout<<"******** Test5 *************\n";
try{
    ParsedFile<Formula1> file(fname);
    file.Show(cout);cout<<'\n';
    file.Sort(Formula1::OrdreByCountry);
    file.Show(cout);cout<<'\n';
}
catch (exception&e) //la classe mere de invalid_argument
{
    cerr<<"Exception de type \""<<typeid(e).name()<< e.what()<<"\n"; //recuper cet chaine oss.str()
}

}
#include"Fract.h" 
using namespace Fract;
void test6a(const char* fname){
  cout<<"******** Test6a *************\n";
  std::ofstream os(fname);
  for(size_t i=0;i<20;i++){
  os<<CFract(-100+(rand()%200),1+(rand()%100))<<"\n";
  }
}

void test6b(const char* fname){
  cout<<"******** Test6b *************\n";
  ParsedFile<CFract> file(fname);
  file.Show(cout);cout<<'\n';
  }
#include <regex>
#if _MSC_VER < 1600 //older than VC++ 10
namespace std {using namespace tr1;} //pour visiual 9 seulment pas besoin pour les plus recent
#endif
template <typename TObj,size_t SZ> inline
size_t GetSize(const TObj(& o1)[SZ]){ // () o1 pour etre fort que SZ
	return sizeof(o1)/sizeof(o1[0]);
}
void test7(){
  cout<<"******** Test7 *************\n";
  const char* s1 ="Coucou c'est nous 127.0.0.1 et toi c'est 127.0.0.3";
  const char* expr[]={"XYZ",".+","ou","cou","\\d","\\d+","\\d+\\.","(\\d+\\.){3}\\d+"}; //.+ n'importe qu'elle caractere qui se repete //"(\\d+\\.){3}\\d+" pour IPv4 // \\. = vrai point
  for (size_t i=0;i<GetSize(expr);i++)
  {
   regex rx(expr[i]);
   cout<<"\nRechercher \""<<expr[i]<<"\" dans \""<<s1<<"\"\n";
   size_t ofs=0;
   do{
   cmatch res;
   bool found=regex_search(s1+ofs,res,rx);
   cout<< (found?"trouve":"pas trouve")<<": "<<res.size()<<" submatch\n";
   if(!found || res.size()==0) break;
   cout<<"A partir de la position "<<ofs<<" :\n";
   cout<<" avant: \""<<res.prefix()<<" :\n";
   cout<<" trouve: \""<<res.length()<<" char(s): \""<<res.str()<<"\"\n";
   cout<<" apres: \""<<res.suffix()<<" :\n";
   ofs+=res.length(0)+res.position(0);
  }while(true);
  }}
void main(){
  //test3("figures.txt");
  //test4("ff.txt");
  //test4("Formula1_2020.txt");
  //test5("Formula1_2020.txt");
  //test6a("CfractTest.txt");
  //test6b("CfractTest.txt");
  test7();
}