#include "parametres.h"
#include <math.h>

void to0_2PI(float &a) {
    if (a > (PI * 2.0)) {
        a -= (PI * 2.0);
        to0_2PI(a);
    }
    else {
        if (a < 0.0) {
            a += (PI * 2.0);
            to0_2PI(a);
        }
    }        
}


