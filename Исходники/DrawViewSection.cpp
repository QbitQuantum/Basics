//! calculate the section Normal/Projection Direction given baseView projection direction and section name
Base::Vector3d DrawViewSection::getSectionVector (const std::string sectionName)
{
    Base::Vector3d result;
    Base::Vector3d stdX(1.0,0.0,0.0);
    Base::Vector3d stdY(0.0,1.0,0.0);
    Base::Vector3d stdZ(0.0,0.0,1.0);

    double adjustAngle = 0.0;
    if (getBaseDPGI() != nullptr) {
        adjustAngle = getBaseDPGI()->getRotateAngle();
    }

    Base::Vector3d view = getBaseDVP()->Direction.getValue();
    view.Normalize();
    Base::Vector3d left = view.Cross(stdZ);
    left.Normalize();
    Base::Vector3d up = view.Cross(left);
    up.Normalize();
    double dot = view.Dot(stdZ);

    if (sectionName == "Up") {
        result = up;
        if (DrawUtil::fpCompare(dot,1.0)) {            //view = stdZ
            result = (-1.0 * stdY);
        } else if (DrawUtil::fpCompare(dot,-1.0)) {    //view = -stdZ
            result = stdY;
        }
    } else if (sectionName == "Down") {
        result = up * -1.0;
        if (DrawUtil::fpCompare(dot,1.0)) {            //view = stdZ
            result = stdY;
        } else if (DrawUtil::fpCompare(dot, -1.0)) {   //view = -stdZ
            result = (-1.0 * stdY);
        }
    } else if (sectionName == "Left") {
        result = left * -1.0;
        if (DrawUtil::fpCompare(fabs(dot),1.0)) {      //view = +/- stdZ
            result = stdX;
        }
    } else if (sectionName == "Right") {
        result = left;
        if (DrawUtil::fpCompare(fabs(dot),1.0)) {
            result = -1.0 * stdX;
        }
    } else {
        Base::Console().Log("Error - DVS::getSectionVector - bad sectionName: %s\n",sectionName.c_str());
        result = stdZ;
    }
    Base::Vector3d adjResult = DrawUtil::vecRotate(result,adjustAngle,view);
    return adjResult;
}