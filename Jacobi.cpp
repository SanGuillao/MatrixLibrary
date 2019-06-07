#include "Matrix.h"
#include <math.h>

/**
 * Norm function
 * - Finds the norm of vector v
 */
double Matrix::norm(std::vector<double>& v) {
    double sum = 0;
    for (int i = 0; i < row; i++) {
        sum += v[i] * v[i];
    }
    return sqrt(sum);
}

/**
 * TwoNorm function
 * - Finds the two norm of vector x
 */
double Matrix::TwoNorm(std::vector<double>& x)
{
    //double fin = 0;
    std::vector<double> temp(row, 0);
    DotProduct(mat_Array, x, temp);
    SubVec(b_Vec, temp);
    return norm(temp);
}

/**
 * Jacobi function
 * - Will apply the Jacobi iterative method onto matrix A
 */
bool Matrix::Jacobi()
{
     /// declare and init variables
    //double  sum = 0;

    double **l_Mat;
    double **u_Mat;
    double **d_Mat;
    double **t_Mat;

    std::vector<double> y_Vec;
    std::vector<double> oldX;
    std::vector<double> guess;

    /// init y vector
    for(int i = 0; i < row; i++)
    {
        y_Vec.push_back(0);
        oldX.push_back(0);
        guess.push_back(1);
    }

    /// separate original matrix into LU
    l_Mat = new double *[row];
    u_Mat = new double *[row];
    d_Mat = new double *[row];
    t_Mat = new double *[row];
    for(int i = 0; i < row; i++)
    {
        // give the matrices cols
        l_Mat[i] = new double [col];
        u_Mat[i] = new double [col];
        d_Mat[i] = new double [col];
        t_Mat[i] = new double [col];
        for(int j = 0; j < col; j++)
        {
            l_Mat[i][j] = 0;
            u_Mat[i][j] = 0;
            d_Mat[i][j] = 0;
            t_Mat[i][j] = 0;
        }
    }

    /// split original A into the Lower Upper and Diagonal Matrices
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            if(j < i)
            {
                l_Mat[i][j] = mat_Array[i][j];
            }
            else if(j > i)
            {
                u_Mat[i][j] = mat_Array[i][j];
            }
            else if(j == i)
            {
                d_Mat[i][i] = mat_Array[i][i];
            }
        }
    }


    // give the guess to oldX
    AddVec(oldX, guess);
    // make D into its inverse D^-1
    Inverse(d_Mat);
    int counter = 0;

    while(TwoNorm(oldX) > pow(10, -12))
    {
        counter++;
        // L + U = C (in this case save into t_Mat)
        AddMatrices(l_Mat, u_Mat, t_Mat);
        // C * oldX = vector ( in this case save into y_Vec)
        DotProduct(t_Mat, oldX, y_Vec);
        // b - (C * xold) = vector ( in this case save into y_Vec)
        SubVec(b_Vec, y_Vec);
        // D^-1 * (b - (C * xold)) = vector (in this case save into the oldX)
        DotProduct(d_Mat, y_Vec, oldX);
        cout << "Two Norm: " << TwoNorm(oldX) << endl;
    }

    for(int i = 0; i < row; i++)
    {
        sol_Vec[i] = oldX[i];
    }

    cout << "Number of Iterations till Convergence: " << counter << endl;
    cout << "Solution Vector: " << endl;
    for(int i = 0; i < row; i++)
    {
        cout << sol_Vec[i] << endl;
    }

    CheckSol();

    // clean up the pointers & vector
    for(int i = 0; i < row; i++)
    {
        // delete individual row from matrix
        delete [] l_Mat[i];
        delete [] u_Mat[i];
        delete [] d_Mat[i];
        delete [] t_Mat[i];
    }

    // delete matrix as a whole
    delete [] l_Mat;
    delete [] u_Mat;
    delete [] d_Mat;
    delete [] t_Mat;

    std::vector<double>().swap(y_Vec);
    std::vector<double>().swap(oldX);
    std::vector<double>().swap(guess);

    return true;
}
