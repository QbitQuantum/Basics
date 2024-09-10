Curve *EllipticalArc::transformed(Affine const& m) const
{
    Ellipse e(center(X), center(Y), ray(X), ray(Y), _rot_angle);
    Ellipse et = e.transformed(m);
    Point inner_point = pointAt(0.5);
    return et.arc( initialPoint() * m,
                                  inner_point * m,
                                  finalPoint() * m,
                                  isSVGCompliant() );
}