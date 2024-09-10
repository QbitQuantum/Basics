void Matrix3DUtils::getRotation(const Matrix3D &m, Vector3D &out) {
    Vector3D *v = new Vector3D[3]();
    m.decompose(Matrix3D::Style::EulerAngles, v);
    _vector.copyFrom(v[1]);
    out.x = _vector.x * _toAng;
    out.y = _vector.y * _toAng;
    out.z = _vector.z * _toAng;
    // free v
    delete [] v;
}