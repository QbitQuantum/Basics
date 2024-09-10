double
PTnint(double arg1)
{
    /* round to "nearest integer",
     *   round half-integers to the nearest even integer
     *   rely on default rounding mode of IEEE 754 to do so
     */
    return nearbyint(arg1);
}