/*!
 * @file BasicOperation.h
 * @date 2023/12
 * @brief Header file of Basic Operation
*/
#ifndef __BASICOPERATION_H__
#define __BASICOPERATION_H__
#include "config.h"
#include "Div.h"

/// ======================( Create / Delete BigInt )========================= ///
/*!
 * @section Create / Delete BigInt
*/
/*!
 * @fn void bi_new(bigint** x, unsigned int wordlen)
 * @brief  Allocate Big integer memory space
 * @param[in] x Double pointer of big integer
 * @param[in] wordlen Word length of Big integer
 * @return void
*/
void bi_new(bigint** x, unsigned int wordlen);

/*!
 * @fn void bi_delete(bigint** x)
 * @brief Delete big integer memory space
 * @param[in] x Double pointer of big integer
 * @return void
*/
void bi_delete(bigint** x);

/*!
 * @fn void array_init(word* a, unsigned int wordlen)
 * @brief  Initialize the array
 * @param[in] a Word pointer
 * @param[in] wordlen Length of word
 * @return void
*/
void array_init(word* a, unsigned int wordlen);
/// ========================================================================= ///


/// =============================( Show BigInt )============================= ///
/*!
 * @section Show BigInt
*/
/*!
 * @fn void bi_show_hex(bigint* x) 
 * @brief Show Big integer in hexadecimal form
 * @param[in] x Pointer of big integer
 * @return void
*/
void bi_show_hex(bigint* x);

/*!
 * @fn void bi_show_bin(bigint* x)
 * @brief Show Big integer in binary form
 * @param[in] x Pointer of big integer
 * @return void
*/
void bi_show_bin(bigint* x);

/*!
 * @fn void bi_show_dec(bigint* x)
 * @brief Show Big integer in decimal form
 * @param[in] x Pointer of big integer
 * @return void
*/
void bi_show_dec(bigint* x);
/// ========================================================================= ///


/// =============================( Set BigInt )============================== ///
/*!
 * @section Set Bigint
*/
/*!
 * @fn int set_hex_bi(const char* str, word* bi, unsigned int wordlen)
 * @brief Change a string in hexadecimal form to binary array
 * @param[in] str String with hexadecimal form
 * @param[in] bi Array to store binary converted value
 * @param[in] wordlen Show the length of array(bi)
 * @return int
*/
int set_hex_bi(const char* str, word* bi, unsigned int wordlen);

/*!
 * @fn int set_bin_bi(const char* str, word* bi, unsigned int wordlen)
 * @brief Change a string in binary form to binary array
 * @param[in] str String with binary form
 * @param[in] bi Array to store binary converted value
 * @param[in] wordlen Show the length of array(bi)
 * @return int
*/
int set_bin_bi(const char* str, word* bi, unsigned int wordlen);

/*!
 * @fn void bi_set_by_array(bigint** x, int sign, word* a, unsigned int wordlen)
 * @brief Set the array value of big integer structure
 * @param[in] x Double pointer of big integer
 * @param[in] sign Sign of big integer
 * @param[in] a Word pointer
 * @param[in] wordlen Word length of big integer
 * @return void
*/
void bi_set_by_array(bigint** x, int sign, word* a, unsigned int wordlen);

/*!
 * @fn void bi_set_by_string(bigint** x, int sign, char* str, int base);
 * @brief Set the string value of Big integer structure
 * @param[in] x Double pointer of big integer
 * @param[in] sign Sign of big integer
 * @param[in] str Character pointer
 * @param[in] base
 * @return void
 * @warning Unfinished Func!
*/
void bi_set_by_string(bigint** x, int sign, char* str, int base);
/// ========================================================================= ///


/// ===========================( Refine BigInt )============================= ///
/*!
 * @section Refine Bigint
*/
/*!
 * @fn void bi_refine(bigint* x) 
 * @brief Remove the last zero words
 * @param[in] x Pointer of big integer
 * @return void
*/
void bi_refine(bigint* x); 
/// ========================================================================= ///


/// ===========================( Assign BigInt )============================= ///
/*!
 * @section Assign Bigint ( Y <- X )
*/
/*!
 * @fn void array_copy(word* y_a, word* x_a, unsigned int wordlen)
 * @brief Copy the array x_a to y_a
 * @param[in] y_a Word pointer get copy
 * @param[in] x_a Word pointer 
 * @param[in] wordlen Length of word
 * @return void
*/
void array_copy(word* y_a, word* x_a, unsigned int wordlen);

/*!
 * @fn void bi_assign(bigint** y, bigint* x)
 * @brief Copy the big integer x to y
 * @param[in] y Double pointer of big integer get copy
 * @param[in] x Pointer of big integer 
 * @return void
*/
void bi_assign(bigint** y, bigint* x);
/// ========================================================================= ///


