#pragma once

#include <utilities.h>

void estimate_OLS(int n, int m, real_t *XMAT, real_t *yVEC, real_t *OLSest, int method);

void estOLS_normal_equation(int n, int m, real_t *XMAT, real_t *yVEC, real_t *OLSest);

void estOLS_Ax_b_LU_factorization(int n, int m, real_t *XMAT, real_t *yVEC, real_t *OLSest);