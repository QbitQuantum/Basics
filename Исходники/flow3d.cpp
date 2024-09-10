tgt::vec3 Flow3D::lookupFlowTrilinear(const tgt::vec3& r) const {
    tgt::ivec3 ir1(static_cast<int>(floorf(r.x)), static_cast<int>(floorf(r.y)),
        static_cast<int>(floorf(r.z)));
    ir1 = clampToFlowDimensions(ir1);
    tgt::ivec3 ir2 = clampToFlowDimensions(ir1 + tgt::ivec3(1));

    // interpolate in x-direction
    //
    tgt::vec3 v1 = linearInterpolation(r.x, ir1, 0);
    tgt::vec3 v2 = linearInterpolation(r.x, tgt::ivec3(0, ir2.y, ir1.z), 0);
    tgt::vec3 v3 = linearInterpolation(r.x, tgt::ivec3(0, ir1.y, ir2.z), 0);
    tgt::vec3 v4 = linearInterpolation(r.x, ir2, 0);

    // interpolates value from x-direction interpolation in y-direction
    //
    float fintegral = 0.0f;
    float b = modff(r.y, &fintegral);
    float a = 1.0f - b;
    tgt::vec3 v5 = ((v1 * a) + (v2 * b));
    tgt::vec3 v6 = ((v3 * a) + (v4 * b));

    // interpolate values from y-direction interpolation in z-drection
    //
    b = modff(r.z, &fintegral);
    a = 1.0f - b;
    return ((v5 * a) + (v6 * b));
}