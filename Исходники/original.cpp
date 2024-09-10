Vec radiance(const Ray &r, int depth, unsigned short *Xi) {
	double t;                               // distance to intersection
	int id = 0;                               // id of intersected object
	if(!intersect(r, t, id)) return Vec(); // if miss, return black
	const Sphere &obj = spheres[id];        // the hit object
	Vec x = r.o + r.d*t, n = (x - obj.p).norm(), nl = n.dot(r.d) < 0 ? n : n*-1, f = obj.c;
	double p = f.x > f.y && f.x>f.z ? f.x : f.y > f.z ? f.y : f.z; // max refl
	if(depth > 255) return obj.e;
	if(++depth > 5) if(erand48(Xi) < p) f = f*(1 / p); else return obj.e; //R.R.
	if(obj.refl == DIFF) {                  // Ideal DIFFUSE reflection
		double r1 = 2 * M_PI*erand48(Xi), r2 = erand48(Xi), r2s = sqrt(r2);
		Vec w = nl, u = ((fabs(w.x) > .1 ? Vec(0, 1) : Vec(1)) % w).norm(), v = w%u;
		Vec d = (u*cos(r1)*r2s + v*sin(r1)*r2s + w*sqrt(1 - r2)).norm();
		return obj.e + f.mult(radiance(Ray(x, d), depth, Xi));
	}
	else if(obj.refl == SPEC)            // Ideal SPECULAR reflection
		return obj.e + f.mult(radiance(Ray(x, r.d - n * 2 * n.dot(r.d)), depth, Xi));
	Ray reflRay(x, r.d - n * 2 * n.dot(r.d));     // Ideal dielectric REFRACTION
	bool into = n.dot(nl) > 0;                // Ray from outside going in?
	double nc = 1, nt = 1.5, nnt = into ? nc / nt : nt / nc, ddn = r.d.dot(nl), cos2t;
	if((cos2t = 1 - nnt*nnt*(1 - ddn*ddn)) < 0)    // Total internal reflection
		return obj.e + f.mult(radiance(reflRay, depth, Xi));
	Vec tdir = (r.d*nnt - n*((into ? 1 : -1)*(ddn*nnt + sqrt(cos2t)))).norm();
	double a = nt - nc, b = nt + nc, R0 = a*a / (b*b), c = 1 - (into ? -ddn : tdir.dot(n));
	double Re = R0 + (1 - R0)*c*c*c*c*c, Tr = 1 - Re, P = .25 + .5*Re, RP = Re / P, TP = Tr / (1 - P);
	return obj.e + f.mult(depth > 2 ? (erand48(Xi) < P ?   // Russian roulette
		radiance(reflRay, depth, Xi)*RP : radiance(Ray(x, tdir), depth, Xi)*TP) :
		radiance(reflRay, depth, Xi)*Re + radiance(Ray(x, tdir), depth, Xi)*Tr);
}