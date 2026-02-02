/*!
 * @file BasicOperation.c
 * @date 2023/12
 * @brief Source code of Basic Operation
*/
#include "BasicOperation.h"

/// ======================( Create / Delete BigInt )========================= ///

void bi_new(bigint** x, unsigned int wordlen)
{
    if( *x != NULL ) {
        bi_delete(x);
    }

    *x = (bigint*)malloc(sizeof(bigint));
    (*x)->sign = NON_NEGATIVE;
    (*x)->wordlen = wordlen;
    (*x)->a = (word*)calloc(wordlen, sizeof(word));
}

void array_init(word* a, unsigned int wordlen)
{
    memset(a, 0, wordlen*sizeof(word));
}

void bi_delete(bigint** x)
{
    if( *x == NULL )
        return;
    
#ifdef ZERORIZE
    array_init((*x)->a, (*x)->wordlen);
#endif

    free((*x)->a);
    free(*x);
    *x = NULL;
}
/// ========================================================================= ///


/// =============================( Show BigInt )============================= ///

void bi_show_hex(bigint* x) 
{
    if( x->sign == NEGATIVE ) printf("- ");
    printf("0x"HEX_F, x->a[(x->wordlen)-1]);
    for( int i=(x->wordlen)-2; i>=0; i-- ) {
        printf(HEX, x->a[i]);
    }
    printf("\n");
}

void bi_show_bin(bigint* x)
{
    if( x->sign == NEGATIVE ) printf("-");
    printf("0b");
    word *p = x->a;
    for( int i=x->wordlen-1; i >= 0; i-- ) {
        for( int j=WORD_BIT_SIZE-1; j>=0; j-- ) 
            printf(DEC, (p[i]>>j) & 0x1);
    }
    printf("\n");
}

void bi_show_dec(bigint* x) {
    if (x->sign == 1) printf("-");  // 음수일 경우 출력

    char str[1000] = "";
    char intst = '\0';
    bigint* tmp = NULL; // 출력될 나머지 저장
    bigint* tmp1 = NULL;
    bigint* tmp2 = NULL;
    bigint* tmpx = NULL;
    bigint* mod = NULL;
    bigint* q = NULL;
    bi_set_zero(&tmp);
    bi_new(&mod, 1);
    bi_assign(&tmp1, x);
    mod->a[0] = 0b1010;

    // sub, div
    int i=0;
    while( compare(tmp1, mod) >= 0 ){
        DIV_long(&q, &tmp, tmp1, mod);
        intst = tmp->a[0] + 48;
        str[i] = intst;
        //printf("%c", str[i]);

        SUB(&tmp2, tmp1, tmp);  //bi_show_bin(tmp2);
        DIV_long(&tmpx, &tmp, tmp2, mod); //bi_show_bin(tmpx);
        bi_assign(&tmp1, tmpx);
        
        i++;
    }
    intst = tmp1->a[0] + 48;
    str[i] = intst;
    //printf("%c\n", str[i]);

    int len = strlen(str);
    for(int j = len-1; j >= 0; j--){
        printf("%c", str[j]);
    }
    printf("\n");

    bi_delete(&tmp);
    bi_delete(&mod);
    bi_delete(&q);
    bi_delete(&tmpx);
    bi_delete(&tmp1);
    bi_delete(&tmp2);

}
/// ========================================================================= ///


/// =============================( Set BigInt )============================== ///
/*
    Sign, Word-String -> Big Integer
    Sign, Character String -> Big Integer
*/
void bi_set_by_array(bigint** x, int sign, word* a, unsigned int wordlen)
{
    if ( a == NULL )
        return;

    if ( *x != NULL )
        bi_delete(x);

    if( x == NULL)
        return;

    bi_new(x, wordlen);

    (*x)->sign = sign;
    array_copy((*x)->a, a, wordlen);
}

