#include "unity.h"
#include "num.h"
#include "new.h"

void
setUp (void)
{
    // set stuff up here
}

void
tearDown (void)
{
    // clean stuff up here
}

void
test_allocate_num (void) 
{
    num_t z = new(num, 0.0, 0.0);    
    delete(z);
}

void
test_is_zero (void)
{
    num_t z = new(num, 0.0, 0.0);    
    const int ret = num_is_zero(z);
    delete(z);
    
    TEST_ASSERT_MESSAGE( ret == 1 , "zero isn't 0, end of the world!");
}

void
test_is_not_zero (void)
{
    num_t z = new(num, 1.0, 0.0);    
    const int ret = num_is_zero(z);
    delete(z);
    
    TEST_ASSERT_MESSAGE( ret != 1 , "one equals zero, end of the world!");
}

void
test_is_not_zero_I (void)
{
    num_t z = new(num, 0.0, 1.0);    
    const int ret = num_is_zero(z);
    delete(z);
    
    TEST_ASSERT_MESSAGE( ret != 1 , "I equals zero, end of the world!");
}

void
test_is_real (void)
{
    num_t z = new(num, 3.0, 0.0);    
    const int ret = num_is_real(z);
    delete(z);
    
    TEST_ASSERT_MESSAGE( ret == 1 , "3 has an imaginary part (?)");
}

void
test_is_not_real (void)
{
    num_t z = new(num, 3.0, 4.0);    
    const int ret = num_is_real(z);
    delete(z);
    
    TEST_ASSERT_MESSAGE( ret != 1 , "3+4i is real (?)");
}

void
test_is_not_real_I (void)
{
    num_t z = new(num, 0.0, 1.0);    
    const int ret = num_is_real(z);
    delete(z);
    
    TEST_ASSERT_MESSAGE( ret != 1 , "I is real(?)");
}

void
test_num_to_double (void)
{
    num_t z = new(num, 5.4, 0.0);    
    const double ret = num_to_double(z);
    delete(z);

    TEST_ASSERT_EQUAL_DOUBLE( 5.4, ret );        
}

void
test_num_to_double_fail (void)
{
    num_t z = new(num, 5.4, 3.0);    
    const double ret = num_to_double(z);
    delete(z);

    TEST_ASSERT_EQUAL_DOUBLE( NAN, ret );        
}

void
test_num_to_pair (void)
{
    num_t z = new(num, 5.4, 3.0);
    double ret[2];
    num_to_pair(&ret, z);
    delete(z);

    TEST_ASSERT_EQUAL_DOUBLE( 5.4, ret[0] );
    TEST_ASSERT_EQUAL_DOUBLE( 3.0, ret[1] ); 
}

void
test_real_part (void)
{
    num_t z = new(num, 3.0, 4.0);
    const double ret = num_to_double(num_real_part(z));
    delete(z);
    
    TEST_ASSERT_EQUAL_DOUBLE( 3.0, ret ); 
}

void
test_imag_part (void)
{
    num_t z = new(num, 3.0, -4.0);    
    const double ret = num_to_double(num_imag_part(z));
    delete(z);

    TEST_ASSERT_EQUAL_DOUBLE( -4.0, ret );         
}


void
test_num_abs2 (void)
{
    num_t z = new(num, 3.0, 4.0);    
    const double ret = num_to_double(num_abs2(z));
    delete(z);

    TEST_ASSERT_EQUAL_DOUBLE( 25.0, ret );        
}

void
test_num_abs_real (void)
{
    num_t z = new(num, -3.0, 0.0);    
    const double ret = num_to_double(num_abs(z));
    delete(z);

    TEST_ASSERT_EQUAL_DOUBLE( 3.0, ret );        
}

void
test_num_abs_complex (void)
{
    num_t z = new(num, 3.0, 4.0);    
    const double ret = num_to_double(num_abs(z));
    delete(z);

    TEST_ASSERT_EQUAL_DOUBLE( 5.0, ret );        
}

void
test_num_negative (void)
{
    num_t z = new(num, 4.0, 0.0);    
    const double ret = num_to_double(num_negative(z));
    delete(z);

    TEST_ASSERT_EQUAL_DOUBLE( -4.0, ret );        
}

void
test_num_conjugate (void)
{
    num_t z = new(num, 3.0, 4.0);    
    num_t ret = num_conjugate(z);
    const double re = num_to_double(num_real_part(ret));
    const double im = num_to_double(num_imag_part(ret));
    delete(z), delete(ret);

    TEST_ASSERT_EQUAL_DOUBLE(  3.0, re );
    TEST_ASSERT_EQUAL_DOUBLE( -4.0, im );    
}

void
test_num_arg (void)
{
    num_t z = new(num, 0.0, 4.0);    
    const double ret = num_to_double(num_arg(z));
    delete(z);

    TEST_ASSERT_EQUAL_DOUBLE( 0.5*M_PI, ret );        
}


