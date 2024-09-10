Crossings mono_intersect(Curve const & A, Interval const &Ad,
                         Curve const & B, Interval const &Bd) {
    Crossings ret;
    mono_intersect(A, Ad.min(), Ad.max(), B, Bd.min(), Bd.max(), ret);
    return ret;
}