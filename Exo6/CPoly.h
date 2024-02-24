#ifndef _CPOLY_
#define _CPOLY_
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <iomanip>
#include <fstream>

class CPoly
{
static const unsigned short MAX_SZ = 256;

unsigned char ordre;
float coeff[MAX_SZ];

public:
	// Constructeur 5 coeffs
    CPoly(float a = 0, float b = 0, float c = 0, float d = 0, float e = 0) {
		ordre = 4;
		coeff[0]=a;coeff[1]=b;coeff[2]=c;coeff[3]=d;coeff[4]=e; //avoiding unneccessary temp array like in dynamic allocation version 
        while (ordre > 0 && coeff[ordre] == 0) { //check consecutive 0s
            ordre--;
        }
    }
	// Constructeur ordre,tableau
    CPoly(int ord, const float* coeffs) {
        ordre = ord;
        for (int i = 0; i <= ordre; i++) {
            coeff[i] = coeffs[i];
        }
    }

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
	CPoly& operator+=(const CPoly& other) {
		int maxOrdre = (ordre > other.ordre)? ordre : other.ordre;
        for (int i = 0; i <= maxOrdre; i++) {
			if (i < other.ordre || maxOrdre==ordre) coeff[i] += other.coeff[i];
			else coeff[i] = other.coeff[i]; //make sure to add with 0 if not exist
        }
        ordre = maxOrdre;
        return *this;
    }

    CPoly operator+(const CPoly& other) const {
        return CPoly (*this)+= other;
    }
	CPoly& operator*=(const CPoly& other) {
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

    CPoly operator*(const CPoly& other) const {
        return CPoly (*this)*= other;
    }

	CPoly& operator*=(float num) { //right
        for (int i = 0; i <= ordre; ++i) {
            coeff[i] *= num;
        }
        return *this;
    }
	CPoly operator*(float num) const {//right
        return CPoly (*this)*= num;
    }

};
inline std::ostream& operator<<(std::ostream& os, const CPoly& p) { return p.Show(os); }
inline CPoly operator*(float num, const CPoly& poly) {
    return CPoly (poly)*= num;
}

#endif