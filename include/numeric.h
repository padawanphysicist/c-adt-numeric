/** 
 * @file numeric.h
 * @brief Interface of the numeric Abstract Data Type.
 * @details
 *
 * Inspired by the development model of GiNaC numeric class:
 *
 * https://www.ginac.de/reference/classGiNaC_1_1numeric.html
 */

/* 
 * Copyright (c) 2023 Victor Santos <victor_santos@fisica.ufc.br>.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef __NUMERIC_H__
#define __NUMERIC_H__

#include <stdbool.h>

/** Class name
 *
 * This should be used in the initialization of the variable:
 * @example 
 * This is an example of how to use the Example_Test class.
 * More details about this example.
 * 
 */
extern const void * numeric;

/** Type associated with the class
 *
 * Objects of this type may directly be created by the user.
 * 
 */
typedef void * numeric_t;

/**
 * Returns the real part of the number.
 */
numeric_t
numeric_real_part (const numeric_t _self);

/**
 * Returns the imaginary part of the number.
 */
numeric_t
numeric_imag_part (const numeric_t _self);

/**
 * Returns the complex conjugate of the number.
 */
numeric_t
numeric_conjugate (const numeric_t _self);

/**
 * Returns the negative of the number.
 */
numeric_t
numeric_negative (const numeric_t _self);

/**
 * returns the addition of \p _self and \p _other, \f$z = x + y\f$.
 */
numeric_t
numeric_add (const numeric_t _self, const numeric_t _other);

/**
 * returns the subtraction of numbers \p x and \p y, \f$z = x - y\f$.
 */
numeric_t
numeric_sub (const numeric_t _self, const numeric_t _other);

/**
 * returns the multiplication of numbers \p x and \p y, \f$z = xy\f$.
 */
numeric_t
numeric_mul (const numeric_t _self, const numeric_t _other);

/**
 * returns the division of numbers \p x and \p y, \f$z = x/y\f$.
 */
numeric_t
numeric_div (const numeric_t _self, const numeric_t _other);

/**
 * Converts numeric types to machine's double.
 */
void
numeric_to_double (double res[2], const numeric_t _self);

#endif /* __NUMERIC_H__ */
