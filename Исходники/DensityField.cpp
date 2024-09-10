void DensityField::computePiDensity(const PerspectiveCamera& cam, const Scene& scene) {
    printInfo("Performing fog density preintegration.");
    printInfo("This will take a few seconds. Please wait! :-)");
    const auto& res = m_pi_dens_res = ivec3{cam.resolution(), m_res.z};
    // Allocate storage
    m_pi_dens_data = new float[piDensSize()];
    // Set up render loop
    assert(0 == res.x % PACKET_SZ && 0 == res.y % PACKET_SZ);
    const ivec2 n_packets{cam.resolution() / PACKET_SZ};
    #pragma omp parallel for
    for (int p_j = 0; p_j < n_packets.y; ++p_j)
        for (int p_i = 0; p_i < n_packets.x; ++p_i)
            for (int p_y = 0; p_y < PACKET_SZ; ++p_y)
                for (int p_x = 0; p_x < PACKET_SZ; ++p_x) {
                    const int x{p_x + p_i * PACKET_SZ};
                    const int y{p_y + p_j * PACKET_SZ};
                    // Use pixel center: offset by 0.5
                    rt::Ray ray{cam.getPrimaryRay(x + 0.5f, y + 0.5f)};
                    // Intersect the bounding volume of density field
                    const auto is = m_bbox.intersect(ray);
                    if (is) {
                        // Determine distance to the geometry
                        scene.trace(ray);
                        // Compute parametric ray bounds
                        const float t_min{max(is.entr, 0.0f)};
                        const float t_max{min(is.exit, ray.inters.distance)};
                        // Sample density at interval endpoints
                        const int   n_intervals{res.z * 4};
                        const float dt{(t_max - t_min) / n_intervals};
                        // Perform ray marching
                        float prev_dens{sampleDensity(ray.o + t_min * ray.d)};
                        float dens{0.0f};
                        for (int i = 1; i <= n_intervals; ++i) {
                            // Distance to the end of the interval
                            const float t{t_min + i * dt};
                            const float curr_dens{sampleDensity(ray.o + t * ray.d)};
                            // Use trapezoidal rule for integration
                            dens += 0.5f * (curr_dens + prev_dens);
                            prev_dens = curr_dens;
                            if (2 == i % 4) {
                                // We are in the middle of the camera-space voxel (froxel)
                                const int z{i / 4};
                                m_pi_dens_data[x + y * res.x + z * res.x * res.y] = dens * dt;
                            }
                        }     
                    } else {
                        // Set density to zero along the ray
                        for (int z = 0; z < res.z; ++z) {
                            m_pi_dens_data[x + y * res.x + z * res.x * res.y] = 0.0f;
                        }
                    }
                }
    // Save it to disk
    writePiDens("Assets\\pi_df.3dt");
    // Load data into OpenGL texture
    createPiDensTex();
}