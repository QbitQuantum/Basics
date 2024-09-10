Spectrum UseRadianceProbes::Li(const Scene *scene, const Renderer *renderer,
            const RayDifferential &ray, const Intersection &isect,
            const Sample *sample, RNG &rng, MemoryArena &arena, int wavelength) const {
    Spectrum L(0.);
    Vector wo = -ray.d;
    // Compute emitted light if ray hit an area light source
    L += isect.Le(wo);

    // Evaluate BSDF at hit point
    BSDF *bsdf = isect.GetBSDF(ray, arena, wavelength);
    const Point &p = bsdf->dgShading.p;
    const Normal &n = bsdf->dgShading.nn;
    // Compute reflection for radiance probes integrator
    if (!includeDirectInProbes)
        L += UniformSampleAllLights(scene, renderer, arena, p, n,
                wo, isect.rayEpsilon, ray.time, bsdf, sample, rng,
                lightSampleOffsets, bsdfSampleOffsets);

    // Compute reflected lighting using radiance probes

    // Compute probe coordinates and offsets for lookup point
    Vector offset = bbox.Offset(p);
    float voxx = (offset.x * nProbes[0]) - 0.5f;
    float voxy = (offset.y * nProbes[1]) - 0.5f;
    float voxz = (offset.z * nProbes[2]) - 0.5f;
    int vx = Floor2Int(voxx), vy = Floor2Int(voxy), vz = Floor2Int(voxz);
    float dx = voxx - vx, dy = voxy - vy, dz = voxz - vz;

    // Get radiance probe coefficients around lookup point
    const Spectrum *b000 = c_inXYZ(lmax, vx,   vy,   vz);
    const Spectrum *b100 = c_inXYZ(lmax, vx+1, vy,   vz);
    const Spectrum *b010 = c_inXYZ(lmax, vx,   vy+1, vz);
    const Spectrum *b110 = c_inXYZ(lmax, vx+1, vy+1, vz);
    const Spectrum *b001 = c_inXYZ(lmax, vx,   vy,   vz+1);
    const Spectrum *b101 = c_inXYZ(lmax, vx+1, vy,   vz+1);
    const Spectrum *b011 = c_inXYZ(lmax, vx,   vy+1, vz+1);
    const Spectrum *b111 = c_inXYZ(lmax, vx+1, vy+1, vz+1);

    // Compute incident radiance from radiance probe coefficients
    Spectrum *c_inp = arena.Alloc<Spectrum>(SHTerms(lmax));
    for (int i = 0; i < SHTerms(lmax); ++i) {
        // Do trilinear interpolation to compute SH coefficients at point
        Spectrum c00 = Lerp(dx, b000[i], b100[i]);
        Spectrum c10 = Lerp(dx, b010[i], b110[i]);
        Spectrum c01 = Lerp(dx, b001[i], b101[i]);
        Spectrum c11 = Lerp(dx, b011[i], b111[i]);
        Spectrum c0 = Lerp(dy, c00, c10);
        Spectrum c1 = Lerp(dy, c01, c11);
        c_inp[i] = Lerp(dz, c0, c1);
    }

    // Convolve incident radiance to compute irradiance function
    Spectrum *c_E = arena.Alloc<Spectrum>(SHTerms(lmax));
    SHConvolveCosTheta(lmax, c_inp, c_E);

    // Evaluate irradiance function and accumulate reflection
    Spectrum rho = bsdf->rho(wo, rng, BSDF_ALL_REFLECTION);
    float *Ylm = ALLOCA(float, SHTerms(lmax));
    SHEvaluate(Vector(Faceforward(n, wo)), lmax, Ylm);
    Spectrum E = 0.f;
    for (int i = 0; i < SHTerms(lmax); ++i)
        E += c_E[i] * Ylm[i];
    L += rho * INV_PI * E.Clamp();
    return L;
}