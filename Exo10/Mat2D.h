#ifndef _MAT2D_H_
#define _MAT2D_H_
#include <string> //important to (cout << string) not <string.h>
#include <iostream>
#include <iomanip>
#include <typeinfo.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <ctime>

//template random function to be called within the method
template<typename CElem>
CElem Rand(const CElem& vmin,const CElem& vmax){
	CElem rnd= (CElem)rand();
	//no `%` operator because it's not available for floats per example
	return (CElem)(vmin*rnd + vmax*(CElem(RAND_MAX)-rnd)) / CElem(RAND_MAX);
} 
//specialization for char
template<> char Rand(const char& vmin,const char& vmax){
	return vmin + char( rand()%int(vmax-vmin) );
}

//custom classe d'exception
class Mat2D_Exception{ 
public:
  size_t r,c;
  std::string MatTypeName;
  Mat2D_Exception(size_t _r,size_t _c,const char* _MatTypeName): r(_r),c(_c),MatTypeName(_MatTypeName){}
  void Show(std::ostream& os) const{
    os<< "Exception a l'acces de l'element ("<< r <<","<<c<<") dans la "<< MatTypeName<< "\n";
  }
};

inline std::ostream& operator<<(std::ostream& os, const Mat2D_Exception& e) {  e.Show(os); return os;  }

template <const size_t NR, const size_t NC, typename CElem>
class Mat2D
{
protected:
	static size_t width;
	static size_t precision;
	CElem tab[NR][NC];
public:
	
	//Exo5 A
	Mat2D( ) {} // constructeur sans paramètres qui ne fait rien
	//constructeur qui demande un CElem et remplit toute la matrice avec sa valeur
	Mat2D( const CElem& v){ 
		for (size_t r=0; r<NR; ++r){
			for (size_t c=0; c<NC; ++c){
				tab[r][c]=v;
			}
		}
	}
	// constructeur copie
	Mat2D(const Mat2D& other) {
        for (size_t r = 0; r < NR; ++r) {
            for (size_t c = 0; c < NC; ++c) {
				tab[r][c] = other(r, c); //other.tab[r][c]
            }
        }
    }
    // operateur d’attribution (copie)
    Mat2D& operator=(const Mat2D& other) {
        if (this != &other) { //not copying myself
            for (size_t r = 0; r < NR; ++r) {
                for (size_t c = 0; c < NC; ++c) {
                    tab[r][c] = other(r, c);
                }
            }
        }
        return *this;
    }

	////accesseurs : version unsafe mais rapide
	//CElem& operator()(size_t r, size_t c) { return tab[r][c]; } //lw hy5rog mn el matrix lmfrod a5leeh safe flexecution
	//const CElem& operator()(size_t r, size_t c) const { return tab[r][c]; }

	////accesseurs : version safe without exception
	//CElem& operator()(size_t r, size_t c) { return tab[r<NR?r:NR-1][c<NC?c:NC-1]; } //lw hy5rog mn el matrix lmfrod a5leeh safe flexecution
	//const CElem& operator()(size_t r, size_t c) const { return tab[r<NR?r:NR-1][c<NC?c:NC-1]; }

    //accesseurs : version exception
	CElem& operator()(size_t r, size_t c) {
    if (r>=NR || c>= NC) throw Mat2D_Exception(r,c,typeid(*this).name()) ;
    return tab[r][c];
	}
	const CElem& operator()(size_t r, size_t c) const {
    if (r>=NR || c>= NC) throw int(2);
    return tab[r][c];
	}

	void Rand(const CElem& vmin, const CElem& vmax) //entre vmin to vmax-1 avec template Rand() and its specializations
	{
		static bool initialized = false; //making sure that it's feeded only ONE time.
		if (!initialized) {
			srand(static_cast<unsigned>(time(0)));//static_cast<unsigned> to remove warning of perte possible de donnees
			initialized = true;
		}
		for (size_t r = 0; r < NR; ++r) {
			for (size_t c = 0; c < NC; ++c) {
				tab[r][c] = ::Rand(vmin,vmax); 
			}
		}
	}

	//Exo5 B
	void Show(std::ostream& os, size_t w = width, size_t p = precision) const {
		os << "Matrice " << NR << " x " << NC << " de type " << typeid(CElem).name() << " @=" << this << ":\n";
		for (size_t r = 0; r < NR; ++r) {
			for (size_t c = 0; c < NC; ++c) {
				os << std::setw(w) << std::fixed << std::setprecision(p) << tab[r][c] << " ";
			}
			os << std::endl;
		}
	}
	// Setter for printing width
	static void SetW(size_t w) { width = w; }
    // Setter for precision
    static void SetPrec(size_t p) { precision = p; }
	
	//Exo5 D
	//Transposing without modifying the original 
	Mat2D<NC, NR, CElem> Transpose() const {
        Mat2D<NC, NR, CElem> m;
        for (size_t r = 0; r < NC; ++r) {
            for (size_t c = 0; c < NR; ++c) {
                m(r, c) = tab[c][r]; //car la classe retourne n'est pas notre classe donc c'est protege,m.tab[r][c] private member donc use public operator ()
			}
        }
        return m;
    }
	Mat2D<NC, NR, CElem> operator~() const { return Transpose(); }

	//Exo5 F //Exo5 D when removing UElem
	//sum of 2 matricies per example int + float so i should have UElem different from CElem and can be casted to CElem
	template <typename UElem> 
    Mat2D<NR, NC, CElem> operator+(const Mat2D<NR, NC, UElem>& m) const {
        Mat2D<NR, NC, CElem> result;
        for (size_t r = 0; r < NR; ++r) {
            for (size_t c = 0; c < NC; ++c) {
                result(r, c) = tab[r][c] + static_cast<CElem>(m(r, c));
            }
        }
        return result;
    }
	//sum with one element that can be casted to CElem
	template <typename UElem> 
    Mat2D<NR, NC, CElem> operator+(const UElem& m) const {
        Mat2D<NR, NC, CElem> result;
        for (size_t r = 0; r < NR; ++r) {
            for (size_t c = 0; c < NC; ++c) {
                result(r, c) = tab[r][c] + CElem(m);
            }
        }
        return result;
    }

	//Exo5 E
	template <const size_t NX>
	Mat2D<NR, NX, CElem> operator*(const Mat2D<NC, NX, CElem>& m) const {
		Mat2D<NR, NX, CElem> result;
		for (size_t r = 0; r < NR; ++r) {
			for (size_t c = 0; c < NX; ++c) {
				result(r, c) = 0;
				for (size_t k = 0; k < NC; ++k) {
					result(r, c) += tab[r][k] * m(k, c);
				}
			}
		}
		return result;
	}

};

template <const size_t NR, const size_t NC, typename CElem>
size_t Mat2D<NR, NC, CElem>::width = 10;

template <const size_t NR, const size_t NC, typename CElem>
size_t Mat2D<NR, NC, CElem>::precision = 3;

template <const size_t NR, const size_t NC, typename CElem>
inline std::ostream& operator<<(std::ostream& os, const Mat2D<NR, NC, CElem>& mat) {
    mat.Show(os);
    return os;
}

#endif //_MAT2D_H_