 void SBAutoCorrelate::SBAutoCorrelateImpl::fillKValue(
     tmv::MatrixView<std::complex<double> > val,
     double x0, double dx, double dxy,
     double y0, double dy, double dyx) const
 {
     dbg<<"SBCorrelate fillKValue\n";
     dbg<<"x = "<<x0<<" + ix * "<<dx<<" + iy * "<<dxy<<std::endl;
     dbg<<"y = "<<y0<<" + ix * "<<dyx<<" + iy * "<<dy<<std::endl;
     GetImpl(_adaptee)->fillKValue(val,x0,dx,dxy,y0,dy,dyx);
     val = ElemProd(val,val.conjugate());
 }