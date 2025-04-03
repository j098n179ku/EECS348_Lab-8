//matrix.cpp

#include <iostream>
#include <fstream>
#include <vector>
#include <string>


#include "matrix.hpp"

/*
    function definition was given by the EECS348 lab github,
    code under the function I needed help from chatgpt to figure out, as my implementation of the constructor was
    not the correct way of doing it
    this constructor creates an empty NxN matrix to be filled in later and added to,
    this is needed because there are multiple instances where a matrix needs to be
    made but cannot take any values yet
*/
Matrix::Matrix(size_t N) // initialization for an empty NxN matrix. passes N as a parameter for size
{
    size = N;//passes the matrix size as parameter N and saves it under the size variable which will be used in a ton of the functions below since thats the index limit
    data.resize(size); //the matrix is resized to be an NxN matrix based on the size of the matrix
    for (size_t i = 0; i < size; i++) //this loops through every row in the matrix
    {
        data[i].resize(size, 0);//this resizes the row that i is on to have the same amount of columns as size to keep the matrix equal in rows and columns
    }
}


/*
    function definition was given by the EECS348 lab github,
    code under the function I needed help from chatgpt to figure out, as my implementation of the constructor was
    not the correct way of doing it
    this constructor makes a matrix based on another matrix,
    i ended up not using it for anything, but i think its good
    to keep this code in to refer to in the future for implementations
    of a constructor so I do not have to reference other sources
*/
Matrix::Matrix(std::vector<std::vector<int>> nums) //inits the contructor and takes a 2d vector as the parameter
{
    size = nums.size();//the size of nums is the row, which is also the size of the columns because the matrix will always be NxN
    data = nums; //the data is a vector of vectors. nums passeds information through and saves it as data. then data at a particular index can be found
}

/*
    function definition was given by the EECS348 lab github,
    code under the function declaration is made by me
    this function prints out the matrix by iterating through the rows and colums,
    then it prints out each individual data piece until it reaches the end of the row,
    then the next row starts and each data piece in that column is printed out
    until the entire matrix is printed out.
*/
void Matrix::print_matrix() const //inits the function to print out the matrix
{
    for (size_t i = 0; i < size; i++) //i loops over each row in the matrix until it reaches the size of the row
    {
        for (size_t j = 0; j < size; j++)//j loops over each column in the matrix until it reaches the size of the column
        {
            std::cout << data[i][j] << " "; //prints out the number at that particular row and column and prints a space for easier reading
        }
        std::cout << "\n"; //makes a new line after iterating over that set of columns so the new row can be printed out
    }
}
/*
    the definition of the fucntion was given by the github lab.
    the code under the function declaration is made by me.
    This function takes in the row and column as the parameter
    and the number that is going to replace the data at that
    row and column, then it overrites that data at that
    index
*/
void Matrix::set_value(std::size_t i, std::size_t j, int n) //passes through integer n, size_t is an unsigned integer type. this is to help against negative indexes
{
    data[i][j] = n; //at row index i and column index j, that value is changed to whatever the parameter n is.
}
/*
    header written by EECS348 github branch
    code under the declaration of the fuction was written by me
    this takes in an index row and index column, then it returns
    the data at that particular row and column
*/
int Matrix::get_value(std::size_t i, std::size_t j) const //initializes the get value function. takes i and j as parameter which is the row and column
{
    return data[i][j]; //returns the data at that specific row and column index
}
/*
    header written by EECS348 github branch
    code under the declaration of the fuction was written by me
    this just returns the size of the matrix. the same
    size defined by N. size is a public variable though so get_size wasnt really necessary
    but it was part of the hpp file and it was easy to implement
*/
int Matrix::get_size() const //intializes the get size function to return the size of the matrix
{
    return size; //returns the size of the matrix
}
/*
    header written by EECS348 github branch
    code under the declaration of the fuction was written by me
    for the sum of the diagonal from top left to bottom right is returned
    in this function by using only 1 loop that represents both the row and column
*/
int Matrix::sum_diagonal_major() const //initializes the sum diagonal in the major direction function and takes no parameters
{
    int major_sum = 0;//initializes the major sum as 0 to reset any values stored
    for (size_t i = 0; i < size; i++) //this loop represents both the row and column, they increment together so that way only the diagonal is looked at
    {
        major_sum = major_sum +data[i][i];//the row and column index have the same index number. the data at that index is added into major_sum
    }
    return major_sum;//returns the total sum of the diagonal to the user
}

/*
    header written by EECS348 github branch
    code under the declaration of the fuction was written by me
    the diagonal sum in the minor direction works by going through the row and then getting the column by taking the size, subtracting 1 to get the index
    and then using a negative counter to go back by one more index per loop,
    this will then sum together to get the total sum of the diagonal from top right to bottom left
*/
int Matrix::sum_diagonal_minor() const//initialize the diagonal addition of the minor diagonal. takes no parameters
{
    int neg_counter = 0; //this counter will iterate each loop so it can be subtracted from the size and get the column index
    int minor_sum = 0; //this will store the total sum of the diagonals, it will be looped over to add each diagonal
    for (size_t i = 0; i < size; i++)//this iterates over the rows. no column loop is needed for this particular case because the size and negative counter will handle the column part
    {
        minor_sum = minor_sum + data[i][size-neg_counter-1]; //-1 is needed because the index is one less than the size
        neg_counter++; //increments the negative counter for subtraction during the next pass of the loop
    }
    return minor_sum; //this returns the minor diagonal sum, so the top right to the bottom left
}



