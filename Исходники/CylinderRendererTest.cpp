void CylinderRendererTest::common3D() {
    const Vector3 a(0.5f, 3.0f, 7.0f);
    const Vector3 b(7.5f, -1.0f, 1.5f);
    const Matrix4 transformation = Implementation::cylinderRendererTransformation<3>(a, b, 3.5f);

    /* Rotation + scaling */
    CORRADE_COMPARE(transformation.up(), Vector3(3.5f, -2.0f, -2.75f));
    CORRADE_COMPARE(transformation.right(), Vector3(-2.0f, -3.5f, 0.0f).resized(3.5f));
    CORRADE_COMPARE(transformation.backward(), Vector3(9.625f, -5.5f, 16.25f).resized(3.5f));

    /* Orthogonality */
    CORRADE_COMPARE(Math::dot(transformation.up(), transformation.right()), 0.0f);
    CORRADE_COMPARE(Math::dot(transformation.up(), transformation.backward()), 0.0f);
    CORRADE_COMPARE(Math::dot(transformation.right(), transformation.backward()), 0.0f);

    CORRADE_COMPARE(transformation.translation(), 0.5f*(a + b));
}