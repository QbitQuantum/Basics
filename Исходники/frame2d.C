void
Frame2d::set_angle( const Angle & a )
{
    n_x = a.cos() * scale;
    n_y = a.sin() * scale;
    //f1.n_y= sqrt(1-f1.n_x*f1.n_x);
}