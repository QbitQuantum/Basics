 T BivarStats<T>::sigmaSlope(void) const
 {
    if (ns>2)
       return sigmaYX() / (stdDevX() * SQRT(T(ns-1)));
    else
       return T();
 }