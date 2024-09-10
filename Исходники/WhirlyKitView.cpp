double View::currentMapScale(const WhirlyKit::Point2f &frameSize)
{
    //    *height = globeView.heightAboveGlobe;
    //    Point3d localPt = [globeView currentUp];
    //    GeoCoord geoCoord = globeView.coordAdapter->getCoordSystem()->localToGeographic(globeView.coordAdapter->displayToLocal(localPt));
    //    pos->x = geoCoord.lon();  pos->y = geoCoord.lat();
    
//    Point2f frameSize(sceneRenderer.framebufferWidth,sceneRenderer.framebufferHeight);
//    Eigen::Matrix4d modelTrans = [visualView calcFullMatrix];
//    Point3d sp0,sp1;
//    bool sp0Valid = [globeView pointOnSphereFromScreen:CGPointMake(0.0, frameSize.y()/2.0) transform:&modelTrans frameSize:frameSize hit:&sp0 normalized:true];
//    bool sp1Valid = [globeView pointOnSphereFromScreen:CGPointMake(frameSize.x(), frameSize.y()/2.0) transform:&modelTrans frameSize:frameSize hit:&sp1 normalized:true];
//    // Bogus scale at this point
//    if (!sp0Valid || !sp1Valid)
//        return 0.0;
//    sp0 *= EarthRadius;
//    sp1 *= EarthRadius;
//    // Assume the local coordinate are in meters.  WHAT COULD POSSIBLY GO WRONG!
//    double dist = (sp1-sp0).norm();
    
    // This is Mapnik scale:
    // scale_denominator = map_width_in_metres/ (map_width_in_pixels * standardized_pixel_size/*0.28mm*/)
    double scale = (2 * heightAboveSurface() *  tan(fieldOfView/2.0) * EarthRadius) / (frameSize.x() * 0.00096) ;
    return scale;
}