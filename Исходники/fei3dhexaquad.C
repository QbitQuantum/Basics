double
FEI3dHexaQuad :: surfaceEvalNormal(FloatArray &answer, int isurf, const FloatArray &lcoords, const FEICellGeometry &cellgeo)
{
    FloatArray a, b, dNdksi(8), dNdeta(8);
    double ksi, eta;
    IntArray snodes;
    
    this->computeLocalSurfaceMapping(snodes, isurf);

    ksi = lcoords.at(1);
    eta = lcoords.at(2);

    // No need to divide by 1/4, we'll normalize anyway;
    dNdksi.at(1) =  0.25 * ( 1. + eta ) * ( 2.0 * ksi + eta );
    dNdksi.at(2) = -0.25 * ( 1. + eta ) * ( -2.0 * ksi + eta );
    dNdksi.at(3) = -0.25 * ( 1. - eta ) * ( -2.0 * ksi - eta );
    dNdksi.at(4) =  0.25 * ( 1. - eta ) * ( 2.0 * ksi - eta );
    dNdksi.at(5) = -ksi * ( 1. + eta );
    dNdksi.at(6) = -0.5 * ( 1. - eta * eta );
    dNdksi.at(7) = -ksi * ( 1. - eta );
    dNdksi.at(8) =  0.5 * ( 1. - eta * eta );
    
    dNdeta.at(1) =  0.25 * ( 1. + ksi ) * ( 2.0 * eta + ksi );
    dNdeta.at(2) =  0.25 * ( 1. - ksi ) * ( 2.0 * eta - ksi );
    dNdeta.at(3) = -0.25 * ( 1. - ksi ) * ( -2.0 * eta - ksi );
    dNdeta.at(4) = -0.25 * ( 1. + ksi ) * ( -2.0 * eta + ksi );
    dNdeta.at(5) =  0.5 * ( 1. - ksi * ksi );
    dNdeta.at(6) = -eta * ( 1. - ksi );
    dNdeta.at(7) = -0.5 * ( 1. - ksi * ksi );
    dNdeta.at(8) = -eta * ( 1. + ksi );

    for ( int i = 1; i <= 8; ++i ) {
        a.add(dNdksi.at(i), *cellgeo.giveVertexCoordinates(snodes.at(i)));
        b.add(dNdeta.at(i), *cellgeo.giveVertexCoordinates(snodes.at(i)));
    }
    
    answer.beVectorProductOf(a, b);
    return answer.normalize();
}