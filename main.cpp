//main.cpp

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "matrix.hpp"

int main(int argc, char *argv[])
{
    std::string file_name; //this is the file input name that the user will enter in
    std::string line; //string variable that stores the line that the program is looking at
    int matrix_size; //string that initializes and stores the matrix size so it can be passed to the constructor
    int matrix_data; //this grabs the matrix data from the line so it can be added to the matrix

    std::cout << "Please Enter the name of the matrix file: "; //prompts the user to enter the file name
    std::cin >> file_name; //gets and saves the user input in file_name
    std::ifstream file(file_name); //opens up the file by looking in the folder for the file_name
    if (!file) //if the file was not found, then let the user know that the fle wasnt able to be opened
    {
        std::cout << "File not found. exitting"; //lets the user know that the file wasnt found and the program will exit
        return 0;//exits the program
    }
    else//otherwise
    {
        std:: getline(file, line); //gets the first line. the first line should store the data of 
        matrix_size = std::stoi(line); //stoi command converts the string inside of the line into an integer. then the matrix size will be saved so a new instance of the matrix can be created with this parameter
        std:: getline(file, line); //this skips the empty line in the text file so the matrix doesnt store non integer values
        Matrix matrix1(matrix_size); //initializes the first matrix that will be used with all the menu options
        Matrix matrix2(matrix_size);//initializes the second matrix that will be used for all the menu options
        


        /*
            I needed help from chat gpt to be able to extract the matrix data using c++ and it gave me
            the very handy >> fstream operator. these loops go through the rows and columns of the
            input file and saves it to the matrices
            I also used these as references to fully understand the >> operator:
            extract data overload operator: https://stackoverflow.com/questions/7443787/using-c-ifstream-extraction-operator-to-read-formatted-data-from-a-file
            extract data overload operator: https://cplusplus.com/reference/istream/istream/operator%3E%3E/

        */

        for (int i = 0; i < matrix_size; i++) //for each row in the text file that has the matrix data in it
        {
            for (int j = 0; j < matrix_size; j++) //for each column in the text file that has the matrix data in it
            {
                file >> matrix_data; //the >> overload operator is part of fstream. it automatically splits up the data by using whitespace as a delimiter and saves it to the matrix_data to be passed to the constructor
                matrix1.set_value(i, j, matrix_data); //uses the set_value function of the matrix to add the matrix data at that specific index for matrix 1
            }
        }
        for(int i = 0; i < matrix_size; i++) //starts the for loop for the second matrix, this loop iterates through the rows
        {
            for(int j = 0; j < matrix_size; j++)//for each row in the text file that has the matrix data in it
            {
                file >> matrix_data; //the >> overload operator is part of fstream. it automatically splits up the data by using whitespace as a delimiter and saves it to the matrix_data to be passed to the constructor
                matrix2.set_value(i, j, matrix_data);//uses the set_value function of the matrix to add the matrix data at that specific index for matrix 2
            }
        }




        /*
            this whole block for the user input was authored by me,
            this section of code is basically just a menu. it lets the user know to select
            an option or end the program by pressing something outside the scope of the if-else statement,
            then based on the user input, it will call a function and print out a matrix,
            most of these user inputs are basically structured the exact same way too, most of the user
            choices ask for which matrix, a row, a column, and sometimes an additional input to replace a data point with
        */
        while (true) //while true allows the menu to be repeatedly used  until the user is done using the program, if the user inputs anything that isnt a choice on the menu, then itll end the program
        {
            try//this try block is used to catch any errors and allows the loop to continue without crashing. its here to catch indexes that are out of bounds or type mismatches like the user trying to enter a string for an integer input
            {
                int user_input;//inits the user input as an integer to choose the menu option
                std::cout << "Please select a menu option by typing the number:\n1: Add Matrices together\n2: Multiply the matrices\n3: Get sum of matrix diagonal elements\n4: Swap matrix rows\n5: Swap matrix columns\n6: Update matrix data\nOr type anything else to quit: "; //this is to let the user know about all their options and what to type if they want a specific menu option
                std::cin >> user_input; //stores the user input so it can be interpretted in the if statement
            

                /*
                    code authored by me. if the users input is 1, then
                    it calls the matrix addition overload operator
                    and then it prints the new matrix out that the overload
                    operator created
                */
                if (user_input == 1) //if the user input is 1, it adds the matrices together and prints it out in a new matrix
                {
                    std::cout << "\nMatrix 1 + Matrix 2 =\n"; //lets the user know what the result is so the user can easily identify the choice they made
                    Matrix added_matrix = matrix1 + matrix2; //uses the addition overload operator for adding together the first and second matrix
                    added_matrix.print_matrix(); //prints out the newly made matrix that added together the values of the matrix using matrix addition
                }
                /*
                    code authored by me. if the users input is 2, then
                    it calls the matrix multiplication overload operator
                    and then it prints the new matrix out that the overload
                    operator created
                */
                else if (user_input == 2) //if the user input is 2, then it multiplies out the matrices and prints out a new matrix
                {
                    std::cout << "\nMatrix 1 * Matrix 2:\n";//lets the user know that the output will be matrix1 times matrix2
                    Matrix mult_matrix = matrix1 * matrix2; //initializes a new matrix and then saves the matrix multiplication table of matrix1 times matrix2
                    mult_matrix.print_matrix();//prints out the newly made matrix made by multiplication
                }
                /*
                    code authored by me. if the users input is 3, then
                    it calls the diagonal sum functions for both major and minor
                    diagonals for both matrix 1 and matrix 2
                */
                else if (user_input == 3)//if the user input is 3, then it sums up the major and minor diagonal of both matrices and prints out all 4
                {
                    std::cout << "\nMajor Diagonal Sum of matrix 1: " << matrix1.sum_diagonal_major() << "\n"; //calls the sum_diagonal_major function and prints out the result for matrix 1
                    std::cout << "Minor Diagonal Sum of matrix 1: " << matrix1.sum_diagonal_minor() << "\n";//calls the sum_diagonal_minor function and prints out the result for matrix 2
        
                    std::cout << "Major Diagonal Sum of matrix 2: " << matrix2.sum_diagonal_major() << "\n";//calls the sum_diagonal_major function and prints out the result for matrix 2
                    std::cout << "Minor Diagonal Sum of matrix 2: " << matrix2.sum_diagonal_minor() << "\n";//calls the sum_diagonal_minor function and prints out the result for matrix 2
                }
                /*
                    code authored by me. if the users input is 4, then
                    it asks the user to pick either matrix 1 or 2,
                    then it asks for 2 specific row inputs within the row
                    index. those two rows then swap
                */
                else if (user_input == 4)//if the user input is 4 then it will ask the user to pick a matrix, then 2 rows. those two rows will then swap positions
                {
                    int choose_matrix;//user input to pick matrix 1 or 2
                    int row1_input; //user input to pick any row within the valid index
                    int row2_input;//user input to pick a second row within the valid index
                    std::cout << "\nPlease enter 1 or 2 to select matrix 1 or matrix 2: "; //prompts the user to pick out a matrix to use
                    std::cin >> choose_matrix;//stores the users input here to decide which matrix to pass through
        
                    std::cout << "\nPlease enter a row index (the index starts at 0) for row 1: "; //prompts the user to select the index of the first row they want
                    std::cin >> row1_input;//saves the user input to be passed through as the first index
        
                    std::cout << "\nPlease enter a row index (the index starts at 0) for row 2 to swap with: "; //prompts the user to select the index of the second row they want
                    std::cin >> row2_input;//saves the user input to be passed through as the second index
        
                    if(choose_matrix == 1) //if the first matrix was chosen to be swapped
                    {
                        matrix1.swap_rows(row1_input, row2_input);//call the swap rows on matrix1 and pass through the row 1 and row 2 inputs as parameters
                        matrix1.print_matrix();//calls the print function to out the newly swapped matrix1 for the user to show it happened
                    }
                    else if (choose_matrix ==2)//if the second matrix was chosen to be swapped
                    {
                        matrix2.swap_rows(row1_input, row2_input);//call the swap rows on matrix2 and pass through the row 1 and row 2 inputs as parameters
                        matrix2.print_matrix();//calls the print function to out the newly swapped matrix2 for the user to show it happened
                    }
                    else //otherwise, the input is invalid
                    {
                        std::cout << "\nmatrix choice does not exist\n ";//let the user know the matrix choice doesnt exist, this will kick back to the menu
                    }
                }
                /*
                    code authored by me. if the users input is 4 then it will
                    prompt the user for a matrix, a column, and another column within
                    the index of the matrix so the 2 columns then swap positions with each other
                    the try block should catch an incorrect index and boot the user back to the menu.
                    it works pretty much identically to the row swap except the logic is geared for
                    the columns instead of the rows
                */
                else if (user_input == 5)//if the user input is 4 then it will ask the user to pick a matrix, then 2 columns. those two columns will then swap positions
                {
                    int choose_matrix_col; //variable to let the user choose to use matrix 1 or 2 for the one they want to change the columns
                    int col1_input;//input variable for the first column index that will be swapped
                    int col2_input;//input variable for the second column index that will be swapped with
                    std::cout << "\nPlease enter 1 or 2 to select matrix 1 or matrix 2";//prompts the user to pick either the first or second matrix as the one they want to modify
                    std::cin >> choose_matrix_col;//saves the user input in this variable and will be used to choose which matrix gets passed to the function
        
                    std::cout << "\nPlease enter a row index (the index starts at 0) for row 1: ";//prompts the user to enter in a column index and lets them know the index starts at 0
                    std::cin >> col1_input;//this saves the column index that the user enters so it can be swapped with the second column index
        
                    std::cout << "\nPlease enter a row index (the index starts at 0) for row 2 to swap with: ";//prompts the user to enter in a second column index so it can be swapped with the first column
                    std::cin >> col2_input;//saves the users input for the column index that will swap with the first column index input
        
                    if(choose_matrix_col == 1)//if the matrix chosen by the user is matrix 1, then it will use matrix 1 to call the swap
                    {
                        matrix1.swap_cols(col1_input, col2_input);//calls the swap columns function and passes in the column 1 and 2 input as the parameters
                        matrix1.print_matrix();//prints out the newly modified matrix to show that the modification did happen
                    }
                    else if (choose_matrix_col ==2)//otherwise, if the second matrix was chosen to be the one to column swap with
                    {
                        matrix2.swap_cols(col1_input, col2_input);//uses matrix 2 to call the swap column function and passes the column 1 and 2 inputs as parameters
                        matrix2.print_matrix();//prints out the newly modified matrix to show that the modification did happen
                    }
                    else//otherwise the matrix chosen didnt exist
                    {
                        std::cout << "matrix choice does not exist ";//this will let the user know what went wrong and boot them back to the menu
                    }
                }
                /*
                    if the uers input it 6, then the program will ask for which matrix to use.
                    from there, it asks for a row index, a column index, both of which need to be inside the index of the matrix,
                    finally it asks for a replacement input to replace the data at that specific row and column index
                */
                else if (user_input == 6)//if the user input is 6, then it will ask the user to either use matrix 1 or 2, then it asks for a row and column, then it updates that matrix at that specific index
                {
                    int choose_matrix_update;//this will save the user input to pick which matrix they want to update
                    int row;//this will save the row index that they want to change from the chosen matrix
                    int col;//this will save the row index that they want to change from the chosen matrix 
                    int new_num;//this is the new number that will replace the old number at the index
        
                    std::cout << "\nPlease enter 1 or 2 to select matrix 1 or matrix 2";//prompts the user to choose between matrix 1 and 2
                    std::cin >> choose_matrix_update;//saves the users choise in this variable for when the functions are ready to be called
        
                    std::cout << "\nPlease enter a row index (the index starts at 0) for row: ";//asks the user for a row index that they want the data to be replaced at
                    std::cin >> row;//saves the users input in row for the row index
        
                    std::cout << "\nPlease enter a row index (the index starts at 0) for column: ";//prompts the user for an input for the column index that will be replaced
                    std::cin >> col;//saves the users input for the column index to pass as a parameter later
        
                    std::cout << "\nPlease enter a new integer data value to replace it with: ";//prompts the user to input a new data for that specific index
                    std::cin >> new_num;//saves the user input as new_num so it can replace the old number at the specific index
        
                    if(choose_matrix_update == 1)//if the users input is one then it chooses the first matrix
                    {
                        matrix1.set_value(row, col, new_num);//calls the set value function to change the value at that specific index
                        matrix1.print_matrix(); //calls the function to print out the updated matrix
                    }
                    else if (choose_matrix_update ==2)//if the user chooses the second matrix to update
                    {
                        matrix2.set_value(row, col, new_num); //calls the set value function to change the value at that specific indexn
                        matrix2.print_matrix();//prints out the newly modified matrix2 for the user to look at
                    }
                    else//otherwise
                    {
                        std::cout << "\nmatrix choice does not exist \n"; //lets the user know that the matrix entered is invalid
                    }
                }
                else //if anything else is typed and entered into the user input, then it will just end the program
                {
                    std::cout << "Exiting program.\n"; //lets the user know that the program is ending
                    break; // Break the loop to end the program
                }
            }
            catch (...) //generic catch for the try block that will use this to catch any error instead of making the program crash
            {
                std::cout << "\nSomething went wrong. make sure if you are entering indexes, make sure it is within the bounds\n"; //tells the user the possible error encountered. I used one big try block because theres really only 2 ways there could be an error, an index error or a type error
            }

        }
    }
    return 0; //returns to end the program
}