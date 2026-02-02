/*!
 * @file Mul.c
 * @date 2023/12
 * @brief Source code of Multiplication
*/
#include "Mul.h"

/// ======================( Multiplication )=========================== ///

void SingleWordMul(word* C, word A, word B)
{
    /// Exception Handling
    if ( C == NULL )
        C = (word*)calloc(2, sizeof(word));

    /// Split a word into half size
    word A0 = (A & MASK_LAST);
    word A1 = A >> (WORD_BIT_SIZE/2);

    word B0 = (B & MASK_LAST);
    word B1 = B >> (WORD_BIT_SIZE/2);

    word T1 = A1 * B0;
    word T0 = A0 * B1;

    T0 = T1 + T0;
    T1 = (T0 < T1);

    word C1 = A1 * B1;
    word C0 = A0 * B0;

    word T = C0; 

    C0 = C0 + (T0 << WORD_BIT_SIZE/2);
    C1 = C1 + (T1 << WORD_BIT_SIZE/2) + (T0 >> WORD_BIT_SIZE/2) + (C0 < T);
    
    /// C <- (C1 << w) + C0
    C[1] = C1;
    C[0] = C0;
}

void MulC(bigint** C, bigint* A, bigint* B)
{
    /// Exception Handling
    if( A == NULL || B == NULL ) {
        puts("--MulC function error--\nInvalid input value : null");
        return;
    }
    int n = A->wordlen;
    int m = B->wordlen;

    bi_new(C, n+m);
    bigint *re_C = NULL;
    bi_new(&re_C, n+m);
    set_all_zero(C);

    for(int i=0; i<n; i++){
        for(int j=0 ;j<m; j++){
            bigint* T = NULL;
            bi_new(&T, 2);
            SingleWordMul(T->a, A->a[i], B->a[j]);      /// T <- A_j * B_i
            l_shift(&T, (i+j)*WORD_BIT_SIZE);           /// T <- T << w*(i+j)
            
            ADD(C, re_C, T);                            /// C <- ADD(C,T)
            bi_assign(&re_C, *C);
            //-------------
            bi_delete(&T);
        }
    }
    bi_refine(*C);
    //-----------------
    bi_delete(&re_C);
}

void MUL(bigint** C, bigint* A, bigint* B)
{
    /// Exception Handling
    if( A == NULL || B == NULL ) {
        puts("--MUL function error--\nInvalid input value : null");
        return;
    }

    // case : A == 0 or B == 0
    if( bi_is_zero(A) == TRUE || bi_is_zero(B) == TRUE ) {
        bi_set_zero(C);
        return;
    }
    else if( bi_is_one(A) == TRUE ) { // case : A == 1
        bi_assign(C, B);
        return;
    }
    else if( bi_is_one(B) == TRUE ) { // case : B == 1
        bi_assign(C, A);
        return;
    }

    bigint* re_A = NULL;
    bigint* re_B = NULL;
    bi_assign(&re_A, A);    
    bi_assign(&re_B, B);
    re_A->sign = NON_NEGATIVE;
    re_B->sign = NON_NEGATIVE;
    
    MulC(C, re_A, re_B);      /// C <- MULC(|A|,|B|)
    (*C)->sign = (A->sign ^ B->sign);

    //-----------------
    bi_delete(&re_A);
    bi_delete(&re_B);
    //-----------------
    return;
}



