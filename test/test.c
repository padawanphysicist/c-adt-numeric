#include "unity.h"
#include "num.h"
#include "new.h"

#include <stdbool.h>

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
test_is_zero (void)
{
    num_t z = num_from_d(0.0);
    const bool ret = num_is_zero(z);
    delete(z);
    
    TEST_ASSERT_MESSAGE(ret, "zero isn't 0, end of the world!");
}

void
test_is_not_zero (void)
{
    num_t z = num_from_d(1.0);
    const bool ret = !num_is_zero(z);
    delete(z);
    
    TEST_ASSERT_MESSAGE(ret , "one equals zero, end of the world!");
}

void
test_is_real (void)
{
    num_t z = num_from_d(3.0);
    const bool ret = num_is_real(z);
    delete(z);
    
    TEST_ASSERT_MESSAGE(ret, "3 has an imaginary part (?)");
}

void
test_is_not_real (void)
{
    num_t z = num_from_d_d(3.0, 4.0);
    const bool ret = !num_is_real(z);
    delete(z);
    
    TEST_ASSERT_MESSAGE(ret, "3+4i is real (?)");
}

void
test_is_not_real_I (void)
{
    num_t z = num_from_d_d(0.0, 1.0);
    const bool ret = !num_is_real(z);
    delete(z);
    
    TEST_ASSERT_MESSAGE(ret, "I is real(?)");
}

void
test_num_to_d (void)
{
    num_t z = num_from_d(5.4);
    const double ret = num_to_d(z);
    delete(z);

    TEST_ASSERT_EQUAL_DOUBLE(5.4, ret);
}

void
test_num_abs_real (void)
{
    num_t z = num_from_d(-3.0);
    num_t abs_z = num_abs(z);
    
    const double ret = num_to_d(abs_z);
    delete(z), delete(abs_z);

    TEST_ASSERT_EQUAL_DOUBLE(3.0, ret);
}

void
test_num_abs_complex (void)
{
    num_t z = num_from_d_d(3.0, 4.0);
    num_t abs_z = num_abs(z);
    const double ret = num_to_d(abs_z);
    delete(z), delete(abs_z);

    TEST_ASSERT_EQUAL_DOUBLE(5.0, ret);
}

void
test_num_neg (void)
{
    num_t z = num_from_d(4.0);
    num_t neg_z = num_neg(z);
    const double ret = num_to_d(neg_z);
    delete(z), delete(neg_z);

    TEST_ASSERT_EQUAL_DOUBLE(-4.0, ret);
}

void
test_num_conjugate (void)
{
    num_t z = num_from_d_d(3.0, 4.0);
    num_t conj_z = num_conj(z);
    const double complex ret = num_to_complex(conj_z);
    delete(z), delete(conj_z);

    TEST_ASSERT_EQUAL_DOUBLE(3.0, creal(ret));
    TEST_ASSERT_EQUAL_DOUBLE(-4.0, cimag(ret));
}

void
test_num_arg (void)
{
    num_t z = num_from_d_d(0.0, 4.0);
    num_t arg_z = num_arg(z);
    const double ret = num_to_d(arg_z);
    delete(z); delete(arg_z);

    TEST_ASSERT_EQUAL_DOUBLE(0.5 * M_PI, ret);
}

void
test_num_sqrt_real (void)
{
    num_t z = num_from_d(4.0);
    num_t sqrt_z = num_sqrt(z);
    const double ret = num_to_d(sqrt_z);
    delete(z), delete(sqrt_z);

    TEST_ASSERT_EQUAL_DOUBLE(2.0, ret);
}

void
test_num_sqrt_complex (void)
{
    num_t z = new(num, 3.0, 4.0);
    num_t sqrt_z = num_sqrt(z);
    const double complex ret = num_to_complex(sqrt_z);
    delete(z), delete(sqrt_z);

    TEST_ASSERT_EQUAL_DOUBLE(2.0, creal(ret));
    TEST_ASSERT_EQUAL_DOUBLE(1.0, cimag(ret));
}

void 
test_num_exp_zero (void)
{
    num_t z = num_from_d(0.0);
    num_t exp_z = num_exp(z);
    const double complex ret = num_to_complex(exp_z);
    delete(z), delete(exp_z);

    TEST_ASSERT_EQUAL_DOUBLE(1.0, creal(ret));
    TEST_ASSERT_EQUAL_DOUBLE(0.0, cimag(ret));
}

void
test_num_exp_imag (void)
{
    TEST_IGNORE_MESSAGE ("Still lacking proper float comparison");
    num_t z = num_from_d_d(0.0, 0.5 * M_PI);
    num_t exp_z = num_exp(z);
    const double complex ret = num_to_complex(exp_z);
    delete(z), delete(exp_z);

    TEST_ASSERT_EQUAL_DOUBLE(0.0, creal(ret));
    TEST_ASSERT_EQUAL_DOUBLE(1.0, cimag(ret));
}

