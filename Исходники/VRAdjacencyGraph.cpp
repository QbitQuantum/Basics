void VRAdjacencyGraph::compCurvatures(int range) {
    vertex_curvatures.clear();
    auto sgeo = geo.lock();
    if (!sgeo) return;

    auto pos = sgeo->getMesh()->geo->getPositions();
    auto norms = sgeo->getMesh()->geo->getNormals();
    int N = pos->size();

    /*auto curvMax = [&](int i, int range) {
		Vec3d n = norms->getValue<Vec3f>(i);
		Vec3d vi = pos->getValue<Pnt3f>(i);
		float K = 0;
		float Kmax = 0;
		auto Ne = getNeighbors(i,range);
		if (Ne.size() == 0) return K;

		for (int j : Ne) {
			if (j >= N) continue;
			Vec3d d = pos->getValue<Pnt3f>(j) - vi;
			float k = 2*n.dot(d)/d.squareLength();
			if (abs(k) > Kmax) {
                K = k;
                Kmax = abs(k);
			}
		}

		return K;
    };*/

    auto curvAvg = [&](int i, int range) {
		Vec3d n = Vec3d(norms->getValue<Vec3f>(i));
		Pnt3f vi = pos->getValue<Pnt3f>(i);
		float K = 0;
		auto Ne = getNeighbors(i,range);
		if (Ne.size() == 0) return K;

		for (int j : Ne) {
			if (j >= N) continue;
			Vec3d d = Vec3d(pos->getValue<Pnt3f>(j) - vi);
			K += 2*n.dot(d)/d.length();
		}

		K /= Ne.size();
		return K;
    };

    vertex_curvatures.resize(N);
    for (int i = 0; i < N; i++) vertex_curvatures[i] = curvAvg(i,range);
}