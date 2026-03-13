#pragma once

#include <vector>

/**
 * @brief Computes the product of polynomial A and B using FFT computations.
 * 
 * @param A The first polynomial.
 * @param B The second polynomial.
 * 
 * @return std::vector<int> The resulting polynomial.
 */
std::vector<int> multiplyPolynomials(const std::vector<int>& A, const std::vector<int>& B);
