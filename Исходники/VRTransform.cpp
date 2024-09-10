        /** Rotate the object around its x axis **/
void VRTransform::rotateX(float a) {//rotate around x axis
    Vec3f dir = _at - _from;
    Vec3f d = dir.cross(_up);
    d.normalize();

    Quaternion q = Quaternion(d, a);
    q.multVec(_up,_up);
    q.multVec(dir,dir);
    _at = _from + dir;

    reg_change();
    //cout << "\nRotating " << name << " " << a ;
}