/* log(3+4*I) = 1.60943791243410 + 0.927295218001612*I */
void
test_num_log (void)
{
    num_t z = num_from_d_d(3.0, 4.0);
    num_t log_z = num_log(z);
    const double complex ret = num_to_complex(log_z);
    delete(z), delete(log_z);

    TEST_ASSERT_EQUAL_DOUBLE(1.60943791243410,  creal(ret));
    TEST_ASSERT_EQUAL_DOUBLE(0.927295218001612, cimag(ret));
}

/* sin(3 + 4*I) = 3.85373803791938 - 27.0168132580039*I */
void
test_num_sin (void)
{
    num_t z = num_from_d_d(3.0, 4.0);
    num_t sin_z = num_sin(z);
    const double complex ret = num_to_complex(sin_z);
    delete(z), delete(sin_z);

    TEST_ASSERT_EQUAL_DOUBLE(3.85373803791938, creal(ret));
    TEST_ASSERT_EQUAL_DOUBLE(-27.0168132580039, cimag(ret));
}

/* cos(3 + 2*I) = -3.72454550491532 - 0.511822569987385*I */
void
test_num_cos (void)
{   
    num_t z = num_from_d_d(3.0, 2.0);
    num_t cos_z = num_cos(z);
    const double complex ret = num_to_complex(cos_z);
    delete(z), delete(cos_z);

    TEST_ASSERT_EQUAL_DOUBLE(-3.72454550491532,  creal(ret));
    TEST_ASSERT_EQUAL_DOUBLE(-0.511822569987385, cimag(ret));
}

void
test_num_add (void)
{
    num_t x = num_from_d_d(3.0, 2.0);
    num_t y = num_from_d_d(-3.1, 2.5);
    num_t z = num_add(x, y);
    const double complex ret = num_to_complex(z);
    delete(x), delete(y), delete(z);

    TEST_ASSERT_EQUAL_DOUBLE(-0.1, creal(ret));
    TEST_ASSERT_EQUAL_DOUBLE(4.5, cimag(ret));
}

void
test_num_sub (void)
{
    num_t x = num_from_d_d(3.0, 2.0);
    num_t y = num_from_d_d(-3.1, 2.5);
    num_t z = num_sub(x, y);
    const double complex ret = num_to_complex(z);
    delete(x), delete(y), delete(z);

    TEST_ASSERT_EQUAL_DOUBLE(6.1, creal(ret));
    TEST_ASSERT_EQUAL_DOUBLE(-0.5, cimag(ret));
}

void
test_num_mul (void)
{
    num_t x = num_from_d_d(3.0, 4.0);
    num_t y = num_from_d_d(2.0, 1.0);
    num_t z = num_mul(x, y);
    const double complex ret = num_to_complex(z);
    delete(x), delete(y), delete(z);

    TEST_ASSERT_EQUAL_DOUBLE(2.0, creal(ret));
    TEST_ASSERT_EQUAL_DOUBLE(11.0, cimag(ret));
}

void
test_num_div (void)
{
    num_t x = num_from_d_d(3.0, 4.0);
    num_t y = num_from_d_d(2.0, 1.0);
    num_t z = num_div(x, y);
    const double complex ret = num_to_complex(z);
    delete(x), delete(y), delete(z);

    TEST_ASSERT_EQUAL_DOUBLE(2.0, creal(ret));
    TEST_ASSERT_EQUAL_DOUBLE(1.0, cimag(ret));
}

void
test_num_fmod (void)
{
    num_t x = num_from_d(9.2);
    num_t y = num_from_d(2.0);
    num_t z = num_fmod(x, y);
    const double ret = num_to_d(z);
    delete(x), delete(y), delete(z);

    TEST_ASSERT_EQUAL_DOUBLE(1.2, ret);
}

void
test_num_pow (void)
{
    num_t x = num_from_d_d(3.0, 4.0);
    num_t y = num_from_d_d(2.0, 0.0);
    num_t z = num_pow(x, y);
    const double complex ret = num_to_complex(z);
    delete(x), delete(y), delete(z);

    TEST_ASSERT_EQUAL_DOUBLE(-7.0, creal(ret));
    TEST_ASSERT_EQUAL_DOUBLE(24.0, cimag(ret));
}

void
test_num_pow_cmplx (void)
{
    num_t x = num_from_d_d(3.0, 4.0);
    num_t y = num_from_d_d(0.0, 2.0);
    num_t z = num_pow(x, y);
    const double complex ret = num_to_complex(z);
    delete(x), delete(y), delete(z);

    TEST_ASSERT_EQUAL_DOUBLE(-0.156049852140608, creal(ret));
    TEST_ASSERT_EQUAL_DOUBLE(-0.0120840952149667, cimag(ret));
}

