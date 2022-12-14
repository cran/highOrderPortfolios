// This file is a copy of several internal functions in R package PerformanceAnalytics (version: 2.0.4)
// for full details see: https://cran.r-project.org/web/packages/PerformanceAnalytics/
// Copyright (c) 2004-2020 Kris Boudt and Brian G. Peterson
// Copyright (c) 2004-2020 Peter Carl and Brian G. Peterson for PerformanceAnalytics

#include <R.h>
#include <Rinternals.h>

SEXP  M3vec2mat(SEXP XX, SEXP PP){
  /*
   arguments
   XX        : numeric vector with unique elements of a coskewness matrix
   PP        : integer, number of assets
   
   Written by Dries Cornilly
   */
  
  // // declare pointers for the vectors
  double *X;
  
  // use REAL() to access the C array inside the numeric vector passed in from R
  X = REAL(XX);
  int P = asInteger(PP);
  
  // allocate and construct the coskewness matrix
  SEXP M3mat = PROTECT(allocMatrix(REALSXP, P, P * P));
  double *rM3mat = REAL(M3mat);
  
  int iter = 0;
  // construct the coskewness matrix
  for (int ii = 0; ii < P; ii++) {
    for (int jj = ii; jj < P; jj++) {
      for (int kk = jj; kk < P; kk++) {
        // extract unique element and place into all positions
        if (ii == jj) {
          if (jj == kk) {
            // element phi_iii
            rM3mat[(ii * P + ii) * P + ii] = X[iter];
          } else {
            // element phi_iik
            rM3mat[(ii * P + ii) * P + kk] = X[iter];
            rM3mat[(ii * P + kk) * P + ii] = X[iter];
            rM3mat[(kk * P + ii) * P + ii] = X[iter];
          }
        } else {
          if (jj == kk) {
            // element phi_ijj
            rM3mat[(ii * P + jj) * P + jj] = X[iter];
            rM3mat[(jj * P + ii) * P + jj] = X[iter];
            rM3mat[(jj * P + jj) * P + ii] = X[iter];
          } else {
            // element phi_ijk
            rM3mat[(ii * P + jj) * P + kk] = X[iter];
            rM3mat[(ii * P + kk) * P + jj] = X[iter];
            rM3mat[(jj * P + ii) * P + kk] = X[iter];
            rM3mat[(jj * P + kk) * P + ii] = X[iter];
            rM3mat[(kk * P + ii) * P + jj] = X[iter];
            rM3mat[(kk * P + jj) * P + ii] = X[iter];
          }
        }
        iter++;
      } // loop kk
    } // loop jj
  } // loop ii
  
  UNPROTECT(1);
  return M3mat;
}

SEXP  M3mat2vec(SEXP XX, SEXP PP){
  /*
   arguments
   XX        : numeric vector with full vectorized coskewness matrix
   PP        : integer, number of assets
   
   Written by Dries Cornilly
   */
  
  // // declare pointers for the vectors
  double *X;
  
  // use REAL() to access the C array inside the numeric vector passed in from R
  X = REAL(XX);
  int P = asInteger(PP);
  
  // allocate and construct the vector with unique coskewness elements
  SEXP M3vec = PROTECT(allocVector(REALSXP, P * (P + 1) * (P + 2) / 6));
  double *rM3vec = REAL(M3vec);
  
  int iter = 0;
  // construct the vector with unique coskewness elements
  for (int ii = 0; ii < P; ii++) {
    for (int jj = ii; jj < P; jj++) {
      for (int kk = jj; kk < P; kk++) {
        // extract unique element
        rM3vec[iter] = X[(ii * P + jj) * P + kk];
        iter++;
      } // loop kk
    } // loop jj
  } // loop ii
  
  UNPROTECT(1);
  return M3vec;
}

