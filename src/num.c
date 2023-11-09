/*
 * This file is part of num.c (https://github.com/padawanphysicist/num.c).
 *
 * num.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option) any
 * later version.
 *
 * num.c is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * num.c. If not, see <https://www.gnu.org/licenses/>.
 */

/** 
 * @file num.c
 * @brief Implementation of the Abstract Data Type (ADT).
 */
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <complex.h>
#include <stdarg.h>

#include "abc.h"
#include "new.h"
#include "num.h"
#include "log.h"

#include <arb.h>
#include <acb.h>
#include <acb_hypgeom.h>

#define PREC 53

struct num {
    const void * class; /* must be first */
    acb_t z;
};

static void *
num_ctor (void * _self, va_list * app)
{
    struct num * self = _self;

    acb_init(self -> z);
	
    const double re = va_arg(* app, const double);
    const double im = va_arg(* app, const double);
    acb_set_d_d(self -> z, re, im);

    log_trace("Allocate = %s, %p[%li]", __func__, self -> z, size_of(self));

	return self;
}

static void *
num_dtor (void * self)
{
    struct num * _self = self;

    log_trace("Free = %s, %p[%li]", __func__, _self -> z, size_of(_self));
    acb_clear(_self -> z);
	return self;
}

static const struct ABC _num = {
	sizeof(struct num),
	num_ctor, num_dtor//,	num_clone
};

const void * num = & _num;

// Converts an arb_t number to double.
static double
arbtod (const arb_t x)
{
    return arf_get_d(arb_midref(x), ARF_RND_NEAR);
}

/****************************/
/* User interface functions */
/****************************/

/* Basic manipulation */
num_t
num_from_d (const double x)
{
    return new(num, x, 0.0);
}

num_t
num_from_d_d (const double re, const double im)
{
    return new(num, re, im);
}

num_t
num_from_arb (const arb_t x)
{
    return new(num, arbtod(x), 0.0);
}

num_t
num_from_acb (const acb_t z)
{
    arb_t _re, _im;

    arb_init(_re), arb_init(_im);
    acb_get_real(_re, z);
    acb_get_imag(_im, z);
    const double re = arbtod(_re);
    const double im = arbtod(_im);
    arb_clear(_re), arb_clear(_im);
    
    return num_from_d_d(re, im);
}

/* Input and Output */
void
num_print (const num_t self, const bool endline)
{
    const struct num * _self = self;
    const slong digits = 8;
    const ulong flags = 0;

    acb_printn(_self -> z, digits, flags);
    if (endline) puts("\n");
}

/* Accessors: Real and Imaginary parts */
num_t
num_real (const num_t self)
{
    const struct num * _self = self;
    
    double re;
    arb_t _re;
    arb_init(_re);
    acb_get_real(_re, _self -> z);
    re = arbtod(_re);
    arb_clear(_re);
    
	return num_from_d(re);
}

num_t
num_imag (const num_t self)
{
    const struct num * _self = self;

    double im;
    arb_t _im;
    arb_init(_im);
    acb_get_imag(_im, _self -> z);
    im = arbtod(_im);
    arb_clear(_im);
    
	return num_from_d(im);
}

/* Predicates */
bool
num_is_zero (const num_t self)
{
    const struct num * _self = self;

    const int res = acb_is_zero(_self -> z);

    return (res != 0) ? true : false;
}

bool
num_is_real (const num_t self)
{
    const struct num * _self = self;

    const int res = acb_is_real(_self -> z);

    return (res != 0) ? true : false;
}

/* /\* Type casting *\/ */

double
num_to_d (const num_t self)
{
    assert(num_is_real(self));

    arb_t x;
    const struct num * _self = self;

    arb_init(x);
    acb_get_real(x, _self -> z);

    return arbtod(x);
}

/* void */
/* num_to_pair (double* res, const num_t _self) */
/* { */
/*     const struct num* self = _self; */

/*     for (int i = 0; i < NCOMP; i++) */
/*         res[i] = self->dat[i]; */
/* } */

