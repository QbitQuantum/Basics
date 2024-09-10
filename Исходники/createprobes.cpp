void CreateRadianceProbes::Render(const Scene *scene) {
    // Compute scene bounds and initialize probe integrators
    if (bbox.pMin.x > bbox.pMax.x)
        bbox = scene->WorldBound();
    surfaceIntegrator->Preprocess(scene, camera, this);
    volumeIntegrator->Preprocess(scene, camera, this);
    Sample *origSample = new Sample(NULL, surfaceIntegrator, volumeIntegrator,
                                    scene);

    // Compute sampling rate in each dimension
    Vector delta = bbox.pMax - bbox.pMin;
    int nProbes[3];
    for (int i = 0; i < 3; ++i)
        nProbes[i] = max(1, Ceil2Int(delta[i] / probeSpacing));

    // Allocate SH coefficient vector pointers for sample points
    int count = nProbes[0] * nProbes[1] * nProbes[2];
    Spectrum **c_in = new Spectrum *[count];
    for (int i = 0; i < count; ++i)
        c_in[i] = new Spectrum[SHTerms(lmax)];

    // Compute random points on surfaces of scene

    // Create scene bounding sphere to catch rays that leave the scene
    Point sceneCenter;
    float sceneRadius;
    scene->WorldBound().BoundingSphere(&sceneCenter, &sceneRadius);
    Transform ObjectToWorld(Translate(sceneCenter - Point(0,0,0)));
    Transform WorldToObject(Inverse(ObjectToWorld));
    Reference<Shape> sph = new Sphere(&ObjectToWorld, &WorldToObject,
        true, sceneRadius, -sceneRadius, sceneRadius, 360.f);
    Reference<Material> nullMaterial = Reference<Material>(NULL);
    GeometricPrimitive sphere(sph, nullMaterial, NULL);
    vector<Point> surfacePoints;
    uint32_t nPoints = 32768, maxDepth = 32;
    surfacePoints.reserve(nPoints + maxDepth);
    Point pCamera = camera->CameraToWorld(camera->shutterOpen,
                                          Point(0, 0, 0));
    surfacePoints.push_back(pCamera);
    RNG rng;
    while (surfacePoints.size() < nPoints) {
        // Generate random path from camera and deposit surface points
        Point pray = pCamera;
        Vector dir = UniformSampleSphere(rng.RandomFloat(), rng.RandomFloat());
        float rayEpsilon = 0.f;
        for (uint32_t i = 0; i < maxDepth; ++i) {
            Ray ray(pray, dir, rayEpsilon, INFINITY, time);
        
            Intersection isect;
            if (!scene->Intersect(ray, &isect) &&
                !sphere.Intersect(ray, &isect))
                break;
        
            surfacePoints.push_back(ray(ray.maxt));
        
            DifferentialGeometry &hitGeometry = isect.dg;
            pray = isect.dg.p;
            rayEpsilon = isect.rayEpsilon;
            hitGeometry.nn = Faceforward(hitGeometry.nn, -ray.d);
        
            dir = UniformSampleSphere(rng.RandomFloat(), rng.RandomFloat());
            dir = Faceforward(dir, hitGeometry.nn);
        }
    }

    // Launch tasks to compute radiance probes at sample points
    vector<Task *> tasks;
    ProgressReporter prog(count, "Radiance Probes");
    for (int i = 0; i < count; ++i)
        tasks.push_back(new CreateRadProbeTask(i, nProbes, time,
                                   bbox, lmax, includeDirectInProbes,
                                   includeIndirectInProbes, nIndirSamples,
                                   prog, origSample, surfacePoints,
                                   scene, this, c_in[i]));
    EnqueueTasks(tasks);
    WaitForAllTasks();
    for (uint32_t i = 0; i < tasks.size(); ++i)
        delete tasks[i];
    prog.Done();

    // Write radiance probe coefficients to file
    FILE *f = fopen(filename.c_str(), "w");
    if (f) {
        if (fprintf(f, "%d %d %d\n", lmax, includeDirectInProbes?1:0, includeIndirectInProbes?1:0) < 0 ||
            fprintf(f, "%d %d %d\n", nProbes[0], nProbes[1], nProbes[2]) < 0 ||
            fprintf(f, "%f %f %f %f %f %f\n", bbox.pMin.x, bbox.pMin.y, bbox.pMin.z,
              bbox.pMax.x, bbox.pMax.y, bbox.pMax.z) < 0)
            Severe("Error writing radiance file \"%s\"", filename.c_str());
        for (int i = 0; i < nProbes[0] * nProbes[1] * nProbes[2]; ++i) {
            for (int j = 0; j < SHTerms(lmax); ++j) {
                fprintf(f, "  ");
                if (c_in[i][j].Write(f) == false)
                    Severe("Error writing radiance file \"%s\"", filename.c_str());
                fprintf(f, "\n");
            }
            fprintf(f, "\n");
        }
        fclose(f);
    }
    for (int i = 0; i < nProbes[0] * nProbes[1] * nProbes[2]; ++i)
        delete[] c_in[i];
    delete[] c_in;
    delete origSample;
}