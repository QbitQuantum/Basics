void ForceRendererTest::common2D() {
    Vector2 force(2.7f, -11.5f);
    Matrix3 m = Implementation::forceRendererTransformation<2>({0.5f, -3.0f}, force);

    /* Translation, right-pointing base vector is the same as force */
    CORRADE_COMPARE(m.translation(), Vector2(0.5f, -3.0f));
    CORRADE_COMPARE(m.right(), force);

    /* All vectors have the same length */
    CORRADE_COMPARE(m.up().length(), force.length());

    /* All vectors are orthogonal */
    CORRADE_COMPARE(Math::dot(m.right(), m.up()), 0.0f);
}