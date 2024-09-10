std::vector<TestIntegrator> GetIntegrators() {
    std::vector<TestIntegrator> integrators;

    Point2i resolution(10, 10);
    AnimatedTransform identity(new Transform, 0, new Transform, 1);

    for (auto scene : GetScenes()) {
        // Path tracing integrators
        for (auto sampler : GetSamplers(Bounds2i(Point2i(0, 0), resolution))) {
            std::unique_ptr<Filter> filter(new BoxFilter(Vector2f(0.5, 0.5)));
            Film *film =
                new Film(resolution, Bounds2f(Point2f(0, 0), Point2f(1, 1)),
                         std::move(filter), 1., "test.exr", 1.);
            std::shared_ptr<Camera> camera =
                std::make_shared<PerspectiveCamera>(
                    identity, Bounds2f(Point2f(-1, -1), Point2f(1, 1)), 0., 1.,
                    0., 10., 45, film, nullptr);

            Integrator *integrator =
                new PathIntegrator(8, camera, sampler.first);
            integrators.push_back({integrator, film,
                                   "Path, depth 8, Perspective, " +
                                       sampler.second + ", " +
                                       scene.description,
                                   scene});
        }

        for (auto sampler : GetSamplers(Bounds2i(Point2i(0, 0), resolution))) {
            std::unique_ptr<Filter> filter(new BoxFilter(Vector2f(0.5, 0.5)));
            Film *film =
                new Film(resolution, Bounds2f(Point2f(0, 0), Point2f(1, 1)),
                         std::move(filter), 1., "test.exr", 1.);
            std::shared_ptr<Camera> camera =
                std::make_shared<OrthographicCamera>(
                    identity, Bounds2f(Point2f(-.1, -.1), Point2f(.1, .1)), 0.,
                    1., 0., 10., film, nullptr);

            Integrator *integrator =
                new PathIntegrator(8, camera, sampler.first);
            integrators.push_back({integrator, film,
                                   "Path, depth 8, Ortho, " + sampler.second +
                                       ", " + scene.description,
                                   scene});
        }

        // Volume path tracing integrators
        for (auto sampler : GetSamplers(Bounds2i(Point2i(0, 0), resolution))) {
            std::unique_ptr<Filter> filter(new BoxFilter(Vector2f(0.5, 0.5)));
            Film *film =
                new Film(resolution, Bounds2f(Point2f(0, 0), Point2f(1, 1)),
                         std::move(filter), 1., "test.exr", 1.);
            std::shared_ptr<Camera> camera =
                std::make_shared<PerspectiveCamera>(
                    identity, Bounds2f(Point2f(-1, -1), Point2f(1, 1)), 0., 1.,
                    0., 10., 45, film, nullptr);

            Integrator *integrator =
                new VolPathIntegrator(8, camera, sampler.first);
            integrators.push_back({integrator, film,
                                   "VolPath, depth 8, Perspective, " +
                                       sampler.second + ", " +
                                       scene.description,
                                   scene});
        }
        for (auto sampler : GetSamplers(Bounds2i(Point2i(0, 0), resolution))) {
            std::unique_ptr<Filter> filter(new BoxFilter(Vector2f(0.5, 0.5)));
            Film *film =
                new Film(resolution, Bounds2f(Point2f(0, 0), Point2f(1, 1)),
                         std::move(filter), 1., "test.exr", 1.);
            std::shared_ptr<Camera> camera =
                std::make_shared<OrthographicCamera>(
                    identity, Bounds2f(Point2f(-.1, -.1), Point2f(.1, .1)), 0.,
                    1., 0., 10., film, nullptr);

            Integrator *integrator =
                new VolPathIntegrator(8, camera, sampler.first);
            integrators.push_back({integrator, film,
                                   "VolPath, depth 8, Ortho, " +
                                       sampler.second + ", " +
                                       scene.description,
                                   scene});
        }

        // BDPT
        for (auto sampler : GetSamplers(Bounds2i(Point2i(0, 0), resolution))) {
            std::unique_ptr<Filter> filter(new BoxFilter(Vector2f(0.5, 0.5)));
            Film *film =
                new Film(resolution, Bounds2f(Point2f(0, 0), Point2f(1, 1)),
                         std::move(filter), 1., "test.exr", 1.);
            std::shared_ptr<Camera> camera =
                std::make_shared<PerspectiveCamera>(
                    identity, Bounds2f(Point2f(-1, -1), Point2f(1, 1)), 0., 1.,
                    0., 10., 45, film, nullptr);

            Integrator *integrator =
                new BDPTIntegrator(sampler.first, camera, 6, false, false);
            integrators.push_back({integrator, film,
                                   "BDPT, depth 8, Perspective, " +
                                       sampler.second + ", " +
                                       scene.description,
                                   scene});
        }
#if 0
    // Ortho camera not currently supported with BDPT.
    for (auto sampler : GetSamplers(Bounds2i(Point2i(0,0), resolution))) {
      std::unique_ptr<Filter> filter(new BoxFilter(Vector2f(0.5, 0.5)));
      Film *film = new Film(resolution, Bounds2f(Point2f(0,0), Point2f(1,1)),
                            std::move(filter), 1., "test.exr", 1.);
      std::shared_ptr<Camera> camera = std::make_shared<OrthographicCamera>(
          identity, Bounds2f(Point2f(-.1,-.1), Point2f(.1,.1)), 0., 1.,
          0., 10., film, nullptr);

      Integrator *integrator = new BDPTIntegrator(sampler.first, camera, 8,
                                            false, false);
      integrators.push_back({integrator, film,
              "BDPT, depth 8, Ortho, " + sampler.second + ", " +
              scene.description, scene});
    }
#endif

        // MLT
        {
            std::unique_ptr<Filter> filter(new BoxFilter(Vector2f(0.5, 0.5)));
            Film *film =
                new Film(resolution, Bounds2f(Point2f(0, 0), Point2f(1, 1)),
                         std::move(filter), 1., "test.exr", 1.);
            std::shared_ptr<Camera> camera =
                std::make_shared<PerspectiveCamera>(
                    identity, Bounds2f(Point2f(-1, -1), Point2f(1, 1)), 0., 1.,
                    0., 10., 45, film, nullptr);

            Integrator *integrator = new MLTIntegrator(
                camera, 8 /* depth */, 100000 /* n bootstrap */,
                1000 /* nchains */, 1024 /* mutations per pixel */,
                0.01 /* sigma */, 0.3 /* large step prob */);
            integrators.push_back(
                {integrator, film,
                 "MLT, depth 8, Perspective, " + scene.description, scene});
        }
    }

    return integrators;
}