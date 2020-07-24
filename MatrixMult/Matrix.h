#ifndef __Matrix_h_
#define __Matrix_h_
#include <iostream>
using namespace std;
//ALL FUNCTIONS DESCRIBED IN Matrix.cpp
class Matrix {
	public:
	//Constructors and Destructor
	Matrix();
	Matrix(unsigned int rows,unsigned int cols, double fill);
	Matrix(const Matrix &other);
	~Matrix();
	//Accessors and Modifier
	const unsigned int num_rows() const {return rows_;};
	const unsigned int num_cols() const {return cols_;};
	bool get(unsigned int row,unsigned int col, double &fill) const;
	bool set(unsigned int row,unsigned int col, double fill);
	void clear();
	//Operators
	void operator =(const Matrix &b);
	bool operator ==(const Matrix &b) const;
	bool operator !=(const Matrix &b) const;
	//Simple - MODIFIERS
	void multiply_by_coefficient(double coefficient);
	bool swap_row(unsigned int source, unsigned int target);
	void transpose();
	//Binary
	bool add(const Matrix &B);
	bool subtract(const Matrix &B);
	//Harder
	double* get_row(unsigned int row);
	double* get_col(unsigned int col);
	Matrix* quarter(); 
	//Extra Credit - comment out until all else is done
	void resize(unsigned int rows,unsigned int cols,double fill);
	private:
	
	double **data_;
	unsigned int rows_;
	unsigned int cols_;
};
//Output
ostream& operator<< (ostream& out, const Matrix& m);
#endif