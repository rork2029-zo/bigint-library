/*!
 * @file Div.c
 * @date 2023/12
 * @brief Source code of Division
*/
#include "Div.h"

/// =======================( Division )========================= ///
/*
    DIV_long
    - Multi-Precision Long DIvision
    - A : n워드 정수, B : 양수
    - A = BQ + R (Q:n워드 정수, 0 <= R < B)
    - return (Q, R0)
*/
void DIV_long(bigint** Q, bigint** R, bigint* A, bigint* B) {

    if( A == NULL || B == NULL ) {
        puts("--DIV_long function error--\nInvalid input value : null");
        return;
    }
    
    // case : A < B
    if( compare(A, B) == -1 ) {
        // return (0, A)
        bi_set_zero(Q);     // Q = 0
        bi_assign(R, A);    // R = A
        return;             /// return (0, A)
    }

    unsigned int n = A->wordlen;
    bi_new(Q, n);

    bigint* Qi = NULL;
    bigint* Ri = NULL, *Ri_1 = NULL;
    
    bi_set_zero(&Ri_1); // R_n = 0
    for( int i=n-1; i>=0; i-- )
    {
        l_shift(&Ri_1, WORD_BIT_SIZE); // Ri_1 << W
        Ri_1->a[0] = A->a[i];   // Ri_1W + Ai
        bi_refine(Ri_1);
        DIVC(&Qi, &Ri, Ri_1, B); // (Qi, Ri) <- DIVC(Ri_1W + Ai, B)
        bi_assign(&Ri_1, Ri);   // Ri_1 update
        (*Q)->a[i] = Qi->a[0];
    }
    bi_assign(R, Ri_1); // R0 = Ri_1
    bi_refine((*Q));

    //-----------------
    bi_delete(&Qi);
    bi_delete(&Ri);
    bi_delete(&Ri_1);
    //-----------------
    
    return;
}

/*
    DIVC
    - A : m+1워드 정수, B : m워드 정수
    - 0 <= A < BW
    - A = BQ + R (0 <= Q < W, 0 <= R < B)
*/
void DIVC(bigint** Q, bigint** R, bigint* A, bigint* B){

    if( A == NULL || B == NULL ) {
        puts("--DIVC function error--\nInvalid input value : null");
        return;
    }

    if( A->sign == NEGATIVE || B->sign == NEGATIVE ) {
        puts("--DIVC function error--\nInvalid input value : A: +, B: +");
        return;
    }

    // case : A < B 
    if( compareABS(A, B) == -1 ) {
        // return(0, A)
        bi_set_zero(Q);     // Q = 0
        bi_assign(R, A);    // R = A
        bi_refine((*R));
        return;             // return (0, A)
    }

    bigint* Ap = NULL;  bigint* Bp = NULL;  bigint* Qp = NULL;  bigint* Rp = NULL;

    unsigned int m = B->wordlen;
    unsigned int k = 0;
    
    /// Find k that makes msb = 1
    word B_msw = B->a[m-1];
    while( ((B_msw << k) & MSB_MASK) != MSB_MASK ) // msb = 1이 되는 k 구하기
        k++;
    
    bi_assign(&Ap, A);
    bi_assign(&Bp, B);
    l_shift(&Ap, k);    /// A' = 2^kA
    l_shift(&Bp, k);    /// B' = 2^kB

    DIVCC(&Qp, &Rp, Ap, Bp);    // Q', R' <- DIVCC(A', B')

    bi_assign(Q, Qp);   // Q <- Q'
    r_shift(&Rp, k);    // R' <- 2^(-k)R'
    bi_assign(R, Rp);
    bi_refine((*R));

    //-----------------
    bi_delete(&Ap);
    bi_delete(&Bp);
    bi_delete(&Qp);
    bi_delete(&Rp);
    //-----------------

    return;
}

