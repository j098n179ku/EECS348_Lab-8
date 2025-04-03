//matrix.hpp

/*
    Everything in matrix.hpp was given by the EECS348
    github lab. 
    this class declaration is a header file to
    define a bunch of classes that will be needed
    in order to finish the lab. the actual implementation
    of these will be found in matrix.cpp and main.cpp

    I used this header file as checklist to make sure I have
    everyhing in my matrix.cpp, comments explaining
    each function is in matrix.cpp
*/

#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <cstdint>
#include <vector>

class Matrix
{
    public:
    std::size_t size;
    std::vector<std::vector<int>> data;

    Matrix(std::size_t N);//done
    Matrix(std::vector<std::vector<int>> nums);//done

    Matrix operator+(const Matrix &rhs) const;//done
    Matrix operator*(const Matrix &rhs) const;//done
    void set_value(std::size_t i, std::size_t j, int n);//done
    int get_value(std::size_t i, std::size_t j) const;//done
    int get_size() const; //done
    int sum_diagonal_major() const;//done
    int sum_diagonal_minor() const;//done
    void swap_rows(std::size_t r1, std::size_t r2);//done
    void swap_cols(std::size_t c1, std::size_t c2);//done
    void print_matrix() const; //Done
};

#endif // __MATRIX_HPP__