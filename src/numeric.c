#include <assert.h>
#include <stdlib.h>

#include "numeric.h"
#include "new.h"
#include "new.r"

#define NCOMP 2

struct numeric {
	const void * class;	/* must be first */
	double* dat; /* data */
};

static void *
numeric_ctor (void * _self, va_list * app)
{
    struct numeric * self = _self;
	
	self -> dat = malloc(NCOMP*sizeof(double));
	assert(self -> dat);

    for (int i = 0; i < NCOMP; i++)
    {
        const double res = va_arg(* app, const double);
        self -> dat[i] = res;
    }

	return self;
}

static void *
numeric_dtor (void * _self)
{
    struct numeric * self = _self;

	free(self -> dat), self -> dat = 0;
	return self;
}

static void *
numeric_clone (const void * _self)
{
    const struct numeric * self = _self;
	return new(numeric, self -> dat);
}

static int
numeric_differ (const void * _self, const void * _b)
{
    const struct numeric * self = _self;
	const struct numeric * b = _b;

	if (self == b)
		return 0;
	if (! b || b -> class != numeric)
		return 1;
	return (self -> dat[0] == b -> dat[0] && self -> dat[1] == b -> dat[1]);
}

static const struct Class _numeric = {
	sizeof(struct numeric),
	numeric_ctor, numeric_dtor,
	numeric_clone, numeric_differ
};

const void * numeric = & _numeric;

/****************************/
/* User interface functions */
/****************************/
numeric_t
numeric_real_part (const numeric_t _self)
{
    const struct numeric * self = _self;
    
	return new(numeric, self -> dat[0], 0.0);
}

numeric_t
numeric_imag_part (const numeric_t _self)
{
    const struct numeric * self = _self;
    
	return new(numeric, self -> dat[1], 0.0);
}

numeric_t
numeric_conjugate (const numeric_t _self)
{
    const struct numeric * self = _self;
    
	return new(numeric, self -> dat[0], -1 * self -> dat[1]);
}

numeric_t
numeric_negative (const numeric_t _self)
{
    const struct numeric * self = _self;
    
	return new(numeric, -1 * self -> dat[0], -1 * self -> dat[1]);
}

numeric_t
numeric_add (const numeric_t _self, const numeric_t _other)
{
    const struct numeric * self  = _self;
    const struct numeric * other = _other;

    return new(numeric, self->dat[0] + other->dat[0], self->dat[1] + other->dat[1]);
}

numeric_t
numeric_sub (const numeric_t _self, const numeric_t _other)
{
    const struct numeric * self  = _self;
    const struct numeric * other = _other;

    return new(numeric, self->dat[0] - other->dat[0], self->dat[1] - other->dat[1]);
}

numeric_t
numeric_mul (const numeric_t _self, const numeric_t _other)
{
    const struct numeric * self  = _self;
    const struct numeric * other = _other;
    
    const double a = self -> dat[0];
    const double b = self -> dat[1];
    const double c = other -> dat[0];
    const double d = other -> dat[1];

    return new(numeric, a * c - b * d, a * d + b * c);
}

numeric_t
numeric_div (const numeric_t _self, const numeric_t _other)
{
    const struct numeric * self  = _self;
    const struct numeric * other = _other;
    
    const double a = self -> dat[0];
    const double b = self -> dat[1];
    const double c = other -> dat[0];
    const double d = other -> dat[1];
    
    const double abs2_other = c * c + d * d;

    return new(numeric, (a * c + b * d)/abs2_other, (b * c - a * d)/abs2_other);
}

void
numeric_to_double (double res[NCOMP], const numeric_t _self)
{
    const struct numeric * self = _self;

    for (int i = 0; i < NCOMP; i++)
        res[i] = self -> dat[i];
}