/*
    DIVCC
    - A : n워드 정수, B : m워드 정수
    - 0 < B <= A < B*W, B_m-1 >= 2^(w-1)
    - A = BQ + R (0 <= Q < W, 0 <= R < B)
*/
void DIVCC(bigint** Q, bigint** R, bigint* A, bigint* B) {

    /// Exception Handling
    if( A == NULL || B == NULL ) {
        puts("--DIVCC function error--\nInvalid input value : null");
        return;
    }

    if( A->sign == NEGATIVE || B->sign == NEGATIVE ) {
        puts("--DIVCC function error--\nInvalid input value : NEGATIVE INPUT");
        return;
    }

    if( compare(A, B) == -1 ) {
        puts("--DIVCC function error--\nInvalid input value : A should be larger than B");
        return;
    }

    bigint* bq = NULL;
    bigint* rp = NULL;
    bigint* temp = NULL;
    bigint* temp2 = NULL;

    unsigned int n = A->wordlen;
    unsigned int m = B->wordlen;

    bi_new(Q, 1);

    if( n == m ) 
    {
        (*Q)->a[0] = A->a[m-1] / B->a[m-1];
    }
    
    else if( n == (m+1) ) 
    {
        if( A->a[m] == B->a[m-1] ) {
            (*Q)->a[0] = WORD_INTEGER_MAX; // Q <- W-1
        }
        else {
            // temp = Am*W + Am-1
            bi_new(&temp, 2);
            temp->a[1] = A->a[m];
            temp->a[0] = A->a[m-1];
            Two_word_long_DIV(&((*Q)->a[0]), temp, &(B->a[m-1]));
        }
    }
    // R <- A - BQ
    Karatsuba_MUL(&bq, B, (*Q), 2);  // Calculate BQ
    SUB(R, A, bq);  

    while( (*R)->sign == NEGATIVE ) 
    {
        (*Q)->a[0] -= 1;
        ADD(&temp2, (*R), B);
        bi_assign(R, temp2);        
    }
    //-----------------
    bi_delete(&temp);
    bi_delete(&temp2);
    bi_delete(&bq);
    bi_delete(&rp);
    //-----------------

    return;
}

/*
    Two_word_long_DIV
    - A = A1*W + A0 (A1, A0 : 1-word)
    - B : [2^(w-1), 2^w)
    - A1 < B
    - A = BQ + R  (0 <= Q < W, 0 <= R < B)
    - return Q (1-word)
*/
void Two_word_long_DIV(word* Q, bigint* A, word* B) 
{   
    if( Q == NULL || A == NULL || B == NULL ) {
        puts("--Two_word_long_DIV function error--\nInvalid input : null");
        return;
    }
    /// (Q, R) <- (0, A1)
    *Q = 0;           /// Q <- 0
    word R = A->a[1]; /// R <- A1

    for( int j = WORD_BIT_SIZE-1; j>=0; j-- ) {
        if( R >= MSB_MASK ) 
        /// R >= 2^(w-1) = 0b100....0000 = 0x80...0 = MSB_MASK
        {  
            /// (Q, R) <- (Q + 2^j, 2R + aj - B)
            (*Q) += ((word)1 << j);
            R = 2*R + (((A->a[0] >> j) & 0x1) - (*B));
        }
        else { 
            /// R <- 2R + aj
            R = 2*R + ((A->a[0] >> j) & 0x1);
            
            if( R >= (*B) ) {
                // (Q, R) <- (Q + 2^j, R - B)
                (*Q) += ((word)1 << j);
                R = R - (*B);
            }
        }
    }
    return; // return Q
}
/// =========================================================== ///


/// ====================( Fast Reduction )===================== ///
/*
    Barrett Reduction
    + : T를 사전계산하여 연산 속도를 개선함

    - 0 <= A < W^2n

*/
void Barrett_reduction(bigint** R, bigint* A, bigint* N, bigint* T) {
    
    if( A == NULL || N == NULL || T == NULL ) {
        puts("--Barrett_reduction function error--\nInvalid input value");
        return;
    }

    if( A->sign == NEGATIVE || N->sign == NEGATIVE || T->sign == NEGATIVE) {
        puts("--Barrett_reduction function error--\nInvalid input value : BARRETT REDUCTION CAN'T PROCESS NEGATIVE INPUT");
        return;
    }
    
    if( A->wordlen > 2*(N->wordlen) ) {
        puts("--Barrett_reduction function error--\nInvalid input : 0 <= A < W^(2*n)");
        return;
    }

    unsigned int n = N->wordlen;

    bigint* Q_hat = NULL;
    bigint* Ap = NULL;
    bigint* Rp = NULL;

    bi_assign(&Ap, A);
    r_shift(&Ap, WORD_BIT_SIZE*(n-1));
    Karatsuba_MUL(&Q_hat, Ap, T, 2);
    r_shift(&Q_hat, WORD_BIT_SIZE*(n+1));

    Karatsuba_MUL(&Rp, N, Q_hat, 2); /// Rp = N * Q_hat
    SUB(R, A, Rp);  /// R = A - Rp = A - N * Q_hat

    while( compare(*R, N) >= 0 ) {
        SUB(&Rp, *R, N);
        bi_assign(R, Rp);
    }

    //-----------------
    bi_delete(&Q_hat);
    bi_delete(&Ap);
    bi_delete(&Rp);
    //-----------------

    return;
}
/// =========================================================== ///

