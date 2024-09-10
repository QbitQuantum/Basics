MTransformationMatrix ffdPlanar::getXyzToStuTransformation( MBoundingBox& boundingBox )
{
    MTransformationMatrix transform = MTransformationMatrix();
    
    double scale[3] = { FFD_DIMENSIONS_S > 0 ? 1.f / boundingBox.width() : 1.f,
                        FFD_DIMENSIONS_T > 0 ? 1.f / boundingBox.height() : 1.f,
                        FFD_DIMENSIONS_U > 0 ? 1.f / boundingBox.depth() : 1.f };
    
    transform.addScale( scale, MSpace::kObject );
    
    MVector boundsMinOffset = MPoint::origin - boundingBox.min();
    transform.addTranslation( boundsMinOffset, MSpace::kObject );
    
    return transform;
}