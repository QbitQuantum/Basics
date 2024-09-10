void paperweight(Pt3D pt[], Pt3D F) {
	Pt3D g = center(pt);
	double mn = 10000, mx = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = i+1; j < 5; j++) {
			for (int k = j+1; k < 5; k++) {
				// find the bottom facet
				auto t = facet(pt[i], pt[j], pt[k], pt, 5);
				if (t.first == false)
					continue;
				Plane bottom = Plane(pt[i], pt[j], pt[k]);
				Pt3D proj_g = bottom.project(g);
				if (!stable(t.second, proj_g))
					continue;
				double dist = bottom.distance(F);
				mn = min(mn, dist), mx = max(mx, dist);
//				printf("%lf\n", dist);
			}
		}
	}
	printf("%.5lf %.5lf\n", mn, mx);
}