SEXP  M4mat2vec(SEXP XX, SEXP PP){
  /*
   arguments
   XX        : numeric vector with full vectorized cokurtosis matrix
   PP        : integer, number of assets
   
   Written by Dries Cornilly
   */
  
  // // declare pointers for the vectors
  double *X;
  
  // use REAL() to access the C array inside the numeric vector passed in from R
  X = REAL(XX);
  int P = asInteger(PP);
  
  // allocate and construct the vector with unique cokurtosis elements
  SEXP M4vec = PROTECT(allocVector(REALSXP, P * (P + 1) * (P + 2) * (P + 3) / 24));
  double *rM4vec = REAL(M4vec);
  
  int iter = 0;
  // construct the vector with unique cokurtosis elements
  for (int ii = 0; ii < P; ii++) {
    for (int jj = ii; jj < P; jj++) {
      for (int kk = jj; kk < P; kk++) {
        for (int ll = kk; ll < P; ll++) {
          // extract unique element
          rM4vec[iter] = X[(ii * P * P + jj * P + kk) * P + ll];
          iter++;
        } // loop ll
      } // loop kk
    } // loop jj
  } // loop ii
  
  UNPROTECT(1);
  return M4vec;
}

SEXP  M4vec2mat(SEXP XX, SEXP PP){
  /*
   arguments
   XX        : numeric vector with unique elements of a cokurtosis matrix
   PP        : integer, number of assets
   
   Written by Dries Cornilly
   */
  
  // // declare pointers for the vectors
  double *X;
  
  // use REAL() to access the C array inside the numeric vector passed in from R
  X = REAL(XX);
  int P = asInteger(PP);
  
  // allocate and compute the cokurtosis matrix
  SEXP M4mat = PROTECT(allocMatrix(REALSXP, P, P * P * P));
  double *rM4mat = REAL(M4mat);
  
  int iter = 0;
  // compute the cokurtosis matrix
  for (int ii = 0; ii < P; ii++) {
    for (int jj = ii; jj < P; jj++) {
      for (int kk = jj; kk < P; kk++) {
        for (int ll = kk; ll < P; ll++) {
          // extract unique element and place into all positions
          if (ii == jj) {
            if (jj == kk) {
              if (kk == ll) {
                // element psi_iiii
                rM4mat[(ii * P * P + ii * P + ii) * P + ii] = X[iter];
              } else {
                // element psi_iiil
                rM4mat[(ii * P * P + ii * P + ii) * P + ll] = X[iter];
                rM4mat[(ii * P * P + ii * P + ll) * P + ii] = X[iter];
                rM4mat[(ii * P * P + ll * P + ii) * P + ii] = X[iter];
                rM4mat[(ll * P * P + ii * P + ii) * P + ii] = X[iter];
              }
            } else {
              if (kk == ll) {
                // element psi_iikk
                rM4mat[(ii * P * P + ii * P + kk) * P + kk] = X[iter];
                rM4mat[(ii * P * P + kk * P + ii) * P + kk] = X[iter];
                rM4mat[(ii * P * P + kk * P + kk) * P + ii] = X[iter];
                rM4mat[(kk * P * P + ii * P + ii) * P + kk] = X[iter];
                rM4mat[(kk * P * P + ii * P + kk) * P + ii] = X[iter];
                rM4mat[(kk * P * P + kk * P + ii) * P + ii] = X[iter];
              } else {
                // element psi_iikl
                rM4mat[(ii * P * P + ii * P + kk) * P + ll] = X[iter];
                rM4mat[(ii * P * P + ii * P + ll) * P + kk] = X[iter];
                rM4mat[(ii * P * P + kk * P + ii) * P + ll] = X[iter];
                rM4mat[(ii * P * P + kk * P + ll) * P + ii] = X[iter];
                rM4mat[(ii * P * P + ll * P + ii) * P + kk] = X[iter];
                rM4mat[(ii * P * P + ll * P + kk) * P + ii] = X[iter];
                rM4mat[(kk * P * P + ii * P + ii) * P + ll] = X[iter];
                rM4mat[(kk * P * P + ii * P + ll) * P + ii] = X[iter];
                rM4mat[(kk * P * P + ll * P + ii) * P + ii] = X[iter];
                rM4mat[(ll * P * P + ii * P + ii) * P + kk] = X[iter];
                rM4mat[(ll * P * P + ii * P + kk) * P + ii] = X[iter];
                rM4mat[(ll * P * P + kk * P + ii) * P + ii] = X[iter];
              }
            }
          } else {
            if (jj == kk) {
              if (kk == ll) {
                // element psi_ijjj
                rM4mat[(ii * P * P + jj * P + jj) * P + jj] = X[iter];
                rM4mat[(jj * P * P + ii * P + jj) * P + jj] = X[iter];
                rM4mat[(jj * P * P + jj * P + ii) * P + jj] = X[iter];
                rM4mat[(jj * P * P + jj * P + jj) * P + ii] = X[iter];
              } else {
                // element psi_ijjl
                rM4mat[(ii * P * P + jj * P + jj) * P + ll] = X[iter];
                rM4mat[(ii * P * P + jj * P + ll) * P + jj] = X[iter];
                rM4mat[(ii * P * P + ll * P + jj) * P + jj] = X[iter];
                rM4mat[(jj * P * P + ii * P + jj) * P + ll] = X[iter];
                rM4mat[(jj * P * P + ii * P + ll) * P + jj] = X[iter];
                rM4mat[(jj * P * P + jj * P + ii) * P + ll] = X[iter];
                rM4mat[(jj * P * P + jj * P + ll) * P + ii] = X[iter];
                rM4mat[(jj * P * P + ll * P + ii) * P + jj] = X[iter];
                rM4mat[(jj * P * P + ll * P + jj) * P + ii] = X[iter];
                rM4mat[(ll * P * P + ii * P + jj) * P + jj] = X[iter];
                rM4mat[(ll * P * P + jj * P + ii) * P + jj] = X[iter];
                rM4mat[(ll * P * P + jj * P + jj) * P + ii] = X[iter];
              }
            } else {
              if (kk == ll) {
                // element psi_ijkk
                rM4mat[(ii * P * P + jj * P + kk) * P + kk] = X[iter];
                rM4mat[(ii * P * P + kk * P + jj) * P + kk] = X[iter];
                rM4mat[(ii * P * P + kk * P + kk) * P + jj] = X[iter];
                rM4mat[(jj * P * P + ii * P + kk) * P + kk] = X[iter];
                rM4mat[(jj * P * P + kk * P + ii) * P + kk] = X[iter];
                rM4mat[(jj * P * P + kk * P + kk) * P + ii] = X[iter];
                rM4mat[(kk * P * P + ii * P + jj) * P + kk] = X[iter];
                rM4mat[(kk * P * P + ii * P + kk) * P + jj] = X[iter];
                rM4mat[(kk * P * P + jj * P + ii) * P + kk] = X[iter];
                rM4mat[(kk * P * P + jj * P + kk) * P + ii] = X[iter];
                rM4mat[(kk * P * P + kk * P + ii) * P + jj] = X[iter];
                rM4mat[(kk * P * P + kk * P + jj) * P + ii] = X[iter];
              } else {
                // element psi_ijkl
                rM4mat[(ii * P * P + jj * P + kk) * P + ll] = X[iter];
                rM4mat[(ii * P * P + jj * P + ll) * P + kk] = X[iter];
                rM4mat[(ii * P * P + kk * P + jj) * P + ll] = X[iter];
                rM4mat[(ii * P * P + kk * P + ll) * P + jj] = X[iter];
                rM4mat[(ii * P * P + ll * P + jj) * P + kk] = X[iter];
                rM4mat[(ii * P * P + ll * P + kk) * P + jj] = X[iter];
                rM4mat[(jj * P * P + ii * P + kk) * P + ll] = X[iter];
                rM4mat[(jj * P * P + ii * P + ll) * P + kk] = X[iter];
                rM4mat[(jj * P * P + kk * P + ii) * P + ll] = X[iter];
                rM4mat[(jj * P * P + kk * P + ll) * P + ii] = X[iter];
                rM4mat[(jj * P * P + ll * P + ii) * P + kk] = X[iter];
                rM4mat[(jj * P * P + ll * P + kk) * P + ii] = X[iter];
                rM4mat[(kk * P * P + ii * P + jj) * P + ll] = X[iter];
                rM4mat[(kk * P * P + ii * P + ll) * P + jj] = X[iter];
                rM4mat[(kk * P * P + jj * P + ii) * P + ll] = X[iter];
                rM4mat[(kk * P * P + jj * P + ll) * P + ii] = X[iter];
                rM4mat[(kk * P * P + ll * P + ii) * P + jj] = X[iter];
                rM4mat[(kk * P * P + ll * P + jj) * P + ii] = X[iter];
                rM4mat[(ll * P * P + ii * P + jj) * P + kk] = X[iter];
                rM4mat[(ll * P * P + ii * P + kk) * P + jj] = X[iter];
                rM4mat[(ll * P * P + jj * P + ii) * P + kk] = X[iter];
                rM4mat[(ll * P * P + jj * P + kk) * P + ii] = X[iter];
                rM4mat[(ll * P * P + kk * P + ii) * P + jj] = X[iter];
                rM4mat[(ll * P * P + kk * P + jj) * P + ii] = X[iter];
              }
            }
          }
          iter++;
        } // loop ll
      } // loop kk
    } // loop jj
  } // loop ii
  
  UNPROTECT(1);
  return M4mat;
}

