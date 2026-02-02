/*!
 * @file verify.h
 * @date 2023/12
 * @brief Header file of Verify
*/
#ifndef __VERIFY_H__
#define __VERIFY_H__
#include "ntro.h"
#include <time.h>
#include <stdlib.h>

//---------------------------------------( verify parameter )-----------------------------------------

#define V_ITERATION             10000                           /* Iteration of Verification      */

/*  Input x, y parameter     */
#define V_WORDLEN_X             50                              /*  x wordlen  */
#define V_WORDLEN_Y             50                              /*  y wordlen  */

/*  (Modular Exponentiation) 
    Input x, n, m parameter */
#define V_EXP_WORDLEN_X         10                              /*  x wordlen  */
#define V_EXP_WORDLEN_N         10                              /*  n wordlen  */
#define V_EXP_WORDLEN_M         10                              /*  m wordlen  */

#define V_WORDLEN_BARRET        10                              /*  Barret Reduction wordlen       */
#define V_KARATSUBA_MUL_FLAG    2                               /*  Karatsuba Multiplication Flag  */
#define V_KARATSUBA_SQU_FLAG    2                               /*  Karatsuba Squaring Flag        */


#define V_RAND_SIGN             (rand() % 2)                    /*  Random Sign */

#define V_RAND_WORDLEN_X        (rand() % V_WORDLEN_X + 1)      /*  Random x wordlen */
#define V_RAND_WORDLEN_Y        (rand() % V_WORDLEN_Y + 1)      /*  Random y wordlen */

//-----------------------------------------------------------------------------------------------------


/// =================( Addition Verify Function )================== ///

void add_check_py()
{
    puts("print(\"-------------------------------------\")");
    printf("print(\"\\n[[ Addition TEST START ! ]]\")\n");

    for( int i=0; i<V_ITERATION; i++ ) {
        bigint* x = NULL;
        bigint* y = NULL;
        bigint* z = NULL;

        bi_gen_rand(&x, V_RAND_SIGN, V_RAND_WORDLEN_X);
        bi_gen_rand(&y, V_RAND_SIGN, V_RAND_WORDLEN_Y);

        printf("x = "); bi_show_hex(x); 
        printf("y = "); bi_show_hex(y); 

        ADD(&z, x, y);

        printf("z = "); bi_show_hex(z);
        printf("if(z != x+y):\n");
        printf("\tprint(\"# %d-th test\")\n", i+1);
        printf("\tprint(\"x = \", hex(x))\n");
        printf("\tprint(\"y = \", hex(y))\n");
        printf("\tprint(\"z = \", hex(z))\n");
        printf("\tprint(\"true value (x+y) = \", hex(x+y))\n\n");

        bi_delete(&x);
        bi_delete(&y);
        bi_delete(&z);
    }

    printf("print(\"[[ Addition TEST DONE  ! ]]\\n\")\n\n");
    puts("print(\"-------------------------------------\")");
}

/// =============================================================== ///


/// ===============( Substraction Verify Function )================ ///

void sub_check_py()
{
    puts("print(\"\\n-------------------------------------\")");
    printf("print(\"\\n[[ Substraction TEST START ! ]]\")\n");

    for( int i=0; i<V_ITERATION; i++ ) {
        bigint* x = NULL;
        bigint* y = NULL;
        bigint* z = NULL;

        bi_gen_rand(&x, V_RAND_SIGN, V_RAND_WORDLEN_X);
        bi_gen_rand(&y, V_RAND_SIGN, V_RAND_WORDLEN_Y);

        printf("x = "); bi_show_hex(x); 
        printf("y = "); bi_show_hex(y); 

        SUB(&z, x, y);

        printf("z = "); bi_show_hex(z);
        printf("if(z != x-y):\n");
        printf("\tprint(\"# %d-th test\")\n", i+1);
        printf("\tprint(\"x = \", hex(x))\n");
        printf("\tprint(\"y = \", hex(y))\n");
        printf("\tprint(\"z = \", hex(z))\n");
        printf("\tprint(\"true value (x-y) = \", hex(x-y))\n\n");


        bi_delete(&x);
        bi_delete(&y);
        bi_delete(&z);
    }

    printf("print(\"[[ Substraction TEST DONE  ! ]]\")\n\n");
    puts("print(\"\\n-------------------------------------\")");
}

/// =============================================================== ///


/// ===============( Multiplication Verify Function )============== ///

