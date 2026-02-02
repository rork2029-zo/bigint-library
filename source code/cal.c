/*!
 * @file cal.c
 * @date 2023/12
 * @brief Source code of Calculation
*/
#include "ntro.h"

//=======( cal.c 함수 LIST )======

//----------[ 연산 함수 ]----------
void ADDITION();
void SUBSRACTION();
void MULTIPLICATION();
void MODULAR_EXPONENTIATION();
void DIVISION();
//-------------------------------

//-------[ 메모리 처리 함수 ]-------
void flush_buffer();
void free_bi_3(bigint* x1, bigint* x2, bigint* x3);
void free_bi_4(bigint* x1, bigint* x2, bigint* x3, bigint* x4);
//-------------------------------

//================================

int r;
int main()
{
    
    while(1) {
        int num;
        puts("\n\n************************************************************");
        puts("|                    Hi! THIS IS Ntro :)                   |");
        puts("************************************************************");
        puts("| [ OPTION LIST ]                                          |");
        puts("| 1. CALCULATOR       2. ABOUT FUNCTION       3. CLOSE     |");
        // printf("============================================================\n>> ");
                printf("************************************************************\n>> ");

        
        //====== USER COMMAND 입력 (OPTION 선택)======
        r = scanf("%d", &num);     // 첫번째 입력값
    
        flush_buffer();

        if(num == 1){
            // CALCULATOR
            int operation; 
        //===========================================

        {            
            printf("\n=============[ Select the operation you want ]==============\n");
            printf("|                                                          |\n");
            printf("|                * Num type is HEXADECIMAL *               |\n");
            printf("|                                                          |\n");
            printf("|  1. ADD                        2. SUB          3. MUL    |\n");
            printf("|  4. MODULAR EXPONENTIATION     5. DIVISION     6. EXIT   |\n");
            printf("|                                                          |\n");
            printf("============================================================\n ");
            printf("[ Press Operation Number ]\n");
            printf(">> ");

            //-------( 사용자가 원하는 연산 번호 입력 )-------
            r = scanf("%d", &operation);
            flush_buffer();
            //-------------------------------------------
            
            switch(operation)
            {
                case 1:
                {   
                    ADDITION();
                    break;
                }
                case 2:
                {   
                    SUBSRACTION();
                    break;
                }
                case 3:
                {
                    MULTIPLICATION();
                    break;
                }
                case 4:
                {
                    MODULAR_EXPONENTIATION();
                    break;
                }
                case 5:
                {
                    DIVISION();
                    break;
                }
                case 6:
                {
                    break;
                }
                default:
                {
                    puts("\n[WARNING] Invalid choice. Please choose a number between 1 and 6. \n");
                    break;
                }
            }
                puts("\n************************************************************");
                puts("|                  CALCULATION IS OVER.                    |");
                puts("|                  THANK YOU FOR USING !                   |");
                puts("************************************************************\n\n");
            }
        }

        else if(num == 2){
            ///-------[ HELP ]  
            puts("\n------------[Description of Functions]-------------");
            puts("# This is a calculator for big integers.");
            puts("# This provides five following fuctions.");
            puts("# [ADD] [SUB] [MUL] [RECUCTION] ");
            puts("# [MODULAR EXPONENTIATION] [DIVISION].");
            puts("# If you put the number of function that you want,");
            puts("# It will print the result :)");
            puts("---------------------------------------------------");
            
        }

        else if(num == 3){
            // CLOSE
            printf("See you next time ~\n");
                // system("leaks out");
            return 0;
        }

        else{
            printf("\n[WARNING] Invalid choice. Please choose a number between 1 and 3!\n");
            return 0;
        }
    }
    return 0;
}

void ADDITION()
{   
    /*
        ADDITION : (A + B) 출력
        - A 입력 받기
        - B 입력 받기
        - C = A + B
    */

    puts("[ ADDITION : A + B ]\n");
    //----------------( BIG NUM 1 : A 입력 )-------------------
    char* buffer1 = NULL; 
    size_t size1 = 0;     

    printf("( A ) : ");
    r = getline(&buffer1, &size1, stdin);
    buffer1[strcspn(buffer1, "\n")] = '\0'; 

    if(buffer1 == NULL){
        printf("\nFailed to input Big integer!\n");
        exit(1);
    }
    bigint* A = NULL;
    bi_set_by_string(&A, NON_NEGATIVE, buffer1, HEXADECIMAL);
    //-------------( BIG NUM 1 : A 입력 완료 )------------------


    //---------------( BIG NUM 2 : B 입력 )---------------------
    char* buffer2 = NULL; 
    size_t size2 = 0;     

    printf("( B ) : ");
    r = getline(&buffer2, &size2, stdin);
    buffer2[strcspn(buffer2, "\n")] = '\0';        
    
    if(buffer2 == NULL){
        printf("Failed to input Big integer!\n");
        exit(1);
    }

    bigint* B = NULL;
    bi_set_by_string(&B, NON_NEGATIVE, buffer2, HEXADECIMAL);

    free(buffer1);
    free(buffer2);
    //--------------( BIG NUM 2 : B 입력 완료 )-----------------

    //-------------------( ADDITION 연산 )----------------------
    bigint* C = NULL;
    ADD(&C, A, B);
    printf("\n[ ADD RESULT ] :  "); bi_show_hex(C); 
    //-----------------( ADDITION 연산 완료 )--------------------
    
    free_bi_3(A, B, C);
}

