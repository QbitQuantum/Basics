// MLT Method Definitions
Spectrum MLTIntegrator::L(const Scene &scene, MemoryArena &arena,
                          const std::unique_ptr<Distribution1D> &lightDistr,
                          const std::unordered_map<const Light *, size_t> &lightToIndex,
                          MLTSampler &sampler, int depth, Point2f *pRaster) {
    sampler.StartStream(cameraStreamIndex);
    // Determine the number of available strategies and pick a specific one
    int s, t, nStrategies;
    if (depth == 0) {
        nStrategies = 1;
        s = 0;
        t = 2;
    } else {
        nStrategies = depth + 2;
        s = std::min((int)(sampler.Get1D() * nStrategies), nStrategies - 1);
        t = nStrategies - s;
    }

    // Generate a camera subpath with exactly _t_ vertices
    Vertex *cameraVertices = arena.Alloc<Vertex>(t);
    Bounds2f sampleBounds = (Bounds2f)camera->film->GetSampleBounds();
    *pRaster = sampleBounds.Lerp(sampler.Get2D());
    if (GenerateCameraSubpath(scene, sampler, arena, t, *camera, *pRaster,
                              cameraVertices) != t)
        return Spectrum(0.f);

    // Generate a light subpath with exactly _s_ vertices
    sampler.StartStream(lightStreamIndex);
    Vertex *lightVertices = arena.Alloc<Vertex>(s);
    if (GenerateLightSubpath(scene, sampler, arena, s, cameraVertices[0].time(),
                             *lightDistr, lightToIndex, lightVertices) != s)
        return Spectrum(0.f);

    // Execute connection strategy and return the radiance estimate
    sampler.StartStream(connectionStreamIndex);
    return ConnectBDPT(scene, lightVertices, cameraVertices, s, t, *lightDistr,
                       lightToIndex, *camera, sampler, pRaster) *
           nStrategies;
}