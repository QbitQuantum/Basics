static double find_inverse_gamma(double a, double p, double q)
{
    /*
     * In order to understand what's going on here, you will
     * need to refer to:
     *
     * Computation of the Incomplete Gamma Function Ratios and their Inverse
     * ARMIDO R. DIDONATO and ALFRED H. MORRIS, JR.
     * ACM Transactions on Mathematical Software, Vol. 12, No. 4,
     * December 1986, Pages 377-393.
     */
    double result;

    if (a == 1) {
        if (q > 0.9) {
            result = -log1p(-p);
        }
        else {
            result = -log(q);
        }
    }
    else if (a < 1) {
        double g = Gamma(a);
        double b = q * g;

        if ((b > 0.6) || ((b >= 0.45) && (a >= 0.3))) {
            /* DiDonato & Morris Eq 21:
             *
             * There is a slight variation from DiDonato and Morris here:
             * the first form given here is unstable when p is close to 1,
             * making it impossible to compute the inverse of Q(a,x) for small
             * q. Fortunately the second form works perfectly well in this case.
             */
            double u;
            if((b * q > 1e-8) && (q > 1e-5)) {
                u = pow(p * g * a, 1 / a);
            }
            else {
                u = exp((-q / a) - NPY_EULER);
            }
            result = u / (1 - (u / (a + 1)));
        }
        else if ((a < 0.3) && (b >= 0.35)) {
            /* DiDonato & Morris Eq 22: */
            double t = exp(-NPY_EULER - b);
            double u = t * exp(t);
            result = t * exp(u);
        }
        else if ((b > 0.15) || (a >= 0.3)) {
            /* DiDonato & Morris Eq 23: */
            double y = -log(b);
            double u = y - (1 - a) * log(y);
            result = y - (1 - a) * log(u) - log(1 + (1 - a) / (1 + u));
        }
        else if (b > 0.1) {
            /* DiDonato & Morris Eq 24: */
            double y = -log(b);
            double u = y - (1 - a) * log(y);
            result = y - (1 - a) * log(u)
                - log((u * u + 2 * (3 - a) * u + (2 - a) * (3 - a))
                      / (u * u + (5 - a) * u + 2));
        }
        else {
            /* DiDonato & Morris Eq 25: */
            double y = -log(b);
            double c1 = (a - 1) * log(y);
            double c1_2 = c1 * c1;
            double c1_3 = c1_2 * c1;
            double c1_4 = c1_2 * c1_2;
            double a_2 = a * a;
            double a_3 = a_2 * a;

            double c2 = (a - 1) * (1 + c1);
            double c3 = (a - 1) * (-(c1_2 / 2)
                                   + (a - 2) * c1
                                   + (3 * a - 5) / 2);
            double c4 = (a - 1) * ((c1_3 / 3) - (3 * a - 5) * c1_2 / 2
                                   + (a_2 - 6 * a + 7) * c1
                                   + (11 * a_2 - 46 * a + 47) / 6);
            double c5 = (a - 1) * (-(c1_4 / 4)
                                   + (11 * a - 17) * c1_3 / 6
                                   + (-3 * a_2 + 13 * a -13) * c1_2
                                   + (2 * a_3 - 25 * a_2 + 72 * a - 61) * c1 / 2
                                   + (25 * a_3 - 195 * a_2 + 477 * a - 379) / 12);

            double y_2 = y * y;
            double y_3 = y_2 * y;
            double y_4 = y_2 * y_2;
            result = y + c1 + (c2 / y) + (c3 / y_2) + (c4 / y_3) + (c5 / y_4);
        }
    }
    else {
        /* DiDonato and Morris Eq 31: */
        double s = find_inverse_s(p, q);

        double s_2 = s * s;
        double s_3 = s_2 * s;
        double s_4 = s_2 * s_2;
        double s_5 = s_4 * s;
        double ra = sqrt(a);

        double w = a + s * ra + (s_2 - 1) / 3;
        w += (s_3 - 7 * s) / (36 * ra);
        w -= (3 * s_4 + 7 * s_2 - 16) / (810 * a);
        w += (9 * s_5 + 256 * s_3 - 433 * s) / (38880 * a * ra);

        if ((a >= 500) && (fabs(1 - w / a) < 1e-6)) {
            result = w;
        }
        else if (p > 0.5) {
            if (w < 3 * a) {
                result = w;
            }
            else {
                double D = fmax(2, a * (a - 1));
                double lg = lgam(a);
                double lb = log(q) + lg;
                if (lb < -D * 2.3) {
                    /* DiDonato and Morris Eq 25: */
                    double y = -lb;
                    double c1 = (a - 1) * log(y);
                    double c1_2 = c1 * c1;
                    double c1_3 = c1_2 * c1;
        	    double c1_4 = c1_2 * c1_2;
		    double a_2 = a * a;
		    double a_3 = a_2 * a;

		    double c2 = (a - 1) * (1 + c1);
		    double c3 = (a - 1) * (-(c1_2 / 2)
					   + (a - 2) * c1
					   + (3 * a - 5) / 2);
		    double c4 = (a - 1) * ((c1_3 / 3)
					   - (3 * a - 5) * c1_2 / 2
					   + (a_2 - 6 * a + 7) * c1
					   + (11 * a_2 - 46 * a + 47) / 6);
		    double c5 = (a - 1) * (-(c1_4 / 4)
					   + (11 * a - 17) * c1_3 / 6
					   + (-3 * a_2 + 13 * a -13) * c1_2
					   + (2 * a_3 - 25 * a_2 + 72 * a - 61) * c1 / 2
					   + (25 * a_3 - 195 * a_2 + 477 * a - 379) / 12);

		    double y_2 = y * y;
		    double y_3 = y_2 * y;
		    double y_4 = y_2 * y_2;
		    result = y + c1 + (c2 / y) + (c3 / y_2) + (c4 / y_3) + (c5 / y_4);
		}
		else {
		    /* DiDonato and Morris Eq 33: */
		    double u = -lb + (a - 1) * log(w) - log(1 + (1 - a) / (1 + w));
		    result = -lb + (a - 1) * log(u) - log(1 + (1 - a) / (1 + u));
		}
	    }
	}
	else {
	    double z = w;
	    double ap1 = a + 1;
	    double ap2 = a + 2;
	    if (w < 0.15 * ap1) {
		/* DiDonato and Morris Eq 35: */
		double v = log(p) + lgam(ap1);
		z = exp((v + w) / a);
		s = log1p(z / ap1 * (1 + z / ap2));
		z = exp((v + z - s) / a);
		s = log1p(z / ap1 * (1 + z / ap2));
		z = exp((v + z - s) / a);
		s = log1p(z / ap1 * (1 + z / ap2 * (1 + z / (a + 3))));
		z = exp((v + z - s) / a);
	    }

	    if ((z <= 0.01 * ap1) || (z > 0.7 * ap1)) {
		result = z;
	    }
	    else {
		/* DiDonato and Morris Eq 36: */
		double ls = log(didonato_SN(a, z, 100, 1e-4));
		double v = log(p) + lgam(ap1);
		z = exp((v + z - ls) / a);
		result = z * (1 - (a * log(z) - z - v + ls) / (a - z));
	    }
	}
    }
    return result;
}