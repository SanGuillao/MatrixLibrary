#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::setw;

class Matrix
{
    private:
        /// declared Matrix array pointer
        double **mat_Array;
        double **original;
        /// declared vector;
        std::vector<double> sol_Vec;
        std::vector<double> b_Vec;
        /// declare row, col, value
        int row, col;
        double value = 0;

    public:
        // constructor
        Matrix();
        // destructor
        ~Matrix();
        // copy constructor
        ///Matrix(const Matrix& src);
        bool CopyOriginalMatrix();
        bool CopyMatrices(double **lhs, double **rhs);
        // display
        void Display();
        void Display(double **l, double **u);
        void Display(double **l, double **u, double **d);
        void CurrentSolution();
        // Menu
        bool Menu();
        // Starting Matrices
        bool InputFile();
        bool RandomStart();
        // Save current Matrix and current vector to file called Output.txt
        bool SaveData();
        bool SaveSolution();
        // Check Solution
        bool CheckSol();
        // Affect Matrices
        bool GaussianElim();
        bool LU_Decom();
        bool BackSolve();
        bool BackSolve(double **, std::vector<double>&);
        bool ForwardSolve(double **, std::vector<double>&);
        bool SwitchRows(int, int);
        double UpdateNextRow(double, double, double);
        bool DotProduct(double **, std::vector<double>&);
        bool DotProduct(double **, std::vector<double>&, std::vector<double>&);
        bool DotProduct(double **, int x);
        bool DotProduct(double **lhs, double **rhs, double **newM);
        bool AddMatrices(double **lhs, double **rhs, double **newM);
        bool AddVec(std::vector<double>&, std::vector<double>&);
        bool SubVec(std::vector<double>&, std::vector<double>&);
        double norm(std::vector<double>& v);
        double TwoNorm(std::vector<double>&);
        // Iterative
        // Jacobi
        bool Jacobi();
        bool Inverse(double **);
        // Gauss Seidel
        bool GaussSeidel();
        // SOR
        bool SOR();
        // Power Method
        bool PowerMethod();
        bool Bisection();
        bool NewthonMethod();
        double f(double x);
        double ff(double x);
        double Fx(double x);

};


#endif // MATRIX_H_INCLUDED
