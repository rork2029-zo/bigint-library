/*!
 * @file verify.c
 * @date 2023/12
 * @brief Source code of Verify
*/
#include "verify.h"


/* 

=================( Verify Function List )================== 

|- add_check_py();
|- sub_check_py();
|- mul_check_py(mode);
|- div_check_py();
|- squ_check_py(mode);
|- exp_check_py();
|- Barrett_Reduction_check_py();

=========================================================== 

*/


int main()
{
    srand((unsigned)time(NULL));

/// =================( Addition Verify Function )================== ///
    
    // add_check_py(); 

/// =============================================================== ///


/// ===============( Substraction Verify Function )================ ///

    // sub_check_py();

/// =============================================================== ///


/// ===============( Multiplication Verify Function )============== ///

    mul_check_py("karatsuba");

/// =============================================================== ///


/// ==================( Division Verify Function )================= ///

    div_check_py();

/// =============================================================== ///


/// =================( Squaring Verify Function )================== ///

    // squ_check_py("karatsuba");

/// =============================================================== ///


/// ============( Modular Exponentiation Verify Function )=========== ///

    // exp_check_py();

/// ================================================================= ///


/// ==============( Barrett Reduction Verify Function )============== ///

    // Barrett_Reduction_check_py();
    
/// ================================================================= ///    

    // system("leaks out");

    return 0;
}