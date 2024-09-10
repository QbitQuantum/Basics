bool Surface3D::deleteRandomAtomKmc(AllNeighbors const& neighbors,
    size_t z_min,
    const std::vector<bool>& mask,
    const float* rates) {
    const int yC = static_cast<int>(m_surfaces2D[z_min].size());
    const int xC = static_cast<int>(m_surfaces2D[z_min][0].size());
    bool result = false;

    static std::mt19937 randomProviderDevice(std::random_device {} ());

    auto const i = std::uniform_int_distribution<size_t>{0, m_surfaceAtoms.size() - 1} (randomProviderDevice);

    auto& surfAtom = m_surfaceAtoms[i];
    int x = surfAtom.x;
    int y = surfAtom.y;
    int z = surfAtom.z;
    unsigned char a = surfAtom.type;
    auto& surfaceZY = m_surfaces2D[z][y];

    if (isMaskedAtom(surfAtom, mask)) {
        return result;
    }

    int const bonds = surfaceZY[x].getAtoms()[a].firstNeighborsCount;

    if (bonds <= 0) {
        std::swap(m_surfaceAtoms[i], m_surfaceAtoms.back());
        m_surfaceAtoms.pop_back();
        std::swap(m_surfaceAtoms[i], m_surfaceAtoms.back());
        return false;
    }

    if (!shouldDeleteAtom(bonds, rates)) {
        return result;
    }

    deleteAtom(x, y, z, a, i);

    // Delete appropriate edge atom too
    if (x == 4 || x == 5) {
        deleteAtom(5 - x, y, z, a);
    }

    if (x == xC - 6 || x == xC - 5) {
        deleteAtom(2 * (xC - 1) - 5 - x, y, z, a);
    }

    if (y == 4 || y == 5) {
        deleteAtom(x, 5 - y, z, a);
    }

    if (y == yC - 6 || y == yC - 5) {
        deleteAtom(x, 2 * yC - 7 - y, z, a);
    }

    if (z >= static_cast<decltype(z)>(size()) - 3) {
        addLayer(neighbors, xC, yC, static_cast<int>(size()));
    }
    
    return result;
}