void SUBSRACTION()
{
    /*
        SUBSTRACTION : (A - B) 출력
        - A 입력 받기
        - B 입력 받기
        - C = A - B
    */

    puts("[ SUBSTRACTION : A - B ]\n");
    //----------------( BIG NUM 1 : A 입력 )-------------------
    char* buffer1 = NULL; 
    size_t size1 = 0;     

    printf("( A ): ");
    r = getline(&buffer1, &size1, stdin);
    buffer1[strcspn(buffer1, "\n")] = '\0'; 

    if(buffer1 == NULL){
        printf("\nFailed to input Big integer!\n");
        exit(1);
    }
    bigint* A = NULL;
    bi_set_by_string(&A, NON_NEGATIVE, buffer1, HEXADECIMAL);
    //-------------( BIG NUM 1 : A 입력 완료 )------------------


    //---------------( BIG NUM 2 : B 입력 )---------------------
    char* buffer2 = NULL; 
    size_t size2 = 0;     

    printf("( B ): ");
    r = getline(&buffer2, &size2, stdin);
    buffer2[strcspn(buffer2, "\n")] = '\0';        
    
    if(buffer2 == NULL){
        printf("Failed to input Big integer!\n");
        exit(1);
    }

    bigint* B = NULL;
    bi_set_by_string(&B, NON_NEGATIVE, buffer2, HEXADECIMAL);

    free(buffer1);
    free(buffer2);
    //--------------( BIG NUM 2 : B 입력 완료 )-----------------

    //-----------------( SUBSTRACTION 연산 )--------------------
    bigint* C = NULL;
    SUB(&C, A, B);
    printf("\n[ SUBSTRACTION RESULT ] : "); bi_show_hex(C);
    //---------------( SUBSTRACTION 연산 완료 )------------------

    free_bi_3(A, B, C);
}

void MULTIPLICATION()
{
    /*
        MULTIPLICATION : (A * B) 출력
        - A 입력 받기
        - B 입력 받기
        - C = A * B
    */

    puts("[ MULTIPLICATION : A * B ]\n");\
    //----------------( BIG NUM 1 : A 입력 )-------------------
    char* buffer1 = NULL; 
    size_t size1 = 0;     

    printf("( A ): ");
    r = getline(&buffer1, &size1, stdin);
    buffer1[strcspn(buffer1, "\n")] = '\0'; 

    if(buffer1 == NULL){
        printf("\nFailed to input Big integer!\n");
        exit(1);
    }
    bigint* A = NULL;
    bi_set_by_string(&A, NON_NEGATIVE, buffer1, HEXADECIMAL);
    //-------------( BIG NUM 1 : A 입력 완료 )------------------


    //---------------( BIG NUM 2 : B 입력 )---------------------
    char* buffer2 = NULL; 
    size_t size2 = 0;     

    printf("( B ): ");
    r = getline(&buffer2, &size2, stdin);
    buffer2[strcspn(buffer2, "\n")] = '\0';        
    
    if(buffer2 == NULL){
        printf("Failed to input Big integer!\n");
        exit(1);
    }

    bigint* B = NULL;
    bi_set_by_string(&B, NON_NEGATIVE, buffer2, HEXADECIMAL);

    free(buffer1);
    free(buffer2);
    //--------------( BIG NUM 2 : B 입력 완료 )-----------------

    //---------------( MULTIPLICATION 연산 )-------------------
    bigint* C = NULL;
    Karatsuba_MUL(&C, A, B, 2);
    printf("\n[ MULTIPLICATION RESULT ] : "); bi_show_hex(C);
    //---------------( MULTIPLICATION 연산 완료 )---------------

    free_bi_3(A, B, C);
}

