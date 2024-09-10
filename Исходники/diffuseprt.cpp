Spectrum DiffusePRTIntegrator::Li(const Scene *scene, const Renderer *,
            const RayDifferential &ray, const Intersection &isect,
            const Sample *sample, MemoryArena &arena) const {
    Spectrum L = 0.f;
    Vector wo = -ray.d;
    // Compute emitted light if ray hit an area light source
    L += isect.Le(wo);

    // Evaluate BSDF at hit point
    BSDF *bsdf = isect.GetBSDF(ray, arena);
    const Point &p = bsdf->dgShading.p;
    const Normal &n = bsdf->dgShading.nn;
    // Compute reflected radiance using diffuse PRT

    // Project diffuse transfer function at point to SH
    Spectrum *c_transfer = arena.Alloc<Spectrum>(SHTerms(lmax));
    SHComputeDiffuseTransfer(p, Faceforward(n, wo), isect.rayEpsilon,
        scene, *sample->rng, nSamples, lmax, c_transfer);

    // Compute integral of product of incident radiance and transfer function
    Spectrum LT = 0.f;
    for (int i = 0; i < SHTerms(lmax); ++i)
        LT += c_in[i] * c_transfer[i];

    // Compute reflectance at point for diffuse transfer
    const int sqrtRhoSamples = 6;
    float rhoRSamples[2*sqrtRhoSamples*sqrtRhoSamples];
    StratifiedSample2D(rhoRSamples, sqrtRhoSamples, sqrtRhoSamples, *sample->rng);
    Spectrum Kd = bsdf->rho(wo, sqrtRhoSamples*sqrtRhoSamples, rhoRSamples,
        BSDF_ALL_REFLECTION) * INV_PI;
    return L + Kd * LT.Clamp();
}