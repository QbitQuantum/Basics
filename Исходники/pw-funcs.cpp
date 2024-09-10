Piecewise<SBasis> log(Interval in) {
    Piecewise<SBasis> I = integral(Geom::reciprocal(Linear(in.min(), in.max())));
    return I + Piecewise<SBasis> (-I.segs[0][0] + log(in.min()));
}