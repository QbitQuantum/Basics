void
Structural2DElement :: giveMaterialOrientationAt(FloatArray &x, FloatArray &y, const FloatArray &lcoords)
{
    if ( this->elemLocalCS.isNotEmpty() ) { // User specified orientation
        x = {
            elemLocalCS.at(1, 1), elemLocalCS.at(2, 1)
        };
        y = {
            -x(1), x(0)
        };
    } else {
        FloatMatrix jac;
        this->giveInterpolation()->giveJacobianMatrixAt( jac, lcoords, * this->giveCellGeometryWrapper() );
        x.beColumnOf(jac, 1); // This is {dx/dxi, dy/dxi, dz/dxi}
        x.normalize();
        y = {
            -x(1), x(0)
        };
    }
}