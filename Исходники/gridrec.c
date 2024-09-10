void 
set_pswf_tables(
    float C, int nt, float lambda, const float *coefs, 
    int ltbl, int linv, float* wtbl, float* winv)                                            
{
    // Set up lookup tables for convolvent (used in Phase 1 of   
    // do_recon()), and for the final correction factor (used in 
    // Phase 3).

    int i;
    float norm;
    const float fac = (float)ltbl / (linv+0.5);
    const float polyz = legendre(nt, coefs, 0.);

    wtbl[0] = 1.0;
    for(i=1; i<=ltbl; i++) 
    {   
        wtbl[i] = legendre(nt, coefs, (float)i/ltbl) / polyz;
    }

    // Note the final result at end of Phase 3 contains the factor, 
    // norm^2.  This incorporates the normalization of the 2D
    // inverse FFT in Phase 2 as well as scale factors involved
    // in the inverse Fourier transform of the convolvent.
    norm = sqrt(M_PI/2/C/lambda) / 1.2;

    winv[linv] = norm / wtbl[0];
    for(i=1; i<=linv; i++)
    {
        // Minus sign for alternate entries
        // corrects for "natural" data layout
        // in array H at end of Phase 1.
        norm = -norm; 
        winv[linv+i] = winv[linv-i] = norm / wtbl[lroundf(i*fac)];
    }
}