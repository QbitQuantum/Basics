int Gelatin::setNormals(int curNorIndex, int index, int adj[4]) {
    Vector3d x = particles[index]->x;
    Vector3d nor(0.0, 0.0, 0.0);

    for (int k = 0; k < 3; k++) {
        if (adj[k] != -1 && adj[k+1] != -1) {
            Vector3d first = (particles[adj[k]]->x - x).normalized();
            Vector3d second = (particles[adj[k+1]]->x - x).normalized();

            Vector3d res = first.cross(second).normalized();
            nor += res;
        }
    }

    if (adj[3] != -1 && adj[0] != -1) {
        Vector3d first = (particles[adj[3]]->x - x).normalized();
        Vector3d second = (particles[adj[0]]->x - x).normalized();

        Vector3d res = first.cross(second).normalized();
        nor += res;
    }

    nor = nor.normalized();

    norBuf[curNorIndex++] = nor(0);
    norBuf[curNorIndex++] = nor(1);
    norBuf[curNorIndex++] = nor(2);

    return curNorIndex;
}