// Matrix of complex numbers 
// nrComplex class holds 2 float variables representing the real part and the imaginary part
// mMatrix class holds 2 int variables represting the rows and columns and has a double pointer of type nrComplex represiting the matrix of complex numbers
// Addition and multiplying of the matrixes is made using the "+" and "*" operators by overloading them. They are WIP as the rules for the operations are missing (very simple fix)
// Matrici de numere complexe
// Clasa nrComplex are doua variable de tip float care reprezinta partea reala si partea imaginara
// Clasa mMatrix are doua variable intregi care reprezinta nr de rows si columns si o un dublu pointer de tip nrComplex care reprezinta matricea de nr
// Adunarea si inmultirea matricei se face prin operatorii overloaded "+" si "*". Mai trebuiesc adaugate exceptiile pentru adunare si inmultire la operatori


#include <iostream>
#include <fstream>

using namespace std;

class nrComplex
{
	float mReala, mImaginara;
public:
	nrComplex();
	nrComplex(float, float);
	float getReal();
	float getImaginara();
	void setReal(float real);
	void setImaginar(float imaginar);

	nrComplex operator+ (nrComplex const & tmp); // overload + operator
	nrComplex operator* (nrComplex const & tmp); // overload * operator 
	
	friend std::ifstream& operator>>(std::ifstream& input, nrComplex& tmp) // overload >> operator 
	{
		input >> tmp.mReala >> tmp.mImaginara;
		return input;
	}

	friend std::ostream& operator<<(std::ostream& output, const nrComplex& tmp) // overload << operator
	{
		output << "( " << tmp.mReala << " , i" << tmp.mImaginara << " ) ";
		return output;
	}
	
	friend class mMatrix;
};

nrComplex::nrComplex() // default constrcutor 
{
	mReala = 0;
	mImaginara = 0;
}

nrComplex::nrComplex(float a, float b) // overloaded constructor 
{
	mReala = a;
	mImaginara = b;
}

float nrComplex::getImaginara()
{
	return this->mImaginara;
}

float nrComplex::getReal()
{
	return this->mReala;
}

void nrComplex::setImaginar(float imaginar)
{
	this->mImaginara = imaginar;
}

void nrComplex::setReal(float real)
{
	this->mReala = real;
}

nrComplex nrComplex::operator+ (nrComplex const& tmp)
{
	nrComplex res;
	res.mReala = this->mReala + tmp.mReala;
	res.mImaginara = this->mImaginara + tmp.mImaginara;
	
	return res;
}

nrComplex nrComplex::operator* (nrComplex const& tmp)
{
	nrComplex res;
	res.mReala = this->mReala * tmp.mReala;
	res.mImaginara = this->mImaginara * tmp.mImaginara;
	return res;
}

class mMatrix
{
	int row, column;
	nrComplex **matrice;

public:
	mMatrix() = default;
	mMatrix(int rows, int columns);
	int getRow();
	int getColumn();



	mMatrix operator+ (mMatrix const& tmp); // overload + operator
	mMatrix operator* (mMatrix const& tmp); // overload * operator 

	friend std::ifstream& operator>>(std::ifstream& input, const mMatrix& tmp) // overload >> operator 
	{
		for (int i = 0; i < tmp.row; i++)
			for (int j = 0; j < tmp.column; j++)
				input >> tmp.matrice[i][j];

		return input;
	}

	friend std::ostream& operator<<(std::ostream& output, const mMatrix& tmp) // overload << operator
	{
		for (int i = 0; i < tmp.row; i++)
		{
			output << "| ";
			for (int j = 0; j < tmp.column; j++)
				output << tmp.matrice[i][j];
			output << "|\n";
		}
			
		
		return output;
	}



};

mMatrix::mMatrix(int rows, int columns)
{
	this->row = rows;
	this->column = columns;
	matrice = new nrComplex * [this->row];
	for (int i = 0; i < this->row; i++)
		matrice[i] = new nrComplex[this->column];


}

int mMatrix::getRow()
{
	return this->row;
}
int mMatrix::getColumn()
{
	return this->column;
}

mMatrix mMatrix::operator+ (mMatrix const& tmp) // adunarea matricei 
{
	mMatrix res(row, column);
	for (int i = 0; i < row; i++)
		for (int j = 0; j < column; j++)
			res.matrice[i][j] = this->matrice[i][j] + tmp.matrice[i][j];

	return res;
}

mMatrix mMatrix::operator* (mMatrix const& tmp) // inmultirea matricei
{
	mMatrix res(row, tmp.column);
	for(int i = 0 ; i < res.row; i++)
		for (int j = 0; j < res.column; j++)
		{
			for (int l = 0; l < res.column; l++)
				res.matrice[i][j] = res.matrice[i][j] + matrice[i][l] * tmp.matrice[l][j];
		}


	return res;

}

mMatrix* reading(int& mNumber)
{
	ifstream mFile;
	mFile.open("matrix.in");

	mFile >> mNumber;
	mMatrix* _matrix;
	_matrix = new mMatrix[mNumber];

	for (int i = 0; i < mNumber; i++)
	{
		int rowT, colT;
		mFile >> rowT >> colT;

		mMatrix tmp(rowT, colT);
		mFile >> tmp;
		_matrix[i] = tmp;
	}
	return _matrix;
}

void print(mMatrix* tmp, int number)
{
	for (int i = 0; i < number; i++)
	{
		cout << tmp[i] << "\n";
	}
}

int main()
{
	int mNumber;
	mMatrix* _matrix;
	_matrix = reading(mNumber);
	print(_matrix, mNumber);
	cout << "Adition: \n";
	cout << _matrix[0] + _matrix[2];
	cout << "\nMultiplying: \n";
	cout << _matrix[0] * _matrix[2];
	return 0;
}
