void AnimatedTransform::Interpolate(float time, Transform *t) const {
    // Handle boundary conditions for matrix interpolation
    if (!actuallyAnimated || time <= startTime) {
        *t = *startTransform;
        return;
    }
    if (time >= endTime) {
        *t = *endTransform;
        return;
    }
    float dt = (time - startTime) / (endTime - startTime);
    // Interpolate translation at _dt_
    Vector trans = (1.f - dt) * T[0] + dt * T[1];

    // Interpolate rotation at _dt_
    Quaternion rotate = Slerp(dt, R[0], R[1]);

    // Interpolate scale at _dt_
    Matrix4x4 scale;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            scale.m[i][j] = Lerp(dt, S[0].m[i][j], S[1].m[i][j]);

    // Compute interpolated matrix as product of interpolated components
    *t = Translate(trans) * rotate.ToTransform() * Transform(scale);
}