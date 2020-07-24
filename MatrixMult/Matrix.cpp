#include "Matrix.h"
#include <iostream>
#include <stddef.h>
#include <cmath>
using namespace std;
Matrix::Matrix() { //initializes matrix when nothing defined
	data_ = NULL;
	rows_=0;
	cols_=0;
}
Matrix::Matrix(unsigned int rows,unsigned int cols, double fill) { //constructor
	if (rows == 0 || cols == 0) { //if rows or cols = 0, initialize to NULL matrix
		data_ = NULL;
		rows_ = 0;
		cols_ = 0;
	} else { //otherwise, create a dynamic 2D array to store data
	rows_ = rows;
	cols_ = cols;
	data_ = new double*[rows];
	for(unsigned int r=0; r<rows; r++) {
		data_[r] = new double[cols];
		for (unsigned int c=0; c<cols; c++) {
			data_[r][c] = fill; //put fill value in every slot
		}
	}
	}
}

Matrix::~Matrix() { //destructor
	clear();
}

Matrix::Matrix(const Matrix &other) { //copy constructor
	this->rows_ = other.rows_;
	this->cols_ = other.cols_;
	this->data_ = new double*[other.rows_]; //create new 2D array
	for(unsigned int r=0; r<this->rows_; r++) {
		this->data_[r] = new double[other.cols_];
		for (unsigned int c=0; c<this->cols_; c++) {
			this->data_[r][c] = other.data_[r][c];
		} //read all other's data in one by one and assign to same location
	} //in the copy
}
bool Matrix::get(unsigned int row,unsigned int col, double &fill) const{
	if (row<rows_&& col<cols_ && row>=0 && col>=0) {
		fill = data_[row][col];
		return true;
	}//if location is within the matrix, assign fill to its value and return true
	return false; //otherwise, do nothing, return false
}

bool Matrix::set(unsigned int row,unsigned int col, double fill) {
	if (row<rows_&& col<cols_ && row>=0 && col>=0) {
		data_[row][col] = fill;
		return true;
	} //if location within the matrix, replace the value with the fill passed in
	return false;
}

void Matrix::clear() { //CLEAR: DELETES ALL HEAP DATA
	for (unsigned int r = 0; r<rows_; r++) {
		delete [] data_[r]; //delete each row
	}
	delete [] data_; //delete array of rows
	data_=NULL;
	rows_ = 0;
	cols_ = 0;
}
void Matrix::operator =(const Matrix &other) {
	clear();
	//makes a copy of the other matrix same as copy constructor
	this->rows_ = other.rows_;
	this->cols_ = other.cols_;
	this->data_ = new double*[other.rows_];
	for(unsigned int r=0; r<this->rows_; r++) {
		this->data_[r] = new double[other.cols_];
		for (unsigned int c=0; c<this->cols_; c++) {
			this->data_[r][c] = other.data_[r][c];
		}
	}
}

bool Matrix::operator ==(const Matrix &b) const {
	if ((this->data_==NULL&&b.data_!=NULL) || (this->data_!=NULL&&b.data_==NULL)) {
	//if one is NULL but other is not, return false
		return false;
	}
	for(unsigned int r=0; r<rows_; r++) {
		for (unsigned int c=0; c<cols_; c++) {
			if(this->data_[r][c] != b.data_[r][c]) {
				return false; //check that each value in entire matrix equals the other
			}//if one value if off, return false
		}
	} //if the matrices pass all tests, they are equal
	return true;
}

bool Matrix::operator !=(const Matrix &b) const {
	//calls == and returns the opposite of it
	if (operator==(b)) {
		return false;
	}
	return true;
}

