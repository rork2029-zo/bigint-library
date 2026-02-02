/*!
 * @file Exp.h
 * @date 2023/12
 * @brief Header file of Modular Exponentiation
*/
#ifndef __EXPONENTIATION_H__
#define __EXPONENTIATION_H__
#include "config.h"
#include "BasicOperation.h"
#include "Add_Sub.h"
#include "Mul.h"
#include "Squ.h"
#include "Div.h"


/*!
 * @section Modular Exponentiation
*/
/*!
 * @fn void montgomery_ladder(bigint** xn, bigint* x, bigint* M, bigint* n)
 * @brief  Perform exponential calculation big integer
 * @param[in] xn Double pointer of big integer to assign the result of the exponentiation
 * @param[in] x Pointer of big integer that input value
 * @param[in] M Pointer of big integer that modular
 * @param[in] n Pointer of big integer that exponent power
 * @return void, bigint xn
*/
/*!  [Pseudo code]
 *  Input: x, n and M
 *  Output: x^n mod M
 *  1. t0, t1 <- 1, x
 *  2. for i <- l-1 downto 0 do
 *  3.      t_(1-n_i) <- t0 * t1 mod M
 *  4.      t_(n_i) <- (t_(n_i))^2 mod M
 *  5. end for
 *  6. return t0
*/
void montgomery_ladder(bigint** xn, bigint* x, bigint* N, bigint* M);

#endif