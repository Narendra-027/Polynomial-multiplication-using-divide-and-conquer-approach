#include<stdio.h>
#include<stdlib.h>

// function will return the integer part of log value.
int log_a_to_base_2(int a){
    if(a <= 1){
        return 0;
    }
    else{
        return 1 + log_a_to_base_2(a / 2);
    }
}

int Pow(int x, int n){
    int res = 1;
    for(int i = 0; i < n; i++){
        res = res*x;
    }
    return res;
}

int *Multiply(int *p, int *q, int n);

int main(){
    int degree; // degree of polynomial
    int *pq;
    scanf("%d", &degree);
    
    int log2a = log_a_to_base_2(degree);
    int newDegree = Pow(2, log2a + 1) - 1; // converting the degree of polynomial in form of {2^(k) - 1}
    
    int *p = (int *)malloc((newDegree)*sizeof(int));
    int *q = (int *)malloc((newDegree)*sizeof(int));

    for(int i = 0; i <= degree; i++){
        scanf("%d", &p[i]);
    }

    for(int i = 0; i <= degree; i++){
        scanf("%d", &q[i]);
    }
    
    // filling the remaining spaces with 0
    for(int i = degree+1; i <= newDegree; i++){
        p[i] = 0;
        q[i] = 0;
    }
    
    pq = Multiply(p, q, newDegree+1);

    for(int i = 0; i <= degree*2; i++){
        printf("%d ", pq[i]);
    }
}

int** split(int *p, int n);
int* addPolynomial(int *p1, int *p2, int n);
int *MiddleTerm(int *A, int *B, int *C,int m);
int *combine(int *A, int *B, int *C, int m);


// function for multiplication of polynomial
/*
P(x) = P1(x) + x^(2^k)*P2(x)
Q(x) = Q1(x) + x^(2^k)*Q2(x)
and we wish to calculate
P(x)*Q(x) = {P1(x)*Q1(x)} + x^(2^k)*{(P1(x)*Q2(x) + P2(x)*Q1(x))} + x^(2^(k+1))*{P2(x)*Q2(x)}.
*/
int *Multiply(int *p, int *q, int n){
    n = (n+1)/2;
    
    if(n == 1){
        int a, b, c;
        a = (p[0])*(q[0]); 
        b = (p[1])*(q[1]);
        c = (p[0] + p[1])*(q[0] + q[1]);
        int *arr = (int*)malloc(3*sizeof(int));

        arr[0] = a;
        arr[1] = c - a - b;
        arr[2] = b;
        return arr;
    }
    else{
        int **P = split(p,2*n); // P(x) = p1(x) + p2(x)*(x^(n/2))
        int **Q = split(q,2*n); // Q(x) = q1(x) + q2(x)*(x^(n/2))
        int *p1 = P[0]; // p1(x)
        int *p2 = P[1]; // p2(x)
        int *q1 = Q[0]; // q1(x)
        int *q2 = Q[1]; // q2(x)
        
        int *p1_add_p2 = addPolynomial(p1, p2, n);
        int *q1_add_q2 = addPolynomial(q1, q2, n);

        int *A = Multiply(p1, q1, n); // p1(x)*p2(x)
        int *B = Multiply(p2, q2, n); //q1(x)*q2(x)
        int *C = Multiply(p1_add_p2, q1_add_q2, n); //(p1(x) + p2(x))*(q1(x) + q2(x))

        int *C1 = MiddleTerm(A, B, C, n); // (C - A - B) => {(p1(x) + p2(x))*(q1(x) + q2(x)) - p1(x)*q1(x) - p2(x)*q2(x)}
        int *PQ = combine(A, B, C1, n); 
        
        free(p1); free(p2); free(P);
        free(q1); free(q2); free(Q);
        free(A); free(B); free(C);
        free(p1_add_p2); free(q1_add_q2);
        free(C1);
       
        return PQ;
    }
}

// function for deviding the polynomial in two parts => P(x) = p1(x) + p2(x)*x^(n/2)
int** split(int *p, int n){
    int m = (n+1)/2;
    int *P1 = (int*)malloc(m*sizeof(int));
    int *P2 = (int*)malloc(m*sizeof(int));
    int j = 0;
    for(int i = 0; i < m; i++){
        P1[j] = p[i];
        j++;
    }
    j = 0;
    for(int i = m; i < n; i++){
        P2[j] = p[i];
        j++;
    }

    int **returnARR = (int* *)malloc(2*sizeof(int*));
    returnARR[0] = P1;
    returnARR[1] = P2;

    return returnARR;
}

// function for adding two polynomial.
int* addPolynomial(int *p1, int *p2, int n){
    int *arr = (int *)malloc(n*sizeof(int));

    for(int i = 0; i < n; i++){
        arr[i] = p1[i] + p2[i];
    }
    return arr;
}

//function for finding middle term which is C(x) - A(x) - B(x) => (p1(x) + p2(x))*((q1(x) + q2(x))) - p1(x)*q1(x) - p2(x)*q2(x);
int *MiddleTerm(int *A, int *B, int *C,int m){
    int size = 2*m - 2;
    int *arr = (int*)malloc((size+1)*sizeof(int));
    for(int i = 0; i <= size; i++){
        arr[i] = C[i] - A[i] - B[i];
    }
    return arr;
}


// function for combining the three multiplication terms in recursive function.
int *combine(int *A, int *B, int *C, int m){
    int size = 2*m + 2*m - 2;
    int *arr = (int *)malloc((size+1)*sizeof(int));
    for(int i = 0; i <= size; i++){
        arr[i] = 0;
    }
    int j = 0;
    for(int i = 0; i <= (2*m - 2); i++){
        arr[i] = A[j];
        j++;
    }
    j = 0;
    for(int i = m; i <= (m + 2*m - 2); i++){
        arr[i] = C[j] + arr[i];
        j++;
    }
    j = 0;
    for(int i = 2*m; i <= (2*m + 2*m - 2); i++){
        arr[i] = B[j] + arr[i];
        j++;
    }
    return arr;
}
