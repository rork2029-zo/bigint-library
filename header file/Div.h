/*!
 * @file Div.h
 * @date 2023/12
 * @brief Header file of Division
*/
#ifndef __DIV_H__
#define __DIV_H__

#include "config.h"
#include "BasicOperation.h"
#include "Add_Sub.h"
#include "Mul.h"

/// ========================( Division )=========================== ///
/*!
 * @section Division
*/
/*!
 * @fn void DIV_long(bigint** Q, bigint** R, bigint* A, bigint* B)
 * @brief  Multi-Precision long division
 * @param[in] Q Double pointer of big integer to assign the result of the quotient
 * @param[in] R Double pointer of big integer to assign the result of the remainder
 * @param[in] A Pointer of big integer that n word size
 * @param[in] B Pointer of big integer that non-negative
 * @remark A = BQ + R
 * @return void, (Q, R)
*/
/*!  [Pseudo code]
 *  Input: A, B
 *  Output: (Q, R) -> A = BQ + R
 *  1. if A<B then
 *  2.      return (0,A)
 *  3. end if
 *  4. R_n <- 0
 *  5. for i=n-1 downto 0 do
 *  6.      (Q_i, R_i) <- DIVC(R_i+1*W + A_i, B)
 *  7. end for
 *  8. Q <- Q_j for j=0, ..., n-1
 *  9. return (Q,R_0)
*/
void DIV_long(bigint** Q, bigint** R, bigint* A, bigint* B);

/*!
 * @fn void DIVC(bigint** Q, bigint** R, bigint* A, bigint* B)
 * @brief  Division that wordlen of A is bigger than wordlen of B
 * @param[in] Q Double pointer of big integer to assign the result of the quotient
 * @param[in] R Double pointer of big integer to assign the result of the remainder
 * @param[in] A Pointer of big integer that m+1 word size
 * @param[in] B Pointer of big integer that m word size
 * @remark A = BQ + R
 * @return void, (Q, R)
*/
/*!  [Pseudo code]
 *  Input: A, B -> different word length (wordlen(A) >= wordlen(B), 0 <= A < BW)
 *  Output: (Q, R) -> A = BQ + R (0 <= Q < W, 0 <= R < B)
 *  1. if A<B then
 *  2.      return (0,A)
 *  3. end if
 *  4. Compute k -> Integer that bigger than zero; 2^k * B_m-1 -> [2^w-1, 2^w)
 *  5. A', B' <- 2^k*A, 2^k*B
 *  6. Q', R' <- DIVCC(A',B')
 *  7. Q, R <- Q', 2^(-k) * R'
 *  8. return (Q,R)
*/
void DIVC(bigint** Q, bigint** R, bigint* A, bigint* B);

/*!
 * @fn void DIVCC(bigint** Q, bigint** R, bigint* A, bigint* B)
 * @brief  Divide big integer
 * @param[in] Q Double pointer of big integer to assign the result of the quotient
 * @param[in] R Double pointer of big integer to assign the result of the remainder
 * @param[in] A Pointer of big integer that n word size
 * @param[in] B Pointer of big integer that m word size
 * @remark A = BQ + R
 * @return void, (Q, R)
*/
/*!  [Pseudo code]
 *  Input: A, B -> different word length (wordlen(A) >= wordlen(B), 0 < B <= A < BW)
 *  Output: (Q, R) -> A = BQ + R (0 <= Q < W, 0 <= R < B)
 *  1. if n=m then
 *  2.      Q <- floor(A_m-1 / B_m-1)
 *  3. end if
 *  4. if n=m+1 then
 *  5.      if A_m = B_m-1 then
 *  6.          Q <- W -1
 *  7.      else
 *  8.          Q <- floor((A_m*W + A_m-1) / B_m-1)
 *  9.      end if
 *  10. end if
 *  11. R <- A - BQ
 *  12. while R<0 do
 *  13.     (Q,R) <- (Q-1, R+B)
 *  14. end while
 *  15. return (Q,R)
*/
void DIVCC(bigint** Q, bigint** R, bigint* A, bigint* B);

/*!
 * @fn void Two_word_long_DIV(word* Q, bigint* A, word* B)
 * @brief  Binary long division in two word size
 * @param[in] Q Word pointer to assign the result of the quotient
 * @param[in] A Pointer of big integer
 * @param[in] B Word pointer
 * @remark A = BQ + R
 * @return void, word Q
*/
/*!  [Pseudo code]
 *  Input: A, B -> A = A1*W + A0 (A1, A0 : 1-word), B = [2^(w-1), 2^w), A1 < B, 0 < B <= A < BW
 *  Output: Q -> A = BQ + R (0 <= Q < W, 0 <= R < B)
 *  1. (Q,R) <- (0, A1)
 *  2. for j=w-1 downto 0 do
 *  3.      if R>=2^w-1 then
 *  4.          (Q,R) <- (Q + 2^j, 2R + a_j - B)
 *  5.      else
 *  6.          R <- 2R + a_j
 *  7.          if R>=B then
 *  8.              (Q,R) <- (Q + 2^j, R - B)
 *  9.          end if
 *  10.     end if
 *  11. end for
 *  12. return Q
*/
void Two_word_long_DIV(word* Q, bigint* A, word* B);
/// =========================================================== ///


/// ====================( Fast Reduction )====================== ///
/*!
 * @section Fast reduction
*/
/*!
 * @fn void Barrett_reduction(bigint** R, bigint* A, bigint* N, bigint* T)
 * @brief  Improve computation speed by pre-calculating T
 * @param[in] R Double pointer of big integer to assign the result of the reduction
 * @param[in] A Pointer of big integer
 * @param[in] N Pointer of big integer
 * @param[in] T Pointer of big integer that pre-calculating value
 * @remark R = A mod N
 * @return void, bigint R
*/
/*!  [Pseudo code]
 *  Input: A, N, T -> 0 <= A < W^2n, W^n-1 <= N < W^n, pre-computed T = floor(W^2n / N)
 *  Output: R = A mod N -> 0 <= R < W^n
 *  1. Q_hat <- A >> w*(n-1)
 *  2. Q_hat <- Q_hat * T
 *  3. Q_hat <- Q_hat >> w**(n+1)
 *  4. R <- N * Q_hat
 *  5. R <- A - R
 *  6. while R >= N do
 *  7.      R <- R - N
 *  8. end while
 *  9. return R
*/
void Barrett_reduction(bigint** R, bigint* A, bigint* N, bigint* T);
/// =========================================================== ///


#endif