/*!
 * @file Squ.c
 * @date 2023/12
 * @brief Source code of Squaring
*/
#include "Squ.h"

/// ==================( Squaring )======================== ///

void SingleWordSqu(bigint* C, word A)
{   
    if ( C == NULL )
    {
        bi_new(&C, 2);
    }

    /// Split a word into half size
    word mask = MASK_LAST;

    word A0 = (A & mask);
    word A1 = A >> (WORD_BIT_SIZE/2);

    word C0 = A0 * A0;
    word C1 = A1 * A1;

    /// C <- (C1 << w) + C0
    C->a[0] = C0;
    C->a[1] = C1;

    word tmpT = A0 * A1;

    word* T = (word*)calloc(2, sizeof(word));
    T[0] = tmpT << 1;

    T[1] = T[0] >> WORD_BIT_SIZE/2;
    T[0] = T[0] << WORD_BIT_SIZE/2;

    /// C <- C + T
    for(int i=0; i<2; i++){
        C->a[i] += T[i];
    }
    free(T);
}

void SQUC(bigint** C, bigint* A)
{   
    /// Exception Handling
    if( A == NULL ) {
        puts("--SQUC function error--\nInvalid input value : null");
        return;
    }

    int t = A->wordlen;
    int tt = 2*t;

    if(C == NULL){
        bi_new(C, tt);
    }

    /// Split a big integer into an array
    word* tmpA = (word*)calloc(tt, sizeof(word));
    for(int i=0; i<tt; i++){
        if(i%2==0){tmpA[i] = A->a[i/2] & MASK_LAST;}
        else{tmpA[i]= A->a[i/2] >> (WORD_BIT_SIZE/2);}
    }

    bigint* C1 = NULL;
    bigint* tmpC1 = NULL;
    bigint* C2 = NULL;
    bigint* tmpC2 = NULL;
    
    
    bi_new(&C1, tt);
    bi_new(&tmpC1, tt);
    bi_new(&C2, tt);
    bi_new(&tmpC2, tt);
    

    for(int j=0; j<tt; j++){
        bigint* T1 = NULL;
        bi_new(&T1, 2);

        SingleWordSqu(T1, tmpA[j]);         /// T1 <- A_j^2
        l_shift(&T1, j*WORD_BIT_SIZE);      /// T1 <- T1 << 2*jw
        bi_refine(T1);
        
        ADD(&C1, tmpC1, T1);             /// C1 <- T1 + C1
        bi_assign(&tmpC1, C1);

        for(int i = (j+1); i<tt; i++){
            bigint* T2 = NULL;
            bi_new(&T2, 2);

            word* tmp = (word*)calloc(2, sizeof(word));
            SingleWordMul(tmp, tmpA[j], tmpA[i]);

            /// tmp(word array) => T2(bigint struct)
            bi_set_by_array(&T2, 0, tmp, 2);
            
            l_shift(&T2, WORD_BIT_SIZE/2*(i+j));
            bi_refine(T2); 

            ADD(&C2, tmpC2, T2);
            bi_assign(&tmpC2, C2);

            free(tmp);
            bi_delete(&T2);
        }
        bi_delete(&T1);
    }
    l_shift(&C2, 1);
    ADD(C, C1, C2);

    //-----------------
    bi_delete(&C1);
    bi_delete(&C2);
    bi_delete(&tmpC1);
    bi_delete(&tmpC2);
    //-----------------
}

void SQU(bigint** C, bigint* A)
{
    /// Exception Handling
    if( A == NULL ) {
        puts("--SQU function error--\nInvalid input value : null");
        return;
    }

    int w = A->wordlen;

    if(C == NULL){
        bi_new(C, 2*w);
    }

    if(A->a[0]==0){         /// C = A^2 = 0
        (*C)->a[0] = 0;
    }
    else if(A->a[0]==1){   /// C = A^2 = 1
        (*C)->sign = NON_NEGATIVE;
        (*C)->a[0] = 1;
    }
    else{
        SQUC(C, A);
    }
}

void Karatsuba_SQU(bigint** C, bigint* A, unsigned int flag)
{
    int w = A->wordlen;
    int ww = 2*w;
    if(flag >= w){
        SQUC(C, A);
        return;
    }
    
    if(C==NULL){
        bi_new(C, ww);
    }

    int l = (w+1) >> 1;

    /// Set A0, A1
    bigint* A0 = NULL;
    bigint* A1 = NULL;
    bi_assign(&A0, A);
    bi_assign(&A1, A);

    A0->sign = NON_NEGATIVE;
    reduction(&A0, l*WORD_BIT_SIZE);
    
    A1->sign = NON_NEGATIVE;
    r_shift(&A1, l*WORD_BIT_SIZE);

    /// Set T0, T1
    bigint* T0 = NULL;
    bigint* T1 = NULL;
    bi_new(&T0, ww);
    bi_new(&T1, ww);
    Karatsuba_SQU(&T0, A0, flag);
    Karatsuba_SQU(&T1, A1, flag);

    /// Set R
    bigint* R = NULL;
    l_shift(&T1, 2*l*WORD_BIT_SIZE);
    ADD(&R, T1, T0);

    /// Set S
    bigint* S = NULL;
    Karatsuba_MUL(&S, A1, A0, flag);
    l_shift(&S, l*WORD_BIT_SIZE + 1);

    ADDC(C, R, S);  /// C <- ADDC(R,S)

    //-----------------
    bi_delete(&A0);
    bi_delete(&A1);
    bi_delete(&T0);
    bi_delete(&T1);
    bi_delete(&R);
    bi_delete(&S);
    //-----------------
}

/// =========================================================== ///
