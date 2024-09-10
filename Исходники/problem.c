void problem_migration_forces(){
    if(mig_forces==1){
        int print = 1;
        struct particle com = particles[0]; // calculate migration forces with respect to center of mass;
        for(int i=1;i<N;i++){ // N = _N + 1 = total number of planets + star
                double t_migend = t_mig[i] + t_damp[i]; //when migration ends
                if (t > t_mig[i] && t < t_migend) { //ramp down the migration force (by increasing the migration timescale)
                    tau_a[i] *= expf(dt/expmigfac[i]);
                    tau_e[i] = tau_a[i]/K;
                } else if(t > t_migend){
                    tau_a[i]=0.;
                    tau_e[i]=0.;
                    double sum = 0;
                    for(int j=0;j<N;j++) sum += tau_a[j];
                    if(sum < 0.1){
                        mig_forces = 0; //turn migration loop off altogether, save calcs
                        if(p_suppress == 0 && print == 1) printf("\n\n **migration loop off at t=%f** \n\n",t);
                        print = 0;
                    }
                }
            
            if (tau_e[i]!=0||tau_a[i]!=0){
                struct particle* p = &(particles[i]);
                const double dvx = p->vx-com.vx;
                const double dvy = p->vy-com.vy;
                const double dvz = p->vz-com.vz;
                
                if (tau_a[i]!=0){ 	// Migration
                    double const term = 1/(2.*tau_a[i]);
                    p->ax -=  dvx*term;
                    p->ay -=  dvy*term;
                    p->az -=  dvz*term;
                }
                
                if (tau_e[i]!=0){ 	// Eccentricity damping
                    const double mu = G*(com.m + p->m);
                    const double dx = p->x-com.x;
                    const double dy = p->y-com.y;
                    const double dz = p->z-com.z;
                    
                    const double hx = dy*dvz - dz*dvy;
                    const double hy = dz*dvx - dx*dvz;
                    const double hz = dx*dvy - dy*dvx;
                    const double h = sqrt ( hx*hx + hy*hy + hz*hz );
                    const double v = sqrt ( dvx*dvx + dvy*dvy + dvz*dvz );
                    const double r = sqrt ( dx*dx + dy*dy + dz*dz );
                    const double vr = (dx*dvx + dy*dvy + dz*dvz)/r;
                    const double ex = 1./mu*( (v*v-mu/r)*dx - r*vr*dvx );
                    const double ey = 1./mu*( (v*v-mu/r)*dy - r*vr*dvy );
                    const double ez = 1./mu*( (v*v-mu/r)*dz - r*vr*dvz );
                    const double e = sqrt( ex*ex + ey*ey + ez*ez );		// eccentricity
                    const double a = -mu/( v*v - 2.*mu/r );			// semi major axis, AU
                    
                    //TESTP5m*********************** to get them all starting off in line together
                    /**
                    //if(a < 0.091432 && t > 500 && i==2){
                    if(a < 0.078 && t > 500 && i==2){
                        mig_forces = 0;
                        if(p_suppress == 0) printf("\n\n **migration loop off (abrupt) at t=%f** \n\n",t);
                    }
                    **/
                    const double prefac1 = 1./(1.-e*e) /tau_e[i]/1.5;
                    const double prefac2 = 1./(r*h) * sqrt(mu/a/(1.-e*e))  /tau_e[i]/1.5;
                    p->ax += -dvx*prefac1 + (hy*dz-hz*dy)*prefac2;
                    p->ay += -dvy*prefac1 + (hz*dx-hx*dz)*prefac2;
                    p->az += -dvz*prefac1 + (hx*dy-hy*dx)*prefac2;
                }
            }
            com = tools_get_center_of_mass(com,particles[i]);
        }
    }
    
    //This calculates the tau_e for tides as forces, now that we have the resonance eccentricities
    if(tautide_force_calc == 0 && mig_forces == 0. && tide_force == 1 && tides_on == 1){
        tautide_force_calc = 1; //only do this process once
        struct particle com = particles[0];
        for(int i=1;i<N;i++){
            struct particle* par = &(particles[i]);
            const double m = par->m;
            const double mu = G*(com.m + m);
            const double rp = par->r*0.00464913;       //Rp from Solar Radii to AU
            const double Qp = par->k2/(par->Q);
            
            const double dvx = par->vx-com.vx;
            const double dvy = par->vy-com.vy;
            const double dvz = par->vz-com.vz;
            const double dx = par->x-com.x;
            const double dy = par->y-com.y;
            const double dz = par->z-com.z;
            
            const double v = sqrt ( dvx*dvx + dvy*dvy + dvz*dvz );
            const double r = sqrt ( dx*dx + dy*dy + dz*dz );
            const double vr = (dx*dvx + dy*dvy + dz*dvz)/r;
            const double ex = 1./mu*( (v*v-mu/r)*dx - r*vr*dvx );
            const double ey = 1./mu*( (v*v-mu/r)*dy - r*vr*dvy );
            const double ez = 1./mu*( (v*v-mu/r)*dz - r*vr*dvz );
            const double e = sqrt( ex*ex + ey*ey + ez*ez );   // eccentricity
            const double a = -mu/( v*v - 2.*mu/r );			// semi major axis, AU
            double a5r5 = pow(a/rp, 5);
            
            tidetauinv_e[i] = 1.0/(2./(9*M_PI)*(1./Qp)*sqrt(a*a*a/com.m/com.m/com.m)*a5r5*m);
            //tidetau_a[i] = tidetau_e[i]*K; //Dan uses a K factor instead.
            
            if(p_suppress == 0) printf("planet %i: tau_e,=%.1f Myr, a=%f,e=%f \n",i,1.0/(tidetauinv_e[i]*1e6),a,e);
        }
    }
    
    if(tides_on == 1 && tide_force == 1 && t > tide_delay){
        struct particle com = particles[0]; // calculate add. forces w.r.t. center of mass
        for(int i=1;i<N;i++){
            struct particle* p = &(particles[i]);
            const double dvx = p->vx - com.vx;
            const double dvy = p->vy - com.vy;
            const double dvz = p->vz - com.vz;
            
          //if(i==1){
                /*Papaloizou & Larwood (2000) - Unlike the orbital elements version of tides,
                 tidetau_e already induces an a' (Gold&Schlich2015), and so the tidetau_a is
                 an additional migration on top... don't think I need it. */
                /*
                if (tidetau_a[i] != 0.){
                    p->ax +=  -dvx/(2.*tidetau_a[i]);
                    p->ay +=  -dvy/(2.*tidetau_a[i]);
                    p->az +=  -dvz/(2.*tidetau_a[i]);
                }
                 */
                 
                //Papaloizou & Larwood (2000)
                if (tidetauinv_e[i] != 0. ){ 	// need h and e vectors for both types
                    const double dx = p->x-com.x;
                    const double dy = p->y-com.y;
                    const double dz = p->z-com.z;
                
                    const double rinv = 1/sqrt ( dx*dx + dy*dy + dz*dz );
                    const double vr = (dx*dvx + dy*dvy + dz*dvz)*rinv;
                    const double term = -2.*tidetauinv_e[i]*vr*rinv;
                    
                    p->ax += term*dx;
                    p->ay += term*dy;
                    p->az += term*dz;

                }
                com = tools_get_center_of_mass(com,particles[i]);
            //}
        }
        
        //print message
        if(tide_print == 0 && p_suppress == 0){
            printf("\n\n ***Tides (forces!) have just been turned on at t=%f years***\n\n",t);
            tide_print = 1;
        }
    }
}