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
 * @file num.h
 * @brief Interface of the Abstract Data Type (ADT).
 * @details This should encapsulate any routine working with numbers.
 */
#ifndef __NUM_H__
#define __NUM_H__

/**
 * This should be used in the initialization of the variable
 */
extern const void* num;

/**
 * Type associated with the class
 *
 * Objects of this type may directly be created by the user.
 * 
 */
typedef void* num_t;

num_t
num_zero (void);

/***************************************/
/* Accessors: Real and Imaginary parts */
/***************************************/

/**
 * Returns the real part of \p _self (\f$x\f$), \f$\mathrm{Re}(x)\f$.
 */
num_t
num_real_part (const num_t _self);

/**
 * Returns the imaginary part of \p _self (\f$x\f$), \f$\mathrm{Im}(x)\f$.
 */
num_t
num_imag_part (const num_t _self);

/**************/
/* Predicates */
/**************/

/**
 * Returns nonzero iff \p _self is zero, within tolerance.
 */
int
num_is_zero (const num_t _self);

/**
 * Returns nonzero iff \p _self has a zero imaginary part.
 */
int
num_is_real (const num_t _self);

/****************/
/* Type casting */
/****************/

/**
 * Converts numeric types to machine's double.
 */
double
num_to_double (const num_t _self);

void
num_to_pair (double* res, const num_t _self);

/********************/
/* Unary operations */
/********************/

/**
 * Returns the square of absolute value of \p _self (\f$x\f$), \f$|x|\f$.
 */
num_t
num_abs2 (const num_t _self);

/**
 * Returns the absolute value of \p _self (\f$x\f$), \f$|x|\f$.
 */
num_t
num_abs (const num_t _self);

/**
 * Returns the negative of \p _self (\f$x\f$), \f$-x\f$.
 */
num_t
num_negative (const num_t _self);

/**
 * Returns the complex conjugate of \p _self (\f$x\f$), \f$x^\ast\f$.
 */
num_t
num_conjugate (const num_t _self);

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

/***********/
/* Logical */
/***********/

/**
 * This function determines whether \p _self (\f$x\f$) and \p _other (\f$y\f$),
 * are approximately equal to a relative accuracy.
 */
int
num_eq (const num_t _self, const num_t _other);

#endif /* __NUM_H__ */
