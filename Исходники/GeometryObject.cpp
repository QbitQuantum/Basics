/// utility non-class member functions
//! gets a coordinate system that matches view system used in 3D with +Z up (or +Y up if neccessary)
//! used for individual views, but not secondary views in projection groups
gp_Ax2 TechDrawGeometry::getViewAxis(const Base::Vector3d origin,
                                     const Base::Vector3d& direction,
                                     const bool flip)
{
    gp_Pnt inputCenter(origin.x,origin.y,origin.z);
    Base::Vector3d stdZ(0.0,0.0,1.0);
    Base::Vector3d flipDirection(direction.x,-direction.y,direction.z);
    if (!flip) {
        flipDirection = Base::Vector3d(direction.x,direction.y,direction.z);
    }
    Base::Vector3d cross = flipDirection;
    //special cases
    if (flipDirection == stdZ) {
        cross = Base::Vector3d(1.0,0.0,0.0);
    } else if (flipDirection == (stdZ * -1.0)) {
        cross = Base::Vector3d(1.0,0.0,0.0);
    } else {
        cross.Normalize();
        cross = cross.Cross(stdZ);
    }
    gp_Ax2 viewAxis;
    viewAxis = gp_Ax2(inputCenter,
                      gp_Dir(flipDirection.x, flipDirection.y, flipDirection.z),
//                      gp_Dir(1.0, 1.0, 0.0));
                      gp_Dir(cross.x, cross.y, cross.z));
    return viewAxis;
}