int set_hex_bi(const char* str, word* bi, unsigned int wordlen)
{
    int word_ = 0;
    int cnt_i=0;
    word num;

    for( int i=(strlen(str)-1); i>=0; i-- )
    {
        if( (str[i]>='0') && (str[i]<='9') )
            num = (word)(str[i] - '0');

        else if( (str[i]>='a') && (str[i]<='f') )
            num = ((word)(str[i] - 'a') + 10);
        
        else if( (str[i]>='A') && (str[i]<='F') )
            num = ((word)(str[i] - 'A') + 10);
        
        else {
            puts("--set_hex_bi function error--\nInvalid input error");
            return FALSE;
        }
        bi[word_] ^= (num << ((cnt_i)*4));
        cnt_i++;

        if( cnt_i == (sizeof(word)*2) )
        {
            word_++;
            cnt_i = 0;
        }
    }
    return TRUE;
}

int set_bin_bi(const char* str, word* bi, unsigned int wordlen)
{
    int word_ = 0, cnt_i = 0;
    word num;

    for( int i=(strlen(str)-1); i>=0; i-- )
    {
        if( (str[i] == '0') || (str[i] == '1') )
            num = (word)(str[i] - '0');
        else {
            puts("--set_bin_bi function error--\nInvalid input error");
            return FALSE;
        }

        bi[word_] ^= (num << cnt_i);
        cnt_i++;

        if( cnt_i == WORD_BIT_SIZE ) 
        {
            word_++;
            cnt_i = 0;
        }
    }
    return TRUE;
}

int set_dec_bi(const char* str, bigint* bi, unsigned int wordlen)
{
    int word_ = 0, cnt_i = 0;
    word num;

    return TRUE;
}

void bi_set_by_string(bigint** x, int sign, char* str, int base)
{
    if ((*x) != NULL )
        bi_delete(x);

    /*  string length  */   
    unsigned int len = strlen(str);

    if( base == HEXADECIMAL ) // 16진수
    { 
        unsigned int w_len = (len / (sizeof(word)*2)) + 1;
        bi_new(x, w_len);
        set_hex_bi(str, (*x)->a, w_len);
        (*x)->sign = sign;
        bi_refine((*x));
        return;

    } else
    if( base == BINARY ) // 2진수
    { 
        unsigned int w_len = (len / (sizeof(word)*8)) + 1;
        bi_new(x, w_len);
        set_bin_bi(str, (*x)->a, w_len);
        (*x)->sign = sign;
        bi_refine((*x));
        return;

    } else
    if( base == DECIMAL ) { // 10진수
        
        bi_new(x, 1);

        int word_ = 0, cnt_i = 0;
        word num;

        for( int i=(strlen(str)-1); i>=0; i-- )
        {
            if( (str[i]>='0') && (str[i]<='9') ) {
                // num = (word)(str[i] - '0');
                // bigint* temp_x = NULL;
                // ADD(temp_x, (*x), NULL);
            }
        }
        (*x)->sign = sign;
        return;
    }
    else 
    {
        puts("--bi_set_by_string function error--\nInvalid input value");
        return;
    }
}
/// ========================================================================= ///


/// ===========================( Refine BigInt )============================= ///

void bi_refine(bigint* x) 
{
    if( x == NULL )
        return;
    
    int new_wordlen = x->wordlen;
    while(new_wordlen > 1)  // at least one word needed
    {
        if(x->a[new_wordlen - 1] != 0)
            break;
        new_wordlen--;
    }
    if( x->wordlen != new_wordlen )
    {
        x->wordlen = new_wordlen;
        x->a = (word*)realloc(x->a, sizeof(word)*new_wordlen);
    }
    if( (x->wordlen == 1) && (x->a[0] == 0x0) )
        x->sign = NON_NEGATIVE;
}

/// ========================================================================= ///


/// ===========================( Assign BigInt )============================= ///

void array_copy(word* y_a, word* x_a, unsigned int wordlen)
{  
    if( x_a == NULL || y_a == NULL || wordlen == 0 )
        return;

    memcpy(y_a, x_a, sizeof(word)*wordlen);
}

void bi_assign(bigint** y, bigint* x)
{
    if( *y != NULL )
        bi_delete(y);
    
    bi_new(y, x->wordlen);
    (*y)->sign = x->sign;
    array_copy((*y)->a, x->a, x->wordlen);
}
/// ========================================================================= ///


/// ======================( Generate Random BigInt )========================= ///

