void Matrix4::makeInverseTransform(const Vector3& position, const Vector3& scale, const Quaternion& orientation) {
    // Invert the parameters
    Vector3 invTranslate = -position;
    Vector3 invScale(1 / scale.x(), 1 / scale.y(), 1 / scale.z());
    Quaternion invRot = orientation.inverse();

    // Because we're inverting, order is translation, rotation, scale
    // So make translation relative to scale & rotation
    invTranslate *= invScale; // scale
    invTranslate = invRot * invTranslate; // rotate

    // Next, make a 3x3 rotation matrix and apply inverse scale
    Matrix3 rot3x3, scale3x3;
    invRot.toRotationMatrix(rot3x3);
    scale3x3 = Matrix3::ZERO;
    scale3x3[0][0] = invScale.x();
    scale3x3[1][1] = invScale.y();
    scale3x3[2][2] = invScale.z();

    // Set up final matrix with scale, rotation and translation
    *this = scale3x3 * rot3x3;
    this->setTrans(invTranslate);

    // No projection term
    m_fm[3][0] = 0;
    m_fm[3][1] = 0;
    m_fm[3][2] = 0;
    m_fm[3][3] = 1;
}