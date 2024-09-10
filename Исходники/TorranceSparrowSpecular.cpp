RGB TorranceSparrowSpecular::f(const Intersection &sr, const Vector &wi, const Vector &wo) {
    Vector half=Normalize(wi + wo);
    return mAlbedo/(4*M_PI*Dot(sr.normal,wi))*_NDF(sr.normal,half)*_Fresnel(wo,half)*_G(sr.normal,half,wi,wo);
}