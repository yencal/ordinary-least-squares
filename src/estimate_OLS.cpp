#include <estimate_OLS.h>
#include <iostream>
#include <string>

void estimate_OLS(int n, int m, real_t *XMAT, real_t *yVEC, real_t *OLSest, int method)
{
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



// void estOLS_normal_equation(int n, int m, real_t *XMAT, real_t *yVEC, real_t *OLSest)
// {
// /*
//     This function computes OLS estimates by directly evaluating the normal equation
//     OLSest = ((X^T)*X)^(-1) * (X^T) * y

//     parameter naming:
//     A = (X^T)*X
//     note that the matrix inverse will be inplace
// */

//     // allocate memory for A
//     real_t *A = new real_t[m*m];

//     // allocate memory to store A^(-1) * X^T
//     real_t *C = new real_t[m*m];

//     // create matrix view of XMAT, A, and C
//     gsl_matrix_view XMAT_view = gsl_matrix_view_array(XMAT, n, m);
//     gsl_matrix_view A_view = gsl_matrix_view_array(A, m, m);
//     gsl_matrix_view C_view = gsl_matrix_view_array(C, m, m);

//     // create vector view of yVEC and OLSest
//     gsl_vector_view yVEC_view = gsl_vector_view_array(yVEC, n);
//     gsl_vector_view OLSest_view = gsl_vector_view_array(OLSest, m);

//     // calculate A (A = XMAT_transpose * XMAT)
//     gsl_blas_dgemm (CblasTrans, CblasNoTrans, 1.0, &XMAT_view.matrix, &XMAT_view.matrix, 0.0, &A_view.matrix);

//     // LAPACKE parameters
//     lapack_int info = 0;
//     lapack_int lda = m;
//     lapack_int *ipiv = new lapack_int[m*m];

//     // compute LU factorization needed for computing A^(-1). Note that result is stored in A
//     info = LAPACKE_dgetrf(LAPACK_ROW_MAJOR, m, m, A, lda, ipiv);
//     if (info == 1)
//     {
//         throw std::runtime_error("LAPACKE_dgetrf failed.");
//     }

//     // compute A^(-1). Note that result is stored in A
//     info = LAPACKE_dgetri(LAPACK_ROW_MAJOR, m, A, lda, ipiv);
//     if (info == 1)
//     {
//         throw std::runtime_error("LAPACKE_dgetri failed.");
//     }

//     // compute A^(-1) * X^T. Result is stored in C
//     printf("A_View: %ld x %ld\n", A_view.matrix.size1, A_view.matrix.size2);
//     printf("XMAT_View: %ld x %ld\n", XMAT_view.matrix.size1, XMAT_view.matrix.size2);
//     printf("C_View: %ld x %ld\n", C_view.matrix.size1, C_view.matrix.size2);
//     gsl_blas_dgemm (CblasNoTrans, CblasTrans, 1.0, &A_view.matrix, &XMAT_view.matrix, 0.0, &C_view.matrix);
// #if 0
//     // compute C * yVEC. Result is stored in OLSest
//     gsl_blas_dgemv (CblasNoTrans, 1.0,  &C_view.matrix, &yVEC_view.vector, 0.0, &OLSest_view.vector);

//     // free allocated memory
//     delete [] A;
//     delete [] C;
//     delete [] ipiv;
// #endif
// }

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

    // // create matrix view of XMAT and A 
    // gsl_matrix_view XMAT_view = gsl_matrix_view_array(XMAT, n, m);
    // gsl_matrix_view A_view = gsl_matrix_view_array(A, m, m);

    // // create vector view of yVEC and OLSest
    // gsl_vector_view yVEC_view = gsl_vector_view_array(yVEC, n);
    // gsl_vector_view OLSest_view = gsl_vector_view_array(OLSest, m);
    
    // calculate A (A = XMAT_transpose * XMAT)
    //gsl_blas_dgemm (CblasTrans, CblasNoTrans, 1.0, &XMAT_view.matrix, &XMAT_view.matrix, 0.0, &A_view.matrix);
    //cblas_sgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,M,N,K,alpha,A,LDA,B,LDB,beta,C,LDC);
    // op(A) is an m-by-k matrix,
    // op(B) is a k-by-n matrix,
    // C is an m-by-n matrix.
    cblas_dgemm(CblasRowMajor, CblasTrans, CblasNoTrans, m, m, n, 1.0, XMAT, m, XMAT, m, 0.0, A, m);

    print_data_to_screen<real_t> (A, m*m);

    // // calculate XMAT^T * yVEC. Result is stored in OLSest
    // //gsl_blas_dgemv (CblasTrans, 1.0,  &XMAT_view.matrix, &yVEC_view.vector, 0.0, &OLSest_view.vector);

    // // LAPACKE parameters
    // lapack_int info = 0;
    // lapack_int lda = m;
    // lapack_int ldb = 1;
    // lapack_int *ipiv = new lapack_int[m*m];

    // // compute LU factorization of A. Note that result is stored in A
    // info = LAPACKE_dgetrf(LAPACK_ROW_MAJOR, m, m, A, lda, ipiv);
    // if (info == 1)
    // {
    //     throw std::runtime_error("LAPACKE_dgetrf failed.");
    // }
    
    // // use the LU factorization of A to solve Ax = b. Note that result is stored in b(OLSest)
    // info = LAPACKE_dgetrs(LAPACK_ROW_MAJOR, 'N', m, 1, A, lda, ipiv, OLSest, ldb);
    // if (info == 1)
    // {
    //     throw std::runtime_error("LAPACKE_dgetrs failed.");
    // }

    // // free allocated memory
    // delete [] A;
    // delete [] ipiv;
}