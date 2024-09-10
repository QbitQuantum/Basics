double SurfaceFit::PolynomFit()
{
    if (PlaneFit::Fit() == FLOAT_MAX)
        return FLOAT_MAX;

    Base::Vector3d bs(this->_vBase.x,this->_vBase.y,this->_vBase.z);
    Base::Vector3d ex(this->_vDirU.x,this->_vDirU.y,this->_vDirU.z);
    Base::Vector3d ey(this->_vDirV.x,this->_vDirV.y,this->_vDirV.z);
    Base::Vector3d ez(this->_vDirW.x,this->_vDirW.y,this->_vDirW.z);

    // A*x = b
    // See also www.cs.jhu.edu/~misha/Fall05/10.23.05.pdf
    // z = f(x,y) = a*x^2 + b*y^2 + c*x*y + d*x + e*y + f
    // z = P * Vi with Vi=(xi^2,yi^2,xiyi,xi,yi,1) and P=(a,b,c,d,e,f)
    // To get the best-fit values the sum needs to be minimized:
    // S = sum[(z-zi)^2} -> min with zi=z coordinates of the given points
    // <=> S = sum[z^2 - 2*z*zi + zi^2] -> min
    // <=> S(P) = sum[(P*Vi)^2 - 2*(P*Vi)*zi + zi^2] -> min
    // To get the optimum the gradient of the expression must be the null vector
    // Note: grad F(P) = (P*Vi)^2 = 2*(P*Vi)*Vi
    //       grad G(P) = -2*(P*Vi)*zi = -2*Vi*zi
    //       grad H(P) = zi^2 = 0
    //  => grad S(P) = sum[2*(P*Vi)*Vi - 2*Vi*zi] = 0
    // <=> sum[(P*Vi)*Vi] = sum[Vi*zi]
    // <=> sum[(Vi*Vi^t)*P] = sum[Vi*zi] where (Vi*Vi^t) is a symmetric matrix
    // <=> sum[(Vi*Vi^t)]*P = sum[Vi*zi]
    Eigen::Matrix<double,6,6> A = Eigen::Matrix<double,6,6>::Zero();
    Eigen::Matrix<double,6,1> b = Eigen::Matrix<double,6,1>::Zero();
    Eigen::Matrix<double,6,1> x = Eigen::Matrix<double,6,1>::Zero();

    std::vector<Base::Vector3d> transform;
    transform.reserve(_vPoints.size());

    double dW2 = 0;
    for (std::list<Base::Vector3f>::const_iterator it = _vPoints.begin(); it != _vPoints.end(); ++it) {
        Base::Vector3d clPoint(it->x,it->y,it->z);
        clPoint.TransformToCoordinateSystem(bs, ex, ey);
        transform.push_back(clPoint);
        double dU = clPoint.x;
        double dV = clPoint.y;
        double dW = clPoint.z;

        double dU2 = dU*dU;
        double dV2 = dV*dV;
        double dUV = dU*dV;

        dW2 += dW*dW;

        A(0,0) = A(0,0) + dU2*dU2;
        A(0,1) = A(0,1) + dU2*dV2;
        A(0,2) = A(0,2) + dU2*dUV;
        A(0,3) = A(0,3) + dU2*dU ;
        A(0,4) = A(0,4) + dU2*dV ;
        A(0,5) = A(0,5) + dU2    ;
        b(0)   = b(0)   + dU2*dW ;

        A(1,1) = A(1,1) + dV2*dV2;
        A(1,2) = A(1,2) + dV2*dUV;
        A(1,3) = A(1,3) + dV2*dU ;
        A(1,4) = A(1,4) + dV2*dV ;
        A(1,5) = A(1,5) + dV2    ;
        b(1)   = b(1)   + dV2*dW ;

        A(2,2) = A(2,2) + dUV*dUV;
        A(2,3) = A(2,3) + dUV*dU ;
        A(2,4) = A(2,4) + dUV*dV ;
        A(2,5) = A(2,5) + dUV    ;
        b(3)   = b(3)   + dUV*dW ;

        A(3,3) = A(3,3) + dU *dU ;
        A(3,4) = A(3,4) + dU *dV ;
        A(3,5) = A(3,5) + dU     ;
        b(3)   = b(3)   + dU *dW ;

        A(4,4) = A(4,4) + dV *dV ;
        A(4,5) = A(4,5) + dV     ;
        b(5)   = b(5)   + dV *dW ;

        A(5,5) = A(5,5) + 1      ;
        b(5)   = b(5)   + 1  *dW ;
    }

    // Mat is symmetric
    //
    A(1,0) = A(0,1);
    A(2,0) = A(0,2);
    A(3,0) = A(0,3);
    A(4,0) = A(0,4);
    A(5,0) = A(0,5);

    A(2,1) = A(1,2);
    A(3,1) = A(1,3);
    A(4,1) = A(1,4);
    A(5,1) = A(1,5);

    A(3,2) = A(2,3);
    A(4,2) = A(2,4);
    A(5,2) = A(2,5);

    A(4,3) = A(3,4);
    A(5,3) = A(3,5);

    A(5,4) = A(4,5);

    Eigen::HouseholderQR< Eigen::Matrix<double,6,6> > qr(A);
    x = qr.solve(b);

    // FunctionContainer gets an implicit function F(x,y,z) = 0 of this form
    // _fCoeff[0] +
    // _fCoeff[1]*x   + _fCoeff[2]*y   + _fCoeff[3]*z   +
    // _fCoeff[4]*x^2 + _fCoeff[5]*y^2 + _fCoeff[6]*z^2 +
    // _fCoeff[7]*x*y + _fCoeff[8]*x*z + _fCoeff[9]*y*z
    //
    // The bivariate polynomial surface we get here is of the form
    // z = f(x,y) = a*x^2 + b*y^2 + c*x*y + d*x + e*y + f
    // Writing it as implicit surface F(x,y,z) = 0 gives this form
    // F(x,y,z) = f(x,y) - z = a*x^2 + b*y^2 + c*x*y + d*x + e*y - z + f
    // Thus:
    // _fCoeff[0] = f
    // _fCoeff[1] = d
    // _fCoeff[2] = e
    // _fCoeff[3] = -1
    // _fCoeff[4] = a
    // _fCoeff[5] = b
    // _fCoeff[6] = 0
    // _fCoeff[7] = c
    // _fCoeff[8] = 0
    // _fCoeff[9] = 0

    _fCoeff[0] = x(5);
    _fCoeff[1] = x(3);
    _fCoeff[2] = x(4);
    _fCoeff[3] = -1.0;
    _fCoeff[4] = x(0);
    _fCoeff[5] = x(1);
    _fCoeff[6] =  0.0;
    _fCoeff[7] = x(2);
    _fCoeff[8] =  0.0;
    _fCoeff[9] =  0.0;

    // Get S(P) = sum[(P*Vi)^2 - 2*(P*Vi)*zi + zi^2]
    double sigma = 0;
    FunctionContainer clFuncCont(_fCoeff);
    for (std::vector<Base::Vector3d>::const_iterator it = transform.begin(); it != transform.end(); ++it) {
        double u = it->x;
        double v = it->y;
        double z = clFuncCont.F(u, v, 0.0);
        sigma += z*z;
    }

    sigma += dW2 - 2 * x.dot(b);
    // This must be caused by some round-off errors. Theoretically it's impossible
    // that 'sigma' becomes negative.
    if (sigma < 0)
        sigma = 0;
    if (!_vPoints.empty())
        sigma = sqrt(sigma/_vPoints.size());

    _fLastResult = static_cast<float>(sigma);
    return _fLastResult;
}