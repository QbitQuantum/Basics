Vec trace(const Ray& r, const int index, const int num_samps) {
	// ray-sphere intersection
	double t;
	if (!intersect(r, t)) return Vec();

	// compute the intersection data
	const Vec x = r.o + r.d * t, n = (x - sph.p).normalized(), w = -r.d;

	// compute Fresnel transmittance at point of emergence
	const double T21 = 1.0 - fresnel(w.dot(n), eta);

	// integration of the BSSRDF over the surface
	unsigned int xi = next_rand(index);
	Vec result;
	for (int i = 0; i < num_samps; i++) {
		// generate a sample
		Vec sp, sn, sw;
		sample(i, Vec(hal(2, index), hal(3, index), 0.0), sp, sn);
		sw = Vec(1, 1, -0.5).normalized();

		// directional light source
		const double radiance = 8.0*PI;
		const double cos_wi_n = sn.dot(sw);
		if (cos_wi_n > 0.0) {
			// Russian roulette (note that accept_prob can be any value in (0, 1))
			const double accept_prob = exp(-(sp - x).len() * min_sigma_tr);
			if ((xi / rand_range) < accept_prob) {
				const double T12 = 1.0 - fresnel(cos_wi_n, eta);
				const double Li_cos = T12 * radiance * cos_wi_n / (samplePDF * accept_prob);

				for (int j = 0; j < 3; j++) result[j] += bssrdf(sp, sn, sw, x, n, w, j) * Li_cos;

				// reciprocal evaulation with the reciprocity hack
				//for (int j = 0; j < 3; j++) result[j] += 0.5 * (bssrdf(sp, sn, sw, x, n, w, j) + bssrdf(x, n, w, sp, sn, sw, j)) * Li_cos;
			}
			xi = next_rand(xi);
		}
	}
	return T21 * result / (double)num_samps;
}