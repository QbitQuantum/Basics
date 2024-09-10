/*
 * By working with the problem, we can express the numbers b and c based on a.
 * So we go through numbers and try to find an a that makes all other
 * restrictions fall into place.
 */
long solution() {
    //natural numbers, so a=0 isn't an accepted solution.
    for(long a = 1; ; ++a) {
        long b = getB(a);
        long c = getC(a, b);
        if(isSolution(a, b, c))
            return a*b*c;
    }

    //if it didn't find a solution return -1 as an indication of error
    return -1;
}