void MODULAR_EXPONENTIATION()
{
    /*   
        MODULAR_EXPONENTIATION : (x^m mod N) 출력

        - 3개의 bignum 입력
            - x 입력 받기
            - m 입력 받기
            - n 입력 받기

        - y = x^m mod N
    */

    puts("[ MODULAR EXPONENTIATION : x^n mod M ]\n");
    //----------------( BIG NUM 1 : x 입력 )-------------------
    char* buffer1 = NULL; 
    size_t size1 = 0;     

    printf("( x ): ");
    r = getline(&buffer1, &size1, stdin);
    buffer1[strcspn(buffer1, "\n")] = '\0'; 

    if(buffer1 == NULL){
        printf("\nFailed to input Big integer!\n");
        exit(1);
    }
    bigint* x = NULL;
    bi_set_by_string(&x, NON_NEGATIVE, buffer1, HEXADECIMAL);
    //-------------( BIG NUM 1 : x 입력 완료 )------------------


    //---------------( BIG NUM 2 : m 입력 )---------------------
    char* buffer2 = NULL; 
    size_t size2 = 0;     

    printf("( n ): ");
    r = getline(&buffer2, &size2, stdin);
    buffer2[strcspn(buffer2, "\n")] = '\0';        
    
    if(buffer2 == NULL){
        printf("Failed to input Big integer!\n");
        exit(1);
    }

    bigint* n = NULL;
    bi_set_by_string(&n, NON_NEGATIVE, buffer2, HEXADECIMAL);
    //--------------( BIG NUM 2 : m 입력 완료 )-----------------

    //----------------( BIG NUM 3 : N 입력 )-------------------
    char* buffer3 = NULL; 
    size_t size3 = 0;     

    printf("( M ): ");
    r = getline(&buffer3, &size3, stdin);
    buffer3[strcspn(buffer3, "\n")] = '\0'; 

    if(buffer3 == NULL){
        printf("\nFailed to input Big integer!\n");
        exit(1);
    }
    bigint* M = NULL;
    bi_set_by_string(&M, NON_NEGATIVE, buffer3, HEXADECIMAL);

    free(buffer1);
    free(buffer2);
    free(buffer3);
    //-------------( BIG NUM 3 : N 입력 완료 )------------------

    //------------( MODULAR EXPONENTIATION 연산 )---------------
    bigint* y = NULL;
    montgomery_ladder(&y, x, n, M);
    printf("\n[ MODULAR EXPONENTIATION RESULT ] : "); bi_show_hex(y);
    //----------( MODULAR EXPONENTIATION 연산 완료 )--------------

    free_bi_4(x, y, n, M);
}

void DIVISION()
{
    /*
        DIVISION : (Q, R) = (A // B), (A % B) 출력
        - A 입력 받기
        - B 입력 받기
        - Q = A // B, R = A % B
    */

    puts("[ DIVISION : Q = A // B , R = A % B]\n");
    bigint *A = NULL, *B = NULL;
    //----------------( BIG NUM 1 : A 입력 )-------------------
    char* buffer1 = NULL;
    size_t size1 = 0;     

    printf("( A ): ");
    r = getline(&buffer1, &size1, stdin);
    buffer1[strcspn(buffer1, "\n")] = '\0'; 

    if(buffer1 == NULL){
        printf("\nFailed to input Big integer!\n");
        exit(1);
    }
    bi_set_by_string(&A, NON_NEGATIVE, buffer1, HEXADECIMAL);
    // -------------( BIG NUM 1 : A 입력 완료 )------------------


    // ---------------( BIG NUM 2 : B 입력 )---------------------
    char* buffer2 = NULL; 
    size_t size2 = 0;     

    printf("( B ): ");
    r = getline(&buffer2, &size2, stdin);
    buffer2[strcspn(buffer2, "\n")] = '\0';        
    
    if(buffer2 == NULL){
        printf("Failed to input Big integer!\n");
        exit(1);
    }
    bi_set_by_string(&B, NON_NEGATIVE, buffer2, HEXADECIMAL);

    free(buffer1);
    free(buffer2);
    //--------------( BIG NUM 2 : B 입력 완료 )-----------------


    //-------------------( DIVISION 연산 )----------------------
    bigint *Q = NULL, *R = NULL;

    DIV_long(&Q, &R, A, B);

    printf("\n[ DIVISION RESULT ] : \n");
    printf("    Quotient =  "); bi_show_hex(Q);
    printf("    Remainder = "); bi_show_hex(R);
    //-----------------( DIVISION 연산 완료 )--------------------

    free_bi_4(Q, R, A, B);
}


void flush_buffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void free_bi_3(bigint* x1, bigint* x2, bigint* x3) { bi_delete(&x1); bi_delete(&x2); bi_delete(&x3); }
void free_bi_4(bigint* x1, bigint* x2, bigint* x3, bigint* x4) { bi_delete(&x1); bi_delete(&x2); bi_delete(&x3); bi_delete(&x4); }
