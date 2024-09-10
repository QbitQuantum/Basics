    double estimate(const std::vector<int>& c, int& outerLoopIterationsCount, int& innerLoop1IterationsCount, int& innerLoop2IterationsCount, int& logEvaluationCount) const {

        outerLoopIterationsCount = 0;
        innerLoop1IterationsCount = 0;
        innerLoop2IterationsCount = 0;
        logEvaluationCount = 0;

        if (c[q+1] == m) return std::numeric_limits<double>::infinity();

        int kMin, kMax;

        for(kMin=0; c[kMin]==0; ++kMin);
        int kMinPrime = std::max(1, kMin);

        for(kMax=q+1; c[kMax]==0; --kMax);
        int kMaxPrime = std::min(q, kMax);

        double z = 0.;
        for (int k = kMaxPrime; k >= kMinPrime; --k) {
            z = 0.5*z + c[k];
        }
        z = ldexp(z, -kMinPrime);

        int cPrime = c[q+1];
        if (q >= 1) {
            cPrime += c[kMaxPrime];
        }

        double gPrevious = 0;

        double x;
        double a = z + c[0];
        int mPrime = m - c[0];
        {
            double b = z + ldexp(c[q+1], -q);
            if (b <= 1.5*a) {
                x = mPrime/(0.5*b+a);
            }
            else {
                x = (mPrime/b)*log1p(b/a);
                logEvaluationCount += 1;
            }
        }

        double deltaX = x;
        while(deltaX > x*relativeErrorLimit) {
            int kappaMinus1;
            frexp(x, &kappaMinus1);
            double xPrime = ldexp(x, -std::max(kMaxPrime+1, kappaMinus1+2));
            double xPrime2 = xPrime*xPrime;
            double h = xPrime - xPrime2/3 + (xPrime2*xPrime2)*(1./45. - xPrime2/472.5);
            for (int k = kappaMinus1; k >= kMaxPrime; --k) {
                double hPrime = 1. - h;
                h = (xPrime + h*hPrime)/(xPrime+hPrime);
                xPrime += xPrime;
                innerLoop1IterationsCount += 1;
            }
            double g = cPrime*h;
            for (int k = kMaxPrime-1; k >= kMinPrime; --k) {
                double hPrime = 1. - h;
                h = (xPrime + h*hPrime)/(xPrime+hPrime);
                xPrime += xPrime;
                g += c[k] * h;
                innerLoop2IterationsCount += 1;
            }
            g += x*a;
            if (gPrevious < g && g <= mPrime) {
                deltaX *= (g-mPrime)/(gPrevious-g);
            }
            else {
                deltaX = 0;
            }
            x += deltaX;
            gPrevious = g;
            outerLoopIterationsCount += 1;
        }
        return x*m;
    }