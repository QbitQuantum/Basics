CoordinateFrame GLight::frame() const {
    CoordinateFrame f;
    if (rightDirection == Vector3::zero()) {
        // No specified right direction; choose one automatically
        if (position.w == 0) {
            // Directional light
            f.lookAt(-position.xyz());
        } else {
            // Spot light
            f.lookAt(spotDirection);
        }
    } else {
        const Vector3& Z = -spotDirection.direction();
        Vector3 X = rightDirection.direction();

        // Ensure the vectors are not too close together
        while (abs(X.dot(Z)) > 0.9f) {
            X = Vector3::random();
        }

        // Ensure perpendicular
        X -= Z * Z.dot(X);
        const Vector3& Y = Z.cross(X);

        f.rotation.setColumn(Vector3::X_AXIS, X);
        f.rotation.setColumn(Vector3::Y_AXIS, Y);
        f.rotation.setColumn(Vector3::Z_AXIS, Z);
    }
    f.translation = position.xyz();

    return f;
}