Vec3 MicrosurfaceDielectric::refract(const Vec3 &wi, const Vec3 &wm, const float eta) const
{
    const float cos_theta_i = wi.dot(wm);
    const float cos_theta_t2 = 1.0f - (1.0f - cos_theta_i*cos_theta_i) / (eta*eta);
    const float cos_theta_t = -sqrtf(std::max(0.0f, cos_theta_t2));

    return wm * (wi.dot(wm) / eta + cos_theta_t) - wi / eta;
}