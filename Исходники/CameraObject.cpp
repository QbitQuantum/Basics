void CameraObject::look_at (const Vector3 &to, const Vector3 &up)
{
    Matrix3 m;	
    Vector3 delta;
    
    delta = translation() - to;
    
    m = Matrix3::set_orientation(delta, up);
    set_orientation(m);
}