SEXP  M3port(SEXP WW, SEXP XX, SEXP PP){
  /*
   arguments
   WW        : numeric vector with the portfolio weights
   XX        : numeric vector with unique elements of a coskewness matrix
   PP        : integer, number of assets
   
   Written by Dries Cornilly
   */
  
  // // declare pointers for the vectors
  double *X, *W;
  
  // use REAL() to access the C array inside the numeric vector passed in from R
  X = REAL(XX);
  W = REAL(WW);
  int P = asInteger(PP);
  
  // allocate and compute the portfolio skewness
  SEXP skew = PROTECT(allocVector(REALSXP, 1));
  double *rskew = REAL(skew);
  rskew[0] = 0.0;
  
  int iter = 0;
  // compute the portfolio skewness
  for (int ii = 0; ii < P; ii++) {
    for (int jj = ii; jj < P; jj++) {
      for (int kk = jj; kk < P; kk++) {
        // add to the matrix product
        if (ii == jj) {
          if (jj == kk) {
            // element phi_iii
            rskew[0] += X[iter] * W[ii] * W[ii] * W[ii];
          } else {
            // element phi_iik
            rskew[0] += 3.0 * X[iter] * W[ii] * W[ii] * W[kk];
          }
        } else {
          if (jj == kk) {
            // element phi_ijj
            rskew[0] += 3.0 * X[iter] * W[ii] * W[jj] * W[jj];
          } else {
            // element phi_ijk
            rskew[0] += 6.0 * X[iter] * W[ii] * W[jj] * W[kk];
          }
        }
        iter++;
      } // loop kk
    } // loop jj
  } // loop ii
  
  UNPROTECT(1);
  return skew;
}


