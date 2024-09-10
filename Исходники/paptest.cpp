Geom::Piecewise<Geom::D2<Geom::SBasis> >
doEffect_pwd2 (Geom::Piecewise<Geom::D2<Geom::SBasis> > & pwd2_in, Geom::Piecewise<Geom::D2<Geom::SBasis> > & pattern)
{
    using namespace Geom;

    Piecewise<D2<SBasis> > uskeleton = arc_length_parametrization(pwd2_in, 2, .1);
    uskeleton = remove_short_cuts(uskeleton,.01);
    Piecewise<D2<SBasis> > n = rot90(derivative(uskeleton));
    n = force_continuity(remove_short_cuts(n,.1));

    D2<Piecewise<SBasis> > patternd2 = make_cuts_independent(pattern);
    Piecewise<SBasis> x = Piecewise<SBasis>(patternd2[0]);
    Piecewise<SBasis> y = Piecewise<SBasis>(patternd2[1]);
    Interval pattBnds = *bounds_exact(x);
    x -= pattBnds.min();
    Interval pattBndsY = *bounds_exact(y);
    y -= (pattBndsY.max()+pattBndsY.min())/2;

    int nbCopies = int(uskeleton.cuts.back()/pattBnds.extent());
    double scaling = 1;

    double pattWidth = pattBnds.extent() * scaling;

    if (scaling != 1.0) {
        x*=scaling;
    }

    double offs = 0;
    Piecewise<D2<SBasis> > output;
    for (int i=0; i<nbCopies; i++){
        output.concat(compose(uskeleton,x+offs)+y*compose(n,x+offs));
        offs+=pattWidth;
    }

    return output;
}