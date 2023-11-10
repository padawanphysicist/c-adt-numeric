#include "unity.h"
#include "num.h"
#include "new.h"

#include <stdbool.h>

#ifndef M_PI
#define M_PI 3.14159265358979323844
#endif

/* delta value for float comparison */
#define DELTA 1e-15

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
    num_t z;
    bool res;

    z = new(num);
    num_zero(z);
    res = num_is_zero(z);
    delete(z);
    
    TEST_ASSERT_MESSAGE(res, "zero isn't 0, end of the world!");
}

void
test_is_not_zero (void)
{
    num_t z;
    bool res;

    z = new(num);
    num_one(z);
    res = !num_is_zero(z);
    delete(z);
    
    TEST_ASSERT_MESSAGE(res , "one equals zero, end of the world!");
}

void
test_is_real (void)
{
    num_t z;
    bool res;
    
    z = new(num);
    num_set_d(z, 3.0);
    res = num_is_real(z);
    delete(z);
    
    TEST_ASSERT_MESSAGE(res, "3 has an imaginary part (?)");
}

void
test_is_not_real (void)
{
    num_t z;
    bool res;

    z = new(num);
    num_set_d_d(z, 3.0, 4.0);
    res = !num_is_real(z);
    delete(z);
    
    TEST_ASSERT_MESSAGE(res, "3+4i is real (?)");
}

void
test_is_not_real_I (void)
{
    num_t z;
    bool res;

    z = new(num);
    num_onei(z);
    res = !num_is_real(z);
    delete(z);
    
    TEST_ASSERT_MESSAGE(res, "I is real(?)");
}

void
test_num_to_d (void)
{
    num_t z;
    double res;

    z = new(num);
    num_set_d(z, 5.4);
    res = num_to_d(z);
    delete(z);

    TEST_ASSERT_EQUAL_DOUBLE(5.4, res);
}

void
test_num_abs_real (void)
{
    num_t z;
    double res;

    z = new(num);
    num_set_d(z, -3.0);
    num_abs(z, z);    
    res = num_to_d(z);
    delete(z);

    TEST_ASSERT_EQUAL_DOUBLE(3.0, res);
}

void
test_num_abs_complex (void)
{
    num_t z;
    double res;

    z = new(num);
    num_set_d_d(z, 3.0, 4.0);
    num_abs(z, z);
    res = num_to_d(z);
    delete(z);

    TEST_ASSERT_EQUAL_DOUBLE(5.0, res);
}

void
test_num_neg (void)
{
    num_t z;
    double res;

    z = new(num);
    num_set_d(z, 4.0);
    num_neg(z, z);
    res = num_to_d(z);
    delete(z);

    TEST_ASSERT_EQUAL_DOUBLE(-4.0, res);
}

void
test_num_conjugate (void)
{
    num_t z;
    double complex res;

    z = new(num);
    num_set_d_d(z, 3.0, 4.0);
    num_conj(z, z);
    res = num_to_complex(z);
    delete(z);

    TEST_ASSERT_EQUAL_DOUBLE(3.0, creal(res));
    TEST_ASSERT_EQUAL_DOUBLE(-4.0, cimag(res));
}

void
test_num_arg (void)
{
    num_t z;
    double res;

    z = new(num);
    num_set_d_d(z, 0.0, 4.0);
    num_arg(z, z);
    res = num_to_d(z);
    delete(z);

    TEST_ASSERT_EQUAL_DOUBLE(0.5 * M_PI, res);
}

void
test_num_sqrt_real (void)
{
    num_t z;
    double res;

    z = new(num);
    num_set_d(z, 4.0);
    num_sqrt(z, z);
    res = num_to_d(z);
    delete(z);

    TEST_ASSERT_EQUAL_DOUBLE(2.0, res);
}

void
test_num_sqrt_complex (void)
{
    num_t z;
    double complex res;

    z = new(num);
    num_set_d_d(z, 3.0, 4.0);
    num_sqrt(z, z);
    res = num_to_complex(z);
    delete(z);

    TEST_ASSERT_EQUAL_DOUBLE(2.0, creal(res));
    TEST_ASSERT_EQUAL_DOUBLE(1.0, cimag(res));
}

void
test_num_exp_zero (void)
{
    num_t z;
    double complex res;

    z = new(num);
    num_exp(z, z);
    res = num_to_complex(z);
    delete(z);

    TEST_ASSERT_EQUAL_DOUBLE(1.0, creal(res));
    TEST_ASSERT_EQUAL_DOUBLE(0.0, cimag(res));
}

