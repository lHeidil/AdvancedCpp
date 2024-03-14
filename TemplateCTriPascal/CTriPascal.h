#include <iostream>

template <typename TElem>
class CTriPascal {
private:
    TElem** triangle;
    int size;

public:
	CTriPascal(int _size):size(_size) {

        // memory allocation
        triangle = new TElem*[size + 1];
        for (int i = 0; i <= size; i++) {
            triangle[i] = new TElem[i + 1];
        }
		// here is the triangle
        for (int i = 0; i <= size; i++) {
            triangle[i][0] = 1;
            triangle[i][i] = 1;

            for (int j = 1; j < i; j++) {
                triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
            }
        }
    }

    ~CTriPascal() {
        // Libération de la mémoire important
        for (int i = 0; i <= size; i++) {
            delete[] triangle[i];
        }
        delete[] triangle;
    }
void resize(int newSize) {
        // Libération de la mémoire de l'ancien triangle
        for (int i = 0; i <= size; i++) {
            delete[] triangle[i];
        }
        delete[] triangle;

        size = newSize;

        // new triangle
        triangle = new TElem*[size + 1];
        for (int i = 0; i <= size; i++) {
            triangle[i] = new TElem[i + 1];
        }

        for (int i = 0; i <= size; i++) {
            triangle[i][0] = 1;
            triangle[i][i] = 1;

            for (int j = 1; j < i; j++) {
                triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
            }
        }
    }
	TElem* operator[](int row) const {
        return triangle[row];
	}
    TElem operator()(int row, int col) const {
        return triangle[row][col];
    }

	void Affiche(std::ostream& os) const {
		os<<"Triangle "<<" des elements de type "<<typeid(TElem).name()<<"\n\n";
        for (int i = 0; i <= size; ++i) {
            for (int j = 0; j <= i; ++j) {
                os << triangle[i][j] << " ";
            }
            os << std::endl;
        }
    }
};
