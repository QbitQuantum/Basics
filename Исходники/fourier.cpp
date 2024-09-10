void Fourier( AbstractBlockDistMatrix<Complex<Real>>& A, Int n )
{
    DEBUG_ONLY(CallStackEntry cse("Fourier"))
    A.Resize( n, n );
    const Real pi = 4*Atan( Real(1) );
    const Real nSqrt = Sqrt( Real(n) );
    auto fourierFill = 
      [=]( Int i, Int j ) -> Complex<Real>
      { const Real theta = -2*pi*i*j/n;
        return Complex<Real>(Cos(theta),Sin(theta))/nSqrt; };
    IndexDependentFill( A, function<Complex<Real>(Int,Int)>(fourierFill) );
}