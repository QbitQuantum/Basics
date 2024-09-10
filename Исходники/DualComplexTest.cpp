void DualComplexTest::translation() {
    Vector2 vec(1.5f, -3.5f);
    DualComplex a = DualComplex::translation(vec);
    CORRADE_COMPARE(a.length(), 1.0f);
    CORRADE_COMPARE(a, DualComplex({}, {1.5f, -3.5f}));
    CORRADE_COMPARE(a.translation(), vec);
}