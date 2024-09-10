RotationMatrix::RotationMatrix(double _teta, Vec3Df axis){
    axis.normalize();
    float c = std::cos(_teta*PI/180.);
    float s = std::sin(_teta*PI/180.);
    float ux = axis[0];
    float uy = axis[1];
    float uz = axis[2];
    new (this) RotationMatrix( ux*ux +(1.-ux*ux)*c , ux*uy*(1-c) - uz*s ,ux*uz*(1-c) + uy*s , 0.,
                               ux*uy*(1-c) + uz*s, uy*uy +(1.-uy*uy)*c, uy*uz*(1-c) - ux*s , 0. ,
                               ux*uz*(1-c) - uy*s, uy*uz*(1-c) + ux*s ,uz*uz +(1.-uz*uz)*c  , 0.,
                               0., 0., 0., 0.,
                               _teta
                             );
}