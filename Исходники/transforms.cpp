/*    Computes a look-at transformation.*/
Mat4 lookAt(const Vec3& eye, const Vec3& target, const Vec3& up) {
    Vec3 vz = eye - target;
    Vec3 vx = up.cross(vz);
    Vec3 vy = vz.cross(vx);
    
    vx /= vx.mag();
    vy /= vy.mag();
    vz /= vz.mag();
    
    return Mat4(
        vx.x, vx.y, vx.z, 0.0,
        vy.x, vy.y, vy.z, 0.0,
        vz.x, vz.y, vz.z, 0.0,
        eye.x, eye.y, eye.z, 1.0).inverse();
};