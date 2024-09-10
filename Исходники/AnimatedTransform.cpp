void AnimatedTransform::setTransforms(const Transform& t1, const Transform& t2) {
    _actuallyAnimated = true;
    _transforms[0] = t1;
    _transforms[1] = t2;
    // Decompose matrices
    decompose(t1.getMatrix(), &_translations[0], &_rotations[0], &_scales[0]);
    decompose(t2.getMatrix(), &_translations[1], &_rotations[1], &_scales[1]);
    if (dot(_rotations[0], _rotations[1]) < 0.f) {
        _rotations[1] = -_rotations[1];
    }
}