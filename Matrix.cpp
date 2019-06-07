#include "Matrix.h"
#include <random>
#include <fstream>

Matrix::Matrix()
{
    value = 0;
    row = 0;
    col = 0;
}

Matrix::~Matrix()
{
    for(int i = 0; i < row; i++)
    {
        // delete individual row from matrix
        delete [] mat_Array[i];
        delete [] original[i];
    }

    // delete matrix as a whole
    delete [] mat_Array;
    delete [] original;

    // delete vector
    std::vector<double>().swap(sol_Vec);
    std::vector<double>().swap(b_Vec);
}
/**
 * InputFile function
 * - Will open a user defined input file and load the matrix and the b vector
 */
bool Matrix::InputFile()
{
    //double temp = 0;
    std::string input = " ";

    cout << "Please input the name of the file (with extension): ";
    cin >> input;
    // open input file
    std::ifstream inFile;
    inFile.open(input.c_str(), std::ifstream::in);

    if(!inFile)
    {
        cout << "Error file not found!" << endl;
        return false;
    }

    // read in row and col values from input file
    inFile >> row;

    col = row;

    // init the Matrix (at least the rows)
    mat_Array = new double *[row];
    for(int i = 0; i < row; i++)
    {
        // give the matrix cols
        mat_Array[i] = new double [col];
        for(int j = 0; j < col; j++)
        {
            // get values from input file
            inFile >> value;
            // put values in
            mat_Array[i][j] = value;
        }
    }

    b_Vec.clear();
    // input values into the vector
    for(int i = 0; i < row; i++)
    {
        inFile >> value;
        b_Vec.push_back(value);
    }

    for(int i = 0; i < row; i++)
    {
        sol_Vec.push_back(1.0);
    }

    // make matrix diag dominant
    /*for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            temp = temp + std::abs(mat_Array[i][j]);
        }
        temp = temp + std::abs(b_Vec[i]);
        mat_Array[i][i] = mat_Array[i][i] + temp;
        temp  = 0;
    }*/

    // close input file
    inFile.close();
    return true;
}

/**
 * RandomStart function
 * - will generate a random matrix, rows & cols specified by the user
 */
bool Matrix::RandomStart()
{
    int temp = 0;
    std::default_random_engine * gptr;
    gptr = new std::default_random_engine(time(NULL));

    std::uniform_real_distribution<double> Udist(-50,50);

    cout << "How many rows & cols: ";
    cin >> row;
    col = row;
    cout << endl;

    // init the Matrix (at least the rows)
    mat_Array = new double *[row];
    for(int i = 0; i < row; i++)
    {
        // give the matrix cols
        mat_Array[i] = new double [col];
        for(int j = 0; j < col; j++)
        {
            // put values in
            mat_Array[i][j] = Udist(*gptr);
        }
    }

    b_Vec.clear();
    // input values into the vector
    for(int i = 0; i < row; i++)
    {
        b_Vec.push_back(Udist(*gptr));
    }

    for(int i = 0; i < row; i++)
    {
        sol_Vec.push_back(1.0);
    }


    // make matrix diag dominant
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            temp = temp + std::abs(mat_Array[i][j]);
        }
        temp = temp + std::abs(b_Vec[i]);
        mat_Array[i][i] = mat_Array[i][i] + temp;
        temp  = 0;
    }

    gptr = nullptr;
    if(row < 11)
        Display();

    return true;
}

/**
 * CopyOriginalMatrix
 * - will copy the A matrix into a temp matrix called original
 * - use in case the A matrix will be modified
 */
bool Matrix::CopyOriginalMatrix()
{
    original = new double *[row];
    for(int i = 0; i < row; i++)
    {
        original[i] = new double [col];
        for(int j = 0; j < col; j++)
        {
            original[i][j] = mat_Array[i][j];
        }
    }
    return true;
}

/**
 * CheckSol function
 * - will multiply the original matrix with the solution vector
 * - use for checking if the solution vector * the A matrix is equal to the b vector
 */
bool Matrix::CheckSol()
{
    std::vector<double> temp;
    double temp2 = 0;
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            temp2 = temp2 + (original[i][j] * sol_Vec[j]);
        }
        temp.push_back(temp2);
        temp2 = 0;
    }

    cout << "\nA * Solution Vector gives: " << endl;
    cout << "-----------------------------------------------" << endl;
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            cout << setw(15) << original[i][j];
        }
        cout << " |  " << setw(15) << sol_Vec[i];
        cout << setw(10) << " ||  "<< setw(10) << temp[i];
        cout << endl;
    }
    std::vector<double>().swap(temp);
    return true;
}

/**
 * Display function
 * - no parameters, output current A matrix
 */
