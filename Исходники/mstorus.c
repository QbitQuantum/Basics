void compute_torus_center (double probe_radius, struct sphere *sphere1,struct sphere *sphere2, double torus_center[3])
{
	int k;
	double radius1, radius2, asymmetry, distance12_squared;
	char message[MAXLINE];
    struct cept *ex;

	distance12_squared =
		distance_squared (sphere1 -> center, sphere2 -> center);
	if (distance12_squared <= 0.0) {
		ex = new_cept (GEOMETRY_ERROR,  DEGENERACY,  FATAL_SEVERITY);
		add_function (ex, "compute_torus_center");
		add_source (ex, "mstorus.c");
		add_message (ex, "coincident atoms");
		add_atom (ex, sphere1);
		add_atom (ex, sphere2);
		return;
	}
	radius1 = sphere1 -> radius;
	radius2 = sphere2 -> radius;
	asymmetry = (radius1 + probe_radius) * (radius1 + probe_radius) -
		(radius2 + probe_radius) * (radius2 + probe_radius);
	for (k = 0; k < 3; k++)
		torus_center[k] = 0.5 * (sphere1 -> center[k] + sphere2 -> center[k])
			+ 0.5 * ( asymmetry / distance12_squared) *
			(sphere2 -> center[k] - sphere1 -> center[k]);
}