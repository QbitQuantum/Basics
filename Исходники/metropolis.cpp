Spectrum MetropolisRenderer::Lbidir(const Scene *scene,
        const PathVertex *cameraPath, int cameraPathLength,
        const PathVertex *lightPath, int lightPathLength,
        MemoryArena &arena, const vector<LightingSample> &samples,
        RNG &rng, float time, const Distribution1D *lightDistribution,
        const RayDifferential &eRay, const Spectrum &eAlpha) const {
    PBRT_MLT_STARTED_LBIDIR();
    Spectrum L = 0.;
    bool previousSpecular = true, allSpecular = true;
    // Compute number of specular vertices for each path length
    int nVerts = cameraPathLength + lightPathLength + 2;
    int *nSpecularVertices = ALLOCA(int, nVerts);
    memset(nSpecularVertices, 0, nVerts * sizeof(int));
    for (int i = 0; i < cameraPathLength; ++i)
        for (int j = 0; j < lightPathLength; ++j)
            if (cameraPath[i].specularBounce || lightPath[j].specularBounce)
                ++nSpecularVertices[i+j+2];
    for (int i = 0; i < cameraPathLength; ++i) {
        // Initialize basic variables for camera path vertex
        const PathVertex &vc = cameraPath[i];
        const Point &pc = vc.bsdf->dgShading.p;
        const Normal &nc = vc.bsdf->dgShading.nn;

        // Compute reflected light at camera path vertex

        // Add emitted light from vertex if appropriate
        if (previousSpecular && (directLighting == NULL || !allSpecular))
            L += vc.alpha * vc.isect.Le(vc.wPrev);

        // Compute direct illumination for Metropolis path vertex
        Spectrum Ld(0.f);
        if (directLighting == NULL || !allSpecular) {
            // Choose light and call _EstimateDirect()_ for Metropolis vertex
            const LightingSample &ls = samples[i];
            float lightPdf;
            uint32_t lightNum = lightDistribution->SampleDiscrete(ls.lightNum,
                                                                  &lightPdf);
            const Light *light = scene->lights[lightNum];
            PBRT_MLT_STARTED_ESTIMATE_DIRECT();
            
            Ld = vc.alpha *
                 EstimateDirect(scene, this, arena, light, pc, nc, vc.wPrev,
                                vc.isect.rayEpsilon, time, vc.bsdf, rng,
                                ls.lightSample, ls.bsdfSample,
                                BxDFType(BSDF_ALL & ~BSDF_SPECULAR)) / lightPdf;
            PBRT_MLT_FINISHED_ESTIMATE_DIRECT();
        }
        previousSpecular = vc.specularBounce;
        allSpecular &= previousSpecular;
        L += Ld / (i + 1 - nSpecularVertices[i+1]);
        if (!vc.specularBounce) {
            // Loop over light path vertices and connect to camera vertex
            for (int j = 0; j < lightPathLength; ++j) {
                const PathVertex &vl = lightPath[j];
                const Point &pl = vl.bsdf->dgShading.p;
                const Normal &nl = vl.bsdf->dgShading.nn;
                if (!vl.specularBounce) {
                    // Compute contribution between camera and light vertices
                    Vector w = Normalize(pl - pc);
                    Spectrum fc = vc.bsdf->f(vc.wPrev, w) * (1 + vc.nSpecularComponents);
                    Spectrum fl = vl.bsdf->f(-w, vl.wPrev) * (1 + vl.nSpecularComponents);
                    if (fc.IsBlack() || fl.IsBlack()) continue;
                    Ray r(pc, pl - pc, 1e-3f, .999f, time);
                    if (!scene->IntersectP(r)) {
                        // Compute weight for bidirectional path, _pathWt_
                        float pathWt = 1.f / (i + j + 2 - nSpecularVertices[i+j+2]);
                        float G = AbsDot(nc, w) * AbsDot(nl, w) / DistanceSquared(pl, pc);
                        L += (vc.alpha * fc * G * fl * vl.alpha) * pathWt;
                    }
                }
            }
        }
    }
    // Add contribution of escaped ray, if any
    if (!eAlpha.IsBlack() && previousSpecular &&
        (directLighting == NULL || !allSpecular))
        for (uint32_t i = 0; i < scene->lights.size(); ++i)
           L += eAlpha * scene->lights[i]->Le(eRay);
    PBRT_MLT_FINISHED_LBIDIR();
    return L;
}