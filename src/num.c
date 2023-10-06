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
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "num.h"
#include "new.h"
#include "abc.h"

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

num_t
num_conjugate (const num_t _self)
{
    const struct num * self = _self;
    
	return new(num, self->dat[0], -1 * self->dat[1]);
}

num_t
num_negative (const num_t _self)
{
    const struct num* self = _self;
    
	return new(num, -1 * self->dat[0], -1 * self->dat[1]);
}

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

void
num_to_double (double* res, const num_t _self)
{
    const struct num* self = _self;

    for (int i = 0; i < NCOMP; i++)
        res[i] = self->dat[i];
}

int
num_eq (const num_t _self, const num_t _other)
{
    const struct num* self  = _self;
    const struct num* other = _other;
    
    const double a = self->dat[0];
    const double b = self->dat[1];
    const double c = other->dat[0];
    const double d = other->dat[1];

    const double eps = 1e-8;

    return (fabs(a-c) < eps && fabs(b-d) < eps);
}
