/*!
 * @file Exp.c
 * @date 2023/12
 * @brief Source code of Modular Exponentiation
*/
#include "exp.h"


/// =========================================================== ///
/*
    Montgomery Ladder (Multiply-and-Square Method)
    - Calculate x^n mod M
*/

void montgomery_ladder(bigint** xn, bigint* x, bigint* N, bigint* M) 
{
    int w = x->wordlen;
    int m = M->wordlen;
    int n = N->wordlen;
    int l = 0;

    if(xn == NULL){
        bi_new(xn, n*w);
    }

    l = getBitLen(N);

    bigint* T0 = NULL;
    bigint* T1 = NULL;
    bigint* tmpT0 = NULL;
    bigint* tmpT1 = NULL;

    bigint* Q = NULL;
    bigint* R = NULL;

    bi_set_one(&tmpT0);
    bi_set_one(&T0);
    
    bi_assign(&tmpT1, x);
    bi_assign(&T1, x);

    for(int i = l-1; i>=0; i--)
    {
        if(get_j_bit(N, i) == 0) // ni = 0인 경우
        { 
            ImpMulC(&T1, tmpT0, tmpT1);  // T1 <- T0 * T1 mod M
            SQUC(&T0, tmpT0);            // T0 <- T0 ^ 2  mod M
            
            DIV_long(&Q, &tmpT1, T1, M);
            DIV_long(&Q, &tmpT0, T0, M);

        }
        else // ni = 1인 경우
        {  
            ImpMulC(&T0, tmpT0, tmpT1); 
            SQUC(&T1, tmpT1);

            DIV_long(&Q, &tmpT0, T0, M);
            DIV_long(&Q, &tmpT1, T1, M);
        }

    }
    bi_assign(&T0, tmpT0);
    bi_assign(xn, T0);
    bi_refine(*xn);

    //-----------------
    bi_delete(&tmpT0);
    bi_delete(&tmpT1);
    bi_delete(&T0);
    bi_delete(&T1);
    //-----------------
}

/// =========================================================== ///


