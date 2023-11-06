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
 * @file num.h
 * @brief Interface of the Abstract Data Type (ADT).
 * @details This should encapsulate any routine working with numbers.
 */
#ifndef __NUM_H__
#define __NUM_H__

#include <stdbool.h>
#include <complex.h>
#include <stdarg.h>

/**
 * This should be used in the initialization of the variable
 */
extern const void * num;

/**
 * Type associated with the class
 *
 * Objects of this type may directly be created by the user.
 * 
 */
typedef void * num_t;

void
num_print (const num_t self, const bool endline);

num_t
num_from_d (const double x);

num_t
num_from_d_d (const double re, const double im);

num_t
num_zero (void);

/***************************************/
/* Accessors: Real and Imaginary parts */
/***************************************/

/**
 * Returns the real part of \p _self (\f$x\f$), \f$\mathrm{Re}(x)\f$.
 */
num_t
num_real (const num_t self);

/**
 * Returns the imaginary part of \p _self (\f$x\f$), \f$\mathrm{Im}(x)\f$.
 */
num_t
num_imag (const num_t self);

/**************/
/* Predicates */
/**************/

/**
 * Returns nonzero iff \p _self is zero, within tolerance.
 */
bool
num_is_zero (const num_t _self);

/**
 * Returns nonzero iff \p _self has a zero imaginary part.
 */
bool
num_is_real (const num_t _self);

/****************/
/* Type casting */
/****************/

/**
 * Converts numeric types to machine's double.
 */
double
num_to_d (const num_t _self);

/* void */
/* num_to_pair (double* res, const num_t _self); */

double complex
num_to_complex (const num_t self);

/********************/
/* Unary operations */
/********************/

/**
 * Returns the absolute value of \p _self (\f$x\f$), \f$|x|\f$.
 */
num_t
num_abs (const num_t self);

/**
 * Returns the negative of \p _self (\f$x\f$), \f$-x\f$.
 */
num_t
num_neg (const num_t self);

num_t
num_inv (const num_t self);

/**
 * Returns the complex conjugate of \p _self (\f$x\f$), \f$x^\ast\f$.
 */
num_t
num_conj (const num_t self);

num_t
num_ceil (const num_t self);

/**
 * Returns the argument of \p _self (\f$x\f$), \f$\mathrm{arg}(x)\f$.
 */
num_t
num_arg (const num_t _self);

/**
 * Returns the square root of the number
 */
num_t
num_sqrt (const num_t _self);

/**
 * Returns the exponential of the number
 */
num_t
num_exp (const num_t _self);

/**
 * Returns the logarithm of the number
 */
num_t
num_log (const num_t _self);

/**
 * Returns the sine of the number
 */
num_t
num_sin (const num_t _self);

/**
 * Returns the cosine of the number
 */
num_t
num_cos (const num_t _self);

/*********************/
/* Binary operations */
/*********************/

/**************/
/* Arithmetic */
/**************/

/**
 * returns the addition of \p _self (\f$x\f$) and \p _other (\f$y\f$), \f$x + y\f$.
 */
num_t
num_add (const num_t _self, const num_t _other);

/**
 * returns the subtraction of \p _self (\f$x\f$) and \p _other (\f$y\f$), \f$x - y\f$.
 */
num_t
num_sub (const num_t _self, const num_t _other);

/**
 * returns the multiplication of \p _self (\f$x\f$) and \p _other (\f$y\f$), \f$x\cdot y\f$.
 */
num_t
num_mul (const num_t _self, const num_t _other);

/**
 * returns the division of \p _self (\f$x\f$) and \p _other (\f$y\f$), \f$x/y\f$.
 */
num_t
num_div (const num_t _self, const num_t _other);

/**
 *  Returns the remainder of the division of \p _self (\f$x\f$) and \p _other (\f$y\f$), \f$x/y\f$.
 */
num_t
num_fmod (const num_t _self, const num_t _other);

/**
 * returns the exponentiation of \p _self (\f$x\f$) to \p _other (\f$y\f$), \f$x^y\f$.
 */
num_t
num_pow (const num_t _self, const num_t _other);

/***********/
/* Logical */
/***********/

/**
 * This function determines whether \p _self (\f$x\f$) and \p _other (\f$y\f$),
 * are approximately equal to a relative accuracy.
 */
bool
num_eq (const num_t _self, const num_t _other);

bool
num_gt (const num_t _self, const num_t _other);

bool
num_lt (const num_t _self, const num_t _other);

bool
num_ge (const num_t _self, const num_t _other);

bool
num_le (const num_t _self, const num_t _other);

/*********************/
/* Special functions */
/*********************/

num_t
num_erf (const num_t self);

num_t
num_erfc (const num_t self);

num_t
num_rgamma (const num_t self);

void
num_cpy (num_t* self, const num_t other);

num_t
num_max (int count, ...);
    

#endif /* __NUM_H__ */
