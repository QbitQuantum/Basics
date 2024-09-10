/**
 * returns the spherical Bessel function of the second kind
 * needed for continuum states
 \param l = order of the function (orbital angular momentum)
 \param rho = independent variable (rho = k * r)
 */
double sphericalB::y(int l, double rho)
{
  switch (l)
    {
    case 0:
      return y0(rho);
    case 1:
      return y1(rho);
    case 2: 
      return y2(rho);
    case 3: 
      return y3(rho);
    case 4:
      return y4(rho);
    case 5:
      return y5(rho);
    case 6:
      return y6(rho);
    case 7:
      return y7(rho);
    default:
      cout << "no l>6 programed in sphericalB" << endl;
      return 0.;
    }
}