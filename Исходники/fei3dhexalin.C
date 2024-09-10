double
FEI3dHexaLin :: surfaceEvalNormal(FloatArray &answer, int isurf, const FloatArray &lcoords, const FEICellGeometry &cellgeo)
{
    FloatArray a, b, dNdksi(4), dNdeta(4);
    double ksi, eta;
    IntArray snodes;
    
    this->computeLocalSurfaceMapping(snodes, isurf);

    ksi = lcoords.at(1);
    eta = lcoords.at(2);

    // No need to divide by 1/4, we'll normalize anyway;
    dNdksi.at(1) =  ( 1. + eta );
    dNdksi.at(2) = -( 1. + eta );
    dNdksi.at(3) = -( 1. - eta );
    dNdksi.at(4) =  ( 1. - eta );

    dNdeta.at(1) =  ( 1. + ksi );
    dNdeta.at(2) =  ( 1. - ksi );
    dNdeta.at(3) = -( 1. - ksi );
    dNdeta.at(4) = -( 1. + ksi );

    for (int i = 1; i <= 4; ++i) {
        a.add(dNdksi.at(i), *cellgeo.giveVertexCoordinates(snodes.at(i)));
        b.add(dNdeta.at(i), *cellgeo.giveVertexCoordinates(snodes.at(i)));
    }
    
    answer.beVectorProductOf(a, b);
    return answer.normalize()*0.0625;
}