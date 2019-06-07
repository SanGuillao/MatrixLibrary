#include "Matrix.h"
#include "math.h"

bool Matrix::PowerMethod()
{
    double counter = 0, tempMu = 0, mu = 0.0;
    int i = 0, j =0;
    std::vector<double> x(row, 1);
    std::vector<double> y(row, 1);

    for(i=0;i<row;i++)
        x[i] = b_Vec[i];

    do
    {
        for(i=0;i<row;i++)
        {
            y[i]=0;
            for(j=0;j<col;j++)
                y[i]+=mat_Array[i][j]*x[j];
        }
        for(i=0;i<row;i++)
            x[i]=y[i];

        tempMu=mu;
        mu=0.0;

        for(i=0;i<row;i++)
        {
            if(fabs(x[i])>fabs(mu))
                mu=x[i];
        }
        for(i=0;i<row;i++)
            x[i]/=mu;

        counter++;

    }while(fabs(mu-tempMu)>0.00001 && counter < 500);

    cout << "Number of iterations: " << counter << endl;
    cout<<"Eigen value is : "<<mu<<endl;

    cout<<"Eigenvector is: " << endl;
    for(i = 0; i < row; i++)
    {
        cout << x[i] << endl;
    }


    //CheckSol();


    std::vector<double>().swap(x);
    std::vector<double>().swap(y);

    return true;
}

double Matrix::f(double x)
{
    double y = 8;
     y = y - (2*x);
     y = y - (9*x*x);
     y = y + 2 * pow(x,3.0);
     y = y + pow(x,4.0);
     return y;
}
double Matrix::ff(double x)
{
     double y = -2;
     y = y - (18*x);
     y = y + (6*pow(x,2.0));
     y = y + (4*pow(x, 3.0));
     return y;
}

bool Matrix::NewthonMethod()
{
    double x0;
    double xnew;
    cout<<"what is your first guess?"<<endl;
    cin>>x0;
    int ct = 0;
    double error=abs(f(x0));
    double tol = pow(10,-5);
    while (error > tol)
    {
        xnew = x0 - (f(x0)/ff(x0));
        error = abs(f(xnew));

        cout<<ct<<" solution "<<xnew<<" error "<<error<<endl;
        x0 = xnew;
        ct++;
    }

    cout<<"Final solution "<< xnew <<" in "<< ct << " iterations"<<endl;

    return false;
}

double Matrix::Fx(double x)
{
    double y = 0;
    y = x + log(x);

    return y;
}

bool Matrix::Bisection()
{
    double xL, xR, xMid;
    double fL, fR, fMid;
    cout<<"what is xL?"<<endl;
    cin>>xL;
    cout<<"what is xR?"<<endl;
    cin>>xR;

    xMid = (xL+xR)/2.0;
    int ct = 1;
    double error=abs(Fx(xMid));
    double tol = pow(10,-5);
    while (error > tol)
    {   fL = Fx(xL);
        fR = Fx(xR);
        fMid = Fx(xMid);
        cout<<"xMid: "<<xMid<<" fMid: "<<fMid<<endl;
        cout<<"fL: "<<fL<<" fR: "<<fR<<endl;
        error = abs(fMid);
        if(error>tol)
        {
        if((fL>0)&&(fR>0)&&(fMid>0)){
                                    if(fR>fL){xR=xMid;}
                                    else{xL=xMid;}
                                    }

        else if(fMid>0){
                    if(fL<0){xR = xMid;}
                    else if(fR<0){xL=xMid;}
                  }
        else if(fMid<0)
                    {
                    if(fL>0){xR=xMid;}
                    else if(fR>0){xL = xMid;}
                    }

        xMid = (xR + xL)/2.0;
        }
        cout<<ct<<" solution "<<xMid<<" error "<<error<<endl;
        ct++;

    }
    cout<<ct<<" solution "<<xMid<<" error "<<error<<endl;
    return false;
}

