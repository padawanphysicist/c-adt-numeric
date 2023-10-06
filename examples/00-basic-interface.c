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

int
main (void)
{
    int code, count = 1;

    /* Binary operations */
    num_t x, y, computed, expected;
    
    /* add */

    /* Test 1 */
    x = new(num, +4.0, +3.0);    
    y = new(num, -3.0, -2.0);
    computed = num_add(x, y);
    expected = new(num, 1.0, 1.0);
    code = test(count, "(4+3i) + (-3-2i)", computed, expected);
    delete(x), delete(y), delete(expected);
    if (code == 1) exit(1);
    count++;

    /* Test 2 */
    x = new(num, 0.0, +3.0);    
    y = new(num, 0.0, -2.0);
    computed = num_add(x, y);
    expected = new(num, 0.0, 1.0);
    code = test(count, "3i + (-2i)", computed, expected);
    delete(x), delete(y), delete(expected);
    if (code == 1) exit(1);
    count++;

    /* Test 3 */
    x = new(num, +4.0, 0.0);    
    y = new(num, -3.0, 0.0);
    computed = num_add(x, y);
    expected = new(num, 1.0, 0.0);
    code = test(count, "4 + (-3)", computed, expected);
    delete(x), delete(y), delete(expected);
    if (code == 1) exit(1);
    count++;
    
	return (count-1);
}