void mul_check_py(const char* mode)
{
    puts("print(\"\\n-------------------------------------\")");
    printf("print(\"\\n[[ %s Multiplication TEST START ! ]]\")\n", mode);

    for( int i=0; i<V_ITERATION; i++ ) 
    {
        bigint* x = NULL;
        bigint* y = NULL;
        bigint* z = NULL;
        
        bi_gen_rand(&x, V_RAND_SIGN, V_RAND_WORDLEN_X);
        bi_gen_rand(&y, V_RAND_SIGN, V_RAND_WORDLEN_Y);


        //------------( mode 선택 )--------------
        if( !strcmp("textbook", mode) )
            MUL(&z, x, y);

        else if( !strcmp("improve", mode) )
            ImpMulC(&z, x, y);

        else if( !strcmp("karatsuba", mode) )
        {
            x->sign = NON_NEGATIVE;
            y->sign = NON_NEGATIVE;
            Karatsuba_MUL(&z, x, y, V_KARATSUBA_MUL_FLAG);
        }

        else {
            printf("Invalid mode selection in mul_check_py()\n");
            exit(0);
        }
        //--------------------------------------

        printf("x = "); bi_show_hex(x);
        printf("y = "); bi_show_hex(y);
        printf("z = "); bi_show_hex(z);
        
        printf("if(z != x*y):\n");
        printf("\tprint(\"# %d-th test\")\n", i+1);
        printf("\tprint(\"x = \", hex(x))\n");
        printf("\tprint(\"y = \", hex(y))\n");
        printf("\tprint(\"z = \", hex(z))\n");
        printf("\tprint(\"true value (x*y) = \", hex(x*y))\n\n");

        bi_delete(&x);
        bi_delete(&y);
        bi_delete(&z);
    }
    printf("print(\"[[ %s Multiplication TEST DONE  ! ]]\")\n\n", mode);
    puts("print(\"\\n-------------------------------------\")");
}

/// =============================================================== ///


/// ==================( Division Verify Function )================= ///

void div_check_py()
{
    puts("print(\"\\n-------------------------------------\")");
    printf("print(\"\\n[[ Division TEST START ! ]]\")\n");
    for( int i=0; i<V_ITERATION; i++ ) 
    {
        bigint* x = NULL;
        bigint* y = NULL;

        bi_gen_rand(&x, NON_NEGATIVE, V_RAND_WORDLEN_X);
        bi_gen_rand(&y, NON_NEGATIVE, V_RAND_WORDLEN_Y);

        bigint* Q = NULL;
        bigint* R = NULL;

        printf("x = "); bi_show_hex(x);
        printf("y = "); bi_show_hex(y);

        DIV_long(&Q, &R, x, y);

        printf("Q = "); bi_show_hex(Q);
        printf("R = "); bi_show_hex(R);

        printf("if((Q != x//y) or (R != x%%y)):\n");
        printf("\tprint(\"# %d-th test\")\n", i+1);
        printf("\tprint(\"x = \", hex(x))\n");
        printf("\tprint(\"y = \", hex(y))\n");
        printf("\tprint(\"Q = \", hex(Q))\n");
        printf("\tprint(\"R = \", hex(R))\n");
        printf("\tprint(\"true value (x//y) = \", hex(x//y))\n");
        printf("\tprint(\"true value (x%%y) = \", hex(x%%y))\n\n");

        bi_delete(&x);
        bi_delete(&y);
        bi_delete(&Q);
        bi_delete(&R);
    }
    printf("print(\"[[ Division TEST DONE  ! ]]\")\n\n");
    puts("print(\"\\n-------------------------------------\")");
}

/// =============================================================== ///


/// =================( Squaring Verify Function )================== ///

void squ_check_py(const char* mode)
{    
    puts("print(\"\\n-------------------------------------\")");
    printf("print(\"\\n[[ %s Squaring TEST START ! ]]\")\n", mode);

    for( int i=0; i<V_ITERATION; i++ ) 
    {
        bigint* x = NULL;
        bigint* y = NULL;
        
        bi_gen_rand(&x, V_RAND_SIGN, V_RAND_WORDLEN_X);
        bi_new(&y, (V_RAND_WORDLEN_X*2));

        if( !strcmp("textbook", mode) ) 
            SQU(&y, x);
        
        else if( !strcmp("karatsuba", mode) )
            Karatsuba_SQU(&y, x, V_KARATSUBA_SQU_FLAG);

        else {
            printf("Invalid mode selecton in squ_check_py()\n");
        }
        printf("x = "); bi_show_hex(x);
        printf("y = "); bi_show_hex(y);

        printf("if(y != pow(x, 2)):\n");
        printf("\tprint(\"# %d-th test\")\n", i+1);
        printf("\tprint(\"x = \", hex(x))\n");
        printf("\tprint(\"y = \", hex(y))\n");
        printf("\tprint(\"true value (x^2) = \", hex(pow(x, 2)))\n\n");

        bi_delete(&x);
        bi_delete(&y);
    }
    printf("print(\"[[ %s Squaring TEST DONE  ! ]]\")\n\n", mode);
    puts("print(\"\\n-------------------------------------\")");
}

