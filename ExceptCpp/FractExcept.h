 #ifndef _FRACT_
#define _FRACT_
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <iomanip>
#include <fstream>

namespace FractExcept {
// une fraction entière avec b>0 et a,b premiers entre eux
class CFract
{
	int a,b;
	/*const int c;*/
	void Norm()
  {
	  if (b<0)
		  b = -b;

	  if (b==0){
		  b=1;}

	   int x=a;
	   int y=b;
	   int r;


    while(y != 0)
    {
      r = x%y;
      x = y;
      y = r; 
    }
   
	if (x != 1){
		a = a/x;
	    b = b/x;
	}
    
  }
public:
	CFract(int _a=0, int _b=1):a(_a),b(_b?_b:1) {Norm();}

	std::ostream& Affiche(std::ostream& os) const{
		return os<<"("<<a<<","<<b<<")" ;
	}

	CFract& MultTo(const CFract& f){
		a = a*(f.a);
		b = b*(f.b);
		Norm();
		return *this;
	}


	const int& GetA() const{return a;}
	const int& GetB() const{return b;}
	void SetA(int _a) {a=_a; Norm();}
	void SetB(int _b) { if(b!=0) {b=_b; Norm();} }


	CFract& operator *=(const CFract& f){
		return MultTo(f);
	}


	CFract& AddTo(const CFract& f){
		a = a*f.b+b*f.a;
		b = b*f.b;
		Norm();
		return *this;
	}

	CFract& operator +=(const CFract& f){
		return AddTo(f);
	}

	CFract& SubTo(const CFract& f){
		a = a*f.b-b*f.a;
		b = b*f.b;
		Norm();
		return *this;
	}

	CFract& operator -=(const CFract& f){
		return SubTo(f);
	}

	CFract& DivTo(const CFract& f){
		if (f.a==0){a= 0; b= 1; return *this;};
		a = a*f.b;
		b = b*f.a;
		Norm();
		return *this;
	}

	CFract& operator /=(const CFract& f){
		return DivTo(f);
	}

	////CFract& operator /=(const CFract& f){
	////	TODO : ???
	////}


	///*const*/ CFract operator +(const CFract& f) const {
	//	CFract res(a,b);
	//	return res+=f;
	//}

	///*const*/ CFract operator +(const CFract& f) const {
	//	CFract res(a,b);
	//	return res.AddTo(f);
	//}

	///*const*/ CFract operator +(const CFract& f) const {
	//	CFract res(*this);
	//	return res+=f;
	//}

	///*const*/ CFract operator +(const CFract& f) const {
	//	CFract res(*this);
	//	return res.AddTo(f);
	//}

	/////*const*/ CFract operator +(const CFract& f) const {
	////	return *this+=f
	////}  non ne fonctionne pas

	//CFract operator +(const CFract& f) const {
	//	return CFract(a*f.b+b*f.a, b*f.b); // oui
	//}

	//CFract operator +(const CFract& f) const {
	//	return CFract(a, b) += f;
	//}


	//CFract operator +(const CFract& f) const {
	//	return CFract(f)+=*this;
	//}

	//CFract operator +(const CFract& f) const {
	//	return CFract(a, b).AddTo(f);
	//}

	//CFract operator +(const CFract& f) const {
	//	return *this+f);
	//} // Appel récursif avec l'opérateur qu'on est entrain de définir! A NE JAMAIS FAIRE! NON NON NON!


	CFract operator +(const CFract& f) const {
		return CFract(*this) += f;
	}

	CFract operator *(const CFract& f) const {
		return CFract(*this) *= f;
	}

	CFract operator -(const CFract& f) const {
		return CFract(*this) -= f;
	}

	CFract operator /(const CFract& f) const {
		return CFract(*this) /= f;
	}

	//CFract operator /(const CFract& f) const {TODO}
	// operateurs unaires

	//CFract operator -() const {
	//	return -(*this); //NOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
	//}

	CFract operator -() const {
		return CFract(-a,b);
	}

	CFract operator +() const {
		return CFract(a,b);
	}

	CFract operator !() const {
		return CFract(a,b)/ CFract(a*a, b*b);
	}

	CFract& operator ~() {
		return DivTo(CFract(a*a, b*b));
	}


	// TODO: +, ! return la fraction inversée (ATTENTION au 0), ~ inverse la fraction *this
	// operateurs bool, >, >=, <, <=, !=

	bool operator ==(const CFract& f) const {
		return a==f.a && b==f.b;
	}

	bool operator !=(const CFract& f) const {
		return !(*this==f);
	}

	bool operator >(const CFract& f) const {
		return a>f.a && b<=f.b;
	}

	bool operator >=(const CFract& f) const {
		return a>=f.a && b<=f.b;
	}

	bool operator <(const CFract& f) const {
		return !(*this >= f);
	}

	bool operator <=(const CFract& f) const {
		return !(*this > f);
	}


	//operateurs pre/post incre/decrementation (voir transparent page 109)

	//CFract& operateur ++() {
	//	return *this += CFract(1,1);
	//}


	CFract& operator ++() {
		return *this += 1;
	}

	CFract operator ++(int) {
		CFract f(*this);
		 ++*this;
		return f;
	}

	CFract& operator --() {
		return *this -= 1;
	}

	CFract operator --(int) {
		CFract f(*this);
		 --*this;
		return f;
	}

	//operateurs typecast

	//operator float() const {printf("CFract:::float\n"); return float(a)/b;}
	//operator double() const {printf("CFract:::double\n"); return double(a)/b;}



};

inline std::ostream& operator<<(std::ostream& os, const CFract& f) { return f.Affiche(os); }
}