void Matrix::Display()
{
    //cout << std::setprecision(5) << std::fixed;
    // display matrix
    cout << "Current Matrix: " << endl;
    cout << "-----------------------------------------------" << endl;
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            cout << setw(15) << mat_Array[i][j];
        }
        cout << setw(10) << " |  " << b_Vec[i];
        cout << endl;
    }
}

/**
 * Display function
 * - 2 parameters, output current L & U matrices
 */
void Matrix::Display(double **l, double **u)
{
    //cout << std::setprecision(5) << std::fixed;
    // display matrix
    cout << "L Matrix: " << endl;
    cout << "-----------------------------------------------" << endl;
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            cout << setw(15) << l[i][j];
        }
        cout << setw(10) << " |  " << b_Vec[i];
        cout << endl;
    }

    cout << "\nU Matrix: " << endl;
    cout << "-----------------------------------------------" << endl;
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            cout << setw(15) << u[i][j];
        }
        cout << setw(10) << " |  " << b_Vec[i];
        cout << endl;
    }

}

/**
 * Display function
 * - 3 parameters, output current L & U & D matrices
 */
void Matrix::Display(double **l, double **u, double **d)
{
    cout << "L Matrix: " << endl;
    cout << "-----------------------------------------------" << endl;
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            cout << setw(15) << l[i][j];
        }
        cout << setw(10) << " |  " << b_Vec[i];
        cout << endl;
    }

    cout << "\nU Matrix: " << endl;
    cout << "-----------------------------------------------" << endl;
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            cout << setw(15) << u[i][j];
        }
        cout << setw(10) << " |  " << b_Vec[i];
        cout << endl;
    }

    cout << "\nD Matrix: " << endl;
    cout << "-----------------------------------------------" << endl;
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            cout << setw(15) << d[i][j];
        }
        cout << setw(10) << " |  " << b_Vec[i];
        cout << endl;
    }
}

/**
 * CurrentSolution function
 * - output the current solution vector to the screen
 */
void Matrix::CurrentSolution()
{
    cout << endl <<"Solution Vector: " << endl;
    cout << "-----------------------------------------------" << endl;
    for(int i = 0; i < row; i++)
    {
        cout << sol_Vec[i] << endl;
    }
}

/**
 * Switch Rows function
 * - Will switch row 1 and row 2
 */
bool Matrix::SwitchRows(int lhs, int rhs)
{
    double *tpr;
    tpr = mat_Array[rhs];
    mat_Array[rhs] = mat_Array[lhs];
    mat_Array[lhs] = tpr;

    //DisplayMatrix();
            //cout <<"------------------AfterSwitch-----------------------" << endl;

    double temp;
    temp = b_Vec[rhs];
    b_Vec[rhs] = b_Vec[lhs];
    b_Vec[lhs] = temp;

    tpr = nullptr;
    return true;
}

/**
 * UpdateNextRow function
 * - takes 3 parameters
 * - performs row operations onto the next row
 */
double Matrix::UpdateNextRow(double x, double y, double z)
{
    /// x = values in the next row
    /// y = value that multiplies the previous row
    /// z = values in the previous row
    double fin = 0;
    fin = x - (y * z);
    //cout << fin << " = " <<x << " " << y << " " << z << endl;
    return fin;
}

/**
 * Inverse function
 * - Finds the inverse of a matrix passed in (src)
 */
bool Matrix::Inverse(double **src)
{
    for(int i = 0; i < row; i++)
    {
        src[i][i] = 1 / src[i][i];
    }
    return true;
}

/**
 * Dot Product function
 * - Multiplies two matrices (lhs, rhs) and saves it into newM
 */
bool Matrix::DotProduct(double **lhs, double **rhs, double **newM)
{
    double sum = 0;
    for (int j = 0; j < col; j++)
    {
		for (int i = 0; i < row; i++)
		{
			sum = 0;
			for (int k = 0; k < col; k++)
			{
				sum = sum + lhs[i][k] * rhs[k][j];
			}
			newM[i][j] = sum;
		}
    }
    return true;
}

/**
 * Dot Product function
 * - Multiplies a matrix (lhs) with the b vector, and saves it into the newVec
 */
bool Matrix::DotProduct(double **lhs, std::vector<double>& newVec)
{
    double sum = 0;
    for(int i = 0; i < row; i++)
    {
        sum = 0;
        for(int j = 0; j < col; j++)
        {
            sum = sum +lhs[i][j] * b_Vec[j];
        }
        newVec[i] = sum;
    }
    return true;
}

/**
 * Dot Product function
 * - Multiplies a matrix (lhs) with an int, and saves it into the same matrix (lhs)
 */
bool Matrix::DotProduct(double **lhs, int x)
{
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
           lhs[i][j] = lhs[i][j] * x;
        }
    }
    return true;
}

/**
 * Dot Product function
 * - Multiplies a matrix (lhs) and a vector (x), saves the result into vector (y)
 */
