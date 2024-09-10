void Bubble:: map_peanut( const Vertex &center, Real radius, Real alpha )
{
    assert(lambda>0);
    empty();
    alpha = clamp<Real>(0,Fabs(alpha),1);
    const Real b = Fabs(radius);
    const Real a = alpha * b;
    const Real a2 = a*a;
    const Real b2 = b*b;
    const Real a4 = a2*a2;
    const Real b4 = b2*b2;
    const Real   theta_max = 2 * atan( lambda/(radius+radius) );
    const size_t nmin      = 2*max_of<size_t>(3,size_t( ceil( numeric<Real>::two_pi/theta_max) ));
    const Real   dtheta    = numeric<Real>::two_pi / nmin;
    
    fprintf( stderr, "peanut @(%g,%g), b=%g, a=%g\n", center.x, center.y, b, a ); 
    
    for( size_t i=0; i < nmin; ++i )
    {
        const Real   theta = i * dtheta;;
        const Real   t2    = theta+theta; 
        Tracer      *p     = append();
        const Real   S     = Sin(t2);
        const  Real  c1    = max_of<Real>(0,b4 - a4 * S*S );
        const  Real  C     = max_of<Real>(0,a2 * Cos( t2 ) + Sqrt(c1));
        const  Real  rho   = Sqrt(C);
        p->vertex.x = center.x + rho * Cos( theta );
        p->vertex.y = center.y + rho * Sin( theta );
    }
    raw_initialize();    
}