/*!
 * @file Squ.h
 * @date 2023/12
 * @brief Header file of Squaring
*/
#ifndef __SQU_H__
#define __SQU_H__
#include "config.h"
#include "BasicOperation.h"
#include "Add_Sub.h"
#include "Mul.h"

/// ==========================( Squaring  )=============================== ///
/*!
 * @section Squaring
*/
/*!
 * @fn void SingleWordSqu(bigint* C, word A)
 * @brief  Square a single word
 * @param[in] C Pointer of big integer to assign the result of the squaring
 * @param[in] A Single word
 * @return void, bigint C
*/
/*!  [Pseudo code]
 *  Input: A->(-W,W)
 *  Output: C = A^2
 *  1. A1, A0 <- A[w:w/2], A[w/2:0]
 *  2. C1, C0 <- A1^2, A0^2
 *  3. C <- (C1 << w) + C0
 *  4. T <- A0*A1
 *  5. T <- T << (w/2 + 1)
 *  6. C <- C + T
 *  7. return C
*/
void SingleWordSqu(bigint* C, word A);

/*!
 * @fn void SQUC(bigint** C, bigint* A)
 * @brief  Textbook squaring of big integer
 * @param[in] C Double pointer of big integer to assign the result of the squaring
 * @param[in] A Pointer of big integer
 * @return void, bigint C
*/
/*!  [Pseudo code]
 *  Input: A->[W^t-1, W^t)
 *  Output: C = A^2
 *  1. C1, C2 <- 0
 *  2. for j=0 to t-1 do
 *  3.      T1 <- A_j^2
 *  4.      T1 <- T1 << 2*jw
 *  5.      C1 <- T1 + C1
 *  6.      for i=j+1 to t-1 do
 *  7.          T2 <- A_j * A_i
 *  8.          T2 <- T2 << (i+j)*w
 *  9.          C2 <- ADD(C2, T2)
 *  10.     end for
 *  11. end for
 *  12. C2 <- C2 << 1
 *  13. C <- ADD(C1,C2)
 *  14. return C
*/
void SQUC(bigint** C, bigint* A);

/*!
 * @fn void SQU(bigint** C, bigint* A)
 * @brief   Square big integer
 * @param[in] C Double pointer of big integer to assign the result of the squaring
 * @param[in] A Pointer of big integer
 * @return void, bigint C
*/
/*!  [Pseudo code]
 *  Input: A -> Sign is non-negative or negative
 *  Output: C = A^2
 *  1. if A=0 of A=1,-1 then
 *  2.      return |A|
 *  3. end if
 *  4. return SQUC(A)
*/
void SQU(bigint** C, bigint* A);

/*!
 * @fn void Karatsuba_SQU(bigint** C, bigint* A, unsigned int flag)
 * @brief  Efficient squaring using Karatsuba algorithm
 * @param[in] C Word pointer to assign the result of the squaring
 * @param[in] A Single word
 * @param[in] flag Determinie how deep to repeat recursion
 * @return void, bigint C
*/
/*!  [Pseudo code]
 *  Input: A -> Sign is non-negative or negative
 *  Output: C = A^2
 *  1. if flag >= wordlen(A) then
 *  2.      return SQUC(A)
 *  3. end if
 *  4. l <- (wordlen(A) + 1) >> 1
 *  5. A1, A0 <- |A| >> lw, |A| mod 2^lw
 *  6. T1, T0 <- Karatsuba_SQU(A1), Karatsuba_SQU(A0)
 *  7. R <- (T1 << 2*lw) + T0
 *  8. S <- Karatsuba_SQU(A1, A0)
 *  9. S <- S << (lw + 1)
 *  10. C <- ADDC(R,S)
 *  11. return C
*/
void Karatsuba_SQU(bigint** C, bigint* A, unsigned int flag);
/// =========================================================== ///


#endif