/// =============================================================== ///



/// ============( Modular Exponentiation Verify Function )=========== ///

void exp_check_py()
{
    puts("print(\"\\n-------------------------------------\")");
    printf("print(\"\\n[[ Modular Exponentiation TEST START ! ]]\")\n");

    for( int i=0; i<100; i++ ) 
    {
        bigint* x = NULL;
        bigint* y = NULL;
        bigint* m = NULL;
        bigint* n = NULL;

        bi_gen_rand(&x, NON_NEGATIVE, V_EXP_WORDLEN_X);
        bi_gen_rand(&n, NON_NEGATIVE, V_EXP_WORDLEN_N);
        bi_gen_rand(&m, NON_NEGATIVE, V_EXP_WORDLEN_M);


        montgomery_ladder(&y, x, n, m);
        
        printf("x = "); bi_show_hex(x);
        printf("n = "); bi_show_hex(n);
        printf("m = "); bi_show_hex(m);
        printf("y = "); bi_show_hex(y);
        printf("result = pow(x, n, m)\n");        

        printf("if(result != y):\n");
        printf("\tprint(\"# %d-th test\")\n", i+1);
        printf("\tprint(\"x = \", hex(x))\n");
        printf("\tprint(\"n = \", hex(n))\n");
        printf("\tprint(\"m = \", hex(m))\n");
        printf("\tprint(\"y = \", hex(y))\n");
        printf("\tprint(\"true value (x^n mode m) = \", hex(result))\n\n");


        bi_delete(&x);
        bi_delete(&y);
        bi_delete(&m);
        bi_delete(&n);
    }
    printf("print(\"[[ Modular Exponentiation TEST DONE  ! ]]\")\n\n");
    puts("print(\"\\n-------------------------------------\")");
}

/// =============================================================== ///


/// =============( Barrett Reduction Verify Function )============= ///

void Barrett_Reduction_check_py() 
{
    puts("print(\"\\n-------------------------------------\")");
    printf("print(\"\\n[[ Barret Reduction TEST START ! ]]\")\n");

    for( int i=0; i<V_ITERATION; i++ )
    {
        bigint* x = NULL;
        bigint* n = NULL;
        bigint* r = NULL;
        bigint* t = NULL;
        bigint* t_r = NULL;

        unsigned int n_len = V_WORDLEN_BARRET;
        unsigned int x_len = 2*n_len;

        bi_gen_rand(&n, NON_NEGATIVE, n_len);
        bi_gen_rand(&x, NON_NEGATIVE, x_len);

        if( x->wordlen > 2*(n->wordlen) ) {
            bi_delete(&x);
            bi_delete(&n);
            continue;
        }

        printf("x = "); bi_show_hex(x);
        printf("n = "); bi_show_hex(n);

        // w^2n
        bigint* w = NULL;
        bi_new(&w, 2*n_len+1);
        w->a[2*n_len] = 0x1;

        // T = floor(W^2n / N)
        DIV_long(&t, &t_r, w /*w = W^2n*/, n);
        printf("t = "); bi_show_hex(t);

        Barrett_reduction(&r, x, n, t);
        printf("r = "); bi_show_hex(r);
        printf("if(r != x%%n):\n");
        printf("\tprint(\"# %d-th test\")\n", i+1);
        printf("\tprint(\"x = \", hex(x))\n");
        printf("\tprint(\"n = \", hex(n))\n");
        printf("\tprint(\"r = \", hex(r))\n");
        printf("\tprint(\"true value (x%%n) = \", hex(x%%n))\n\n");

        //-----------------
        bi_delete(&r);
        bi_delete(&t);
        bi_delete(&t_r);
        bi_delete(&w);
        bi_delete(&x);
        bi_delete(&n);
        //-----------------
    }
    printf("print(\"[[ Barret Reduction TEST DONE  ! ]]\")\n\n");
    puts("print(\"\\n-------------------------------------\")");
}

/// =============================================================== ///

#endif

