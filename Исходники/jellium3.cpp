    double lr_event_rate (const vector <DIM> &r_, unsigned direction)
    {
        const double L = period[direction];
        const vector <DIM> shift = unit_vector <DIM> (direction) * (L/2);

        // assign polar pair partner
        const double x_prim = r_[direction];
        const double x_pair = x_prim - 2*L * floor (x_prim/L) - L;

        bool first_copy = fabs (x_prim - x_pair) < 2*L;
        vector <DIM> r[2] = { r_, r_ };
        if (x_prim >= 0.)
            r[0][direction] = x_pair;
        else
            r[1][direction] = x_pair;
        double rsq[2] = { norm_sq (r[0]), norm_sq (r[1]) };

        assert (r[0][direction] < 0.);
        assert (r[1][direction] >= 0.);

        // compute the rate for the polar pair
        double rate = 0.;

        // for large distances, the naive formula for the event rate can be
        // numerically problematic.
        if (fmax (rsq[0], rsq[1]) < 1e6*L*L)
        {
            for (int i = 0; i != 2; ++i)
            {
                double x = r[i][direction];

                double u_rp = (i==0 && first_copy)
                    ? 0.
                    : unit_potential (r[i] + shift);
                double u_rm = (i==1 && first_copy)
                    ? 0.
                    : unit_potential (r[i] - shift);

                rate += (u_rp-u_rm) / L;

                // main charge -- parts smaller than sr_lr_split are handled by the SR code
                if (rsq[i] > sq (sr_lr_split))
                    rate += unit_directional_derivative (x, rsq[i]);
            }
        }
        else if (fmax (rsq[0], rsq[1]) < 1e20*L*L)
        {
            for (int i = 0; i != 2; ++i)
            {
                double x = r[i][direction];
                // avoid catastrophic cancellation in the far field
                // (valid also for exponent = 0)
                rate += x * pow (rsq[i], -.5*6. -.5*exponent) * L*L
                    * (2+exponent) * (1./24) * (3.*rsq[i] - (4+exponent)*x*x);
            }
        }
        else
        {
            // rate < numerical precision
        }

        // asymptotic decay of particle event rate is ~ 1 / r^(n+4).
        double w = (r[0][direction] == r_[direction])
            ? norm_sq (r[1]) / norm_sq (r[0])
            : norm_sq (r[0]) / norm_sq (r[1]);

        rate /= 1 + pow (w, -.5 * (exponent+4.));

        if (rate <= 0.)
            return 0.;
        else
            return stren * rate;
    }