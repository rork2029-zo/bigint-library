/*!
 * @file Add_Sub.c
 * @date 2023/12
 * @brief Header file of Addition and Subtraction
*/
#ifndef __ADD_SUB_H__
#define __ADD_SUB_H__
#include "config.h"
#include "BasicOperation.h"

/// =========================( Addition )============================= ///
/*!
 * @section Addition
*/
/*!
 * @fn int ADD_ABc(word* C, word A, word B, int c)
 * @brief  Add a single word with carry
 * @param[in] C Word pointer to assign the result of the addition
 * @param[in] A Single word
 * @param[in] B Single word
 * @param[in] c Integer of carry
 * @remark A + B + c = c'W + C
 * @return int c', word C
*/
/*!  [Pseudo code]
 *  Input: A, B->[0,W} and c->{0,1}
 *  Output: c'->{0,1} and C->[0,W}
 *  1. c' <- 0
 *  2. C <- A+B
 *  3. if C < A then
 *  4.      c' <- 1
 *  5. end if
 *  6. C <- C+c
 *  7. if C < c then
 *  8.      c' <- c'+1
 *  9. end if
 *  10. return c', C
*/
int ADD_ABc(word* C, word A, word B, int c);

/*!
 * @fn int ADDC(bigint** C, bigint* A, bigint* B)
 * @brief  Add big integer of the same sign
 * @param[in] C Double pointer of big integer to assign the result of the addition
 * @param[in] A Pointer of big integer 
 * @param[in] B Pointer of big integer 
 * @remark Wordlen of A must be bigger than or equal to wordlen of B
 * @return int 1, bigint C
*/
/*!  [Pseudo code]
 *  Input: A, B -> same sign, different word length (wordlen(A) >= wordlen(B))
 *  Output: C = A + B
 *  1. B_j <- 0 for j=m, m+1, ... , n-1
 *  2. c <- 0
 *  3. for j=0 to n-1 do
 *  4.      c, C_j <- ADD_ABc(A_j, B_j, c)
 *  5. end for
 *  6. C_n <- c
 *  7. if C_n=1 then
 *  8.      return C_j for j=0, ..., n
 *  9. else
 *  10.     return C_j for j=0, ..., n-1
 *  11. end if
*/
int  ADDC(bigint** C, bigint* A, bigint* B);

/*!
 * @fn void ADD(bigint** C, bigint* A, bigint* B)
 * @brief  Add a big integer
 * @param[in] C Double pointer of big integer to assign the result of the addition
 * @param[in] A Pointer of big integer 
 * @param[in] B Pointer of big integer 
 * @return void, bigint C
*/
/*!  [Pseudo code]
 *  Input: A, B -> Integer
 *  Output: C = A + B
 *  1. if A=0 then
 *  2.      return B
 *  3. end if
 *  4. if B=0 then
 *  5.      return A
 *  6. end if
 *  7. if A>0 and B<0 then
 *  8.      return SUB(A,|B|)
 *  9. end if
 *  10. if A<0 and B>0 then
 *  11.     return SUB(B,|A|)
 *  12. end if
 *  13. if wordlen(A) >= wordlen(B) then
 *  14.     return ADDC(A,B)
 *  15. else
 *  16.     return ADDC(B,A)
 *  17. end if
*/
void ADD(bigint** C, bigint* A, bigint* B);
/// ==================================================================== ///


/// =========================( Substraction )=========================== ///
/*!
 * @section Subtraction
*/
/*!
 * @fn int SUB_AbB(word* C, word A, word B, int b)
 * @brief  Subtraction a single word with borrow
 * @param[in] C Word pointer to assign the result of the subtraction
 * @param[in] A Single word
 * @param[in] B Single word
 * @param[in] c Integer of borrow
 * @remark A - b - B = -b'W + C
 * @return int b', word C
*/
/*!  [Pseudo code]
 *  Input: A, B->[0,W} and b->{0,1}
 *  Output: b'->{0,1} and C->[0,W}
 *  1. b' <- 0
 *  2. C <- A-B
 *  3. if A<b then
 *  4.      b' <- 1
 *  5. end if
 *  6. if C<B then
 *  7.      b' <- b'+1
 *  8. end if
 *  9. C <- C-B
 *  10. return b', C
*/
int SUB_AbB(word* C, word A, word B, int b);

/*!
 * @fn int SUBC(bigint** C, bigint* A, bigint* B)
 * @brief  Subtraction big integer that sign is non-negative
 * @param[in] C Double pointer of big integer to assign the result of the subtraction
 * @param[in] A Pointer of big integer 
 * @param[in] B Pointer of big integer 
 * @remark A must be bigger than or equal to B and both are non-negative
 * @return int 1, bigint C
*/
/*!  [Pseudo code]
 *  Input: A, B -> different word length (A >= B > 0)
 *  Output: C = A - B
 *  1. B_j <- 0 for j=m, m+1, ..., n-1
 *  2. b <- 0
 *  3. for j=0 to n-1 do
 *  4.      b, C_j <- SUB_AbB(A_j, b, B_j)
 *  5. end for
 *  6. l <- min{j: C_n-1 = ... = C_j = 0}
 *  7. return C
*/
int SUBC(bigint** C, bigint* A, bigint* B);

/*!
 * @fn void SUB(bigint** C, bigint* A, bigint* B)
 * @brief  Subtraction a big integer
 * @param[in] C Double pointer of big integer to assign the result of the subtraction
 * @param[in] A Pointer of big integer 
 * @param[in] B Pointer of big integer 
 * @return void
*/
/*!  [Pseudo code]
 *  Input: A, B -> Integer
 *  Output: C = A - B
 *  1. if A=0 then
 *  2.      return -B
 *  3. end if
 *  4. if B=0 then
 *  5.      return A
 *  6. end if
 *  7. if A=B then
 *  8.      return 0
 *  9. end if
 *  10. if 0<B<=A then
 *  11.     return SUBC(A,B)
 *  12. else if 0<A<B then
 *  13.     return -SUBC(B,A)
 *  14. end if
 *  15. if 0>A>=B then
 *  16.     return SUBC(|B|,|A|)
 *  17. else if 0>B>A then
 *  18.     return -SUBC(|A|,|B|)
 *  19. end if
 *  20. if A>0 and B<0 then
 *  21.     return ADD(A,|B|)
 *  22. else
 *  23.     return -ADD(|A|,B)
 *  24. end if
*/
void SUB(bigint** C, bigint* A, bigint* B);
/// ==================================================================== ///



#endif