SEXP  M3port_grad(SEXP WW, SEXP XX, SEXP PP){
  /*
   arguments
   WW        : numeric vector with the portfolio weights
   XX        : numeric vector with unique elements of a coskewness matrix
   PP        : integer, number of assets
   
   Written by Dries Cornilly
   */
  
  // // declare pointers for the vectors
  double *X, *W;
  
  // use REAL() to access the C array inside the numeric vector passed in from R
  X = REAL(XX);
  W = REAL(WW);
  int P = asInteger(PP);
  
  // allocate and compute gradient of the portfolio skewness
  SEXP skew_grad = PROTECT(allocVector(REALSXP, P));
  double *rskew_grad = REAL(skew_grad);
  for (int ii = 0; ii < P; ii++) {
    rskew_grad[ii] = 0.0;
  }
  
  int iter = 0;
  // compute the gradient of the portfolio skewness
  for (int ii = 0; ii < P; ii++) {
    for (int jj = ii; jj < P; jj++) {
      for (int kk = jj; kk < P; kk++) {
        // add to the inner product
        if (ii == jj) {
          if (jj == kk) {
            // element phi_iii
            rskew_grad[ii] += 3.0 * X[iter] * W[ii] * W[ii];
          } else {
            // element phi_iik
            rskew_grad[ii] += 6.0 * X[iter] * W[ii] * W[kk];
            rskew_grad[kk] += 3.0 * X[iter] * W[ii] * W[ii];
          }
        } else {
          if (jj == kk) {
            // element phi_ijj
            rskew_grad[ii] += 3.0 * X[iter] * W[jj] * W[jj];
            rskew_grad[jj] += 6.0 * X[iter] * W[ii] * W[jj];
          } else {
            // element phi_ijk
            rskew_grad[ii] += 6.0 * X[iter] * W[jj] * W[kk];
            rskew_grad[jj] += 6.0 * X[iter] * W[ii] * W[kk];
            rskew_grad[kk] += 6.0 * X[iter] * W[ii] * W[jj];
          }
        }
        iter++;
      } // loop kk
    } // loop jj
  } // loop ii
  
  UNPROTECT(1);
  return skew_grad;
}


