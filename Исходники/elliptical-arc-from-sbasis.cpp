bool make_elliptical_arc::make_elliptiarc()
{
    const NL::Vector & coeff = fitter.result();
    Ellipse e;
    try
    {
        e.setCoefficients(1, coeff[0], coeff[1], coeff[2], coeff[3], coeff[4]);
    }
    catch(LogicalError const &exc)
    {
        return false;
    }

    Point inner_point = curve(0.5);

#ifdef CPP11
    std::unique_ptr<EllipticalArc> arc( e.arc(initial_point, inner_point, final_point) );
#else
    std::auto_ptr<EllipticalArc> arc( e.arc(initial_point, inner_point, final_point) );
#endif
    ea = *arc;

    if ( !are_near( e.center(),
                    ea.center(),
                    tol_at_center * std::min(e.ray(X),e.ray(Y))
                  )
       )
    {
        return false;
    }
    return true;
}