bool Matrix::DotProduct(double **lhs, std::vector<double>& x, std::vector<double>& y)
{
    double sum = 0;
    for(int i = 0; i < row; i++)
    {
        sum = 0;
        for(int j = 0; j < col; j++)
        {
            sum = sum +lhs[i][j] * x[j];
        }
        y[i] = sum;
    }
    return true;
}
/**
 * AddMatrices function
 * - Add two matrices (lhs, rhs) and saves it into newM
 */
bool Matrix::AddMatrices(double **lhs, double **rhs, double **newM)
{
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            newM[i][j] = lhs[i][j] + rhs[i][j];
        }
    }
    return true;
}

/**
 * AddVec function
 * - Adds two vectors (x & y) and saves it into x
 */
bool Matrix::AddVec(std::vector<double>& x, std::vector<double>& y)
{
    for(int i = 0; i < row; i++)
    {
        x[i] = x[i] + y[i];
    }
    return true;
}

/**
 * SubVec function
 * - Subtracts two vectors ( x & y) and saves it into y
 */
bool Matrix::SubVec(std::vector<double>& x, std::vector<double>& y)
{
    for(int i = 0; i < row; i++)
    {
        y[i] = x[i] - y[i];
    }
    return true;
}

/**
 * CopyMatrices function
 * - Copies the rhs matrix into the lhs matrix
 */
bool Matrix::CopyMatrices(double **lhs, double **rhs)
{
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            lhs[i][j] = rhs[i][j];
        }
    }
    return true;
}

/**
 * SaveData function
 * - saves the current A matrix and current b Vector to an output file called Output.txt
 */
bool Matrix::SaveData()
{
    std::ofstream outFile;
    outFile.open("Output.txt");

    outFile << row;
    outFile << endl;
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            outFile << mat_Array[i][j] << " ";
        }
        outFile << endl;
    }

    for(int i = 0; i < row; i++)
        outFile << b_Vec[i] << " ";

    outFile << endl;

    cout << "Finished Outputting the Current Matrix and Right Side to file Output.txt" << endl;

    outFile.close();
    return true;
}

/**
 * SaveSolution function
 * - saves the solution vector to an output file called Sol_Output.txt
 */
bool Matrix::SaveSolution()
{
    std::ofstream outFile;
    outFile.open("Sol_Output.txt");
    int nx = sqrt(row);
    int ny = nx;

    for(int i = 0; i < nx; i++)
    {
        for(int j = 0; j < ny; j++)
        {
            int k = (j * nx) + i;
            outFile << sol_Vec[k];
            if(j < ny - 1)
                outFile << " ";
        }
        outFile << endl;
    }

    cout << "Finished Outputting the Solution Vector to file Sol_Output.txt" << endl;

    outFile.close();
    return true;
}

/**
 * Menu function
 * - allows the user to access all important functions of this MathLib
 */
bool Matrix::Menu()
{
    int choice = 55;

    while(choice != 0)
    {
        cout << "1. Create a randomly generated Matrix" << endl;
        cout << "2. Load a Matrix from an input file" << endl;
        cout << "3. Save current matrix and right side to a file." << endl;
        cout << "4. Solve current matrix using Gaussian Elimination" << endl;
        cout << "5. Solve current matrix using LU Decomposition" << endl;
        cout << "6. Solve current matrix with Jacobi iterative method" << endl;
        cout << "7. Solve current matrix with Gauss Seidel iterative method" << endl;
        cout << "8. Solve current matrix with SOR iterative method" << endl;
        cout << "9. Save current solution vector 'x' to file " << endl;
        cout << "10. Graph current solution vector 'x' using GNUPLOT" << endl;
        cout << "11. Power Method" << endl;
        cout << "12. Newton's Method"<< endl;
        cout << "13. Bisection Method" << endl;
        cout << "0. Exit" << endl;

        cin >> choice;

        switch(choice)
        {
            case 1:
            {
                RandomStart();
                CopyOriginalMatrix();
            }break;
            case 2:
            {
                InputFile();
                if(row < 11)
                    Display();
                CopyOriginalMatrix();
            }break;
            case 3:
            {
                SaveData();
            }break;
            case 4:
            {
                GaussianElim();
                //CheckSol();
            }break;
            case 5:
            {
                LU_Decom();
            }break;
            case 6:
            {
                Jacobi();
            }break;
            case 7:
            {
                GaussSeidel();
            }break;
            case 8:
            {
                SOR();
            }break;
            case 9:
            {
                SaveSolution();
            }break;
            case 11:
            {
                PowerMethod();
            }break;
            case 12:
            {
                NewthonMethod();
            }break;
            case 13:
            {
                Bisection();
            }break;
            case 0:
            {
                cout << "Exiting now.." << endl;
                return true;
            }break;
        }
        cout << endl;
    }

    return true;
}
