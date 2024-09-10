// Given a convex curve segment with the following order-2 tangent function:
//
//                                                       |C2x  C2y|
//     tan = some_scale * |dx/dt  dy/dt| = |t^2  t  1| * |C1x  C1y|
//                                                       |C0x  C0y|
//
// This function finds the T value whose tangent angle is halfway between the tangents at T=0 and
// T=1 (tan0 and tan1).
static inline float find_midtangent(const Sk2f& tan0, const Sk2f& tan1,
                                    const Sk2f& C2, const Sk2f& C1, const Sk2f& C0) {
    // Tangents point in the direction of increasing T, so tan0 and -tan1 both point toward the
    // midtangent. 'n' will therefore bisect tan0 and -tan1, giving us the normal to the midtangent.
    //
    //     n dot midtangent = 0
    //
    Sk2f n = normalize(tan0) - normalize(tan1);

    // Find the T value at the midtangent. This is a simple quadratic equation:
    //
    //     midtangent dot n = 0
    //
    //     (|t^2  t  1| * C) dot n = 0
    //
    //     |t^2  t  1| dot C*n = 0
    //
    // First find coeffs = C*n.
    Sk4f C[2];
    Sk2f::Store4(C, C2, C1, C0, 0);
    Sk4f coeffs = C[0]*n[0] + C[1]*n[1];

    // Now solve the quadratic.
    float a = coeffs[0], b = coeffs[1], c = coeffs[2];
    float discr = b*b - 4*a*c;
    if (discr < 0) {
        return 0; // This will only happen if the curve is a line.
    }

    // The roots are q/a and c/q. Pick the one closer to T=.5.
    float q = -.5f * (b + copysignf(std::sqrt(discr), b));
    float r = .5f*q*a;
    return std::abs(q*q - r) < std::abs(a*c - r) ? q/a : c/q;
}