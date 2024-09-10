QString PageItem_OSGFrame::getPDFMatrix(QString viewName)
{
    struct viewDefinition defaultView;
    defaultView = viewMap[viewName];
    osg::Vec3d trackerCenter = defaultView.trackerCenter;
    osg::Vec3d cameraPosition = defaultView.cameraPosition;
    osg::Vec3d cameraUp = defaultView.cameraUp;
    double viewx, viewy, viewz;
    double leftx, lefty, leftz;
    double upx, upy, upz;
    double transx, transy, transz;
    double roll = 0.0;
    double roo = getDistance(cameraPosition, trackerCenter);
    cameraPosition.normalize();
    cameraUp.normalize();
    viewx = -cameraPosition[0];
    viewy = -cameraPosition[1];
    viewz = -cameraPosition[2];
    if (viewx == 0.0 && viewy == 0.0 && viewz == 0.0)
    {
        viewy = 1.0;
    }
    leftx = -1.0f;
    lefty =  0.0f;
    leftz =  0.0f;
    if (viewz < 0.0) /* top view*/
    {
        upx = 0.0f;
        upy = 1.0f;
        upz = 0.0f;
    }
    else /* bottom view*/
    {
        upx = 0.0f;
        upy =-1.0f;
        upz = 0.0f;
    }
    if ( fabs(viewx) + fabs(viewy) != 0.0f) /* other views than top and bottom*/
    {
        cameraUp.normalize();
        upx = cameraUp[0];
        upy = cameraUp[1];
        upz = cameraUp[2];
        leftx = viewz*upy - viewy*upz;
        lefty = viewx*upz - viewz*upx;
        leftz = viewy*upx - viewx*upy;
        normalized(leftx, lefty, leftz);
    }
    /* apply camera roll*/
    {
        double leftxprime, leftyprime, leftzprime;
        double upxprime, upyprime, upzprime;
        double sinroll, cosroll;
        sinroll =  sin((roll/180.0f)*M_PI);
        cosroll =  cos((roll/180.0f)*M_PI);
        leftxprime = leftx*cosroll + upx*sinroll;
        leftyprime = lefty*cosroll + upy*sinroll;
        leftzprime = leftz*cosroll + upz*sinroll;
        upxprime = upx*cosroll + leftx*sinroll;
        upyprime = upy*cosroll + lefty*sinroll;
        upzprime = upz*cosroll + leftz*sinroll;
        leftx = leftxprime;
        lefty = leftyprime;
        leftz = leftzprime;
        upx = upxprime;
        upy = upyprime;
        upz = upzprime;
    }
    /* translation vector*/
    roo = fabs(roo);
    if (roo == 0.0)
    {
        roo = 0.000000000000000001;
    }
    transx = trackerCenter[0] - roo*viewx;
    transy = trackerCenter[1] - roo*viewy;
    transz = trackerCenter[2] - roo*viewz;
    if (fabs(leftx) < 0.0000001)
        leftx = 0.0;
    if (fabs(lefty) < 0.0000001)
        lefty = 0.0;
    if (fabs(leftz) < 0.0000001)
        leftz = 0.0;
    if (fabs(upx) < 0.0000001)
        upx = 0.0;
    if (fabs(upy) < 0.0000001)
        upy = 0.0;
    if (fabs(upz) < 0.0000001)
        upz = 0.0;
    if (fabs(transx) < 0.0000001)
        transx = 0.0;
    if (fabs(transy) < 0.0000001)
        transy = 0.0;
    if (fabs(transz) < 0.0000001)
        transz = 0.0;
    QString ret = "";
    QString desc4 = "%1 %2 %3 ";
    ret += desc4.arg(leftx).arg(lefty).arg(leftz);
    ret += desc4.arg(upx).arg(upy).arg(upz);
    ret += desc4.arg(viewx).arg(viewy).arg(viewz);
    ret += desc4.arg(transx).arg(transy).arg(transz);
    distanceToObj = roo;
    return ret;
}