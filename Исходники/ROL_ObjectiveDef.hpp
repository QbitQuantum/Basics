std::vector<Real> Objective<Real>::checkHessSym( const Vector<Real> &x,
                                                 const Vector<Real> &hv,
                                                 const Vector<Real> &v,
                                                 const Vector<Real> &w,
                                                 const bool printToStream,
                                                 std::ostream & outStream ) {

  Real tol = std::sqrt(ROL_EPSILON);
  
  // Compute (Hessian at x) times (vector v).
  Teuchos::RCP<Vector<Real> > h = hv.clone();
  this->hessVec(*h, v, x, tol);
  Real wHv = w.dot(h->dual());

  this->hessVec(*h, w, x, tol);
  Real vHw = v.dot(h->dual());

  std::vector<Real> hsymCheck(3, 0);

  hsymCheck[0] = wHv;
  hsymCheck[1] = vHw;
  hsymCheck[2] = std::abs(vHw-wHv);

  // Save the format state of the original outStream.
  Teuchos::oblackholestream oldFormatState;
  oldFormatState.copyfmt(outStream);

  if (printToStream) {
    outStream << std::right
              << std::setw(20) << "<w, H(x)v>"
              << std::setw(20) << "<v, H(x)w>"
              << std::setw(20) << "abs error"
              << "\n";
    outStream << std::scientific << std::setprecision(11) << std::right
              << std::setw(20) << hsymCheck[0]
              << std::setw(20) << hsymCheck[1]
              << std::setw(20) << hsymCheck[2]
              << "\n";
  }

  // Reset format state of outStream.
  outStream.copyfmt(oldFormatState);

  return hsymCheck;

} // checkHessSym