// sqrt(r)
// uses bntmp1 - bntmp6 - global temp bignumbers
//  SIDE-EFFECTS:
//      n ends up as |n|
bn_t sqrt_bn(bn_t r, bn_t n)
{
    int comp, almost_match = 0;
    LDBL f;
    bn_t orig_r, orig_n;
    int  orig_bnlength,
         orig_padding,
         orig_rlength,
         orig_shiftfactor;

    // use Newton's recursive method for zeroing in on sqrt(n): r=.5(r+n/r)

    if (is_bn_neg(n))
    {   // sqrt of a neg, return 0
        clear_bn(r);
        return r;
    }

    f = bntofloat(n);
    if (f == 0) // division by zero will occur
    {
        clear_bn(r); // sqrt(0) = 0
        return r;
    }
    f = sqrtl(f); // approximate square root
    // no need to check overflow

    // With Newton's Method, there is no need to calculate all the digits
    // every time.  The precision approximately doubles each iteration.
    // Save original values.
    orig_bnlength      = bnlength;
    orig_padding       = padding;
    orig_rlength       = rlength;
    orig_shiftfactor   = shiftfactor;
    orig_r             = r;
    orig_n             = n;

    // calculate new starting values
    bnlength = intlength + (int)(LDBL_DIG/LOG10_256) + 1; // round up
    if (bnlength > orig_bnlength)
        bnlength = orig_bnlength;
    calc_lengths();

    // adjust pointers
    r = orig_r + orig_bnlength - bnlength;

    floattobn(r, f); // start with approximate sqrt
    copy_bn(bntmp4, r);

    for (int i = 0; i < 25; i++) // safety net, this shouldn't ever be needed
    {
        // adjust lengths
        bnlength <<= 1; // double precision
        if (bnlength > orig_bnlength)
            bnlength = orig_bnlength;
        calc_lengths();
        r = orig_r + orig_bnlength - bnlength;
        n = orig_n + orig_bnlength - bnlength;

        copy_bn(bntmp6, r);
        copy_bn(bntmp5, n);
        unsafe_div_bn(bntmp4, bntmp5, bntmp6);
        add_a_bn(r, bntmp4);
        half_a_bn(r);
        if (bnlength == orig_bnlength && (comp = abs(cmp_bn(r, bntmp4))) < 8)  // if match or almost match
        {
            if (comp < 4  // perfect or near perfect match
                    || almost_match == 1) // close enough for 2nd time
                break;
            else // this is the first time they almost matched
                almost_match++;
        }
    }

    // restore original values
    bnlength      = orig_bnlength;
    padding       = orig_padding;
    rlength       = orig_rlength;
    shiftfactor   = orig_shiftfactor;
    r             = orig_r;

    return r;
}