double complex
num_to_complex (const num_t self)
{
    const struct num * _self = self;
    const double re = arbtod(acb_realref(_self -> z));
    const double im = arbtod(acb_imagref(_self -> z));

    return re + im*I;
}

num_t
num_abs (const num_t self)
{
    const struct num * _self = self;

    arb_t res;
    arb_init(res);
    acb_abs(res, _self -> z, PREC);

    return num_from_arb(res);
}

num_t
num_neg (const num_t self)
{
    const struct num * _self = self;

    acb_t res;
    acb_init(res);
    acb_neg(res, _self -> z);

    return num_from_acb(res);
}

num_t
num_inv (const num_t self)
{
    const struct num * _self = self;

    acb_t res;
    acb_init(res);
    acb_inv(res, _self -> z, PREC);

    return num_from_acb(res);
}

num_t
num_conj (const num_t self)
{
    const struct num * _self = self;

    acb_t res;
    acb_init(res);
    acb_conj(res, _self -> z);

    return num_from_acb(res);
}

num_t
num_ceil (const num_t self)
{
    assert(num_is_real(self));

    const double x = num_to_d(self);

    return num_from_d(ceil(x));
}

num_t
num_arg (const num_t self)
{
    const struct num * _self = self;

    arb_t _arg_z;
    arb_init(_arg_z);
    acb_arg(_arg_z, _self -> z, PREC);
    const double arg_z = arbtod(_arg_z);
    arb_clear(_arg_z);

    return num_from_d(arg_z);
}

num_t
num_sqrt (const num_t self)
{
    const struct num * _self = self;

    arb_t _sqrt_z_re, _sqrt_z_im;
    acb_t _sqrt_z;
    acb_init(_sqrt_z);
    arb_init(_sqrt_z_re); arb_init(_sqrt_z_im);
    acb_sqrt(_sqrt_z, _self -> z, PREC);
    acb_get_real(_sqrt_z_re, _sqrt_z);
    acb_get_imag(_sqrt_z_im, _sqrt_z);
    const double sqrt_z_re = arbtod(_sqrt_z_re);
    const double sqrt_z_im = arbtod(_sqrt_z_im);
    acb_clear(_sqrt_z);
    arb_clear(_sqrt_z_re); arb_clear(_sqrt_z_im);

    return num_from_d_d(sqrt_z_re, sqrt_z_im);
}

num_t
num_exp (const num_t self)
{
    const struct num * _self = self;

    arb_t _exp_z_re, _exp_z_im;
    acb_t _exp_z;
    acb_init(_exp_z);
    arb_init(_exp_z_re); arb_init(_exp_z_im);
    acb_exp(_exp_z, _self -> z, PREC);
    acb_get_real(_exp_z_re, _exp_z);
    acb_get_imag(_exp_z_im, _exp_z);
    const double exp_z_re = arbtod(_exp_z_re);
    const double exp_z_im = arbtod(_exp_z_im);
    acb_clear(_exp_z);
    arb_clear(_exp_z_re); arb_clear(_exp_z_im);

    return num_from_d_d(exp_z_re, exp_z_im);
}

num_t
num_log (const num_t self)
{
    const struct num * _self = self;

    arb_t _log_z_re, _log_z_im;
    acb_t _log_z;
    acb_init(_log_z);
    arb_init(_log_z_re); arb_init(_log_z_im);
    acb_log(_log_z, _self -> z, PREC);
    acb_get_real(_log_z_re, _log_z);
    acb_get_imag(_log_z_im, _log_z);
    const double log_z_re = arbtod(_log_z_re);
    const double log_z_im = arbtod(_log_z_im);
    acb_clear(_log_z);
    arb_clear(_log_z_re); arb_clear(_log_z_im);

    return num_from_d_d(log_z_re, log_z_im);
}

