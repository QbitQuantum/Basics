//--------------------------------------------------------------------------------------------------
// buildNeighbors
void BasicSPH::buildNeighbors()
{
    // Reserve space and initialize neighbors' data
    _neighbors.clear();
    _neighbors.resize(_particles.size());

    // Init spatial grid
    Vec3d borders(_h*2.0, _h*2.0, _h*2.0);
    Vec3d gridMin = _volumeMin;
    gridMin -= borders;
    Vec3d gridMax = _volumeMax;
    gridMax += borders;
    SpatialGrid<long> grid(_h, gridMin, gridMax);

    // Insert particles into grid
    for (long p=0; p<_particles.size(); ++p)
    {
        grid.insert(p, _particles[p].pos);
    }

    // Use grid to retrieve neighbor particles
    double h2 = _h*_h;
    std::vector<long*> nearbyParticles;
    for (long p=0; p<_particles.size(); ++p)
    {
        const SPHParticle &particle = _particles[p];

        // Get nearby particles
        grid.getElements(particle.pos, _h, nearbyParticles);

        // Find particles that are within smoothing radius
        _neighbors[p].reserve(50);
        for (long i=0; i<nearbyParticles.size(); ++i)
        {
            long nID = *nearbyParticles[i];
            const SPHParticle &neighborParticle = _particles[nID];

            // Skip current particle
            if (nID==p)
                continue;

            Vec3d xij = particle.pos - neighborParticle.pos;

            // Check if distance is lower than smoothing radius
            double dist2 = xij.dot(xij);
            if (dist2 < h2)
            {
                // Yup! Add the particle to the neighbors list along with
                // some precomputed informations
                _neighbors[p].push_back(Neighbor(nID, xij, sqrt(dist2)));
            }
        }
    }
}