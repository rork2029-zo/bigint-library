/*!
 * @file Mul.h
 * @date 2023/12
 * @brief Header file of Multiplication
*/
#ifndef __MUL_H__
#define __MUL_H__

#include "config.h"
#include "BasicOperation.h"
#include "Add_Sub.h"

/// =========================================================== ///
/*!
 * @section Multiplication
*/
/*!
 * @fn void SingleWordMul(word* C, word A, word B)
 * @brief  Multiplicate a single word
 * @param[in] C Word pointer to assign the result of the multiplication
 * @param[in] A Single word
 * @param[in] B Single word
 * @remark C = AB
 * @return void, bigint C
*/
/*!  [Pseudo code]
 *  Input: A, B->[0,W}
 *  Output: C = AB
 *  1. A1, A0 <- A[w:w/2], A[w/2:0]
 *  2. B1, B0 <- B[w:w/2], B[w/2:0]
 *  3. T1, T0 <- A1*B0, A0*B1
 *  4. T0 <- T1 + T0
 *  5. T1 <- T0 < T1
 *  6. C1, C0 <- A1*B1, A0*B0
 *  7. T <- C0
 *  8. C0 <- C0 + (T0 << w/2)
 *  9. C1 <- C1 + (T1 << w/2) + (T0 >> w/2) + (C0 < T)
 *  10. C <- (C1 << w) + C0
 *  11. return C
*/
void SingleWordMul(word* C, word A, word B);


/*!
 * @fn void MulC(bigint** C, bigint* A, bigint* B)
 * @brief  Textbook Multiplication of big integer of the same sign
 * @param[in] C Double pointer of big integer to assign the result of the multiplication
 * @param[in] A Pointer of big integer 
 * @param[in] B Pointer of big integer 
 * @return void, bigint C
*/
/*!  [Pseudo code]
 *  Input: A, B -> different word length
 *  Output: C = AB
 *  1. C <- 0
 *  2. for j=0 to n-1 do
 *  3.  for i=0 to m-1 do
 *  4.      T <- A_j * B_i
 *  5.      T <- T << w*(i+j)
 *  6.      C <- ADDC(C,T)
 *  7.  end for
 *  8. end for
 *  9. return C        
*/
void MulC(bigint** C, bigint* A, bigint* B);    // Textbook Multiplicatoin

/*!
 * @fn void MUL(bigint** C, bigint* A, bigint* B)
 * @brief  Multiplicate big integer
 * @param[in] C Double pointer of big integer to assign the result of the multiplication
 * @param[in] A Pointer of big integer 
 * @param[in] B Pointer of big integer 
 * @return void, bigint C
*/
/*!  [Pseudo code]
 *  Input: A, B -> Integer
 *  Output: C = AB
 *  1. if A=0 or B=0 then
 *  2.      return 0
 *  3. end if
 *  4. if A=1,-1 then
 *  5.      return B, -B
 *  6. end if
 *  7. if B=1,-1 then
 *  8.      return A, -A
 *  9. end if
 *  10. C <- MULC(|A|,|B|)
 *  11. return C
*/
void MUL(bigint** C, bigint* A, bigint* B);

/*!
 * @fn void ImpMulC(bigint** C, bigint* A, bigint* B)
 * @brief  Multiplicate big integer more efficient
 * @param[in] C Double pointer of big integer to assign the result of the multiplication
 * @param[in] A Pointer of big integer 
 * @param[in] B Pointer of big integer 
 * @return void, bigint C
*/
/*!  [Pseudo code]
 *  Input: A, B -> different word length
 *  Output: C = AB
 *  1. C <- 0
 *  2. for i=0 to 2m-1 do
 *  3.      T0, T1 <- NULL, 0
 *  4.      for k=0 to n-1 do
 *  5.          T0 <- A_2k * B_i || T0
 *  6.          T1 <- A_2k+1 * B_i || T1
 *  7.      end for
 *  8.      T <- ADDC(T0,T1)
 *  9.      T <- T << w*i
 *  10.     C <- ADDC(C,T)
 *  11. end for
 *  12. return C
*/
void ImpMulC(bigint** C, bigint* A, bigint* B);

/*!
 * @fn void Karatsuba_MUL(bigint** C, bigint* A, bigint* B, unsigned int flag)
 * @brief  Efficient multiplication using Karatsuba algorithm
 * @param[in] C Double pointer of big integer to assign the result of the multiplication
 * @param[in] A Pointer of big integer 
 * @param[in] B Pointer of big integer 
 * @param[in] flag Determinie how deep to repeat recursion
 * @remark Determine the depth of recursive through the flag to find the optimal performance
 * @return void, bigint C
*/
/*!  [Pseudo code]
 *  Input: flag and A, B -> different word length
 *  Output: C = AB
 *  1. if flag >= min(wordlen(A), wordlen(B)) then
 *  2.      return ImpMULC(A,B)
 *  3. end if
 *  4. l <- (max(wordlen(A), wordlen(B)) + 1) >> 1
 *  5. A1, A0 <- A >> lw, A mod 2^lw
 *  6. B1, B0 <- B >> lw, B mod 2^lw
 *  7. T1, T0 <- Karatsuba_MUL(A1,B1), Karatsuba_MUL(A0,B0)
 *  8. C <- (T1 << 2*lw) + T0
 *  9. S1, S0 <- SUB(A0,A1), SUB(B1,B0)
 *  10. S <- Karatsuba_MUL(|S1|,|S0|)
 *  11. S <- ADD(S,T1)
 *  12. S <- ADD(S,T0)
 *  13. S <- S << lw
 *  14. C <- ADD(C,S)
 *  15. return C
*/
void Karatsuba_MUL(bigint** C, bigint* A, bigint* B, unsigned int flag);

/// =============================================================== ///


#endif