void ImpMulC(bigint** C, bigint* A, bigint* B)
{
    /// Exception Handling
    if( A == NULL || B == NULL ) {
        puts("--ImpMulC function error--\nInvalid input value : null");
        return;
    }

    if( A->sign == NEGATIVE || B->sign == NEGATIVE ) {
        puts("--ImpMulC function error--\nimprove multiplication input = A >= 0 , B >= 0");
        return;
    }

    int n = A->wordlen;
    int m = B->wordlen;
    int np = (A->wordlen)*2;
    int mp = (B->wordlen)*2;

    word* tmpA = (word*)calloc(np, sizeof(word));
    word* tmpB = (word*)calloc(mp, sizeof(word));
    
    /// Split a big integer into an array
    for(int i=0; i<np; i++){
        if(i%2==0){tmpA[i] = A->a[i/2] & MASK_LAST;}
        else{tmpA[i]= A->a[i/2] >> (sizeof(word)*4);}
    }

    for(int i=0; i<mp; i++){
        if(i%2==0){tmpB[i] = B->a[i/2] & MASK_LAST;}
        else{tmpB[i] = B->a[i/2] >> (sizeof(word)*4);}
    }

    bi_new(C, np+mp);
    set_all_zero(C);
    
    bigint* tmpC = NULL;
    bi_new(&tmpC, np+mp);

    bigint* T = NULL;
    bi_new(&T, np+1);

    for(int i=0; i<mp; i++){  
        bigint* T0 = NULL;
        bigint* T1 = NULL;
        bi_new(&T1, np);
        bi_new(&T0, np);

        word* tmp1 = (word*)calloc(n, sizeof(word));
        word* tmp2 = (word*)calloc(m, sizeof(word));
        word buf;
        for(int k=0; k<(np/2); k++){
            SingleWordMul(tmp1, tmpA[2*k], tmpB[i]);
            SingleWordMul(tmp2, tmpA[2*k+1], tmpB[i]);
            T0->a[k] = *tmp1;           
            T1->a[k] = *tmp2;
        }
        l_shift(&T1, sizeof(word)*4);
        
        free(tmp1); free(tmp2);
        bi_refine(T0);
        bi_refine(T1);
        
        ADD(&T, T0, T1);                    /// T <- ADDC(T0,T1)
        l_shift(&T, sizeof(word)*4*i);      /// T <- T << w*i

        ADD(C, tmpC, T);                    /// C <- ADDC(C,T)

        bi_assign(&tmpC, *C);

        //-----------------
        bi_delete(&T1);
        bi_delete(&T0);
        bi_delete(&T);
        //-----------------
    }
    free(tmpA); free(tmpB);
    bi_refine(*C);
    bi_delete(&tmpC);
}

void Karatsuba_MUL(bigint** C, bigint* A, bigint* B, unsigned int flag)
{
    /// Exception Handling
    if( A == NULL || B == NULL ) {
        puts("--Karatsuba_MUL fucntion error--\nInvalid input value : null");
        return;
    }

    if( A->sign == NEGATIVE || B->sign == NEGATIVE ) {
        puts("Karatsuba multiplication input = A : +, B : +");
        return;
    }
    unsigned int n = A->wordlen;
    unsigned int m = B->wordlen;

    if( flag >= min(n, m) ) {
        ImpMulC(C, A, B);
        return;
    }
    
    bigint* A1 = NULL, *A0 = NULL, *B1 = NULL, *B0 = NULL;
    bigint* T1 = NULL, *T0 = NULL;
    bigint* Cp = NULL, *S1 = NULL, *S0 = NULL, *S = NULL, *Sp = NULL;

    unsigned int l = (max(n, m)+1) >> 1;

    //== A1 set
    // A1 = A >> lw
    bi_assign(&A1, A);
    r_shift(&A1, l * WORD_BIT_SIZE);

    //== A0 set
    // A0 = A mod 2^lw
    bi_new(&A0, min(A->wordlen,l));
    bi_set_by_array(&A0, A->sign, A->a, min(A->wordlen, l));
    bi_refine(A0);
    
    //== B1 set
    // B1 = B >> lw;
    bi_assign(&B1, B);
    r_shift(&B1, l * WORD_BIT_SIZE);

    //== B0 set
    // B0 = B mod 2^lw
    bi_new(&B0, min(B->wordlen, l));
    bi_set_by_array(&B0, B->sign, B->a, min(B->wordlen, l));
    bi_refine(B0);

    Karatsuba_MUL(&T1, A1, B1, flag); //== T1 set
    Karatsuba_MUL(&T0, A0, B0, flag); //== T0 set

    /// C <- (T1 << 2lw) + T0 구현
    bigint* C_ = NULL;
    bi_assign(&C_, T1);
    l_shift(&C_, 2*l*WORD_BIT_SIZE);
    ADD(&Cp, C_, T0);

    SUB(&S1, A0, A1); 
    SUB(&S0, B1, B0); 
    
    int S_sign = S1->sign ^ S0->sign;

    S1->sign = NON_NEGATIVE;
    S0->sign = NON_NEGATIVE;

    bi_new(&Sp, 1);
    Karatsuba_MUL(&Sp, S1, S0, flag);
    Sp->sign = S_sign;

    ADD(&S, Sp, T1);
    bi_assign(&Sp, S);
    ADD(&S, Sp, T0);

    l_shift(&S, l * WORD_BIT_SIZE);

    ADD(C, Cp, S); /// Final input to C

    //-----------------
    bi_delete(&S);
    bi_delete(&Sp);
    bi_delete(&Cp);
    bi_delete(&C_);
    bi_delete(&A1);
    bi_delete(&A0);
    bi_delete(&B1);
    bi_delete(&B0);
    bi_delete(&T1);
    bi_delete(&T0);
    bi_delete(&S1);
    bi_delete(&S0);
    //-----------------

    return;
}
