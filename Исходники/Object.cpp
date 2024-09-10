void Magic3D::Object::lookAt(Vector3 position, Vector3 up, float factor)
{
    Matrix4 m4EyeFrame;
    Vector3 v3X, v3Y, v3Z;
    Vector3 eyePos = getPositionFromParent();
    v3Y = normalize( up );
    v3Z = normalize( ( position - eyePos ) );
    v3X = normalize( cross( v3Y, v3Z ) );
    v3Y = cross( v3Z, v3X );
    m4EyeFrame = Matrix4( Vector4( v3X ), Vector4( v3Y ), Vector4( v3Z ), Vector4( eyePos ) );

    Quaternion parent = getParent() ? Math::inverse(getParent()->getRotationFromParent()) : Quaternion::identity();
    Quaternion m = slerp(factor, getRotationFromParent(), Quaternion(m4EyeFrame.getUpper3x3()));

    setRotation(parent * m);
}