void array_rand(word* dst, unsigned int wordlen)
{
    byte* p = (byte*)dst;
    int cnt = wordlen * sizeof(word);
    while(cnt > 0){
        *p = rand() & 0xff; // DRBG로 변경 가능하도록 한다.
        p++;
        cnt--;
    }
}

void bi_gen_rand(bigint** x, int sign, unsigned int wordlen)
{
    bi_new(x, wordlen);
    (*x)->sign = sign;
    array_rand((*x)->a, wordlen);

    bi_refine(*x);
}

/// ========================================================================= ///


/// ===========================( Set One/Zero  )============================= ///

void bi_set_one(bigint** x)
{
    if((*x) != NULL )
        bi_delete(x);
    
    bi_new(x, 1);
    (*x)->sign = NON_NEGATIVE;
    (*x)->a[0] = 0x1;
}

void bi_set_zero(bigint** x)
{
    if((*x) != NULL )
        bi_delete(x);

    bi_new(x, 1);
    (*x)->sign = NON_NEGATIVE;
    (*x)->a[0] = 0x0;
}

void set_all_zero(bigint** x)
{
    for(int i=0; i<(*x)->wordlen; i++){
        (*x)->a[i] = 0x0;
    }
}

/// ========================================================================= ///


/// =========================( Is One/Zero BigInt )=========================== ///

int bi_is_one(bigint* x)
{
    if( x->sign == NEGATIVE || x->a[0] != 1 )
        return FALSE;
    for( int j=x->wordlen-1; j>=0; j-- ) {
        if( x->a[j] != 0 ) 
            return FALSE;
    }
    return TRUE;
}

int bi_is_zero(bigint* x)
{
    if( x->sign == NEGATIVE || x->a[0] != 0 )
        return FALSE;
    for( int j=x->wordlen-1; j>=0; j-- ) {
        if( x->a[j] != 0 ) 
            return FALSE;
    }
    return TRUE;
}

/// ========================================================================= ///


/// ==========================( Compare BigInt )============================= ///
/*  
    - x == y ->  0
    - x < y  -> -1
    - x > y  ->  1
*/
int compareABS(bigint* x, bigint *y)
{
    int n = x->wordlen;
    int m = y->wordlen;

    if( n>m ) return 1;
    else if( n<m ) return -1;
    
    // n=m
    for( int j=n-1; j>=0; j-- ) {
        if( x->a[j] > y->a[j] )
            return 1;
        else if( x->a[j] < y->a[j] )
            return -1;
    }
    return 0;
}

int compare(bigint* x, bigint* y)
{
    if( (x->sign == NON_NEGATIVE) && (y->sign == NEGATIVE) )
        return 1;
    
    if( (x->sign == NEGATIVE) && (y->sign == NON_NEGATIVE) )
        return -1;
    
    int ret = compareABS(x, y);
    if( x->sign == NON_NEGATIVE )
        return ret;
    else
        return (-1)*ret;
}

/// ========================================================================= ///


/// =======================( Shift and Reduction )=========================== ///

/*   Left Shift : A << r */
void l_shift(bigint** x, unsigned int r) 
{
    if( (*x) == NULL ) {
        puts("--l_shift function error--\nInvalid input value : null");
        return;
    }

    unsigned int n = (*x)->wordlen;
    unsigned int k = r/WORD_BIT_SIZE;
    unsigned int rp = r%WORD_BIT_SIZE;

    if( r%WORD_BIT_SIZE == 0 ) {
        bigint* re_x = NULL;
        bi_new(&re_x, n + k);
        re_x->sign = (*x)->sign;
        array_copy(re_x->a+k, (*x)->a, n);

        bi_assign(x, re_x);
        bi_delete(&re_x);

        return;
    }
    else {
        bigint* re_x = NULL;
        bi_new(&re_x, n+1);
        re_x->sign = (*x)->sign;
        
        word mask = (1 << (WORD_BIT_SIZE - rp +1)) - 1;

        re_x->a[n] = (*x)->a[n-1] >> (WORD_BIT_SIZE - rp);
        for( int i=n-1; i>0; i-- ) {
            re_x->a[i] = (((*x)->a[i]) /*& mask*/) << rp | ((*x)->a[i-1]) >> (WORD_BIT_SIZE-rp);
        }
        re_x->a[0] = ((*x)->a[0] << rp);

        bi_refine(re_x);
        bi_assign(x, re_x);
        bi_delete(&re_x);

        if( k > 0 ) {
            l_shift(x, k*WORD_BIT_SIZE);
            return;
        }
    }
    return;
}

