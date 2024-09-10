double diskthick (double z)                 //  vertical mass distribution
{                                           //
    return 1.0/pow(cosh(z / z0), 2.0);      //
}                                           //