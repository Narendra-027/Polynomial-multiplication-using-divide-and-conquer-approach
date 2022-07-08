# Polynomial-multiplication-using-divide-and-conquer-approach
A fast algorithm for multiplying polynomials. The naïve algorithm multiplies term by term, yielding time complexity of O(m*n) (where m,n are the number of terms in each polynomial, and assuming unit time for arithmetic operations).

But we can do better here as well! For simplicity, I show the case where n=m=2^(k+1). We wish to multiply P(x) by Q(x), so we write

P(x) = P1(x) + x^2k ⋅ P2(x)

Q(x) = Q1(x) + x^2k ⋅ Q2(x)

and we wish to calculate

P(x)*Q(x) = P1(x)*Q1(x) + x^2k ⋅ (P1(x)*Q2(x) + P2(x)*Q1(x)) + x^(2k+1) ⋅ P2(x)*Q2(x).

So define 3 multiples:

A(x) = P1(x)*Q1(x)

B(x) = P2(x)*Q2(x)

C(x) = (P1(x)+P2(x))*(Q1(x)+Q2(x))

Then

P(x)*Q(x) = A(x) + x^2k ⋅ (C(x)-A(x)-B(x)) + x^(2k+1) ⋅ B(x).

Multiply each of the 3 products using a similar algorithm, until some small value of k is reached (say, k=1). The net effect is to translate the 4 multiplications required by the naïve algorithm into just 3 multiplications.

A similar calculation to that of the Strassen algorithm for matrix multiplication shows that the algorithm runs in time O(3k) = O(nlg2 3) = O(n1.585).
Similar algorithms exist for matrix multiplication and complex number multiplication.
