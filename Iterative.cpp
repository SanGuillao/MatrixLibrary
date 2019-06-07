#include "Matrix.h"

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
 * - will apply the Jacobi method onto the current A matrix and b vector
 */
bool Matrix::Jacobi()
{
    // init vectors & populate
    std::vector<double> oldX(row, 1);
    std::vector<double> y(row, 1);

    // init int
    int i = 0, j = 0, counter = 0;

    double sum = 0;

    while (TwoNorm(oldX) > pow(10, -8) && counter < 500)
    {
        counter++;
        for (i = 0; i < row; i++)
        {
            sum = 0;
            for (j = 0; j < col; j++)
            {
                // if not a diagonal
                if (j != i)
                   {
                       sum = sum + (mat_Array[i][j] * oldX[j]);
                   }
            }
            y[i] = (1 / mat_Array[i][i]) * (b_Vec[i] - sum);
        }

        for (i = 0; i < row; i++)
        {
            oldX[i] = y[i];
        }
        cout << "Two Norm: " << TwoNorm(oldX) << endl;
    }

    if(counter >= 500)
    {
        cout << "Error could not find solution!" << endl;
        return false;
    }

    // save the oldX vector into the solution vector
    for(i = 0; i < row; i++)
    {
        sol_Vec[i] = oldX[i];
    }

    cout << "\nNumber of Iterations till Convergence: " << counter << endl;
    cout << "Solution Vector: " << endl;
    for(i = 0; i < row; i++)
    {
        cout << sol_Vec[i] << endl;
    }

    //CheckSol();

    std::vector<double>().swap(y);
    std::vector<double>().swap(oldX);
    return true;
}

/**
 * Gauss Seidel function
 * - will apply the Gauss Seidel method onto the current A matrix and b vector
 */
bool Matrix::GaussSeidel()
{
    // init vectors & populate
    std::vector<double> oldX(row, 1);
    std::vector<double> y(row, 1);

    // init int
    int i = 0, j = 0, counter = 0;

    double sum = 0;

    while (TwoNorm(y) > pow(10, -8) && counter < 500)
    {
        counter++;
        for (i = 0; i < row; i++)
        {
            sum = 0;
            for (j = 0; j < col; j++)
            {
                // if not a diagonal
                if (j != i)
                   {
                       sum = sum + (mat_Array[i][j] * y[j]);
                   }
            }

            y[i] = (1 / mat_Array[i][i]) * (b_Vec[i] - sum);
        }
        cout << "Two Norm: " << TwoNorm(y) << endl;
    }

    if(counter >= 500)
    {
        cout << "Error could not find solution!" << endl;
        return false;
    }

    // save the oldX vector into the solution vector
    for(i = 0; i < row; i++)
    {
        sol_Vec[i] = y[i];
    }

    cout << "\nNumber of Iterations till Convergence: " << counter << endl;
    cout << "Solution Vector: " << endl;
    for(i = 0; i < row; i++)
    {
        cout << sol_Vec[i] << endl;
    }

    //CheckSol();

    std::vector<double>().swap(y);
    std::vector<double>().swap(oldX);

    return true;
}

/**
 * Successive Over Relaxation function
 * - will apply the Successive Over Relaxation technique on the A matrix and the b vector
 */
bool Matrix::SOR()
{
    // init vectors & populate
    std::vector<double> oldX(row, 1);
    std::vector<double> y(row, 1);

    // init int
    int i = 0, j = 0, counter = 0;

    // init double
    double w = 1.1, sum = 0;

    cout << "Please enter the relaxation factor: ";
    cin >> w;
    cout << endl;
    while(w < 1)
    {
        cout << "Please enter a number greater than 1: " << endl;
        cin >> w;
        cout << endl;
    }
    // while the Two Norm of the oldX vector is greater than 10^-12 ( basically super close to 0 )
    while (TwoNorm(y) > pow(10, -8) && counter < 500)
    {
        counter++;
        for (i = 0; i < row; i++)
        {
            sum = 0;
            //y[i] = (b_Vec[i] / mat_Array[i][i]);
            for (j = 0; j < col; j++)
            {
                // if not a diagonal
                if (j != i)
                   {
                        sum = sum + (mat_Array[i][j] * y[j]);
                   }
            }
            //y[i] = ((1-w) * y[i]) + ((w / mat_Array[i][i]) * (b_Vec[i] - sum));
            y[i] = y[i] + (w * (((b_Vec[i] - sum) / mat_Array[i][i]) - y[i]));
        }
        cout << "Two Norm: " << TwoNorm(y) << endl;
    }

    if(counter >= 500)
    {
        cout << "Error could not find solution!" << endl;
        return false;
    }

    // save the oldX vector into the solution vector
    for(i = 0; i < row; i++)
    {
        sol_Vec[i] = y[i];
    }

    cout << "\nNumber of Iterations till Convergence: " << counter << endl;
    cout << "Solution Vector: " << endl;
    for(i = 0; i < row; i++)
    {
        cout << sol_Vec[i] << endl;
    }

    //CheckSol();

    std::vector<double>().swap(y);
    std::vector<double>().swap(oldX);

    return true;
}