void
test_num_sqrt_real (void)
{
    num_t z = new(num, 4.0, 0.0);    
    const double ret = num_to_double(num_sqrt(z));
    delete(z);

    TEST_ASSERT_EQUAL_DOUBLE( 2.0, ret );        
}

void
test_num_sqrt_complex (void)
{
    num_t z = new(num, 3.0, 4.0);
    num_t sqrt_z = num_sqrt(z);
    const double re = num_to_double(num_real_part(sqrt_z));
    const double im = num_to_double(num_imag_part(sqrt_z));
    delete(z), delete(sqrt_z);

    TEST_ASSERT_EQUAL_DOUBLE( 2.0, re );
    TEST_ASSERT_EQUAL_DOUBLE( 1.0, im );       
}

void
test_num_exp_zero (void)
{
    num_t z = new(num, 0.0, 0.0);
    num_t exp_z = num_exp(z);
    const double re = num_to_double(num_real_part(exp_z));
    const double im = num_to_double(num_imag_part(exp_z));
    delete(z), delete(exp_z);

    TEST_ASSERT_EQUAL_DOUBLE( 1.0, re );
    TEST_ASSERT_EQUAL_DOUBLE( 0.0, im );       
}

void
test_num_exp_imag (void)
{
    TEST_IGNORE_MESSAGE ("Still lacking proper float comparison");
    num_t z = new(num, 0.0, 0.5 * M_PI);
    num_t exp_z = num_exp(z);
    const double re = num_to_double(num_real_part(exp_z));
    const double im = num_to_double(num_imag_part(exp_z));
    delete(z), delete(exp_z);

    TEST_ASSERT_EQUAL_DOUBLE( 0.0, re );
    TEST_ASSERT_EQUAL_DOUBLE( 1.0, im );       
}

/* log(3+4*I) = 1.60943791243410 + 0.927295218001612*I */
void
test_num_log (void)
{
    num_t z = new(num, 3.0, 4.0);
    num_t log_z = num_log(z);
    const double re = num_to_double(num_real_part(log_z));
    const double im = num_to_double(num_imag_part(log_z));
    delete(z), delete(log_z);

    TEST_ASSERT_EQUAL_DOUBLE( 1.60943791243410,  re );
    TEST_ASSERT_EQUAL_DOUBLE( 0.927295218001612, im );       
}

/* sin(3 + 4*I) = 3.85373803791938 - 27.0168132580039*I */
void
test_num_sin (void)
{
    num_t z = new(num, 3.0, 4.0);
    num_t sin_z = num_sin(z);
    const double re = num_to_double(num_real_part(sin_z));
    const double im = num_to_double(num_imag_part(sin_z));
    delete(z), delete(sin_z);

    TEST_ASSERT_EQUAL_DOUBLE(   3.85373803791938, re );
    TEST_ASSERT_EQUAL_DOUBLE( -27.0168132580039,  im );       
}

/* cos(3 + 2*I) = -3.72454550491532 - 0.511822569987385*I */
void
test_num_cos (void)
{
    num_t z = new(num, 3.0, 2.0);
    num_t cos_z = num_cos(z);
    const double re = num_to_double(num_real_part(cos_z));
    const double im = num_to_double(num_imag_part(cos_z));
    delete(z), delete(cos_z);

    TEST_ASSERT_EQUAL_DOUBLE( -3.72454550491532,  re );       
    TEST_ASSERT_EQUAL_DOUBLE( -0.511822569987385, im );
}

void
test_num_add (void)
{
    num_t x = new(num, 3.0, 2.0);
    num_t y = new(num, -3.1, 2.5);
    num_t z = num_add(x, y);
    const double re = num_to_double(num_real_part(z));
    const double im = num_to_double(num_imag_part(z));
    delete(x), delete(y), delete(z);

    TEST_ASSERT_EQUAL_DOUBLE( -0.1, re );       
    TEST_ASSERT_EQUAL_DOUBLE(  4.5, im );
}

void
test_num_sub (void)
{
    num_t x = new(num, 3.0, 2.0);
    num_t y = new(num, -3.1, 2.5);
    num_t z = num_sub(x, y);
    const double re = num_to_double(num_real_part(z));
    const double im = num_to_double(num_imag_part(z));
    delete(x), delete(y), delete(z);

    TEST_ASSERT_EQUAL_DOUBLE( 6.1, re );       
    TEST_ASSERT_EQUAL_DOUBLE( -0.5, im );
}

void
test_num_mul (void)
{
    num_t x = new(num, 3.0, 4.0);
    num_t y = new(num, 2.0, 1.0);
    num_t z = num_mul(x, y);
    const double re = num_to_double(num_real_part(z));
    const double im = num_to_double(num_imag_part(z));
    delete(x), delete(y), delete(z);

    TEST_ASSERT_EQUAL_DOUBLE( 2.0, re );       
    TEST_ASSERT_EQUAL_DOUBLE( 11.0, im );
}

