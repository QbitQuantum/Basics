double Tr21Stokes :: SpatialLocalizerI_giveDistanceFromParametricCenter(const FloatArray &coords)
{
    FloatArray center;
    FloatArray lcoords;
    lcoords.setValues(3, 0.333333, 0.333333, 0.333333);
    interpolation_quad.local2global(center, lcoords, FEIElementGeometryWrapper(this));
    return center.distance(coords);
}