#endif #ifndef _FRACT_
#define _FRACT_
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <iomanip>
#include <fstream>

namespace FractExcept {
// une fraction entière avec b>0 et a,b premiers entre eux
class CFract
{
	int a,b;
	/*const int c;*/
	void Norm()
  {
	  if (b<0)
		  b = -b;

	  if (b==0){
		  b=1;}

	   int x=a;
	   int y=b;
	   int r;


    while(y != 0)
    {
      r = x%y;
      x = y;
      y = r; 
    }
   
	if (x != 1){
		a = a/x;
	    b = b/x;
	}
    
  }
public:
	CFract(int _a=0, int _b=1):a(_a),b(_b?_b:1) {Norm();}

	std::ostream& Affiche(std::ostream& os) const{
		return os<<"("<<a<<","<<b<<")" ;
	}

	CFract& MultTo(const CFract& f){
		a = a*(f.a);
		b = b*(f.b);
		Norm();
		return *this;
	}


	const int& GetA() const{return a;}
	const int& GetB() const{return b;}
	void SetA(int _a) {a=_a; Norm();}
	void SetB(int _b) { if(b!=0) {b=_b; Norm();} }


	CFract& operator *=(const CFract& f){
		return MultTo(f);
	}


	CFract& AddTo(const CFract& f){
		a = a*f.b+b*f.a;
		b = b*f.b;
		Norm();
		return *this;
	}

	CFract& operator +=(const CFract& f){
		return AddTo(f);
	}

	CFract& SubTo(const CFract& f){
		a = a*f.b-b*f.a;
		b = b*f.b;
		Norm();
		return *this;
	}

	CFract& operator -=(const CFract& f){
		return SubTo(f);
	}

	CFract& DivTo(const CFract& f){
		if (f.a==0){a= 0; b= 1; return *this;};
		a = a*f.b;
		b = b*f.a;
		Norm();
		return *this;
	}

	CFract& operator /=(const CFract& f){
		return DivTo(f);
	}

	////CFract& operator /=(const CFract& f){
	////	TODO : ???
	////}


	///*const*/ CFract operator +(const CFract& f) const {
	//	CFract res(a,b);
	//	return res+=f;
	//}

	///*const*/ CFract operator +(const CFract& f) const {
	//	CFract res(a,b);
	//	return res.AddTo(f);
	//}

	///*const*/ CFract operator +(const CFract& f) const {
	//	CFract res(*this);
	//	return res+=f;
	//}

	///*const*/ CFract operator +(const CFract& f) const {
	//	CFract res(*this);
	//	return res.AddTo(f);
	//}

	/////*const*/ CFract operator +(const CFract& f) const {
	////	return *this+=f
	////}  non ne fonctionne pas

	//CFract operator +(const CFract& f) const {
	//	return CFract(a*f.b+b*f.a, b*f.b); // oui
	//}

	//CFract operator +(const CFract& f) const {
	//	return CFract(a, b) += f;
	//}


	//CFract operator +(const CFract& f) const {
	//	return CFract(f)+=*this;
	//}

	//CFract operator +(const CFract& f) const {
	//	return CFract(a, b).AddTo(f);
	//}

	//CFract operator +(const CFract& f) const {
	//	return *this+f);
	//} // Appel récursif avec l'opérateur qu'on est entrain de définir! A NE JAMAIS FAIRE! NON NON NON!


	CFract operator +(const CFract& f) const {
		return CFract(*this) += f;
	}

	CFract operator *(const CFract& f) const {
		return CFract(*this) *= f;
	}

	CFract operator -(const CFract& f) const {
		return CFract(*this) -= f;
	}

	CFract operator /(const CFract& f) const {
		return CFract(*this) /= f;
	}

	//CFract operator /(const CFract& f) const {TODO}
	// operateurs unaires

	//CFract operator -() const {
	//	return -(*this); //NOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
	//}

	CFract operator -() const {
		return CFract(-a,b);
	}

	CFract operator +() const {
		return CFract(a,b);
	}

	CFract operator !() const {
		return CFract(a,b)/ CFract(a*a, b*b);
	}

	CFract& operator ~() {
		return DivTo(CFract(a*a, b*b));
	}


	// TODO: +, ! return la fraction inversée (ATTENTION au 0), ~ inverse la fraction *this
	// operateurs bool, >, >=, <, <=, !=

	bool operator ==(const CFract& f) const {
		return a==f.a && b==f.b;
	}

	bool operator !=(const CFract& f) const {
		return !(*this==f);
	}

	bool operator >(const CFract& f) const {
		return a>f.a && b<=f.b;
	}

	bool operator >=(const CFract& f) const {
		return a>=f.a && b<=f.b;
	}

	bool operator <(const CFract& f) const {
		return !(*this >= f);
	}

	bool operator <=(const CFract& f) const {
		return !(*this > f);
	}


	//operateurs pre/post incre/decrementation (voir transparent page 109)

	//CFract& operateur ++() {
	//	return *this += CFract(1,1);
	//}


	CFract& operator ++() {
		return *this += 1;
	}

	CFract operator ++(int) {
		CFract f(*this);
		 ++*this;
		return f;
	}

	CFract& operator --() {
		return *this -= 1;
	}

	CFract operator --(int) {
		CFract f(*this);
		 --*this;
		return f;
	}

	//operateurs typecast

	//operator float() const {printf("CFract:::float\n"); return float(a)/b;}
	//operator double() const {printf("CFract:::double\n"); return double(a)/b;}



};

inline std::ostream& operator<<(std::ostream& os, const CFract& f) { return f.Affiche(os); }
}

#endif