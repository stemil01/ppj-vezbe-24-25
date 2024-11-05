#include <stdio.h>
#include <stdlib.h>

#define sum(x, y) \
    (x) + \
    (  y)

/* ovo je neki komentar */
int main(int argc, char** argv) {

    int x = 10; /* ovo je neki komentar */
    double y = 43.394e-3; /* ovo je neki komentar */

    /******************* 
     * ovo je 
     * neki 
     * komentar 
     *******************/
    double z = x + y; // komentar

    if (x > y)
        z = 10;
    else
        z = -10.5;

    /* ovo je neki 
       komentar 
     */
    const char *str = "ovo je \" string";
    printf("%lf\n", z);

    /* ovo je neki komentar */
    exit(EXIT_SUCCESS);
}