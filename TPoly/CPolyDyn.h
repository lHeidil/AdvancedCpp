#ifndef _CPolyDyn_
#define _CPolyDyn_
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <iomanip>
#include <fstream>

class CPolyDyn
{
	unsigned char ordre;
	float* coeff;

	void Clean(){
		if(ordre){
			delete[] coeff; 
			coeff = NULL;
		}
	}
	void Implementation(const float* coeffs){
		if (ordre){
			coeff = new float[ordre+1];
			for (int i = 0; i <= ordre; i++) {
				coeff[i] = coeffs[i];
			}
		}
	}
public:
	unsigned Ordre(){ return unsigned(ordre);}
	// Constructeur 5 coeffs
    CPolyDyn(float a = 0, float b = 0, float c = 0, float d = 0, float e = 0) {
		ordre = 4;
		float tempcoeff[5] = {a, b, c, d, e}; //so that i can loop on params
		while (ordre > 0 && tempcoeff[ordre] == 0) { //check consecutive 0s
            ordre--;
        }	
		Implementation(tempcoeff);
    }

	// Constructeur ordre,tableau
	CPolyDyn(int ord, const float* coeffs): ordre(ord){
		Implementation(coeffs);
    }
	// Constructeur par copie
	CPolyDyn(const CPolyDyn& p): ordre(p.ordre) {
		Implementation(p.coeff);
	}
	// Surcharge de l'opérateur d'attribution 
	CPolyDyn& operator=(const CPolyDyn& p){
        if(this != &p) {
			// Liberation de la memoire
            Clean();
            // Copiage des attributs
			ordre = p.ordre;
			// Implementation
			Implementation(p.coeff);
        }
        return *this;
    }
	// Destructeur
	~CPolyDyn() { Clean(); }
	
	float operator()(float x) const {
        float result = 0.0;
        for (int i = 0; i <= ordre; ++i) {
            result += coeff[i] * pow(x, ordre - i);
        }
        return result;
    }

    std::ostream& Show(std::ostream& os) const{
        os << "Poly ordre " << unsigned(ordre) << ": ";
        for (int i = ordre; i >= 0; i--) {
            os << coeff[ordre-i] << "x^" << ordre - i;
			if(i!=0) os<<" + ";
        }
       return os << std::endl;
    }
	
	CPolyDyn& operator+=(const CPolyDyn& other) {
		CPolyDyn resPoly((ordre > other.ordre)? ordre : other.ordre,(ordre > other.ordre)? coeff : other.coeff); //= le plus grand
		int minOrdre = (ordre < other.ordre)? ordre : other.ordre;
        for (int i = 0; i <= minOrdre; i++) { //addition avec le petit en gardant le reste comme il est copie du grand
			if(ordre > other.ordre) resPoly.coeff[i] += other.coeff[i];
			else resPoly.coeff[i] += coeff[i];
			}
		*this = resPoly; //copier le resultat pour retourner
        return *this;
    }
	CPolyDyn operator+(const CPolyDyn& other) const {
        return CPolyDyn (*this)+= other;
    }
	CPolyDyn& operator+=(const int num) {
		coeff[0]+=num;
        return *this;
    }
	CPolyDyn operator+(const int num) const {
			return CPolyDyn (*this)+= num;
		}

	CPolyDyn& operator*=(const CPolyDyn& other) {
		float nll[256]={0}; //isn't there a better way ?
        CPolyDyn resPoly(ordre+other.ordre,nll);
        for (int i = 0; i <= ordre; i++) {
            for (int j = 0; j <= other.ordre; j++) {
                resPoly.coeff[i + j] += coeff[i] * other.coeff[j]; //distributivite
            }
        }
        *this = resPoly; //copier le resultat pour retourner
        return *this;
    }
    CPolyDyn operator*(const CPolyDyn& other) const {
        return CPolyDyn (*this)*= other;
    }

	CPolyDyn& operator*=(float num) { //right
        for (int i = 0; i <= ordre; ++i) {
            coeff[i] *= num;
        }
        return *this;
    }
	CPolyDyn operator*(float num) const { //right
        return CPolyDyn (*this)*= num;
    }

};
inline std::ostream& operator<<(std::ostream& os, const CPolyDyn& p) { return p.Show(os); }
inline CPolyDyn operator*(float num, const CPolyDyn& poly) {
    return CPolyDyn (poly)*= num;
}

#endif