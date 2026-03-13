#include <cmath>
#include <complex>

#include "MultiplyPolynomials.hpp"

// Type alias for complex numbers to reduce messy code.
using cd = std::complex<double>;

const double PI = acos(-1);

void fft(std::vector<cd>& a, bool invert);

std::vector<int> multiplyPolynomials(const std::vector<int>& A, const std::vector<int>& B) {
    // Handle null or zero case.
    if (A.empty() || B.empty() || (A.size() == 1 && A[0] == 0) || (B.size() == 1 && B[0] == 0)) {
        return { 0 };
    }

    // Find the nearest power of 2 that is large enough to hold the product.
    int n = 1;
    while (n < A.size() + B.size()) n <<= 1;

    std::vector<cd> fa(A.begin(), A.end());
    std::vector<cd> fb(B.begin(), B.end());
    fa.resize(n);
    fb.resize(n);

    // Forward FFT: Convert both polynomials to point-value representation.
    fft(fa, false);
    fft(fb, false);

    // Point-wise multiplication in linear time.
    for (int i = 0; i < n; i++) {
        fa[i] *= fb[i];
    }

    // Inverse FFT: Convert the product back to coefficient representation.
    fft(fa, true);

    // Convert the complex numbers back to integers, rounding to fix floating point inaccuracies.
    std::vector<int> result(n);

    for (int i = 0; i < n; i++) {
        result[i] = round(fa[i].real());
    }

    while (result.size() > 1 && result.back() == 0) {
        result.pop_back();
    }

    return result;
}

/**
 * @brief The Cooley-Turkey recursive FFT algorithm.
 * 
 * @param a The polynomial to operate on.
 * @param invert Whether to calculate the inverse FFT or not.
 */
void fft(std::vector<cd> &a, bool invert) {
    int n = a.size();

    // A polynomial of degree 0 is just its constant coefficient.
    if (n == 1) return;

    // Split the polynomial into even and odd indexed coefficients.
    std::vector<cd> a0(n / 2), a1(n / 2);

    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[2 * i];
        a1[i] = a[2 * i + 1];
    }

    // Recursively transform the two halves.
    fft(a0, invert);
    fft(a1, invert);

    // Calculate the principal nth root of unity.
    double angle = 2 * PI / n * (invert ? -1 : 1);
    cd w(1), wn(cos(angle), sin(angle));

    for (int i = 0; i < n / 2; i++) {
        // Evaluate at the positive and negative roots simultaneously.
        a[i] = a0[i] + w * a1[i];
        a[i + n / 2] = a0[i] - w * a1[i];

        // If computing the inverse FFT, divide by 2 at each recursive
        // step to achieve the final division by n.
        if (invert) {
            a[i] /= 2;
            a[i + n / 2] /= 2.0;
        }

        w *= wn;
    }
}
