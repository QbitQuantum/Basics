static Handle powerOf(TaskData *mdTaskData, Handle args)
{
    double x = real_arg1(args), y = real_arg2(args);
    /* Some of the special cases are defined and don't seem to match
       the C pow function (at least as implemented in MS C). */
    /* Maybe handle all this in ML? */
    if (isnan(x))
    {
        if (y == 0.0) return real_result(mdTaskData, 1.0);
        else return real_result(mdTaskData, notANumber);
    }
    else if (isnan(y)) return real_result(mdTaskData, y); /* i.e. nan. */
    else if (x == 0.0 && y < 0.0)
    {
        /* This case is not handled correctly in Solaris. It always
           returns -infinity. */
        int iy = (int)floor(y);
        /* If x is -0.0 and y is an odd integer the result is -infinity. */
        if (copysign(1.0, x) < 0.0 && (double)iy == y && (iy & 1))
            return real_result(mdTaskData, negInf); /* -infinity. */
        else return real_result(mdTaskData, posInf); /* +infinity. */
    }
    return real_result(mdTaskData, pow(x, y));
}