      const bool conjugate = ( shift0.imag() == -shift1.imag() );
      if( !bothReal && !conjugate )
          LogicError("Assumed shifts were either both real or conjugates");
    )
    if( n == 2 )
    {
        const Real& eta00 = H(0,0);
        const Real& eta01 = H(0,1);
        const Real& eta10 = H(1,0);
        const Real& eta11 = H(1,1);

        // It seems arbitrary whether the scale is computed relative
        // to shift0 or shift1, but we follow LAPACK's convention.
        // (While the choice is irrelevant for conjugate shifts, it is not for
        //  real shifts)
        const Real scale = OneAbs(eta00-shift1) + Abs(eta10);
        if( scale == zero )
        {
            v[0] = v[1] = zero;
        }
        else
        {
            // Normalize the first column by the scale
            Real eta10Scale = eta10 / scale;
            v[0] = eta10Scale*eta01 +
                   (eta00-shift0.real())*((eta00-shift1.real())/scale) -
                   shift0.imag()*(shift1.imag()/scale);
            v[1] = eta10Scale*(eta00+eta11-shift0.real()-shift1.real());
        }
    }
    else