num_t
num_sin (const num_t self)
{
    const struct num * _self = self;

    double sin_z_re, sin_z_im;

    arb_t _sin_z_re, _sin_z_im;
    acb_t _sin_z;
    acb_init(_sin_z);
    arb_init(_sin_z_re); arb_init(_sin_z_im);
    acb_sin(_sin_z, _self -> z, PREC);
    acb_get_real(_sin_z_re, _sin_z);
    acb_get_imag(_sin_z_im, _sin_z);
    sin_z_re = arbtod(_sin_z_re);
    sin_z_im = arbtod(_sin_z_im);
    acb_clear(_sin_z);
    arb_clear(_sin_z_re); arb_clear(_sin_z_im);

    return num_from_d_d(sin_z_re, sin_z_im);
}

num_t
num_cos (const num_t self)
{
    const struct num * _self = self;

    double cos_z_re, cos_z_im;

    arb_t _cos_z_re, _cos_z_im;
    acb_t _cos_z;
    acb_init(_cos_z);
    arb_init(_cos_z_re); arb_init(_cos_z_im);
    acb_cos(_cos_z, _self -> z, PREC);
    acb_get_real(_cos_z_re, _cos_z);
    acb_get_imag(_cos_z_im, _cos_z);
    cos_z_re = arbtod(_cos_z_re);
    cos_z_im = arbtod(_cos_z_im);
    acb_clear(_cos_z);
    arb_clear(_cos_z_re); arb_clear(_cos_z_im);

    return num_from_d_d(cos_z_re, cos_z_im);
}

/* Binary operations */

/* Arithmetic */

num_t
num_add (const num_t self, const num_t other)
{
    const struct num * _self = self;
    const struct num * _other = other;

    double add_z_re, add_z_im;

    arb_t _add_z_re, _add_z_im;
    acb_t _add_z;
    acb_init(_add_z);
    arb_init(_add_z_re); arb_init(_add_z_im);
    acb_add(_add_z, _self -> z, _other -> z, PREC);
    acb_get_real(_add_z_re, _add_z);
    acb_get_imag(_add_z_im, _add_z);
    add_z_re = arbtod(_add_z_re);
    add_z_im = arbtod(_add_z_im);
    acb_clear(_add_z);
    arb_clear(_add_z_re), arb_clear(_add_z_im);

    return num_from_d_d(add_z_re, add_z_im);
}

num_t
num_sub (const num_t self, const num_t other)
{
    const struct num * _self = self;
    const struct num * _other = other;

    double sub_z_re, sub_z_im;

    arb_t _sub_z_re, _sub_z_im;
    acb_t _sub_z;
    acb_init(_sub_z);
    arb_init(_sub_z_re); arb_init(_sub_z_im);
    acb_sub(_sub_z, _self -> z, _other -> z, PREC);
    acb_get_real(_sub_z_re, _sub_z);
    acb_get_imag(_sub_z_im, _sub_z);
    sub_z_re = arbtod(_sub_z_re);
    sub_z_im = arbtod(_sub_z_im);
    acb_clear(_sub_z);
    arb_clear(_sub_z_re), arb_clear(_sub_z_im);

    return num_from_d_d(sub_z_re, sub_z_im);
}

num_t
num_mul (const num_t self, const num_t other)
{
    const struct num * _self = self;
    const struct num * _other = other;

    double mul_z_re, mul_z_im;

    arb_t _mul_z_re, _mul_z_im;
    acb_t _mul_z;
    acb_init(_mul_z);
    arb_init(_mul_z_re); arb_init(_mul_z_im);
    acb_mul(_mul_z, _self -> z, _other -> z, PREC);
    acb_get_real(_mul_z_re, _mul_z);
    acb_get_imag(_mul_z_im, _mul_z);
    mul_z_re = arbtod(_mul_z_re);
    mul_z_im = arbtod(_mul_z_im);
    acb_clear(_mul_z);
    arb_clear(_mul_z_re), arb_clear(_mul_z_im);

    return num_from_d_d(mul_z_re, mul_z_im);
}