/*   Right  Shift : A >> r */
void r_shift(bigint** x, unsigned int r)
{
    unsigned int n = (*x)->wordlen;

    if( r >= (n*WORD_BIT_SIZE) ){
        bi_set_zero(x);
        return;
    }

    else if( r%WORD_BIT_SIZE == 0){
        int k = r/WORD_BIT_SIZE;
        bigint* re_x = NULL;
        bi_new(&re_x, n);
        re_x->sign = (*x)->sign;
        array_copy(re_x->a, (*x)->a+k, n-k);

        bi_assign(x, re_x);
        bi_refine((*x));
        bi_delete(&re_x);
        return;
    }

    else {
        int k = r/WORD_BIT_SIZE;
        int rp = r % WORD_BIT_SIZE;

        bigint* re_x = NULL;
        bi_new(&re_x, n);
        re_x->sign = (*x)->sign;

        re_x->a[n-1] = (*x)->a[n-1] >> rp;
        for( int i=n-2; i>=0; i-- ) {
            re_x->a[i] = (((*x)->a[i+1] << (WORD_BIT_SIZE - rp))) | ((*x)->a[i] >> rp);
        }
        bi_assign(x, re_x);
        bi_delete(&re_x);

        if( k > 0 ) {
            r_shift(x, k*WORD_BIT_SIZE);
            return;
        }

        return;
    }
}


/* Reduction */
void reduction(bigint** x, unsigned int r){

    if( (*x) == NULL ) {
        puts("--reduction function error--\nInvalid input value : null");
        return;
    }
    
    if( r < 0 ) {
        puts("--reduction function error--\nInvalid input value : r should be larger than 0");
        return;
    }

    // Case1
    if(r >= ((*x)->wordlen) * WORD_BIT_SIZE){
        return;
    }

    // Case2
    else if(r%WORD_BIT_SIZE == 0){
        unsigned int k = r/WORD_BIT_SIZE;
        for( int i=k; i<(*x)->wordlen; i++) {
            (*x)->a[i] = 0;
        }
        bi_refine((*x));
        return;
    }

    // Case3
    else {
        fflush(stdout);
        unsigned int k = r/WORD_BIT_SIZE;
        unsigned int r_p = r % WORD_BIT_SIZE;

        (*x)->a[k] = ((*x)->a[k] << (WORD_BIT_SIZE - r_p)) >> (WORD_BIT_SIZE - r_p);
        for( int i=k+1; i<(*x)->wordlen; i++ ) {
            (*x)->a[i] = 0;
        }
        bi_refine((*x));
        return;
    }
}

/// ========================================================================= ///


/// ==========================( Other functions )============================ ///

/* Get Word Length */
int getWordLen(bigint* x){
    return x->wordlen;
}

/* Get Bit Length */
int getBitLen(bigint* x){
    int b_length = 0;
    int w = x->wordlen;
    
    word buf = x->a[w-1];
    int ext_length = 0;
    while( buf > 0 ) {
        ext_length++;
        buf >>= 1;
    }
    b_length = ext_length + (w-1)*WORD_BIT_SIZE;

    return b_length;
}

/* Get j-th Bit */
int get_j_bit(bigint* x, unsigned int j){
    // 0 ~ len(A) = wordlen * 32
    int q = j / WORD_BIT_SIZE;
    int r = j % WORD_BIT_SIZE;
    int result;

    word buf = x->a[q];
    for( int i=0; i<r; i++ ) buf >>= 1;
    result = buf & 0x1;
    return result;
}

/* Get Sign of Bigint */
int getSign(bigint* x) {
    return x->sign;
}

/* Flip Sign of Bigint */
void flipSign(bigint** x) {
    if( (*x)->sign == NON_NEGATIVE )
        (*x)->sign = NEGATIVE;
    else
        (*x)->sign = NON_NEGATIVE;
}

/// ========================================================================= ///
