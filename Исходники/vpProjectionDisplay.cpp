void
vpProjectionDisplay::displayCamera(vpImage<unsigned char> &I,
                                   const vpHomogeneousMatrix &cextMo,
                                   const vpHomogeneousMatrix &cMo,
                                   const vpCameraParameters &cam,
                                   const unsigned int thickness)
{
  vpHomogeneousMatrix c1Mc ;
  c1Mc = cextMo*cMo.inverse() ;

  o.track(c1Mc) ;

  if(o.get_Z() < 0)	// do not print camera if behind the external camera
	  return;

  x.track(c1Mc) ;
  y.track(c1Mc) ;
  z.track(c1Mc) ;

  vpImagePoint ipo;
  vpImagePoint ipx;

  vpMeterPixelConversion::convertPoint(cam, o.p[0], o.p[1], ipo) ;

  vpMeterPixelConversion::convertPoint(cam, x.p[0], x.p[1], ipx) ;
  vpDisplay::displayArrow(I, ipo, ipx, vpColor::green, 4+thickness, 2+thickness, thickness) ;

  vpMeterPixelConversion::convertPoint(cam, y.p[0], y.p[1], ipx) ;
  vpDisplay::displayArrow(I, ipo, ipx, vpColor::blue, 4+thickness, 2+thickness, thickness) ;

  vpMeterPixelConversion::convertPoint(cam, z.p[0], z.p[1], ipx) ;
  vpDisplay::displayArrow(I, ipo, ipx, vpColor::red, 4+thickness, 2+thickness, thickness) ;
}