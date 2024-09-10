//===========================================================================
shared_ptr<Circle> Torus::getMinorCircle(double upar) const
//===========================================================================
{
    Point udir = cos(upar) * x_axis_ + sin(upar) * y_axis_;
    Point centre = location_ + major_radius_ * udir;
    Point newz = udir.cross(z_axis_);
    shared_ptr<Circle> circle(new Circle(minor_radius_, centre,
					 newz, udir));
    double vmin = domain_.vmin();
    double vmax = domain_.vmax();
    circle->setParamBounds(vmin, vmax);
    return circle;
}