void
test_num_exp_imag (void)
{
    //TEST_IGNORE_MESSAGE ("Still lacking proper float comparison");
    num_t z;
    double complex res;

    z = new(num);
    num_set_d_d(z, 0.0, 0.5 * M_PI);
    num_exp(z, z);
    res = num_to_complex(z);
    delete(z);


    TEST_ASSERT_DOUBLE_WITHIN (DELTA, 0.0, creal(res));
    TEST_ASSERT_DOUBLE_WITHIN (DELTA, 1.0, cimag(res));
}

/* log(3+4*I) = 1.60943791243410 + 0.927295218001612*I */
void
test_num_log (void)
{
    num_t z;
    double complex res;

    z = new(num);
    num_set_d_d(z, 3.0, 4.0);
    num_log(z, z);
    res = num_to_complex(z);
    delete(z);

    TEST_ASSERT_EQUAL_DOUBLE(1.60943791243410,  creal(res));
    TEST_ASSERT_EQUAL_DOUBLE(0.927295218001612, cimag(res));
}

/* sin(3 + 4*I) = 3.85373803791938 - 27.0168132580039*I */
void
test_num_sin (void)
{
    num_t z;
    double complex res;

    z = new(num);
    num_set_d_d(z, 3.0, 4.0);
    num_sin(z, z);
    res = num_to_complex(z);
    delete(z);

    TEST_ASSERT_EQUAL_DOUBLE(3.85373803791938, creal(res));
    TEST_ASSERT_EQUAL_DOUBLE(-27.0168132580039, cimag(res));
}

/* cos(3 + 2*I) = -3.72454550491532 - 0.511822569987385*I */
void
test_num_cos (void)
{
    num_t z;
    double complex res;

    z = new(num);
    num_set_d_d(z, 3.0, 2.0);
    num_cos(z, z);
    res = num_to_complex(z);
    delete(z);

    TEST_ASSERT_EQUAL_DOUBLE(-3.72454550491532,  creal(res));
    TEST_ASSERT_EQUAL_DOUBLE(-0.511822569987385, cimag(res));
}

void
test_num_add (void)
{
    num_t x, y;
    double complex res;

    x = new(num), y = new(num);
    num_set_d_d(x, 3.0, 2.0);
    num_set_d_d(y, -3.1, 2.5);
    num_add(x, x, y);
    res = num_to_complex(x);
    delete(x), delete(y);

    TEST_ASSERT_EQUAL_DOUBLE(-0.1, creal(res));
    TEST_ASSERT_EQUAL_DOUBLE(4.5, cimag(res));
}

void
test_num_sub (void)
{
    num_t x, y;
    double complex res;
    
    x = new(num), y = new(num);
    num_set_d_d(x, 3.0, 2.0);
    num_set_d_d(y, -3.1, 2.5);
    num_sub(x, x, y);
    res = num_to_complex(x);
    delete(x), delete(y);

    TEST_ASSERT_EQUAL_DOUBLE(6.1, creal(res));
    TEST_ASSERT_EQUAL_DOUBLE(-0.5, cimag(res));
}

void
test_num_mul (void)
{
    num_t x, y;
    double complex res;

    x = new(num), y = new(num);
    num_set_d_d(x, 3.0, 4.0);
    num_set_d_d(y, 2.0, 1.0);
    num_mul(x, x, y);
    res = num_to_complex(x);
    delete(x), delete(y);

    TEST_ASSERT_EQUAL_DOUBLE(2.0, creal(res));
    TEST_ASSERT_EQUAL_DOUBLE(11.0, cimag(res));
}

void
test_num_div (void)
{
    num_t x, y;
    double complex res;

    x = new(num), y = new(num);
    num_set_d_d(x, 3.0, 4.0);
    num_set_d_d(y, 2.0, 1.0);
    num_div(x, x, y);
    res = num_to_complex(x);
    delete(x), delete(y);

    TEST_ASSERT_EQUAL_DOUBLE(2.0, creal(res));
    TEST_ASSERT_EQUAL_DOUBLE(1.0, cimag(res));
}

void
test_num_fmod (void)
{
    num_t x, y;
    double res;

    x = new(num), y = new(num);
    num_set_d(x, 9.2);
    num_set_d(y, 2.0);
    num_fmod(x, x, y);
    res = num_to_d(x);
    delete(x), delete(y);

    TEST_ASSERT_EQUAL_DOUBLE(1.2, res);
}

void
test_num_pow (void)
{
    num_t x, y;
    double complex res;

    x = new(num), y = new(num);
    num_set_d_d(x, 3.0, 4.0);
    num_set_d_d(y, 2.0, 0.0);
    num_pow(x, x, y);
    res = num_to_complex(x);
    delete(x), delete(y);

    TEST_ASSERT_EQUAL_DOUBLE(-7.0, creal(res));
    TEST_ASSERT_EQUAL_DOUBLE(24.0, cimag(res));
}

