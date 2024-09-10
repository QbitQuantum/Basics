    //-----------------------------------------------------------------------
    void Matrix4::MakeInverseTransform(Vector3 position, Vector3 scale, Quaternion orientation)
    {
        // Invert the parameters
        Vector3 invTranslate = -position;
        Vector3 invScale(1 / scale.x, 1 / scale.y, 1 / scale.z);
        Quaternion invRot = orientation.Inverse();

        // Because we're inverting, order is translation, rotation, scale
        // So make translation relative to scale & rotation
        invTranslate *= invScale; // scale
        invTranslate = invRot * invTranslate; // rotate

        // Next, make a 3x3 rotation matrix and apply inverse scale
        Matrix3^ rot3x3, ^scale3x3;
        rot3x3 = invRot.ToRotationMatrix();
        scale3x3 = Matrix3::ZERO;
        scale3x3->m00 = invScale.x;
        scale3x3->m11 = invScale.y;
        scale3x3->m22 = invScale.z;

        // Set up final matrix with scale, rotation and translation
        *this = scale3x3 * rot3x3;
        this->SetTrans(invTranslate);

        // No projection term
        m30 = 0; m31 = 0; m32 = 0; m33 = 1;
    }