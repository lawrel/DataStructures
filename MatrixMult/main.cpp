#include <iostream>
#include <fstream>
#include <cmath>
#include <cassert>
#include "Matrix.h"

#define __EPSILON 0.0000000001 //Need this to compare doubles because representation.

void SimpleTest(); //Some basic tests
void StudentTest(); //Write your own test cases here
void ExtraCreditTest(); //Write this if you write resize()


//Function to test a ton of matrices at once.
void BatchTest(double start, double step, unsigned int rows, unsigned int cols,
               unsigned int num);

//Quick function that returns if two doubles are very similar to each other.
bool double_compare(double a, double b);


int main(){
	SimpleTest();
	std::cout << "Completed all simple tests." << std::endl;

	//Uncomment this to allocate a lot of 100x100 matrices so leaks will be bigger.
	/*
	BatchTest(100,0.1,100,100,50);
	std::cout << "Completed all batch tests." << std::endl;
	*/

	StudentTest();
	std::cout << "Completed all student tests." << std::endl;

	//Uncomment this if you write the resize() function.
	/*
	ExtraCreditTest());
	std::cout << "Completed all student extra credit tests." << std::endl;
	*/
	return 0;
}

void SimpleTest(){  //well behaved getrow/read after
	//Default constructor
	/*Matrix m1;
	assert(m1.num_rows() == 0 && m1.num_cols() == 0);

	//Copy constructor
	Matrix m2(3,4,0);
	assert(m2.num_rows() == 3 && m2.num_cols() == 4);

	Matrix m2_copy(m2);
	assert(m2_copy.num_rows() == 3 && m2_copy.num_cols() == 4);
	m2_copy.set(1,1,27);
	double d0;
	assert(m2.get(1,1,d0));
	assert(double_compare(d0,0.0));
	assert(m2_copy.get(1,1,d0));
	assert(double_compare(d0,27));

	//Equality and Inequality
	Matrix m3;
	assert(m1 == m3);
	assert(m1 != m2);

	//Printing
	std::cout << "Empty matrix:";
	std::cout << m1 << std::endl;

	std::cout << "Zeroed 3x4 matrix:";
	std::cout << m2 << std::endl;

	std::cout << "One after the other:";
	std::cout << m1 << m2 << std::endl;

	//Set & get
	Matrix m5(4,4,2);
	Matrix m6(4,4,12);
	assert(m6.set(2,1,7));
	assert(m6.set(3,3,11));
	double d1;
	assert(m6.get(2,1,d1));
	assert(d1==7);

	//Addition
	std::cout << "Adding m5 and m6" << std::endl;
	std::cout << m5 << m6 << std::endl;

	Matrix m7;
	m7 = m5;
	Matrix m8(m5);
	assert(m7 == m8);
	
	assert(m7.add(m6));
	std::cout << "The result" << std::endl;
	std::cout << m7 << std::endl;
	
	std::cout<<"Subtracting m5 from m6"<<std::endl;
	assert(m6.subtract(m5));
	std::cout<<"The result:"<<std::endl<<m6<<std::endl;
	
	std::cout<<"Multiply m5 by 5"<<std::endl;
	m5.multiply_by_coefficient(5);
	std::cout<<"The result:"<<std::endl<<m5<<std::endl;
	
	std::cout<<"Swap rows 1 and 2 in m7:"<<endl;
	assert(m7.swap_row(1,2));
	std::cout<<"The result:"<<std::endl<<m7<<std::endl;
	
	double* r1 = NULL;
	r1 = m7.get_col(1);
	assert(r1[0] == 14 && r1[1] == 9);

	delete [] r1;
	
	std::cout<<"Transpose Square Matrix m6:"<<std::endl;
	std::cout<<"BEFORE:"<<m6<<std::endl;
	m6.transpose();
	std::cout<<"AFTER: "<<m6<<std::endl;
	
	std::cout<<"Transpose 3x4 Matrix m2:"<<std::endl;
	std::cout<<"BEFORE:"<<m2<<std::endl;
	m2.transpose();
	std::cout<<"AFTER: "<<m2<<std::endl; */
	
	//Checks to make sure quarter() creates the right size
	//quadrants, ignoring contents for now
	Matrix m9(3,3,2);
	Matrix m10(5,4,3);
	Matrix m11(5,5,4);
	Matrix* ma1 = NULL;
	Matrix* ma2 = NULL;
	Matrix* ma3 = NULL;
	ma1 = m9.quarter();
	ma2 = m10.quarter();
	ma3 = m11.quarter();
	cout<<ma1[0];
	cout<<ma2[0];
	cout<<ma3[0];
	delete [] ma1;
	delete [] ma2;
	delete [] ma3;
}
//Write your own test cases here
void StudentTest(){

}

//Write this if you write resize()
void ExtraCreditTest(){

}


////////////////Utility functions//////////////////////

/*  Function that quickly populates a rows x cols matrix with values from     
 *  start in increments of step. Does this num_times times.
 */
void BatchTest(double start, double step, unsigned int rows, unsigned int cols,
               unsigned int num){
	Matrix* m_arr = new Matrix[num];
	for(unsigned int i=0; i<num; i++){
		m_arr[i] = Matrix(rows,cols,0.0);
		unsigned int curr_elem = 0;
		for(unsigned int j=0; j<rows; j++){
			for(unsigned int k=0; k<rows; k++){
				m_arr[i].set(j,k,start+(step*curr_elem));
				curr_elem++;
			}
		}
	}
	delete [] m_arr;
}

//Quick function that returns if two doubles are very similar to each other.
bool double_compare(double a, double b){
	return (fabs(a-b) < __EPSILON);
}