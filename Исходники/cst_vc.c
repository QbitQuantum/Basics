DVECTOR xdvinit(double j, double incr, double n)
{
    long k;
    long num;
    DVECTOR x;

    if ((incr > 0.0 && j > n) || (incr < 0.0 && j < n)) {
	x = xdvnull();
	return x;
    }
    if (incr == 0.0) {
	num = (long)n;
	if (num <= 0) {
	    x = xdvnull();
	    return x;
	}
    } else {
	num = LABS((long)((n - j) / incr)) + 1;
    }
    
    /* memory allocate */
    x = xdvalloc(num);

    /* initailize data */
    for (k = 0; k < x->length; k++) {
	x->data[k] = j + (k * incr);
    }

    return x;
}