void
test_num_div (void)
{
    num_t x = new(num, 3.0, 4.0);
    num_t y = new(num, 2.0, 1.0);
    num_t z = num_div(x, y);
    const double re = num_to_double(num_real_part(z));
    const double im = num_to_double(num_imag_part(z));
    delete(x), delete(y), delete(z);

    TEST_ASSERT_EQUAL_DOUBLE( 2.0, re );       
    TEST_ASSERT_EQUAL_DOUBLE( 1.0, im );
}

void
test_num_fmod (void)
{
    num_t x = new(num, 9.2, 0.0);
    num_t y = new(num, 2.0, 0.0);
    const double ret = num_to_double(num_fmod(x, y));
    delete(x), delete(y);

    TEST_ASSERT_EQUAL_DOUBLE( 1.2, ret );
}

void
test_num_pow (void)
{
    num_t x = new(num, 3.0, 4.0);
    num_t y = new(num, 2.0, 0.0);
    num_t z = num_pow(x, y);
    const double re = num_to_double(num_real_part(z));
    const double im = num_to_double(num_imag_part(z));
    delete(x), delete(y), delete(z);

    TEST_ASSERT_EQUAL_DOUBLE( -7.0, re );       
    TEST_ASSERT_EQUAL_DOUBLE( 24.0, im );
}

void
test_num_pow_cmplx (void)
{
    num_t x = new(num, 3.0, 4.0);
    num_t y = new(num, 0.0, 2.0);
    num_t z = num_pow(x, y);
    const double re = num_to_double(num_real_part(z));
    const double im = num_to_double(num_imag_part(z));
    delete(x), delete(y), delete(z);

    TEST_ASSERT_EQUAL_DOUBLE( -0.156049852140608, re );       
    TEST_ASSERT_EQUAL_DOUBLE( -0.0120840952149667, im );
}

void
test_num_eq (void)
{
    num_t x = new(num, 3.0, 4.0);
    num_t y = new(num, 3.0, 4.0); 
    const int ret = num_eq(x, y);
    delete(x), delete(y);
    
    TEST_ASSERT_MESSAGE( ret == 1 , "3+4i is not equal to itself (?)");
}

void
test_num_lt (void)
{
    num_t x = new(num, 2.0, 0.0);
    num_t y = new(num, 3.0, 0.0); 
    const int ret = num_lt(x, y);
    delete(x), delete(y);
    
    TEST_ASSERT_MESSAGE( ret == 1 , "2 >= 3 (?)");
}

void
test_num_gt (void)
{
    num_t x = new(num, 5.0, 0.0);
    num_t y = new(num, 3.0, 0.0); 
    const int ret = num_gt(x, y);
    delete(x), delete(y);
    
    TEST_ASSERT_MESSAGE( ret == 1 , "5 <= 3 (?)");
}

int
main (void)
{
    UNITY_BEGIN();

    RUN_TEST(test_allocate_num);

    //RUN_TEST(test_is_zero);
    //RUN_TEST(test_is_not_zero);
    //RUN_TEST(test_is_not_zero_I);
    //
    //RUN_TEST(test_is_real);
    //RUN_TEST(test_is_not_real);
    //RUN_TEST(test_is_not_real_I);
    //
    //RUN_TEST(test_num_to_double);
    //RUN_TEST(test_num_to_double_fail);

    //RUN_TEST(test_num_to_pair);

    //RUN_TEST(test_num_abs2);
    //RUN_TEST(test_num_abs_real);
    //RUN_TEST(test_num_abs_complex);

    //RUN_TEST(test_num_negative);

    //RUN_TEST(test_num_conjugate);

    //RUN_TEST(test_num_arg);

    //RUN_TEST(test_num_sqrt_real);
    //RUN_TEST(test_num_sqrt_complex);

    //RUN_TEST(test_num_exp_zero);
    //RUN_TEST(test_num_exp_imag);

    //RUN_TEST(test_num_log);

    //RUN_TEST(test_num_sin);
    //RUN_TEST(test_num_cos);

    //RUN_TEST(test_num_add);
    //RUN_TEST(test_num_sub);
    //RUN_TEST(test_num_mul);
    //RUN_TEST(test_num_div);
    //RUN_TEST(test_num_fmod);
    //RUN_TEST(test_num_pow);
    //RUN_TEST(test_num_pow_cmplx);
    //        
    //RUN_TEST(test_num_eq);
    //RUN_TEST(test_num_lt);
    //RUN_TEST(test_num_gt);


    
    /* RUN_TEST(); */
    
    return UNITY_END();
}
