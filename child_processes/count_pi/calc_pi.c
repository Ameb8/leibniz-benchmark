#include <math.h>

double calcPi(int nTerms) {
    double pi = 0.0;

    for(int i = 0; i < nTerms; i++) {
        int sign = 1;

        if(i % 2 == 1)
            sign = -1;

        pi += sign / (2 * i + 1);
    }

    return 4 * pi;
}