num_t
num_div (const num_t self, const num_t other)
{
    const struct num * _self = self;
    const struct num * _other = other;

    double div_z_re, div_z_im;

    arb_t _div_z_re, _div_z_im;
    acb_t _div_z;
    acb_init(_div_z);
    arb_init(_div_z_re); arb_init(_div_z_im);
    acb_div(_div_z, _self -> z, _other -> z, PREC);
    acb_get_real(_div_z_re, _div_z);
    acb_get_imag(_div_z_im, _div_z);
    div_z_re = arbtod(_div_z_re);
    div_z_im = arbtod(_div_z_im);
    acb_clear(_div_z);
    arb_clear(_div_z_re), arb_clear(_div_z_im);

    return num_from_d_d(div_z_re, div_z_im);
}

num_t
num_fmod (const num_t self, const num_t other)
{
    assert(num_is_real(self) && num_is_real(other));

    const double _self = num_to_d(self);
    const double _other = num_to_d(other);
    
    return num_from_d(fmod(_self, _other));
}

num_t
num_pow (const num_t self, const num_t other)
{
    const struct num * _self = self;
    const struct num * _other = other;

    double pow_z_re, pow_z_im;

    arb_t _pow_z_re, _pow_z_im;
    acb_t _pow_z;
    acb_init(_pow_z);
    arb_init(_pow_z_re); arb_init(_pow_z_im);
    acb_pow(_pow_z, _self -> z, _other -> z, PREC);
    acb_get_real(_pow_z_re, _pow_z);
    acb_get_imag(_pow_z_im, _pow_z);
    pow_z_re = arbtod(_pow_z_re);
    pow_z_im = arbtod(_pow_z_im);
    acb_clear(_pow_z);
    arb_clear(_pow_z_re), arb_clear(_pow_z_im);

    return num_from_d_d(pow_z_re, pow_z_im);
}

/* Logical */

bool
num_eq (const num_t self, const num_t other)
{
    int re_eq, im_eq;
    
    const struct num * _self = self;
    const struct num * _other = other;

    arb_t _self_re, _self_im;
    arb_t _other_re, _other_im;
    arb_init(_self_re), arb_init(_self_im);
    arb_init(_other_re), arb_init(_other_im);
    acb_get_real(_self_re, _self -> z);
    acb_get_real(_other_re, _other -> z);
    acb_get_imag(_self_im, _self -> z);
    acb_get_imag(_other_im, _other -> z);
    re_eq = arb_eq(_self_re, _other_re);
    im_eq = arb_eq(_self_im, _other_im);
    arb_clear(_self_re), arb_clear(_self_im);
    arb_clear(_other_re), arb_clear(_other_im);

    return (re_eq != 0 && im_eq != 0) ? true : false;
}

bool
num_lt (const num_t self, const num_t other)
{
    assert(num_is_real(self) && num_is_real(other));

    int is_lt;
    
    const struct num * _self = self;
    const struct num * _other = other;

    arb_t _self_re,_other_re;
    arb_init(_self_re), arb_init(_other_re);
    acb_get_real(_self_re, _self -> z);
    acb_get_real(_other_re, _other -> z);
    is_lt = arb_lt(_self_re, _other_re);
    arb_clear(_self_re), arb_clear(_other_re);

    return (is_lt != 0) ? true : false;
}

bool
num_gt (const num_t self, const num_t other)
{
    assert(num_is_real(self) && num_is_real(other));

    int is_gt;
    
    const struct num * _self = self;
    const struct num * _other = other;

    arb_t _self_re,_other_re;
    arb_init(_self_re), arb_init(_other_re);
    acb_get_real(_self_re, _self -> z);
    acb_get_real(_other_re, _other -> z);
    is_gt = arb_gt(_self_re, _other_re);
    arb_clear(_self_re), arb_clear(_other_re);

    return (is_gt != 0) ? true : false;
}

