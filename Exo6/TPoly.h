#ifndef _POLY_
#define _POLY_
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <iomanip>
#include <fstream>

template <typename TCoef, unsigned short MAX_SZ = 256>
class TPoly
{
unsigned char ordre;
TCoef coeff[MAX_SZ];

public:
    TPoly(TCoef a = 0, TCoef b = 0, TCoef c = 0, TCoef d = 0, TCoef e = 0) {
		ordre = 4;
		coeff[0]=a;coeff[1]=b;coeff[2]=c;coeff[3]=d;coeff[4]=e;
        while (ordre > 0 && coeff[ordre] == 0) { //check consecutive 0s
            ordre--;
        }
    }

    TPoly(int ord, const TCoef* coeffs) {
        ordre = ord;
        for (int i = 0; i <= ordre; i++) {
            coeff[i] = coeffs[i];
        }
    }

	TCoef operator()(TCoef x) const {
        TCoef result = 0;
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
	TPoly& operator+=(const TPoly& other) {
		int maxOrdre = (ordre > other.ordre)? ordre : other.ordre;
        for (int i = 0; i <= maxOrdre; i++) {
			if (i < other.ordre || maxOrdre==ordre) coeff[i] += other.coeff[i];
			else coeff[i] = other.coeff[i]; //make sure to add with 0 if not exist
        }
        ordre = maxOrdre;
        return *this;
    }

    TPoly operator+(const TPoly& other) const {
        return TPoly (*this)+= other;
    }
	TPoly& operator*=(const TPoly& other) {
        float resCoeff[MAX_SZ] = {0};
        for (int i = 0; i <= ordre; i++) {
            for (int j = 0; j <= other.ordre; j++) {
                resCoeff[i + j] += coeff[i] * other.coeff[j]; //distributivite
            }
        }
        ordre += other.ordre;
        for (int i = 0; i <= ordre; i++) {
            coeff[i] = resCoeff[i];
        }
        return *this;
    }

    TPoly operator*(const TPoly& other) const {
        return TPoly (*this)*= other;
    }

	TPoly& operator*=(TCoef num) { //right
        for (int i = 0; i <= ordre; ++i) {
            coeff[i] *= num;
        }
        return *this;
    }
	TPoly operator*(TCoef num) const {//right
        return TPoly (*this)*= num;
    }

};
template <typename TCoef>
inline std::ostream& operator<<(std::ostream& os, const TPoly<TCoef>& p) { return p.Show(os); }

template <typename TCoef>
inline TPoly<TCoef> operator*(float num, const TPoly<TCoef>& poly) {
    return TPoly<TCoef> (poly)*= num;
}

#endif