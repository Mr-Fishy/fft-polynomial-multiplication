#include <iostream>
#include <vector>
#include <cassert>

#include "MultiplyPolynomials.hpp"

/**
 * @brief Determines if two given polynomial vectors are equal.
 * 
 * @param result Polynomial A
 * @param expected Polynomial B
 * 
 * @return true The polynomials are equal.
 * @return false The polynomials are unequal.
 */
bool checkPolyEqual(std::vector<int> result, std::vector<int> expected) {
    // Clean any trailing zeros.
    while (!result.empty() && result.back() == 0) result.pop_back();
    while (!expected.empty() && expected.back() == 0) expected.pop_back();

    return result == expected;
}

/**
 * @brief Tests a simple multiplication case.
 * 
 * @details A(x) = 1 + 2x + 3x^2
 *          B(x) = 4 + 5x + 6x^2
 *          C(x) = 4 + 13x + 28x^2 + 27x^3 + 18x^4
 */
void testStandardMultiplication() {
    std::vector<int> A = { 1, 2, 3 };
    std::vector<int> B = { 4, 5, 6 };
    std::vector<int> C = { 4, 13, 28, 27, 18 };

    assert(checkPolyEqual(multiplyPolynomials(A, B), C));
    std::cout << "testStandardMultiplication passed.\n";
}

/**
 * @brief Tests for correct multiplication against zero.
 * 
 * @details A(x) = 1 + 2x
 *          B(x) = 0
 *          C(x) = 0
 * 
 */
void testMultiplyByZero() {
    std::vector<int> A = { 1, 2 };
    std::vector<int> B = { 0 };
    std::vector<int> C = { 0 };

    assert(checkPolyEqual(multiplyPolynomials(A, B), C));
    std::cout << "testMultiplyByZero passed.\n";
}

/**
 * @brief Tests for correct identity multiplication.
 * 
 * @details A(x) = 5 + 7x + 9x^2
 *          B(x) = 1
 *          C(x) = 5 + 7x + 9x^2
 * 
 */
void testMultiplyByIdentity() {
    std::vector<int> A = { 5, 7, 9 };
    std::vector<int> B = { 1 };
    std::vector<int> C = { 5, 7, 9 };

    assert(checkPolyEqual(multiplyPolynomials(A, B), C));
    std::cout << "testMultiplyByIdentity passed.\n";
}

/**
 * @brief Tests for correct multiplication between different degree polynomials.
 * 
 * @details A(x) = 1 + 1x
 *          B(x) = 1 + 1x + 1x^2
 *          C(x) = 1 + 2x + 2x^2 + 1x^3
 * 
 */
void testDifferentDegrees() {
    std::vector<int> A = { 1, 1 };
    std::vector<int> B = { 1, 1, 1 };
    std::vector<int> C = { 1, 2, 2, 1 };

    assert(checkPolyEqual(multiplyPolynomials(A, B), C));
    std::cout << "testDifferentDegrees passed.\n";
}

/**
 * @brief Tests for correct multiplication with negative coefficients.
 * 
 * @details A(x) = 1 - 1x
 *          B(x) = 1 + 1x
 *          C(x) = 1 - 1x^2
 * 
 */
void testNegativeCoefficients() {
    std::vector<int> A = { 1, -1 };
    std::vector<int> B = { 1, 1 };
    std::vector<int> C = { 1, 0, -1 };

    assert(checkPolyEqual(multiplyPolynomials(A, B), C));
    std::cout << "testNegativeCoefficients passed.\n";
}

int main(int, char**){
    std::cout << "Running FFT Polynomial Multiplication Tests...\n";

    testStandardMultiplication();
    testMultiplyByZero();
    testMultiplyByIdentity();
    testDifferentDegrees();
    testNegativeCoefficients();

    std::cout << "All tests passed successfully!\n";

    return EXIT_SUCCESS;
}
