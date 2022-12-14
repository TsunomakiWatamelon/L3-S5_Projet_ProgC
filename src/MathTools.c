
#include "../include/MathTools.h"

double randRange(double min, double max){
    assert(min > 0);
    assert(max >= min);
    return min + (rand() / RAND_MAX) * (max - min);
}


int getProbability(int probability){
    return rand() <  probability * ((double)RAND_MAX + 1.0);
}

