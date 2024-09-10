SpotLightParameterEstimationClass::InputForExponentCalculation* SpotLightParameterEstimationClass::GetSpotLightExponentInputParameters() {
    
    if (_inputSetter != nullptr) {
        return _inputSetter;
    }
    const LightEntityClass& light = _lightSystem->GetCurrentLight();
    double materialAlbedo = 0.5;
    
    // Light
    double lightIntensity           = _lightSystem->GetCurrentLightIntensity();
    Eigen::Vector3d lightDirection  = -light.GetDirectionVector();
    lightDirection.normalize();
    Eigen::Vector3d lightPosition   =  light.GetPosition();
    double innerconeangle           =  light.GetSpotLightInnerConeAngle() * M_PI / 180;
    double outerconeangle           =  light.GetSpotLightOuterConeAngle() * M_PI / 180;
    double gammaCorrection          =  light.GetGammaCorrection();
    double cosOfInnerConeAngle      =  cos(innerconeangle);
    double cosOfOuterConeAngle      =  cos(outerconeangle);
    
    // Geometry
    const GeometryEntityClass& geometryEntity = _geometrySystem->GetCurrentGeometry();
   // Point3D<double> vertex = geometryEntity.GetAVertex();
    std::vector<Eigen::Vector3d> vertexNormals = geometryEntity.GetVertexNormals();
    Eigen::Vector3d vnormal = vertexNormals[0];
    vnormal.normalize();
    
    // Image
    _imageWidth = (int)_imageSystem->GetCurrentImageWidth();
    _imageHeight = (int)_imageSystem->GetCurrentImageHeight();
    
    ReprojectionClass* reprojectionClass = new ReprojectionClass();
    std::vector<MapOFImageAndWorldPoints>reprojectedPoints;
    // Uncomment this if we are going to pass in Array<RGBA> of the pixels that we obtained from the circumference of the illumination
    //reprojectedPoints = reprojectionClass->ReprojectImagePixelsTo3DGeometry((_imageSystem->GetCurrentImage()).GetImage2DArrayPixels());
    reprojectedPoints = reprojectionClass->ReprojectImagePixelsTo3DGeometry();
    
    _inputSetter = new InputForExponentCalculation(_imageWidth, _imageHeight, lightIntensity, lightDirection, lightPosition, gammaCorrection,vnormal, cosOfInnerConeAngle, cosOfOuterConeAngle, materialAlbedo, reprojectedPoints);
    
    delete reprojectionClass;
    return _inputSetter;
}