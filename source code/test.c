#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include "BasicOperation.h"
#include "Mul.h"
#include "Squ.h"
#include "Add_Sub.h"
#include "Div.h"
#include "exp.h"

bigint* A = NULL;
bigint* B = NULL;
bigint* C = NULL;

// compare mul, impmul, karatsubamul
void check_mul(){
    unsigned long long mul_cycles1, mul_cycles2, imp_cycle1, imp_cycle2, kmul_cycle1, kmul_cycle2;
    int flag = 2;
    double time1, time2, time3;
    int iteration = 1000;

    bigint* A = NULL;
    bigint* B = NULL;
    bigint* C = NULL;    
    // textbook mul
    mul_cycles1 = clock();
    for(int i = 0; i<iteration; i++){
        bi_gen_rand(&A, NON_NEGATIVE, 100);
        bi_gen_rand(&B, NON_NEGATIVE, 100);
        
        MUL(&C, A, B);
    }
    mul_cycles2 = clock();
    time1 = ((double) (mul_cycles2 - mul_cycles1)) / CLOCKS_PER_SEC;

    // impmul
    imp_cycle1 = clock();
    for(int i = 0; i<iteration; i++)
    {
        bi_gen_rand(&A, NON_NEGATIVE, 100);
        bi_gen_rand(&B, NON_NEGATIVE, 100);
        ImpMulC(&C, A, B);
    }
    imp_cycle2 = clock();
    time2 = ((double) (imp_cycle2 - imp_cycle1)) / CLOCKS_PER_SEC;

    // karatsuba mul
    kmul_cycle1 = clock();  
    for(int i = 0; i<iteration; i++)
    {
        bi_gen_rand(&A, NON_NEGATIVE, 100);
        bi_gen_rand(&B, NON_NEGATIVE, 100);        
        Karatsuba_MUL(&C, A, B, 10);
    }
    kmul_cycle2 = clock();
    time3 = ((double) (kmul_cycle2 - kmul_cycle1)) / CLOCKS_PER_SEC;

    puts("###### Check About Multiplication ######");
    printf("Textbook Mul clocks: %f\n", time1);
    printf("ImpMul clocks: %f\n", time2);
    printf("KaratsubaMul clocks: %f\n", time3);
    puts("########################################");

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}

// compare squ, karatsubasqu
void check_squ(){

    unsigned long long squ_cycle1, squ_cycle2, ksqu_cycle1, ksqu_cycle2;
    double time1, time2;
    int flag = 2;
    int iteration = 1000;
    unsigned int t_wordlen = 100;

    bigint* A = NULL;
    bigint* B = NULL;
    // basic squ
    squ_cycle1 = clock();
    for(int i = 0; i<iteration; i++){

        bi_gen_rand(&A, NON_NEGATIVE, t_wordlen);        
        SQU(&B, A);
    }
    squ_cycle2 = clock();
    time1 = ((double) (squ_cycle2 - squ_cycle1)) / CLOCKS_PER_SEC;

    // karatsuba mul
    ksqu_cycle1 = clock();
    for(int i = 0; i<iteration; i++){

        bi_gen_rand(&A, NON_NEGATIVE, t_wordlen);        
        Karatsuba_SQU(&B, A, flag);
    }
    ksqu_cycle2 = clock();
    time2 = ((double) (ksqu_cycle2 - ksqu_cycle1)) / CLOCKS_PER_SEC;

    puts("###### Check About Squaring ######");
    printf("Textbook Squ clocks: %f\n", time1);
    printf("KaratsubaSqu clocks: %f\n", time2);
    puts("##################################");

    bi_delete(&A);
    bi_delete(&B);
}

int main(){
    check_mul();
    printf("\n");
    check_squ();
    return 0;
}