bool
num_le (const num_t self, const num_t other)
{
    assert(num_is_real(self) && num_is_real(other));

    int is_le;
    
    const struct num * _self = self;
    const struct num * _other = other;

    arb_t _self_re,_other_re;
    arb_init(_self_re), arb_init(_other_re);
    acb_get_real(_self_re, _self -> z);
    acb_get_real(_other_re, _other -> z);
    is_le = arb_le(_self_re, _other_re);
    arb_clear(_self_re), arb_clear(_other_re);

    return (is_le != 0) ? true : false;
}

bool
num_ge (const num_t self, const num_t other)
{
    assert(num_is_real(self) && num_is_real(other));

    int is_ge;
    
    const struct num * _self = self;
    const struct num * _other = other;

    arb_t _self_re,_other_re;
    arb_init(_self_re), arb_init(_other_re);
    acb_get_real(_self_re, _self -> z);
    acb_get_real(_other_re, _other -> z);
    is_ge = arb_ge(_self_re, _other_re);
    arb_clear(_self_re), arb_clear(_other_re);

    return (is_ge != 0) ? true : false;
}

num_t
num_erf (const num_t self)
{
    const struct num * _self = self;

    double erf_z_re, erf_z_im;
    
    acb_t _erf_z;
    arb_t _erf_z_re, _erf_z_im;
    acb_init(_erf_z);
    arb_init(_erf_z_re); arb_init(_erf_z_im);
    acb_hypgeom_erf(_erf_z, _self -> z, PREC);
    acb_get_real(_erf_z_re, _erf_z);
    acb_get_imag(_erf_z_im, _erf_z);
    erf_z_re = arbtod(_erf_z_re);
    erf_z_im = arbtod(_erf_z_im);
    acb_clear(_erf_z);
    arb_clear(_erf_z_re); arb_clear(_erf_z_im);

    return num_from_d_d(erf_z_re, erf_z_im);
}

num_t
num_erfc (const num_t self)
{
    const struct num * _self = self;

    double erf_z_re, erf_z_im;
    
    acb_t _erf_z;
    arb_t _erf_z_re, _erf_z_im;
    acb_init(_erf_z);
    arb_init(_erf_z_re); arb_init(_erf_z_im);
    acb_hypgeom_erfc(_erf_z, _self -> z, PREC);
    acb_get_real(_erf_z_re, _erf_z);
    acb_get_imag(_erf_z_im, _erf_z);
    erf_z_re = arbtod(_erf_z_re);
    erf_z_im = arbtod(_erf_z_im);
    acb_clear(_erf_z);
    arb_clear(_erf_z_re); arb_clear(_erf_z_im);

    return num_from_d_d(erf_z_re, erf_z_im);
}

num_t
num_rgamma (const num_t self)
{
    const struct num * _self = self;

    acb_t _rgamma_z;
    arb_t _rgamma_z_re, _rgamma_z_im;
    arb_init(_rgamma_z_re); arb_init(_rgamma_z_im);
    acb_init(_rgamma_z);
    acb_hypgeom_rgamma(_rgamma_z, _self -> z, PREC);
    acb_get_real(_rgamma_z_re, _rgamma_z);
    acb_get_imag(_rgamma_z_im, _rgamma_z);
    const double rgamma_z_re = arbtod(_rgamma_z_re);
    const double rgamma_z_im = arbtod(_rgamma_z_im);
    acb_clear(_rgamma_z);
    arb_clear(_rgamma_z_re); arb_clear(_rgamma_z_im);

    return num_from_d_d(rgamma_z_re, rgamma_z_im);
}

void
num_cpy (num_t* self, const num_t other)
{
    struct num * _self = *self;
    const struct num * _other = other;
    acb_set(_self -> z, _other -> z);
}

num_t
num_max (int count, ...)
{
    va_list ap;
    va_start(ap, count); 

    double M = num_to_d(va_arg(ap, num_t));
    for (int j = 1; j < count; j++)
    {
        const double n = num_to_d(va_arg(ap, num_t));
	M = (n > M) ? n : M;
    }
    va_end(ap);

    return num_from_d(M);    
}