SEXP  M4port(SEXP WW, SEXP XX, SEXP PP){
  /*
   arguments
   WW        : numeric vector with the portfolio weights
   XX        : numeric vector with unique elements of a cokurtosis matrix
   PP        : integer, number of assets
   
   Written by Dries Cornilly
   */
  
  // // declare pointers for the vectors
  double *X, *W;
  
  // use REAL() to access the C array inside the numeric vector passed in from R
  X = REAL(XX);
  W = REAL(WW);
  int P = asInteger(PP);
  
  // allocate and compute the portfolio kurtosis
  SEXP kurt = PROTECT(allocVector(REALSXP, 1));
  double *rkurt = REAL(kurt);
  rkurt[0] = 0.0;
  
  int iter = 0;
  // compute the portfolio central fourth moment
  for (int ii = 0; ii < P; ii++) {
    for (int jj = ii; jj < P; jj++) {
      for (int kk = jj; kk < P; kk++) {
        for (int ll = kk; ll < P; ll++) {
          // add to the matrix product
          if (ii == jj) {
            if (jj == kk) {
              if (kk == ll) {
                // element psi_iiii
                rkurt[0] += X[iter] * W[ii] * W[ii] * W[ii] * W[ii];
              } else {
                // element psi_iiil
                rkurt[0] += 4.0 * X[iter] * W[ii] * W[ii] * W[ii] * W[ll];
              }
            } else {
              if (kk == ll) {
                // element psi_iikk
                rkurt[0] += 6.0 * X[iter] * W[ii] * W[ii] * W[kk] * W[kk];
              } else {
                // element psi_iikl
                rkurt[0] += 12.0 * X[iter] * W[ii] * W[ii] * W[kk] * W[ll];
              }
            }
          } else {
            if (jj == kk) {
              if (kk == ll) {
                // element psi_ijjj
                rkurt[0] += 4.0 * X[iter] * W[ii] * W[jj] * W[jj] * W[jj];
              } else {
                // element psi_ijjl
                rkurt[0] += 12.0 * X[iter] * W[ii] * W[jj] * W[jj] * W[ll];
              }
            } else {
              if (kk == ll) {
                // element psi_ijkk
                rkurt[0] += 12.0 * X[iter] * W[ii] * W[jj] * W[kk] * W[kk];
              } else {
                // element psi_ijkl
                rkurt[0] += 24.0 * X[iter] * W[ii] * W[jj] * W[kk] * W[ll];
              }
            }
          }
          iter++;
        } // loop ll
      } // loop kk
    } // loop jj
  } // loop ii
  
  UNPROTECT(1);
  return kurt;
}

