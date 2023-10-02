#include <stdio.h>

#include "new.h"
#include "numeric.h"

void
print(const char* name, const numeric_t z)
{
    double r[2];
    numeric_to_double (r, z);    
    printf("%s(%+.5e, %+.5e)\n", name, r[0], r[1]);
}

int main ()
{
    numeric_t tmp;
  
    numeric_t zero = new(numeric, 0.0, 0.0);
    numeric_t I    = new(numeric, 0.0, 1.0);
    numeric_t one  = new(numeric, 1.0, 0.0);    
    numeric_t x    = new(numeric, 3.0, 4.0);    
    numeric_t y    = new(numeric, -1.0, 2.0);

    printf("# Print numbers ==================\n");
    print("zero = ", zero);
    print("   I = ", I);
    print(" one = ", one);
    print("   x = ", x);
    print("   y = ", y);

    printf("\n# Negation ==================\n");  
    tmp = numeric_negative (zero);
    print("-zero =\t", tmp);
    delete(tmp);

    tmp = numeric_negative (I);
    print("-I =\t", tmp);
    delete(tmp);

    tmp = numeric_negative (one);
    print("-x =\t", tmp);
    delete(tmp);

    tmp = numeric_negative (x);
    print("-one =\t", tmp);
    delete(tmp);

    tmp = numeric_negative (y);
    print("-y =\t", tmp);
    delete(tmp);

    printf("\n# Conjugation ==================\n");  
    tmp = numeric_conjugate (zero);
    print("*zero =\t", tmp);
    delete(tmp);

    tmp = numeric_conjugate (I);
    print("*I =\t", tmp);
    delete(tmp);

    tmp = numeric_conjugate (one);
    print("*x =\t", tmp);
    delete(tmp);

    tmp = numeric_conjugate (x);
    print("*one =\t", tmp);
    delete(tmp);

    tmp = numeric_conjugate (y);
    print("*y =\t", tmp);
    delete(tmp);

    printf("\n# Addition ==================\n");  
    tmp = numeric_add (x, y);
    print("x + y =\t", tmp);
    delete(tmp);

    printf("\n# Subtraction ==================\n");  
    tmp = numeric_sub (x, y);
    print("x - y =\t", tmp);
    delete(tmp);

    printf("\n# Multiplication ==================\n");  
    tmp = numeric_mul (x, y);
    print("x * y =\t", tmp);
    delete(tmp);

    printf("\n# Multiplication ==================\n");  
    tmp = numeric_div (x, y);
    print("x / y =\t", tmp);
    delete(tmp);
    
	delete(I), delete(one), delete(zero), delete(x), delete(y);
    
	return 0;
}