/*
    header written by EECS348 github branch
    code under the declaration of the fuction was written by me
    the matrix addition adds the values of the matrix at the same index
    so as an example, the 4th row, third column of both indexes are added
    together and sent to a new matrix to be printed out for the user to look at

*/
Matrix Matrix::operator+(const Matrix &rhs) const //initializes the matrix addition operator. rhs refers to the second matrix. it is basically the same as using "other" in python for the overlaod operators and takes it as a parameter
{
    Matrix matrixadd(size);//initializes a new matrix that will be used to store the results of the matrix addition

    for (size_t i = 0; i < size; i++)//this for loop iterates over the rows of the matrix
    {
        for(size_t j=0; j< size; j++) //for loop that iterates through the columns of the matrix
        {
            matrixadd.data[i][j] = data[i][j] + rhs.data[i][j]; //adds the data of matrix 1 at a particular index with the data of matrix 2 at the exact same index
        }
    }
    return matrixadd; //prints out the new matrix with all the indexes added for the user to see
}
/*
    header written by EECS348 github branch
    code under the declaration of the fuction was written by me, but i needed help from chatgpt to realize
    that i needed a k value to iterate through the row and column at the same time when doing the matrix
    multiplication. everything else was written by me though
    The * overload operator does matrix multiplication. each row is multipied and added with each column of
    the matrix and saved to a newly made matrix that will save the result of the matrix multiplication table
*/
Matrix Matrix::operator*(const Matrix &rhs) const //inititalizes the multiplication overload operator. it takes the values of the "other" matrix as a parameter so it can be multiplied
{
    Matrix matrixmult(size); //initialization of a new matrix with an NxN of size so it can store the result of the matrix multiplication
    int saved_mult; //variable so save the result of one multiplication
    int saved_add; //saves the total of the added sets of multiplications results

    for (size_t i = 0; i < size; i++) //i is used to iterate over the rows of the first matrix
    {
        for(size_t j=0; j< size; j++) //j is used to iterate over the columns of ithe second matrix
        {
            saved_add = 0; //before it goes into the next loop, saved add needs to be reset back to 0 so that way there arent any values from last loop inside
            for (size_t k= 0; k < size; k++) //k is a loop that iterates over both the the row of the first matrix and the column of the second matrix
            {

                saved_mult = data[i][k]*rhs.data[k][j]; //multiplies the data from matrix 1 with the data of matrix 2 and saves it to be added to the next count
                saved_add += saved_mult; //creates a sum of all the multiplications that happen in the loop until the loop is finished
            }
            matrixmult.data[i][j] = saved_add; //the sum of multiplications is then added to the new matrix at that index
        }

    }
    return matrixmult; //returns the matrix so that way it can be printed out and shown to the user
}
/*
    header written by EECS348 github branch
    code under the declaration of the fuction was written by me
    the swap rows function uses r1 and r2 as constant for the rows, and j is used as an iterator through
    the columns. a temporary variable is used to ensure no data loss when the rows are swapped, the data
    from r2 gets passed to the data at index r1, and then the temp variable is used
    to swap the values at r2 with r1
*/
void Matrix::swap_rows(std::size_t r1, std::size_t r2)//inits the swap rows function, it takes 2 row indexes as parameters. the data inside these will be swapped
{
    for (size_t j = 0; j < size; j++)//for loop to iterate through the columns of the matrix. r1 and r2 are constant
    {
        size_t temp = data[r1][j]; //stores a temporary variable of that piece of data to swap out with so the data is not lost when the data at that row isnt changed
        data[r1][j] = data[r2][j]; //swaps the value at the row constant and the variable column j with the row that is being swapped
        data[r2][j] = temp; //the original value from r1 goes into the second row at the specific column
    }

}
/*
    header written by EECS348 github branch
    code under the declaration of the fuction was written by me
    the swap column function uses c1 and c2 as constant for the rows, and j is used as an iterator through
    the rows. a temporary variable is used to ensure no data loss when the columns are swapped, the data
    from c2 gets passed to the data at index c1, and then the temp variable is used
    to swap the values at c2 with c1
*/
void Matrix::swap_cols(std::size_t c1, std::size_t c2)//initializes the swap columns function. it takes in column 1 and 2 from the users input
{
    for (size_t i = 0; i < size; i++) //for loop to iterare through the rows. c1 and c2 are basically constants
    {
        int temp = data[i][c1]; //stores a temporary variable of that piece of data to swap out with so the data is not lost when the data at the column is changed
        data[i][c1] = data[i][c2]; //swaps the value at the column constant and the variable row i with the column that is being swapped
        data[i][c2] = temp; //the original value from c1 goes into the second column at the specific column location determined by c2
    }
}