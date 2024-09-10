void TestBSDF(void (*createBSDF)(BSDF*, MemoryArena&),
              const char* description) {
    MemoryArena arena;

    Options opt;
    pbrtInit(opt);

    const int thetaRes = CHI2_THETA_RES;
    const int phiRes = CHI2_PHI_RES;
    const int sampleCount = CHI2_SAMPLECOUNT;
    Float* frequencies = new Float[thetaRes * phiRes];
    Float* expFrequencies = new Float[thetaRes * phiRes];
    RNG rng;

    int index = 0;
    std::cout.precision(3);

    // Create BSDF, which requires creating a Shape, casting a Ray that
    // hits the shape to get a SurfaceInteraction object.
    BSDF* bsdf = nullptr;
    Transform t = RotateX(-90);
    Transform tInv = Inverse(t);
    {
        bool reverseOrientation = false;
        ParamSet p;

        std::shared_ptr<Shape> disk(
            new Disk(&t, &tInv, reverseOrientation, 0., 1., 0, 360.));
        Point3f origin(0.1, 1,
                       0);  // offset slightly so we don't hit center of disk
        Vector3f direction(0, -1, 0);
        Float tHit;
        Ray r(origin, direction);
        SurfaceInteraction isect;
        disk->Intersect(r, &tHit, &isect);
        bsdf = ARENA_ALLOC(arena, BSDF)(isect);
        createBSDF(bsdf, arena);
    }

    for (int k = 0; k < CHI2_RUNS; ++k) {
        /* Randomly pick an outgoing direction on the hemisphere */
        Point2f sample {rng.UniformFloat(), rng.UniformFloat()};
        Vector3f woL = CosineSampleHemisphere(sample);
        Vector3f wo = bsdf->LocalToWorld(woL);

        FrequencyTable(bsdf, wo, rng, sampleCount, thetaRes, phiRes,
                       frequencies);

        IntegrateFrequencyTable(bsdf, wo, sampleCount, thetaRes, phiRes,
                                expFrequencies);

        std::string filename = StringPrintf("/tmp/chi2test_%s_%03i.m",
                                            description, ++index);
        DumpTables(frequencies, expFrequencies, thetaRes, phiRes,
                   filename.c_str());

        auto result =
            Chi2Test(frequencies, expFrequencies, thetaRes, phiRes, sampleCount,
                     CHI2_MINFREQ, CHI2_SLEVEL, CHI2_RUNS);
        EXPECT_TRUE(result.first) << result.second << ", iteration " << k;
    }

    delete[] frequencies;
    delete[] expFrequencies;

    pbrtCleanup();
}