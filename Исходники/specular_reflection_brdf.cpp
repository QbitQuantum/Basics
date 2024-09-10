nex::color specular_reflection_brdf::sample(const lumen::sample& sample, const surface& surface,
        const nex::vector& wo, nex::vector* wi, float* pdf) const
{
        *wi = reflect(wo, surface.normal);
        *pdf = 1.0f;

        return reflectance / std::abs(nex::dot(surface.normal, *wi));
}