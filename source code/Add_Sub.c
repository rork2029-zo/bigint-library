/*!
 * @file Add_Sub.c
 * @date 2023/12
 * @brief Sorce code of Addition and Subtraction
*/
#include "Add_Sub.h"
#include <time.h>

/// ===========================( Addition )================================ ///

int ADD_ABc(word* C, word A, word B, int c)
{
    /// Exception Handling
    if( C == NULL ) {
        puts("--ADD_ABc function error--\nInvalid input value : null");
        return FALSE;
    }

    int cp = 0;

    *C = A + B;     /// C <- A+B
    if( *C < A ) cp = 1; 
    *C += c;        /// C <- C+c
    if( *C < c ) cp += 1;

    return cp;
}

int ADDC(bigint** C, bigint* A, bigint* B) /// wordlen(A) >= wordlen(B)
{
    /// Exception Handling
    if( A == NULL || B == NULL ) {
        puts("--ADDC function error--\nInvalid input value : null");
        return FALSE;
    }

    bi_new(C, A->wordlen+1); 

    int carry = 0;

    bigint* re_B = NULL;
    if( A->wordlen == B->wordlen ) {
        bi_assign(&re_B, B);
    }
    else if( A->wordlen > B->wordlen ) {
        bi_new(&re_B, A->wordlen);
        re_B->sign = B->sign;
        array_copy(re_B->a, B->a, B->wordlen);
    }

    for(int j=0; j<A->wordlen; j++) {
        carry = ADD_ABc((&(*C)->a[j]), A->a[j], re_B->a[j], carry);
    }
    (*C)->a[A->wordlen] = carry;    /// C_n <- c
    (*C)->sign = A->sign;
    bi_refine(*C);

    bi_delete(&re_B);
    return 1;
}

void ADD(bigint** C, bigint* A, bigint* B)
{
    /// Exception Handling
    if( A == NULL || B == NULL ) {
        puts("--ADD function error--\nInvalid input value : null");
        return;
    }

    // option
    if( bi_is_zero(A) ) {
        bi_assign(C, B);
        return;
    }
    else if( bi_is_zero(B) ) {
        bi_assign(C, A);
        return;
    }

    ///== Different sign
    else if( A->sign == NON_NEGATIVE && B->sign == NEGATIVE ) 
    {
        bigint* re_B = NULL;
        bi_assign(&re_B, B);
        re_B->sign = NON_NEGATIVE;
        SUB(C, A, re_B);
        bi_delete(&re_B);
        return;
    }
    else if( A->sign == NEGATIVE && B->sign == NON_NEGATIVE)
    {
        bigint* re_A = NULL;
        bi_assign(&re_A, A);
        re_A->sign = NON_NEGATIVE;
        SUB(C, B, re_A);
        bi_delete(&re_A);
        return;
    }

    ///== Same sign
    else if(A->wordlen >= B->wordlen) {
        // wordlen(A) >= wordlen(B)
        ADDC(C, A, B);
        return;
    }
    else { // wordlen(B) >= wordlen(A)
        ADDC(C, B, A);
        return;
    }
    return;
}
/// =========================================================== ///


/// ===================( Substraction )========================= ///

int SUB_AbB(word* C, word A, word B, int b)
{
    /// Exception Handling
    if( C == NULL ) {
        puts("--SUB_AbB function error--\nInvalid input value : null");
        return FALSE;
    }

    int bp;

    *C = A - b;
    bp = (A < b);
    bp = bp + (*C<B);

    *C = *C - B;    /// C <- C-B

    return bp;
}

// A >= B --> wordlen(A) >= wordlen(B)
int SUBC(bigint** C, bigint* A, bigint* B)
{
    /// Exception Handling
    if( A == NULL || B == NULL ){
        puts("--SUBC function error--\nInvalid input value : null");
        return FALSE;
    }
    if( A->wordlen < B->wordlen ) {
        puts("--SUBC function error--\nInvlid input value : correct condition -> (wordlen(A) >= wordlen(B))");
        return FALSE;
    }

    bi_new(C, A->wordlen);

    bigint* re_B = NULL;
    if( A->wordlen == B->wordlen ) {
        bi_assign(&re_B, B);
    }
    else {
        bi_new(&re_B, A->wordlen );
        re_B->sign = B->sign;
        array_copy(re_B->a, B->a, B->wordlen);
    }

    int b = 0;
    for(int j=0; j < A->wordlen; j++ )
        b = SUB_AbB(&((*C)->a[j]), A->a[j], re_B->a[j], b);
    
    bi_delete(&re_B);
    bi_refine(*C);

    return 1;
}

void SUB(bigint** C, bigint* A, bigint* B)
{
    /// Exception Handling
    if( A == NULL || B == NULL ) {
        puts("--SUB function error--\nInvalid input value : null");
        return;
    }
    
    int ret = compare(A, B);

    if( bi_is_zero(A) ) { // case : A == 0
        bi_assign(C, B);
        flipSign(C);
        return;
    }
    else if( bi_is_zero(B) ) { // case : B == 0
        bi_assign(C, A);
        return;
    }
    else if( ret == 0 ) { // case : A == B
        bi_set_zero(C);
        return;
    }

    ///== Same sign
    /// Both positive
    if( (getSign(A) == NON_NEGATIVE) && (getSign(B) == NON_NEGATIVE) ) { 
        if( ret == 1 ) { 
            /// case: A > B >= 0
            SUBC(C, A, B);
            return;
        }
        else if( ret == -1 ) {
            /// case: A < B < 0
            SUBC(C, B, A);
            (*C)->sign = NEGATIVE;
            return;
        }
    }
    /// Both negative
    else if( (getSign(A) == NEGATIVE) && (getSign(B) == NEGATIVE)) {    
        bigint* re_A = NULL;
        bigint* re_B = NULL;
        bi_assign(&re_A, A); bi_assign(&re_B, B);
        re_A->sign = NON_NEGATIVE; re_B->sign = NON_NEGATIVE;

        if( ret == 1 ) {
            /// case: 0 > A >= B
            SUBC(C, re_B, re_A);
            return;
        }
        else if( ret == -1 ) {
            /// case: 0 > B > A
            SUBC(C, re_A, re_B);
            (*C)->sign = NEGATIVE;
            return;
        }
        bi_delete(&re_A);
        bi_delete(&re_B);
        return;
    }

    ///== Different sign
    /// case: A > 0, B < 0
    if( (getSign(A) == NON_NEGATIVE) && (getSign(B) == NEGATIVE)) {
        bigint* re_B = NULL;
        bi_assign(&re_B, B);
        re_B->sign = NON_NEGATIVE;
        ADD(C, A, re_B);
        bi_delete(&re_B);
        return;
    }
    /// case: A < 0, B > 0
    else if( (getSign(A) == NEGATIVE) && (getSign(B) == NON_NEGATIVE)) {
        bigint* re_A = NULL;
        bi_assign(&re_A, A);
        re_A->sign = NON_NEGATIVE;
        ADD(C, re_A, B); 
        (*C)->sign = NEGATIVE;
        bi_delete(&re_A);
        return;
    }
}
/// =========================================================== ///