RNRgb R3DirectionalLight::
SpecularReflection(const R3Brdf& brdf, const R3Point& eye, 
    const R3Point& point, const R3Vector& normal) const
{
    // Check if light is active
    if (!IsActive()) return RNblack_rgb;

    // Get material properties
    const RNRgb& Sc = brdf.Specular();
    RNScalar s = brdf.Shininess();

    // Get light properties
    const RNRgb& Ic = Color();
    RNScalar I = Intensity();
    R3Vector L = -(Direction());

    // Compute geometric stuff
    RNScalar NL = normal.Dot(L);
    if (RNIsNegativeOrZero(NL)) return RNblack_rgb;
    R3Vector R = (2.0 * NL) * normal - L;
    R3Vector V = eye - point;
    V.Normalize();
    RNScalar VR = V.Dot(R);
    if (RNIsNegativeOrZero(VR)) return RNblack_rgb;

    // Return specular component of reflection
    return (I * pow(VR,s)) * Sc * Ic;
}