SEXP  M4port_grad(SEXP WW, SEXP XX, SEXP PP){
  /*
   arguments
   WW        : numeric vector with the portfolio weights
   XX        : numeric vector with unique elements of a cokurtosis matrix
   PP        : integer, number of assets
   
   Written by Dries Cornilly
   */
  
  // // declare pointers for the vectors
  double *X, *W;
  
  // use REAL() to access the C array inside the numeric vector passed in from R
  X = REAL(XX);
  W = REAL(WW);
  int P = asInteger(PP);
  
  // allocate and compute the gradient of the portfolio kurtosis
  SEXP kurt_grad = PROTECT(allocVector(REALSXP, P));
  double *rkurt_grad = REAL(kurt_grad);
  for (int ii = 0; ii < P; ii++) {
    rkurt_grad[ii] = 0.0;
  }
  
  int iter = 0;
  // compute the gradient portfolio central fourth moment
  for (int ii = 0; ii < P; ii++) {
    for (int jj = ii; jj < P; jj++) {
      for (int kk = jj; kk < P; kk++) {
        for (int ll = kk; ll < P; ll++) {
          // add to the matrix product
          if (ii == jj) {
            if (jj == kk) {
              if (kk == ll) {
                // element psi_iiii
                rkurt_grad[ii] += 4.0 * X[iter] * W[ii] * W[ii] * W[ii];
              } else {
                // element psi_iiil
                rkurt_grad[ii] += 12.0 * X[iter] * W[ii] * W[ii] * W[ll];
                rkurt_grad[ll] += 4.0 * X[iter] * W[ii] * W[ii] * W[ii];
              }
            } else {
              if (kk == ll) {
                // element psi_iikk
                rkurt_grad[ii] += 12.0 * X[iter] * W[ii] * W[kk] * W[kk];
                rkurt_grad[kk] += 12.0 * X[iter] * W[ii] * W[ii] * W[kk];
              } else {
                // element psi_iikl
                rkurt_grad[ii] += 24.0 * X[iter] * W[ii] * W[kk] * W[ll];
                rkurt_grad[kk] += 12.0 * X[iter] * W[ii] * W[ii] * W[ll];
                rkurt_grad[ll] += 12.0 * X[iter] * W[ii] * W[ii] * W[kk];
              }
            }
          } else {
            if (jj == kk) {
              if (kk == ll) {
                // element psi_ijjj
                rkurt_grad[ii] += 4.0 * X[iter] * W[jj] * W[jj] * W[jj];
                rkurt_grad[jj] += 12.0 * X[iter] * W[ii] * W[jj] * W[jj];
              } else {
                // element psi_ijjl
                rkurt_grad[ii] += 12.0 * X[iter] * W[jj] * W[jj] * W[ll];
                rkurt_grad[jj] += 24.0 * X[iter] * W[ii] * W[jj] * W[ll];
                rkurt_grad[ll] += 12.0 * X[iter] * W[ii] * W[jj] * W[jj];
              }
            } else {
              if (kk == ll) {
                // element psi_ijkk
                rkurt_grad[ii] += 12.0 * X[iter] * W[jj] * W[kk] * W[kk];
                rkurt_grad[jj] += 12.0 * X[iter] * W[ii] * W[kk] * W[kk];
                rkurt_grad[kk] += 24.0 * X[iter] * W[ii] * W[jj] * W[kk];
              } else {
                // element psi_ijkl
                rkurt_grad[ii] += 24.0 * X[iter] * W[jj] * W[kk] * W[ll];
                rkurt_grad[jj] += 24.0 * X[iter] * W[ii] * W[kk] * W[ll];
                rkurt_grad[kk] += 24.0 * X[iter] * W[ii] * W[jj] * W[ll];
                rkurt_grad[ll] += 24.0 * X[iter] * W[ii] * W[jj] * W[kk];
              }
            }
          }
          iter++;
        } // loop ll
      } // loop kk
    } // loop jj
  } // loop ii
  
  UNPROTECT(1);
  return kurt_grad;
}