void
test_num_eq (void)
{
    num_t x = new(num, 3.0, 4.0);
    num_t y = new(num, 3.0, 4.0);
    const bool ret = num_eq(x, y);
    delete(x), delete(y);
    
    TEST_ASSERT_MESSAGE(ret , "3+4i is not equal to itself (?)");
}

void
test_num_lt (void)
{
    num_t x = num_from_d_d(2.0, 0.0);
    num_t y = num_from_d_d(3.0, 0.0);
    const bool ret = num_lt(x, y);
    delete(x), delete(y);
    
    TEST_ASSERT_MESSAGE(ret, "2 >= 3 (?)");
}

void
test_num_gt (void)
{
    num_t x = num_from_d_d(5.0, 0.0);
    num_t y = num_from_d_d(3.0, 0.0);
    const bool ret = num_gt(x, y);
    delete(x), delete(y);
    
    TEST_ASSERT_MESSAGE(ret, "5 <= 3 (?)");
}

void
test_num_erf (void)
{
    num_t z = num_from_d_d(3.0, 4.0);
    num_t erf_z = num_erf(z);
    const double complex ret = num_to_complex(erf_z);
    delete(z), delete(erf_z);

    TEST_ASSERT_EQUAL_DOUBLE(-120.186991395079, creal(ret));
    TEST_ASSERT_EQUAL_DOUBLE(-27.7503372936239, cimag(ret));
}

void
test_num_erfc (void)
{
    num_t z = num_from_d_d(3.0, 4.0);
    num_t erf_z = num_erfc(z);
    const double complex ret = num_to_complex(erf_z);
    delete(z), delete(erf_z);

    TEST_ASSERT_EQUAL_DOUBLE(121.186991395079, creal(ret));
    TEST_ASSERT_EQUAL_DOUBLE(27.7503372936239, cimag(ret));
}

void
test_num_rgamma (void)
{
    num_t z = num_from_d_d(3.0, 4.0);
    num_t rgamma_z = num_rgamma(z);
    const double complex ret = num_to_complex(rgamma_z);
    delete(z), delete(rgamma_z);

    TEST_ASSERT_EQUAL_DOUBLE(0.175354812000324, creal(ret));
    TEST_ASSERT_EQUAL_DOUBLE(5.79020914622202, cimag(ret));
}

void
test_num_ceil (void)
{
    num_t z = num_from_d(2.4);
    num_t ceil_z = num_ceil(z);
    const double ret = num_to_d(ceil_z);
    delete(z), delete(ceil_z);
    
    TEST_ASSERT_EQUAL_DOUBLE(3.0, ret);
}

void
test_num_inv (void)
{
    num_t z = num_from_d(2);
    num_t inv_z = num_inv(z);
    const double ret = num_to_d(inv_z);
    delete(z), delete(inv_z);
    
    TEST_ASSERT_EQUAL_DOUBLE(0.5, ret);
}

int
main (void)
{
    UNITY_BEGIN();

    RUN_TEST(test_is_zero);
    RUN_TEST(test_is_not_zero);

    RUN_TEST(test_is_real);
    RUN_TEST(test_is_not_real);
    RUN_TEST(test_is_not_real_I);
    
    RUN_TEST(test_num_to_d);

    RUN_TEST(test_num_abs_real);
    RUN_TEST(test_num_abs_complex);

    RUN_TEST(test_num_neg);

    RUN_TEST(test_num_conjugate);

    RUN_TEST(test_num_arg);

    RUN_TEST(test_num_sqrt_real);
    RUN_TEST(test_num_sqrt_complex);

    RUN_TEST(test_num_exp_zero);
    RUN_TEST(test_num_exp_imag);

    RUN_TEST(test_num_log);

    RUN_TEST(test_num_sin);
    RUN_TEST(test_num_cos);

    RUN_TEST(test_num_add);
    RUN_TEST(test_num_sub);
    RUN_TEST(test_num_mul);
    RUN_TEST(test_num_div);
    RUN_TEST(test_num_fmod);
    RUN_TEST(test_num_pow);
    RUN_TEST(test_num_pow_cmplx);
    RUN_TEST(test_num_eq);
    RUN_TEST(test_num_lt);
    RUN_TEST(test_num_gt);

    RUN_TEST(test_num_erf);
    RUN_TEST(test_num_erfc);
    RUN_TEST(test_num_rgamma);

    RUN_TEST(test_num_ceil);
    RUN_TEST(test_num_inv);

    return UNITY_END();
}
