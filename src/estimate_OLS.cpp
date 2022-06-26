#include <estimate_OLS.h>
#include <iostream>
#include <string>
#include <write_output.h>

#include <cblas.h>
#include <lapacke.h>

void estimate_OLS(int n, int m, real_t *XMAT, real_t *yVEC, real_t *OLSest, int method)
{
/*
    This function calls the function to compute OLS estimates depending on which method is specified
    if method == 0: estOLS_normal_equation(...)
    if method == 1: estOLS_Ax_b_LU_factorization(...)
*/
    method = 0;
    switch (method) {
        case 0:
            // estimate OLS by directly computing the normal equation
            estOLS_normal_equation(n, m, XMAT, yVEC, OLSest);
            break;

        case 1:
            // estimate OLS using Ax=b and LU factorization
            estOLS_Ax_b_LU_factorization(n, m, XMAT, yVEC, OLSest);
            break;

        default:
            std::string errorMessage = std::string("method variable should be 0 or 1 in function ") + std::string(__FUNCTION__);
            throw std::runtime_error(errorMessage);
    } // end switch

}


void estOLS_normal_equation(int n, int m, real_t *XMAT, real_t *yVEC, real_t *OLSest)
{
/*
    This function computes OLS estimates by directly evaluating the normal equation
    OLSest = ((X^T)*X)^(-1) * (X^T) * y

    parameter naming:
    A = (X^T)*X
    note that the matrix inverse will be inplace
*/

    // allocate memory for A
    real_t *A = new real_t[m*m];

    // allocate memory to store A^(-1) * X^T
    real_t *C = new real_t[m*n];

    // calculate A (A = XMAT_transpose * XMAT)
    cblas_dgemm(CblasRowMajor, CblasTrans, CblasNoTrans, m, m, n, 1.0, XMAT, m, XMAT, m, 0.0, A, m);

    // LAPACKE parameters
    lapack_int info = 0;
    lapack_int lda = m;
    lapack_int *ipiv = new lapack_int[m*m];

    // compute LU factorization needed for computing A^(-1). Note that result is stored in A
    info = LAPACKE_dgetrf(LAPACK_ROW_MAJOR, m, m, A, lda, ipiv);
    if (info != 0)
    {
        throw std::runtime_error("LAPACKE_dgetrf failed.");
    }

    // compute A^(-1). Note that result is stored in A
    info = LAPACKE_dgetri(LAPACK_ROW_MAJOR, m, A, lda, ipiv);
    if (info != 0)
    {
        throw std::runtime_error("LAPACKE_dgetri failed.");
    }

    // compute A^(-1) * X^T. Result is stored in C
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasTrans, m, n, m, 1.0, A, m, XMAT, m, 0.0, C, n);

    // compute C * yVEC. Result is stored in OLSest
    cblas_dgemv(CblasRowMajor, CblasNoTrans, m, n, 1.0, C, n, yVEC, 1, 0.0, OLSest, 1);

    // free allocated memory
    delete [] A;
    delete [] C;
    delete [] ipiv;
}


void estOLS_Ax_b_LU_factorization(int n, int m, real_t *XMAT, real_t *yVEC, real_t *OLSest)
{
/* 
    This function computes OLS estimates by rearranging the normal equation into the
    for Ax = b and then solve Ax = b using LU factorization.

    Ax = b == ((XMAT^T)*XMAT)*beta = (X^T)*y
    therefore,
    A = ((XMAT^T)*XMAT)
    x = beta
    b = (X^T)*y
*/

    // allocate memory for A (Ax = b)
    real_t *A = new real_t[m*m];
    
    // calculate A (A = XMAT_transpose * XMAT)
    cblas_dgemm(CblasRowMajor, CblasTrans, CblasNoTrans, m, m, n, 1.0, XMAT, m, XMAT, m, 0.0, A, m);

    // // calculate XMAT^T * yVEC. Result is stored in OLSest
    cblas_dgemv(CblasRowMajor, CblasTrans, n, m, 1.0, XMAT, m, yVEC, 1, 0.0, OLSest, 1);

    // LAPACKE parameters
    lapack_int info = 0;
    lapack_int lda = m;
    lapack_int ldb = 1;
    lapack_int *ipiv = new lapack_int[m*m];

    // compute LU factorization of A. Note that result is stored in A
    info = LAPACKE_dgetrf(LAPACK_ROW_MAJOR, m, m, A, lda, ipiv);
    if (info != 0)
    {
        throw std::runtime_error("LAPACKE_dgetrf failed.");
    }
    
    // use the LU factorization of A to solve Ax = b. Note that result is stored in b(OLSest)
    info = LAPACKE_dgetrs(LAPACK_ROW_MAJOR, 'N', m, 1, A, lda, ipiv, OLSest, ldb);
    if (info != 0)
    {
        throw std::runtime_error("LAPACKE_dgetrs failed.");
    }

    // free allocated memory
    delete [] A;
    delete [] ipiv;
}