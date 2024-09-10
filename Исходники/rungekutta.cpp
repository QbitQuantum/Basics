void RungeKuttaFehlberg::Integrate 
        (void (*Model)(double t, const Vector &y, Vector &yp),
         Vector &y, 
         double &t, double &tout, 
         double relerr, double abserr,
         int &iflag, int maxnfe)
{
    // Get machine epsilon
 
    const double eps = DBL_EPSILON,
                 u26 = 26*eps;
                 
    // remin is the minimum acceptable value of relerr. Attempts
    // to obtain higher accuracy with this subroutine are usually
    // very expensive and often unsuccessful.

    const double remin = 1e-12;

    // The expense is controlled by restricting the number
    // of function evaluations to be approximately maxnfe.
    // The default value of maxnfe = 3000 corresponds to about 500 steps.

    int mflag = abs(iflag);

    // input check parameters

    if (y.Elements() < 1 || relerr < 0.0 || abserr < 0.0 ||  mflag == 0  
        || mflag > InvalidParameters 
        || ((t == tout) && (kflag != SmallRelErrorBound))) {
        iflag = InvalidParameters;
        return;
    }

    double dt,rer,scale,hmin,eeoet,ee,et,esttol,s,ae,tol = 0;
    int output, hfaild, k;

    // references for convenience

    Vector &yp = Work[0],
           &f1 = Work[1],
           &ss = Work[norder+1];

    int lo = y.Lo(), hi = y.Hi();
    
    int gflag = 0;
         
    if (iflag == SmallRelErrorBound
        || (mflag == NormalStep && (init == 0 || kflag == NormalStep))) {
        gflag = Start;
        goto next;
    }

    if (iflag == TooManyIterations 
        || (kflag == TooManyIterations && mflag == NormalStep)) {
        nfe = 0;
        if (mflag != NormalStep) gflag = Start;
        goto next;
    }
        
    if ((kflag == SmallAbsErrorBound && abserr == 0.0)
        || (kflag == MinimumStepReached && relerr < savre && abserr < savae)) {
        iflag = UnsolvableProblem;
        return;
    }
   
  next:

    if (gflag) {
        iflag = jflag;
        if (kflag == SmallRelErrorBound) mflag = abs(iflag);
    }

    jflag = iflag;
    kflag = 0;
    savre = relerr;
    savae = abserr;
    
    // Restrict relative error tolerance to be at least as large as
    // 2*eps+remin to avoid limiting precision difficulties arising
    // from impossible accuracy requests

    rer = 2 * eps + remin;

    // Relative error tolerance is too small

    if (relerr < rer) {
        relerr = rer;
        iflag = kflag = SmallRelErrorBound;
        return;
    }
    
    gflag = 0;
    dt = tout - t;

    if (mflag == Start) {

        // Initialization
        // Set initialization completion indicator, init
        // Set indicator for too many output points,kop
        // Evaluate initial derivatives
        // Set counter for function evaluations,nfe
        // Estimate starting stepsize

        init = 0;
        kop = 0;
        gflag = Start;
        Model(t,y,yp);  // call function
        nfe = 1;
        if (t == tout) {
            iflag = NormalStep;
            return;
        }
    }

    if (init == 0 || gflag) {
        init = 1;
        h = fabs(dt);
        double ypk;
        for (int k = lo; k <= hi; k++) {
            tol = relerr * fabs(y(k)) + abserr;
            if (tol > 0.0) {
                ypk = fabs(yp(k));
                if (ypk * pow(h,order) > tol)
                    h = pow(tol/ypk,iorder);
            }
        }

        if (tol <= 0.0) h = 0.0;
        ypk = MpMax(fabs(dt),fabs(t));
        h = MpMax(h, u26 * ypk);
        jflag = CopySign((int)NormalStep,iflag);
    }

    // Set stepsize for integration in the direction from t to tout

    h = CopySign(h,dt);

    // Test to see if this routine is being severely impacted by too many
    // output points

    if (fabs(h) >= 2*fabs(dt)) kop++;

    if (kop == 100) {
        kop = 0;
        iflag = TooManyCalls;
        return;
    }

    if (fabs(dt) <= u26 * fabs(t)) {

        // If too close to output point,extrapolate and return

        for (int k = lo; k <= hi; k++)
            y(k) += dt * yp(k);

        Model(tout,y,yp);
        nfe++;
        t = tout;
        iflag = NormalStep;
        return;
    }

    // Initialize output point indicator

    output = false;

    // To avoid premature underflow in the error tolerance function,
    // scale the error tolerances

    scale = 2.0 / relerr;
    ae = scale * abserr; 

    // Step by step integration - as an endless loop over steps

    for (;;) { 

        hfaild = 0;

        // Set smallest allowable stepsize

        hmin = u26 * fabs(t);

        // Adjust stepsize if necessary to hit the output point.
        // Look ahead two steps to avoid drastic changes in the stepsize and
        // thus lessen the impact of output points on the code.

        dt = tout - t;
        if (fabs(dt) < 2 * fabs(h)) {
            if (fabs(dt) <= fabs(h)) {

                // The next successful step will complete the 
                // integration to the output point

                output = true;
                h = dt;
            } else
                h = 0.5 * dt;
        }

        // Core integrator for taking a single step
        //
        // The tolerances have been scaled to avoid premature underflow in
        // computing the error tolerance function et.
        // To avoid problems with zero crossings, relative error is measured
        // using the average of the magnitudes of the solution at the
        // beginning and end of a step.
        // The error estimate formula has been grouped to control loss of
        // significance.
        // To distinguish the various arguments, h is not permitted
        // to become smaller than 26 units of roundoff in t.
        // Practical limits on the change in the stepsize are enforced to
        // smooth the stepsize selection process and to avoid excessive
        // chattering on problems having discontinuities.
        // To prevent unnecessary failures, the code uses 9/10 the stepsize
        // it estimates will succeed.
        // After a step failure, the stepsize is not allowed to increase for
        // the next attempted step. This makes the code more efficient on
        // problems having discontinuities and more effective in general
        // since local extrapolation is being used and extra caution seems
        // warranted.
        //
        // Test number of derivative function evaluations.
        // If okay,try to advance the integration from t to t+h
        
        if (nfe > maxnfe) {

            // Too much work

            iflag = kflag = TooManyIterations;
            return;
        }
        
    step:

        // Advance an approximate solution over one step of length h

        RungeKuttaStep(Model,y,t,h,ss);
        
        for (int i = lo; i <= hi; i++) f1(i) = ss(i);
        nfe += norder;

        // Compute and test allowable tolerances versus local error estimates
        // and remove scaling of tolerances. note that relative error is
        // measured with respect to the average of the magnitudes of the
        // solution at the beginning and end of the step.
        
        eeoet = 0.0;
        for (k = lo; k <= hi; k++) {

            et = fabs(y(k)) + fabs(f1(k)) + ae;

            // Inappropriate error tolerance

            if (et <= 0.0) {
                iflag = SmallAbsErrorBound;
                return;
            }
            
            ee = fabs( ErrorTerm(k) );
            eeoet = MpMax(eeoet,ee/et);
        }
        
        esttol = fabs(h) * eeoet * scale;
        
        if (esttol > 1.0) {

            // Unsuccessful step
            // Reduce the stepsize , try again
            // The decrease is limited to a factor of 1/10

            hfaild = true;
            output = false;
            s = 0.1;
            if (esttol < crit) s = 0.9 / pow(esttol,iorder);
            h *= s;
            if (fabs(h) > hmin) goto step; // loop

            // Requested error unattainable at smallest allowable stepsize

            iflag = kflag = MinimumStepReached;
            return;
        }

        // Successful step
        // Store solution at t+h and evaluate derivatives there

        t += h;
        for (k = lo; k <= hi; k++) y(k) = f1(k);

        Model(t,y,yp);
        nfe++;

        // Choose next stepsize
        // The increase is limited to a factor of 5
        // if step failure has just occurred, next
        // stepsize is not allowed to increase
        
        s = 5.0;
        if (esttol > criti) s = 0.9 / pow(esttol,iorder);
        if (hfaild) s = MpMin(1.0,s);
        h = CopySign(MpMax(hmin,s*fabs(h)),h);
        
        // End of core integrator

        if (output) {
            t = tout;
            iflag = NormalStep;
            return;
        }

        if (iflag <= 0) {

             // one-step mode

            iflag = SingleStep;
            return;
        }
        
    } // for (;;)
}