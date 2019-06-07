#include "Matrix.h"

/**
 * back solve function
 * - takes a double pointer matrix ( called U) and a Y vector
 * - Ux = y
 */
bool Matrix::BackSolve(double **u_Mat, std::vector<double>& y_Vec)
{
    /// assign the last value of the y vec to the solution vec
    sol_Vec[row-1] = y_Vec[row-1];
    double sum = 0;
    for(int i = row-2; i > -1; i--)
    {
        sum = 0;
        for(int j = i+1; j < col; j++)
        {
            /// add up the row times the values in the solution vec
            sum = sum + (u_Mat[i][j] * sol_Vec[j]);
        }
        /// place the new value into the solution vect
        sol_Vec[i] = (y_Vec[i] - sum);
    }

    /// output the solution vector
    cout << "Solution vector: " << endl;
    cout << "-----------------------------------------------" << endl;
    for(int i = 0; i < row; i++)
    {
        cout << setw(15) << sol_Vec[i];
        cout << endl;
    }

    return true;
}

/**
 * Forward solve function
 * - takes a double pointer matrix ( called L) and a Y vector
 * - Ly = x
 */
bool Matrix::ForwardSolve(double **l_Mat, std::vector<double>& y_Vec)
{
    double sum = 0;

    for(int i = 0; i < row; i++)
    {
        sum = 0;

        for(int j = 0; j < i; j++)
        {
            /// add up the entire row into sum
            sum = sum + (l_Mat[i][j] * y_Vec[j]);
        }

        /// subtract from the right side, and divide by the diag. afterwards place in the y vect
        y_Vec[i] = (b_Vec[i] - sum) / l_Mat[i][i];
        //cout << "Y value added: " << y_Vec[i] << endl;
    }

    /// output y vector
    cout << "Y vector: " << endl;
    cout << "-----------------------------------------------" << endl;
    for(int i = 0; i < row; i++)
    {
        cout << setw(15) << y_Vec[i];
        cout << endl;
    }

    return true;
}

bool Matrix::LU_Decom()
{
    /// declare and init variables
    double  sum = 0;

    double **l_Mat;
    double **u_Mat;

    std::vector<double> y_Vec;

    /// init y vector
    for(int i = 0; i < row; i++)
    {
        y_Vec.push_back(0);
    }

    /// separate original matrix into LU
    l_Mat = new double *[row];
    u_Mat = new double *[row];
    for(int i = 0; i < row; i++)
    {
        // give the matrices cols
        l_Mat[i] = new double [col];
        u_Mat[i] = new double [col];
        for(int j = 0; j < col; j++)
        {
            l_Mat[i][j] = 0;
            u_Mat[i][j] = 0;
        }
    }

    /// set diag in U matrix to 1
    for (int i = 0; i < row; i++) {
		u_Mat[i][i] = 1;
	}

	/// Decompose A into the two matrices
	for (int j = 0; j < col; j++)
    {
		for (int i = j; i < row; i++)
		{
			sum = 0;
			for (int k = 0; k < j; k++)
			{
				sum = sum + l_Mat[i][k] * u_Mat[k][j];
			}
			l_Mat[i][j] = mat_Array[i][j] - sum;
		}

		for (int i = j; i < row; i++)
        {
			sum = 0;
			for(int k = 0; k < j; k++)
			{
				sum = sum + l_Mat[j][k] * u_Mat[k][i];
			}
			if (l_Mat[j][j] == 0)
            {
				cout << "ERROR! det(L) close to 0!\n Can't divide by 0...\n";
				for(int i = 0; i < row; i++)
                {
                    // delete individual row from matrix
                    delete [] l_Mat[i];
                    delete [] u_Mat[i];
                }

                // delete matrix as a whole
                delete [] l_Mat;
                delete [] u_Mat;

                std::vector<double>().swap(y_Vec);
				return false;
			}
			u_Mat[j][i] = (mat_Array[j][i] - sum) / l_Mat[j][j];
		}
	}

	// display the current LU matrices
    // Display(l_Mat, u_Mat);
    // start forward solving with the L matrix and the b vector
    ForwardSolve(l_Mat, y_Vec);
    // start back solving with the U matrix and the y vector
    BackSolve(u_Mat, y_Vec);
    // Check if the original matrix and the current solution vector = the original b vector.
    //CheckSol();


    // clean up the pointers & vector
    for(int i = 0; i < row; i++)
    {
        // delete individual row from matrix
        delete [] l_Mat[i];
        delete [] u_Mat[i];
    }

    // delete matrix as a whole
    delete [] l_Mat;
    delete [] u_Mat;

    std::vector<double>().swap(y_Vec);

    return true;
}