/// ======================( Generate Random BigInt )========================= ///
/*!
 * @section Generate Random BigInt
*/
/*!
 * @fn void array_rand(word* dst, unsigned int wordlen)
 * @brief Generate random value for a fixed length
 * @param[in] dst Address pointer of array
 * @param[in] wordlen Length of big integer
 * @return void
*/
void array_rand(word* dst, unsigned int wordlen);

/*!
 * @fn void bi_gen_rand(bigint** x, int sign, unsigned int wordlen)
 * @brief Generate random value for a big integer
 * @param[in] x Double pointer of big integer
 * @param[in] sign Sign of big integer
 * @param[in] wordlen Length of big integer
 * @return void
*/
void bi_gen_rand(bigint** x, int sign, unsigned int wordlen);
/// ========================================================================= ///


/// ===========================( Set One/Zero  )============================= ///
/*!
 * @section Set One/Zero
*/
/*!
 * @fn void bi_set_one(bigint** x)
 * @brief Set a big integer value to one
 * @param[in] x Double pointer of big integer
 * @return void
*/
void bi_set_one(bigint** x);

/*!
 * @fn void bi_set_zero(bigint** x)
 * @brief Set a big integer value to zero
 * @param[in] x Double pointer of big integer
 * @return void
*/
void bi_set_zero(bigint** x);

/*!
 * @fn void set_all_zero(bigint** x)
 * @brief Set a big integer
 * @param[in] x Double pointer of big integer
 * @return void
*/
void set_all_zero(bigint** x);
/// ========================================================================= ///


/// =========================( Is One/Zero BigInt )=========================== ///
/*!
 * @section Is One/Zero?
*/
/*!
 * @fn int bi_is_one(bigint* x)
 * @brief Verify the value of big integer is one
 * @param[in] x Pointer of big integer
 * @return True or False
*/
int bi_is_one(bigint* x);

/*!
 * @fn int bi_is_zero(bigint* x)
 * @brief Verify the value of big integer is zero
 * @param[in] x Pointer of big integer
 * @return True or False
*/
int bi_is_zero(bigint* x);
/// ========================================================================= ///


/// ==========================( Compare BigInt )============================= ///
/*!
 * @section Compare
*/
/*!
 * @fn int compareABS(bigint* x, bigint *y)
 * @brief Compare two non negative integers
 * @param[in] x Pointer of big integer
 * @param[in] y Pointer of big integer
 * @return If x>y 1, else if x<y -1, else 0
*/
int compareABS(bigint* x, bigint *y);

/*!
 * @fn int compare(bigint* x, bigint* y)
 * @brief Compare two integers
 * @param[in] x Pointer of big integer
 * @param[in] y Pointer of big integer
 * @return If x>y 1, else if x<y -1, else 0
*/
int compare(bigint* x, bigint* y);
/// ========================================================================= ///


/// =======================( Shift and Reduction )=========================== ///
/*!
 * @section Shift and Reduction
*/
/*!
 * @fn void l_shift(bigint** x, unsigned int r)
 * @brief Shift big integer to left
 * @param[in] x Double pointer of big integer
 * @param[in] r Size to shift
 * @return void
*/
void l_shift(bigint** x, unsigned int r);

/*!
 * @fn void r_shift(bigint** x, unsigned int r)
 * @brief Shift big integer to right
 * @param[in] x Double pointer of big integer
 * @param[in] r Size to shift
 * @return void
*/
void r_shift(bigint** x, unsigned int r);


/*!
 * @fn void reduction(bigint** x, unsigned int r)
 * @brief Reduce a big integer by mod operation
 * @param[in] x Double pointer of big integer
 * @param[in] r Size to reduce
 * @return void
 * @warning pow -> bit shift
*/
void reduction(bigint** x, unsigned int r);
/// ========================================================================= ///


/// ==========================( Other functions )============================ ///
/*!
 * @section Other functions
*/
/*!
 * @fn int getWordLen(bigint* x)
 * @brief Get word length of big integer
 * @param[in] x Pointer of big integer
 * @return x->wordlen, Word length of big integer
*/
int getWordLen(bigint* x);

/*!
 * @fn int getBitLen(bigint** x)
 * @brief Get big length of big integer
 * @param[in] x Pointer of big integer
 * @return b_length, Bit length of big integer
*/
int getBitLen(bigint* x);

/*!
 * @fn int get_j_bit(bigint* x, unsigned int j)
 * @brief Get the value at the j-th bit
 * @param[in] x Pointer of big integer
 * @param[in] j Position to get the value
 * @return result, Value at the j-th bit
*/
int get_j_bit(bigint* x, unsigned int j);

/*!
 * @fn int getSign(bigint* x)
 * @brief Get the sign of big integer
 * @param[in] x Pointer of big integer
 * @return x->sign, Sign of big integer
*/
int getSign(bigint* x);

/*!
 * @fn void flipSign(bigint** x)
 * @brief Flip the sign of big integer
 * @param[in] x Double pointer of big integer
 * @return void
*/
void flipSign(bigint** x);
/// ========================================================================= ///

#endif