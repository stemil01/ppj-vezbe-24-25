#include <stdio.h>
#include <stdlib.h>

#define sum(x, y) \
    (x) + \
    (  y)


int main(int argc, char** argv) {

    int x = 10; 
    double y = 43.394e-3; 

    
    double z = x + y; 
    if (x > y)
        z = 10;
    else
        z = -10.5;

    
    printf("%lf\n", z);

    
    exit(EXIT_SUCCESS);
}