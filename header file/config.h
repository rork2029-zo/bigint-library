#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#define WORD  64

// 부호
#define NON_NEGATIVE 0
#define NEGATIVE 1

#define ZERORIZE 1

#define TRUE 1
#define FALSE 0

typedef unsigned char byte;

// 워드 단위에 따른 값 정의
#if WORD == 8
typedef unsigned char word;
#define WORD_INTEGER_MAX UINT8_MAX // 2^8-1
#define MASK_LAST 0x0f
#define MSB_MASK 0x80
#define HEX_F "%x"
#define HEX "%02x"
#define DEC "%u"

#elif WORD == 32
typedef unsigned int word;
#define WORD_INTEGER_MAX UINT32_MAX // 2^32-1
#define MASK_LAST 0x0000ffff
#define MSB_MASK 0x80000000
#define HEX_F "%x"
#define HEX "%08x"
#define DEC "%u"

#elif WORD == 64
typedef unsigned long long word;
#define WORD_INTEGER_MAX UINT64_MAX
#define MASK_LAST 0x00000000ffffffff
#define MSB_MASK  0x8000000000000000
#define HEX_F "%llx"
#define HEX "%016llx"
#define DEC "%llu"

#endif


// 공통적으로 사용할 수 있는 파라미터
#define WORD_BIT_SIZE (sizeof(word)*8)
#define BINARY      2
#define DECIMAL     10
#define HEXADECIMAL 16

// 구조체 정의
typedef struct {

    int sign; // 0(non-negative) or 1(negative)
    unsigned int wordlen; // wordlen >= 0
    word* a; // address for big integer

} bigint;



// macro function
#ifndef min
#define min(x, y) ((x < y) ? x : y)
#endif

#ifndef max
#define max(x, y) ((x > y) ? x : y)
#endif

#endif
