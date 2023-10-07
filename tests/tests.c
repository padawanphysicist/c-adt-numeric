
#include <stdio.h>
#include <stdlib.h>
#include "new.h"
#include "num.h"



int
test (const int id, const char* msg, const num_t computed, const num_t expected)
{
    if (! num_eq(computed, expected))
    {
        double c[2];
        double e[2];

        num_to_double(c, computed);
        num_to_double(e, expected);
        
        printf("[id=%02d] %s [ERROR]: expected=(%g, %g), computed=(%g, %g)\n",
               id, msg, e[0], e[1], c[0], c[1]);

        return 1;
    }

    return 0;
}


int main (void)
{
    int code, id = 1;
    num_t x, y, computed, expected;

    
    x = new(num, +4.0, 0.0);
    y = new(num, -3.0, 0.0);
    computed = num_add(x, y);
    expected = new(num, +1.0, 0.0);
    code = test(id, "num_add((+4.0, 0.0), (-3.0, 0.0))", computed, expected);
    delete(x), delete(y), delete(expected);
    if (code == 1) exit(1);
    id++;

    x = new(num, +4.0, +3.0);
    y = new(num, -3.0, -2.0);
    computed = num_add(x, y);
    expected = new(num, +1.0, +1.0);
    code = test(id, "num_add((+4.0, +3.0), (-3.0, -2.0))", computed, expected);
    delete(x), delete(y), delete(expected);
    if (code == 1) exit(1);
    id++;

    x = new(num, 0.0, +3.0);
    y = new(num, 0.0, -2.0);
    computed = num_add(x, y);
    expected = new(num, 0.0, +1.0);
    code = test(id, "num_add((0.0, +3.0), (0.0, -2.0))", computed, expected);
    delete(x), delete(y), delete(expected);
    if (code == 1) exit(1);
    id++;

    x = new(num, 5.0, 8.0);
    y = new(num, 4.0, 6.0);
    computed = num_sub(x, y);
    expected = new(num, 1.0, 2.0);
    code = test(id, "num_sub((5.0, 8.0), (4.0, 6.0))", computed, expected);
    delete(x), delete(y), delete(expected);
    if (code == 1) exit(1);
    id++;

    x = new(num, 3.0, 4.0);
    y = new(num, 2.0, -5.0);
    computed = num_sub(x, y);
    expected = new(num, 1.0, 9.0);
    code = test(id, "num_sub((3.0, 4.0), (2.0, -5.0))", computed, expected);
    delete(x), delete(y), delete(expected);
    if (code == 1) exit(1);
    id++;


    return (id-1); /* Return the number of passed tests */

}