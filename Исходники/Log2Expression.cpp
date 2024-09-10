long double
Log2Expression::getLongDouble(long double op) 
{
    errno=0;
    long double reply ;
#ifdef HAVE_LOGL
    reply = log2l(op);
#else
    reply = static_cast<long double>(log2(static_cast<double>(op)));
#endif
    if( errno && ( errno == EDOM || errno == ERANGE ))
    {
        return edom();
    }
    return reply;
}