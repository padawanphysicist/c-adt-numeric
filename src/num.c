/*
 * This file is part of c-adt-numeric (https://github.com/padawanphysicist/c-adt-numeric).
 *
 * c-adt-numeric is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option) any
 * later version.
 *
 * c-adt-numeric is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * c-adt-numeric. If not, see <https://www.gnu.org/licenses/>.
 */

/** 
 * @file num.c
 * @brief Implementation of the Abstract Data Type (ADT).
 */
#include <assert.h>
#include <math.h>
#include <stdlib.h>

#include "abc.h"
#include "new.h"
#include "num.h"
#include "log.h"

#ifndef _TOLERANCE
#define _TOLERANCE 1.0e-8
#endif

#define NCOMP 2

struct num {
	const void* class;	/* must be first */
	double* dat;        /* data */
};

static void*
num_ctor (void* _self, va_list* app)
{
    struct num* self = _self;
	
	self->dat = malloc(NCOMP*sizeof(double));
	assert(self->dat);

    for (int i = 0; i < NCOMP; i++)
    {
        const double res = va_arg(* app, const double);
        self->dat[i] = res;
    }

	return self;
}

static void*
num_dtor (void* _self)
{
    struct num* self = _self;

	free(self->dat), self->dat = NULL;
	return self;
}

static void*
num_clone (const void* _self)
{
    const struct num* self = _self;
	return new(num, self->dat);
}

static const struct ABC _num = {
	sizeof(struct num),
	num_ctor, num_dtor,	num_clone
};

const void * num = & _num;

/****************************/
/* User interface functions */
/****************************/

/* Accessors: Real and Imaginary parts */
num_t
num_real_part (const num_t _self)
{
    const struct num* self = _self;
    
	return new(num, self->dat[0], 0.0);
}

num_t
num_imag_part (const num_t _self)
{
    const struct num* self = _self;
    
	return new(num, self->dat[1], 0.0);
}

/* Predicates */
int
num_is_zero (const num_t _self)
{
    const struct num* self = _self;

    return ((fabs(self->dat[0]) < _TOLERANCE) && (fabs(self->dat[1]) < _TOLERANCE));
}

int
num_is_real (const num_t _self)
{
    num_t im = num_imag_part(_self);
    const int ret = num_is_zero(im);
    delete(im);

    return ret;    
}

/* Type casting */

double
num_to_double (const num_t _self)
{
    const struct num* self = _self;
      
    if (num_is_real(_self))
    {
        return self->dat[0];
    }

    return NAN;
}

void
num_to_pair (double* res, const num_t _self)
{
    const struct num* self = _self;

    for (int i = 0; i < NCOMP; i++)
        res[i] = self->dat[i];
}

/* Unary operations */
num_t
num_abs2 (const num_t _self)
{
    const struct num* self = _self;
    const double x = self->dat[0];
    const double y = self->dat[1];

    return new(num, x*x + y*y, 0.0);
}

num_t
num_abs (const num_t _self)
{
    const struct num* self = _self;
    const double x = self->dat[0];
    const double y = self->dat[1];

    return new(num, hypot(x, y), 0.0);
}

num_t
num_negative (const num_t _self)
{
    const struct num* self = _self;
    
	return new(num, -1 * self->dat[0], -1 * self->dat[1]);
}

num_t
num_conjugate (const num_t _self)
{
    const struct num * self = _self;
    
	return new(num, self->dat[0], -1 * self->dat[1]);
}

num_t
num_arg (const num_t _self)
{
    const struct num * self = _self;
    const double x = self->dat[0];
    const double y = self->dat[1];

    return new(num, atan2(y, x), 0.0);
}

num_t
num_sqrt (const num_t _self)
{
    const double sqrt_r = sqrt(num_to_double(num_abs(_self)));
    const double half_arg_z = 0.5 * num_to_double(num_arg(_self));

    return new(num, sqrt_r * cos(half_arg_z), sqrt_r * sin(half_arg_z));     
}

