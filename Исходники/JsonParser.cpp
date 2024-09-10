inline Light* getLight(Transform cameraTransform, Json::Value &root, int lightSamples, RenderEnvironment *renderEnv){
    Transform invCam = cameraTransform.inverse(cameraTransform);
        // read all standard data
        // TODO:    std::string name        = getStringAttr("name", root);
    Transform *objTransform  = new Transform(invCam * getTransformAttr("transforms", root));    
    double xScale           = getDoubleAttr("scaleX", root);
    double yScale           = getDoubleAttr("scaleY", root);
    double exposure         = getDoubleAttr("exposure", root);    
    Color color             = getColorAttr("color", root);
    std::string name        = getStringAttr("name", root);

        // construct transforms
    Transform *c2o = new Transform(objTransform->inverse(*objTransform));
    Transform *c2w = new Transform(cameraTransform);
    Transform *w2c = new Transform(cameraTransform.inverse(cameraTransform));
    Transform *o2w = new Transform(*objTransform * *c2w);
    Transform *w2o = new Transform(*w2c * *c2o);
    Light* sqrLight = new SquareLight(objTransform, c2o, o2w, w2o, c2w, w2c, exposure, color, xScale, yScale, name, renderEnv);
    
    return sqrLight;
}