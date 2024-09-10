bool Bridge:: FinalRadius(const double height,
                          const double theta,
                          const double alpha,
                          const bool   save) 
{

    //__________________________________________________________________________
    //
    // do we save ?
    //__________________________________________________________________________
    if(save)
    {
        static vfs & fs = local_fs::instance();
        fs.try_remove_file("profile.dat");
    }

    //__________________________________________________________________________
    //
    // check possibility
    //__________________________________________________________________________
    const double omega = lens->omega(alpha);
    const double angle = omega+theta;
    if(angle>=180)
    {
        return false;
    }

    //__________________________________________________________________________
    //
    // prepare initial conditions
    //__________________________________________________________________________
    const double Rc        = lens->rho(0.0)+height;
    const double R0        = lens->rho(alpha);
    const double r0        = R0*SinDeg(alpha);
    const double z0        = Rc - R0*CosDeg(alpha);
    const double drdz      = CosDeg(angle)/SinDeg(angle);
    Y[1] = r0;
    Y[2] = drdz;

    //__________________________________________________________________________
    //
    // do we save ?
    //__________________________________________________________________________
    auto_ptr<ios::ostream> fp;
    if(save)
    {
        fp.reset(new ios::ocstream("profile.dat",false) );
        (*fp)("%g %g\n", r0, z0 );
    }

    //__________________________________________________________________________
    //
    // Try to integrate
    //__________________________________________________________________________
    double reg[3] = { Y[1],0,0 }; // curvature detector
    size_t num    = 1;
    bool success  = true;
    for(size_t i=NUM_STEPS;i>0;--i)
    {
        const double z_ini = (i*z0)/NUM_STEPS;
        const double z     = ((i-1)*z0)/NUM_STEPS;
        RK4(z_ini, z);

        //______________________________________________________________________
        //
        // analyze
        //______________________________________________________________________
        const double r = Y[1];

        //______________________________________________________________________
        //
        // absolute position
        //______________________________________________________________________
        if( isnan(r) || isinf(r) || r <= 0.0 )
        {
            success = false;
            break;
        }

        //______________________________________________________________________
        //
        // Relative position: inside lens ?
        //______________________________________________________________________
        const double dr   = r;
        const double dz   = Rc-z;
        const double dist = Hypotenuse(dr, dz);
        const double aa   = Rad2Deg(2.0 * Atan( dr / (dz+dist)));
        const double ra   = lens->rho(aa);
        if(dist<ra)
        {
            success = false;
            break;
        }

        //__________________________________________________________________
        //
        // test valid curvature
        //__________________________________________________________________
        if(num<3)
        {
            reg[num++] = r;
        }
        else
        {
            reg[0] = reg[1];
            reg[1] = reg[2];
            reg[2] = r;
            if((reg[1]+reg[1])>= (reg[0]+reg[2]) )
            {
                success = false;
                break;
            }
        }


        if(save && (r<=4*Rc))
        {
            (*fp)("%g %g\n", r, z );
        }
    }
    
    
    
    return success;
}