num_t
num_exp (const num_t _self)
{
    const struct num * self = _self;
    const double x = self->dat[0];
    const double y = self->dat[1];

    return new(num, exp(x)*cos(y), exp(x)*sin(y));
}

num_t
num_log (const num_t _self)
{
    const struct num * self = _self;
    const double x = self->dat[0];
    const double y = self->dat[1];
    const double _abs = hypot(x, y);
    const double _th = atan2(y, x);

    return new(num, log(_abs), _th);
}

/* sin(x+iy) = sin(x) cosh(y) + i cos(x) sinh(y)) */
num_t
num_sin (const num_t _self)
{
    const struct num * self = _self;
    const double x = self->dat[0];
    const double y = self->dat[1];

    return new(num, sin(x) * cosh(y), cos(x) * sinh(y));
}

/* cos(x+iy)=cos(x) cosh(y) − i sin(x) sinh(y) */
num_t
num_cos (const num_t _self)
{
    const struct num * self = _self;
    const double x = self->dat[0];
    const double y = self->dat[1];

    return new(num, cos(x) * cosh(y), -1 * sin(x) * sinh(y));
}

/* Binary operations */

/* Arithmetic */

num_t
num_add (const num_t _self, const num_t _other)
{
    const struct num* self  = _self;
    const struct num* other = _other;

    return new(num, self->dat[0] + other->dat[0], self->dat[1] + other->dat[1]);
}

num_t
num_sub (const num_t _self, const num_t _other)
{
    const struct num* self  = _self;
    const struct num* other = _other;

    return new(num, self->dat[0] - other->dat[0], self->dat[1] - other->dat[1]);
}

num_t
num_mul (const num_t _self, const num_t _other)
{
    const struct num * self  = _self;
    const struct num * other = _other;
    
    const double a = self->dat[0];
    const double b = self->dat[1];
    const double c = other->dat[0];
    const double d = other->dat[1];

    return new(num, a * c - b * d, a * d + b * c);
}

num_t
num_div (const num_t _self, const num_t _other)
{
    const struct num* self  = _self;
    const struct num* other = _other;
    
    const double a = self->dat[0];
    const double b = self->dat[1];
    const double c = other->dat[0];
    const double d = other->dat[1];
    
    const double abs2_other = c * c + d * d;

    return new(num, (a * c + b * d)/abs2_other, (b * c - a * d)/abs2_other);
}

num_t
num_fmod (const num_t _self, const num_t _other)
{
    assert(num_is_real(_self) && num_is_real(_other));
    return new(num, fmod(num_to_double(_self), num_to_double(_other)), 0.0);
}

num_t
num_pow (const num_t _self, const num_t _other)
{
    const struct num* other = _other;

    const double r = num_to_double(num_abs(_self));
    const double th = num_to_double(num_arg(_self));
    const double a = other->dat[0];
    const double b = other->dat[1];

    const double pow_r = pow(r, a) * exp(-th * b);
    const double scale_arg_z = a * th + b * log(r);

    return new(num, pow_r * cos(scale_arg_z), pow_r * sin(scale_arg_z));
}

/* Logical */

int
num_eq (const num_t _self, const num_t _other)
{
    const double eps = num_to_double(num_abs(num_sub(_self, _other)));
    
    return fabs(eps) < _TOLERANCE;
}

int
num_lt (const num_t _self, const num_t _other)
{
    assert(num_is_real(_self) && num_is_real(_other));
    const double x = num_to_double(num_sub(_self, _other));
    return x < 0;
}

int
num_gt (const num_t _self, const num_t _other)
{
    assert(num_is_real(_self) && num_is_real(_other));
    const double x = num_to_double(num_sub(_self, _other));
    return x > 0;
}

int
num_le (const num_t _self, const num_t _other)
{
    assert(num_is_real(_self) && num_is_real(_other));
    return num_lt(_self, _other) || num_eq(_self, _other);
}

int
num_ge (const num_t _self, const num_t _other)
{
    assert(num_is_real(_self) && num_is_real(_other));
    return num_gt(_self, _other) || num_eq(_self, _other);
}

#ifdef _TOLERANCE
#undef _TOLERANCE
#endif
