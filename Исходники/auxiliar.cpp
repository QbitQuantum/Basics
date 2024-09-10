MatrixXd der_logarithm_map(Matrix4d T)
{

    MatrixXd dlogT_dT = MatrixXd::Zero(6,12);

    // Approximate derivative of the logarithm_map wrt the transformation matrix
    Matrix3d L1 = Matrix3d::Zero();
    Matrix3d L2 = Matrix3d::Zero();
    Matrix3d L3 = Matrix3d::Zero();
    Matrix3d Vinv = Matrix3d::Identity();
    Vector6d x = logmap_se3(T);

    // estimates the cosine, sine, and theta
    double b;
    double cos_ = 0.5 * (T.block(0,0,3,3).trace() - 1.0 );
    if(cos_ > 1.f)
        cos_ = 1.f;
    else if (cos_ < -1.f)
        cos_ = -1.f;
    double theta  = acos(cos_);
    double theta2 = theta*theta;
    double sin_   = sin(theta);
    double cot_   = 1.0 / tan( 0.5*theta );
    double csc2_  = pow( 1.0/sin(0.5*theta) ,2);

    // if the angle is small...
    if( cos_ > 0.9999 )
    {
        b = 0.5;
        L1(1,2) = -b;
        L1(2,1) =  b;
        L2(0,2) =  b;
        L2(2,0) = -b;
        L3(0,1) = -b;
        L3(1,0) =  b;
        // form the full derivative
        dlogT_dT.block(3,0,3,3) = L1;
        dlogT_dT.block(3,3,3,3) = L2;
        dlogT_dT.block(3,6,3,3) = L3;
        dlogT_dT.block(0,9,3,3) = Vinv;
    }
    // if not...
    else
    {
        // rotation part
        double k;
        Vector3d a;
        a(0) = T(2,1) - T(1,2);
        a(1) = T(0,2) - T(2,0);
        a(2) = T(1,0) - T(0,1);
        k = ( theta * cos_ - sin_ ) / ( 4 * pow(sin_,3) );
        a = k * a;
        L1.block(0,0,3,1) = a;
        L2.block(0,1,3,1) = a;
        L3.block(0,2,3,1) = a;
        // translation part
        Matrix3d w_skew = skew( x.tail(3) );
        Vinv += w_skew * (1.f-cos_) / theta2 + w_skew * w_skew * (theta - sin_) / pow(theta,3);
        Vinv  = Vinv.inverse().eval();
        // dVinv_dR
        Vector3d t;
        Matrix3d B, skew_t;
        MatrixXd dVinv_dR(3,9);
        t = T.block(0,3,3,1);
        skew_t = skew( t );
        // - form a
        a =  (theta*cos_-sin_)/(8.0*pow(sin_,3)) * w_skew * t
            + ( (theta*sin_-theta2*cos_)*(0.5*theta*cot_-1.0) - theta*sin_*(0.25*theta*cot_+0.125*theta2*csc2_-1.0))/(4.0*theta2*pow(sin_,4)) * w_skew * w_skew * t;
        // - form B
        Vector3d w;
        Matrix3d dw_dR;
        w = x.tail(3);
        dw_dR.row(0) << -w(1)*t(1)-w(2)*t(2), 2.0*w(1)*t(0)-w(0)*t(1), 2.0*w(2)*t(0)-w(0)*t(2);
        dw_dR.row(1) << -w(1)*t(0)+2.0*w(0)*t(1), -w(0)*t(0)-w(2)*t(2), 2.0*w(2)*t(1)-w(1)*t(2);
        dw_dR.row(2) << -w(2)*t(0)+2.0*w(0)*t(2), -w(2)*t(1)+2.0*w(1)*t(2), -w(0)*t(0)-w(1)*t(1);
        B = -0.5*theta*skew_t/sin_ - (theta*cot_-2.0)*dw_dR/(8.0*pow(sin_,2));
        // - form dVinv_dR
        dVinv_dR.col(0) = a;
        dVinv_dR.col(1) = -B.col(2);
        dVinv_dR.col(2) = B.col(1);
        dVinv_dR.col(3) = B.col(2);
        dVinv_dR.col(4) = a;
        dVinv_dR.col(5) = -B.col(0);
        dVinv_dR.col(6) = -B.col(1);
        dVinv_dR.col(7) = B.col(0);
        dVinv_dR.col(8) = a;
        // form the full derivative
        dlogT_dT.block(3,0,3,3) = L1;
        dlogT_dT.block(3,3,3,3) = L2;
        dlogT_dT.block(3,6,3,3) = L3;
        dlogT_dT.block(0,9,3,3) = Vinv;
        dlogT_dT.block(0,0,3,9) = dVinv_dR;
    }

    return dlogT_dT;

}