void Matrix::multiply_by_coefficient(double coefficient) {
	for(unsigned int r=0; r<rows_; r++) {
		for (unsigned int c=0; c<cols_; c++) {
			data_[r][c] *= coefficient;
		}//for each value in matrix, multiply by coefficient
	}
}
bool Matrix::swap_row(unsigned int source, unsigned int target) {
	if (data_!=NULL && source>=0 && target>=0 && target<rows_ && source<rows_) {
	//if data exists and both rows are valid, swap rows
		double temp;
		for (unsigned int c=0; c<cols_; c++) {
		//for each value in row, swap values
			temp = data_[source][c]; 
			data_[source][c] = data_[target][c];
			data_[target][c] = temp;
		}
		return true;
	}
	return false;
}
void Matrix::transpose() {
	unsigned int temprow = cols_; //save rows and columns 
	unsigned int tempcol = rows_; //swapped values for the new matrix
	double **p = new double* [cols_]; //create new pointer to 2D dynamic array
	for(unsigned int c=0; c<cols_; c++) {
		p[c] = new double[rows_];
		for (unsigned int r=0; r<rows_; r++) {
			p[c][r] = data_[r][c];
		} //set pointer's values to opposite of data's
	}
	clear(); //clear old data
	rows_ = temprow; //reassign row and col
	cols_ = tempcol;
	data_ = p; //make data point to swapped data
}
bool Matrix::add(const Matrix &B) {
	if (rows_==B.rows_&& cols_==B.cols_) { 
	//if matrices are same size, proceed to add
	for(unsigned int r=0; r<rows_; r++) {
		for (unsigned int c=0; c<cols_; c++) {
			data_[r][c] += B.data_[r][c];
		} //for each value in A, add value of B
	}
	return true;
}
return false;
}
bool Matrix::subtract(const Matrix &B) {
	//if matrices are same size, proceed to subtract
	if (rows_==B.rows_&& cols_==B.cols_) {
	for(unsigned int r=0; r<rows_; r++) {
		for (unsigned int c=0; c<cols_; c++) {
			data_[r][c] -= B.data_[r][c];
		} //for each value in A, subtract value of B
	}
	return true;
}
return false;
}
double* Matrix::get_row(unsigned int row) {
	//create new pointer
	double *p = NULL;
	if (row>=0&&row<rows_) {
	//if row within matrix, copy value to pointer
		p  = new double[cols_];
		for (unsigned int c=0; c<cols_; c++) {
			p[c] = data_[row][c];
		}
	}
	return p;
}
double* Matrix::get_col(unsigned int col) {
	double *p = NULL;
	if (col>=0&&col<cols_) {
	//if col within matrix, copy values to pointer
		p = new double[rows_];
		for (unsigned int r=0; r<rows_; r++) {
			p[r] = data_[r][col];
		}
	}
	return p;
}
Matrix* Matrix::quarter() {
	Matrix *p = new Matrix[4];
	unsigned int row_n,col_n; //number of rows and columns in quadrant
	if (rows_%2 != 0) { //if odd #of rows, round up size of quadrant's rows
		row_n = (rows_/2)+1;
	} else {
		row_n = (rows_/2);
	}
	if (cols_%2 != 0) { //if odd #of cols, round up size of quadrant's cols
		col_n = (cols_/2)+1;
	} else { 
		col_n = (cols_/2);
	}
	//create four matrices of row_n x col_n size
	for (unsigned int i=0; i<4;i++) {
		p[i] = Matrix(row_n,col_n,0);
	}
	//UPPER LEFT
	for(unsigned int r=0; r<(p[0].rows_); r++) {
		for (unsigned int c=0; c<(p[0].cols_); c++) {
			p[0].set(r,c,this->data_[r][c]);
		}
	}
	//UPPER RIGHT
	for(unsigned int r=0; r<(p[0].rows_); r++) {
		unsigned int j = col_n;
		for (unsigned int c=0; c<(p[0].cols_); c++) {
			p[1].set(r,c,this->data_[r][cols_-j]);
			j--;
		}
	}
	//LOWER LEFT
	unsigned int i = row_n;
	for(unsigned int r=0; r<(p[0].rows_); r++) {
		for (unsigned int c=0; c<(p[0].cols_); c++) {
			p[2].set(r,c,this->data_[rows_-i][c]);
		}
		i--;
	}
	// LOWER RIGHT
	i = row_n;
	for(unsigned int r=0; r<(p[0].rows_); r++) {
		unsigned int j = col_n;
		for (unsigned int c=0; c<(p[0].cols_); c++) {
			p[3].set(r,c,this->data_[rows_-i][cols_-j]);
			j--;
		}
		i--;
	}
	
	return p;
}
void Matrix::resize(unsigned int rows,unsigned int cols,double fill) {
	double **p = new double* [rows]; //create new pointer to 2D dynamic array
	for (unsigned int r=0; r<rows; r++) {
		p[r] = new double[cols];
	}
	//if new size is taller and wider
	if (rows>=rows_&&cols>=cols_) {
		for(unsigned int r=0; r<rows_; r++) {
			for (unsigned int c=0; c<cols_; c++) {
				p[r][c] = data_[r][c];
			} //fills with copied values
		}
		for(unsigned int r=rows_; r<rows; r++) {
			for (unsigned int c=0; c<cols; c++) {
				p[r][c] = fill;
			}//fills any added columns with fill
		}
		for(unsigned int r=0; r<rows; r++) {
			for (unsigned int c=cols_; c<cols; c++) {
				p[r][c] = fill;
			}//fills any added rows with fill
		}
	//if new size is shorter and thinner	
	} else if (rows<=rows_&&cols<=cols_) {
		for(unsigned int r=0; r<rows; r++) {
			for (unsigned int c=0; c<cols; c++) {
				p[r][c] = data_[r][c];
			}
		}
	//if new size is shorter but wider	
	} else if (rows<rows_&&cols>cols_) {
		for(unsigned int r=0; r<rows; r++) {
			for (unsigned int c=0; c<cols_; c++) {
				p[r][c] = data_[r][c];
			}
		}
		for(unsigned int r=0; r<rows; r++) {
			for (unsigned int c=cols_; c<cols; c++) {
				p[r][c] = fill;
			}
		}
	//if new size is taller but thinner	
	} else if (rows>rows_&&cols<cols_) {
		for(unsigned int r=0; r<rows_; r++) {
			for (unsigned int c=0; c<cols; c++) {
				p[r][c] = data_[r][c];
			}
		}
		for(unsigned int r=rows_; r<rows; r++) {
			for (unsigned int c=0; c<cols; c++) {
				p[r][c] = fill;
			}
		}
	}
	clear(); //clear old data
	rows_ = rows; //reassign row and col
	cols_ = cols;
	data_ = p;
}
ostream& operator<< (ostream& out, const Matrix& m) {
	//function to output a matrix
	out<<endl<<m.num_rows()<<" x "<<m.num_cols()<<" matrix:";
	out<<endl<<"[ ";
	for(unsigned int r=0; r<m.num_rows(); r++) {
		if (r!=0) {
			cout<<"  ";
		}
		for (unsigned int c=0; c<m.num_cols(); c++) {
			double val; //since data_ is private, each must be retreived using
			m.get(r,c,val); //get, then outputted
			out<<val<<" ";
		}
		if(r!=(m.num_rows()-1)) {
			cout<<endl; //if not the last row, end line
		}
	}
    out<<"]"<<endl;
	return out;
}