double
NonlocalMaterialExtensionInterface :: computeWeightFunction(const FloatArray &src, const FloatArray &coord)
{
    return computeWeightFunction( src.distance(coord) );
}