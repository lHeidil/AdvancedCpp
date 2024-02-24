#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <vector>
#include <stdexcept>
//hwa 3ml 2 foction f classe TBAsePerm fehom el factorial w fiha el excpetion w 5la el classe l 3adi y inherit mnhom
//mn l awl q5tar llfactorial int64 3shan yb2a akbr 7ga w unsigned 3shan l factorial positive
typedef int TIndex;
typedef size_t TOrdre;
typedef __int64 TFact;
template<TOrdre ORD> class TPerm
{
  TIndex IPerm;
  static const TFact IPermMax; //initialiser au factoriel(ordre)
  static TFact Fact(int n) {
    if (n < 0) { return 0; }//not defined for negative numbers
    if (n == 0 || n == 1) { return 1; } //0! = 1! = 1

    TFact result = 1;
    for (int i = 2; i <= n; ++i) { result *= i; }

    return result;
	}
public:
  
  //static permutation index vs array methods 
  static void Idx2Tab(TIndex _IPerm, TIndex (&Tab)[ORD])//pass tab by ref
  {
	TIndex ofs,Tmp;
	for(int i=0;i<ORD;++i){ Tab[i]=i; }
	for(int i=0;i<ORD;++i){
	  ofs=_IPerm/Fact((ORD-i-1));
	  Tmp = Tab[i+ofs];
	  for (int j = i + ofs; j > i; --j) { //decalage
			if (j < ORD) {
				Tab[j] = Tab[j - 1];
			}
		}
	  Tab[i] = Tmp;
	  _IPerm = _IPerm % Fact((ORD-i-1));
	}
  }

  static TIndex Tab2Idx(TIndex (&Tab)[ORD])
  {
	TIndex IPerm = 0;
	for(int i=0;i<ORD;++i){
		IPerm+=Tab[i]*Fact((ORD-i-1));
		for (int j = i + 1; j < ORD; ++j) {
            if (Tab[j] > Tab[i]) {
                --Tab[j];
            }
		}
	}
	return IPerm;
  }
  
  //constructors
  TPerm(TIndex _IPerm=0):IPerm(_IPerm){}
  TPerm(TIndex (&Tab)[ORD]):IPerm(Tab2Idx(Tab)){}

  //getters
  TIndex GetIdx(){ return IPerm; }
  TFact MaxIdx(){ return IPermMax; }

  //operators ++
  void Next(){IPerm<IPermMax?IPerm++:IPerm=0;}
  //pre-incrementation
  TPerm& operator ++() { 
	Next(); return *this;
  }
  //post-incrementation
  TPerm operator ++(int) { 
	TPerm p(*this); Next();
	return p;
  }

  std::ostream& Show(std::ostream& os) const{
    TIndex TAB[ORD];
    os << "ordre = " << ORD << ", index = " << IPerm;
	Idx2Tab(IPerm,TAB);
	os<<", Table = {";
	for(int i=0;i<ORD;i++){
		os<<TAB[i];
		(i==ORD-1)? os<<"}":os<<",";
	}
    return os << std::endl;
  }

  TPerm& operator *=(const TPerm& pr){
	  TIndex tabL[ORD],tabR[ORD],tabLcopy[ORD];
	  Idx2Tab(IPerm,tabL);
	  Idx2Tab(IPerm,tabLcopy);
	  Idx2Tab(pr.IPerm,tabR); 
	  for (int i=0;i<ORD;++i)
	  {
		tabL[i]=tabLcopy[tabR[i]];
	  }
	  IPerm=Tab2Idx(tabL);
	  return *this;
	}
  TPerm operator *(const TPerm& pr) const {
		return TPerm(*this) *= pr;
	}
  // racine d'ordre N de l'identité?
  template<TIndex N> bool racineID() const {
    TPerm<ORD> id;
    for (TIndex i = 1; i <= N; ++i) {
      id *= *this;
      if (id.GetIdx() == 0) { return true; }// La permutation est une racine d'ordre N de l'identité
      }
    return false;
  }
  std::vector<TIndex> PermuteVect(const std::vector<TIndex>& V1,TIndex _IPerm) const {
    if (V1.size() != ORD) {
      throw "Vector size != permutation order";
    }
    TIndex tab[];
	Idx2Tab(_Perm,tab);
	size_t size = sizeof(tab) / sizeof(tab[0]);
    std::vector<TIndex> V2(tab, tab + size);

    return V2;
  }

};

template<TOrdre ORD> const TFact TPerm<ORD>::IPermMax = TPerm<ORD>::Fact(ORD); // Specialization for IPermMax static const

template <TOrdre ORD>
inline std::ostream& operator<<(std::ostream& os, const TPerm<ORD>& p) { return p.Show(os); }