void
test_num_pow_cmplx (void)
{
    num_t x, y;
    double complex res;

    x = new(num), y = new(num);
    num_set_d_d(x, 3.0, 4.0);
    num_set_d_d(y, 0.0, 2.0);
    num_pow(x, x, y);
    res  = num_to_complex(x);
    delete(x), delete(y);

    TEST_ASSERT_EQUAL_DOUBLE(-0.156049852140608, creal(res));
    TEST_ASSERT_EQUAL_DOUBLE(-0.0120840952149667, cimag(res));
}

void
test_num_eq (void)
{
    num_t x, y;
    bool res;

    x = new(num), y = new(num);
    num_set_d_d(x, 3.0, 4.0);
    num_set_d_d(y, 3.0, 4.0);
    res = num_eq(x, y);
    delete(x), delete(y);
    
    TEST_ASSERT_MESSAGE(res, "3+4i is not equal to itself (?)");
}

void
test_num_lt (void)
{
    num_t x, y;
    bool res;

    x = new(num), y = new(num);
    num_set_d_d(x, 2.0, 0.0);
    num_set_d_d(y, 3.0, 0.0);
    res = num_lt(x, y);
    delete(x), delete(y);
    
    TEST_ASSERT_MESSAGE(res, "2 >= 3 (?)");
}

void
test_num_gt (void)
{
    num_t x, y;
    bool res;

    x = new(num), y = new(num);
    num_set_d_d(x, 5.0, 0.0);
    num_set_d_d(y, 3.0, 0.0);
    res = num_gt(x, y);
    delete(x), delete(y);
    
    TEST_ASSERT_MESSAGE(res, "5 <= 3 (?)");
}

void
test_num_erf (void)
{
    num_t x;
    double complex res;

    x = new(num);
    num_set_d_d(x, 3.0, 4.0);
    num_erf(x, x);
    res = num_to_complex(x);
    delete(x);

    TEST_ASSERT_EQUAL_DOUBLE(-120.186991395079, creal(res));
    TEST_ASSERT_EQUAL_DOUBLE(-27.7503372936239, cimag(res));
}

void
test_num_erfc (void)
{
    num_t x;
    double complex res;

    x = new(num);
    num_set_d_d(x, 3.0, 4.0);
    num_erfc(x, x);
    res = num_to_complex(x);
    delete(x);

    TEST_ASSERT_EQUAL_DOUBLE(121.186991395079, creal(res));
    TEST_ASSERT_EQUAL_DOUBLE(27.7503372936239, cimag(res));
}

void
test_num_rgamma (void)
{
    num_t x;
    double complex res;

    x = new(num);
    num_set_d_d(x, 3.0, 4.0);
    num_rgamma(x, x);
    res = num_to_complex(x);
    delete(x);

    TEST_ASSERT_EQUAL_DOUBLE(0.175354812000324, creal(res));
    TEST_ASSERT_EQUAL_DOUBLE(5.79020914622202, cimag(res));
}

void
test_num_ceil (void)
{
    num_t x;
    double res;

    x = new(num);
    num_set_d(x, 2.4);
    num_ceil(x, x);
    res = num_to_d(x);
    delete(x);
    
    TEST_ASSERT_EQUAL_DOUBLE(3.0, res);
}

void
test_num_inv (void)
{
    num_t x;
    double res;

    x = new(num);
    num_set_d(x, 2.0);
    num_inv(x, x);
    res = num_to_d(x);
    delete(x);
    
    TEST_ASSERT_EQUAL_DOUBLE(0.5, res);
}

void
test_num_cpy (void)
{
    num_t x, y;
    double complex res;

    x = new(num), y = new(num);
    num_set_d_d(x, 2.0, -1.0);
    num_set(y, x);
    res = num_to_complex(y);
    delete(x), delete(y);
    
    TEST_ASSERT_EQUAL_DOUBLE(2.0, creal(res));
    TEST_ASSERT_EQUAL_DOUBLE(-1.0, cimag(res));
}

void
test_num_max (void)
{
    num_t x, y, z;
    double res;

    x = new(num), y = new(num), z = new(num);
    num_set_d(x, 0.0);
    num_set_d(y, -1.0);
    num_set_d(z, 10.0);
    num_max3(x, x, y, z);
    res = num_to_d(x);
    delete(x), delete(y), delete(z);
    
    TEST_ASSERT_EQUAL_DOUBLE(10.0, res);
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

    RUN_TEST(test_num_cpy);
    RUN_TEST(test_num_max);

    return UNITY_END();
}
