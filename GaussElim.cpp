#include "Matrix.h"

bool Matrix::BackSolve()
{
    /// sol_Vec is the solution vector
    /// first solution value is free
    sol_Vec[row-1] = b_Vec[row-1];
    double sum = 0;

    //sum = (sum + mat_Array[row-2][col-1]) * x_Vec[row-1];
    //x_Vec[row-2] = val_Vec[row-2] - sum;

    /// start from the bottom and work up
    for(int i = row-2; i > -1; i--)
    {
        sum = 0;
        /// starting from the first value to the right of the diag
        for(int j = i+1; j < col; j++)
        {
            /// sum up the whole row
            sum = sum + (mat_Array[i][j] * sol_Vec[j]);
            /// set matrix values to 0 to signify row operation is complete
            mat_Array[i][j] = 0.0;
        }
        /// subtract the current given vector by the current sum
        /// store into the solution vector
        sol_Vec[i] = b_Vec[i] - sum;
    }

    /*for(int i = 0; i < x_Vec.size(); i++)
        cout << x_Vec[i] << " " << endl;*/

    return true;
}

bool Matrix::GaussianElim()
{
    /// declare and init variables
    bool flag = false;
    double temp = 1;
    int index = 0;

     //DisplayMatrix();
            //cout <<"-----------------------------------------" << endl;
    /// main loop
    for(int i = 0; i < row; i++)
    {
        cout << endl;
        if(row < 11)
            Display();
        cout <<" -----------------------------------------" << endl;
        /// if the value is anything but 1 or 0, then divide
        if(mat_Array[i][i] > 1 || mat_Array[i][i] < 0)
        {
            temp = mat_Array[i][i];
            mat_Array[i][i] = mat_Array[i][i] / temp;
        }
        /// if the value is 0, then look below current row to see if any non 0 can be found
        else if(mat_Array[i][i] == 0 && i+1 < row)
        {
            for(int z = i+1; z < row; z++)
            {
                if(mat_Array[z][i] > mat_Array[i][i])
                {
                   SwitchRows(i ,z);
                   break;
                }
            }
            /// reset counter
            i--;
            /// flag that the counter is being reset
            flag = true;
            //DisplayMatrix();
            //cout <<"-----------------------------------------" << endl;
        }
        /// if the value is 0, and there are no rows left
        else if(mat_Array[i][i] == 0 && i+1 >= row)
        {
            cout << "Error, Matrix is unsolvable!" << endl;
            return false;
        }
        /// if i was not reset then continue on to other operations
        if(flag == false)
        {
            //DisplayMatrix();
           // cout <<"-------------------BeforeUpdate----------------------" << endl;
           /// divide current row by the value of the diag
             for(int j = 0; j < col; j++)
             {
                if(j > i)
                {
                    mat_Array[i][j] = mat_Array[i][j] / temp;
                    //cout << temp << endl;
                }
             }

             /// divide the current vec by the current diag
            b_Vec[i] = b_Vec[i] / temp;
            index = i;

            /// while there is a row under the current one
            while(index + 1 < row)
            {
                index++;
                //cout << index << endl;
                /// grab the value that will be consistent
                temp = mat_Array[index][i];
                //cout << temp << endl;
                /// reduce the following row
                for(int j = 0; j < col; j++)
                {
                    //cout << mat_Array[index][j] << " " << temp << " " << mat_Array[i][j] << endl;
                    mat_Array[index][j] = UpdateNextRow(mat_Array[index][j], temp, mat_Array[i][j]);
                }

                /// reduce the following vec
                b_Vec[index] = UpdateNextRow(b_Vec[index], temp, b_Vec[i]);

            }


        }

        /// reset flag
        flag = false;

    }

    /// begin to Backsolve
    BackSolve();

    return true;
}
