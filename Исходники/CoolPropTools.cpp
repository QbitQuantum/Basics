void solve_cubic(double a, double b, double c, double d, int &N, double &x0, double &x1, double &x2)
{
    // 0 = ax^3 + b*x^2 + c*x + d
    
    // First check if the "cubic" is actually a second order or first order curve
    if (std::abs(a) < 10*DBL_EPSILON){
        if (std::abs(b) < 10*DBL_EPSILON){
            // Linear solution if a = 0 and b = 0
            x0 = -d/c;
            N = 1;
            return;
        }
        else{
            // Quadratic solution(s) if a = 0 and b != 0
            x0 = (-c+sqrt(c*c-4*b*d))/(2*b);
            x1 = (-c-sqrt(c*c-4*b*d))/(2*b);
            N = 2;
            return;
        }
    }
    
    // Ok, it is really a cubic

    // Discriminant
    double DELTA = 18*a*b*c*d-4*b*b*b*d+b*b*c*c-4*a*c*c*c-27*a*a*d*d;
    // Coefficients for the depressed cubic t^3+p*t+q = 0
    double p = (3*a*c-b*b)/(3*a*a);
    double q = (2*b*b*b-9*a*b*c+27*a*a*d)/(27*a*a*a);

    if (DELTA<0)
    {
        // One real root
        double t0;
        if (4*p*p*p+27*q*q>0 && p<0)
        {
            t0 = -2.0*std::abs(q)/q*sqrt(-p/3.0)*cosh(1.0/3.0*acosh(-3.0*std::abs(q)/(2.0*p)*sqrt(-3.0/p)));
        }
        else
        {
            t0 = -2.0*sqrt(p/3.0)*sinh(1.0/3.0*asinh(3.0*q/(2.0*p)*sqrt(3.0/p)));
        }
        N = 1;
        x0 = t0-b/(3*a);
        x1 = t0-b/(3*a);
        x2 = t0-b/(3*a);
    }
    else //(DELTA>0)
    {
        // Three real roots
        double t0 = 2.0*sqrt(-p/3.0)*cos(1.0/3.0*acos(3.0*q/(2.0*p)*sqrt(-3.0/p))-0*2.0*M_PI/3.0);
        double t1 = 2.0*sqrt(-p/3.0)*cos(1.0/3.0*acos(3.0*q/(2.0*p)*sqrt(-3.0/p))-1*2.0*M_PI/3.0);
        double t2 = 2.0*sqrt(-p/3.0)*cos(1.0/3.0*acos(3.0*q/(2.0*p)*sqrt(-3.0/p))-2*2.0*M_PI/3.0);

        N = 3;
        x0 = t0-b/(3*a);
        x1 = t1-b/(3*a);
        x2 = t2-b/(3*a);
    }
}