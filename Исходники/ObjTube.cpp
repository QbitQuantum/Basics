/*
====================
Tube::intersect
	Computes intersection between the Tube and the ray, and returns itself if 
	it is hit or NULL if it is not along with the point of intersection
====================
*/
SceneObject* Tube::intersect(Ray* r, Point &intersect) {
	Vector dist = this->origin - r->start;

	//norm(dist);
	//norm(r->dir);

	//double a = dot3(r->dir,r->dir);
	//double b = 2 * dot3(r->start - this->origin,r->dir);
	//double c = dot3(r->start - this->origin,r->start - this->origin) - this->radius * this->radius;

	//double disc = discrim(a,b,c);

	////Parallel to tube, does not intersect
	//if(dot3(r->dir,this->up) == 0) return false;
	//else if(disc >= 0) { //Find closest intersection
	//	double discSqrt = sqrt(disc);
	//	double quad;
	//	if (b < 0)	quad = (-b - discSqrt)/2.f;
	//	else quad = (-b + discSqrt)/2.f;

	//	double t0 = quad/a;
	//	double t1 = c/quad;
	//	if(t0 > t1) swap(t0,t1);

	//	double t;
	//	if(t0 < 0 && t1 < 0) return false;
	//	if(t0 < 0) t = t1;
	//	else t = t0;

	//	intersect = r->start + t * r->dir;
	//	return this;
	//}
	//return NULL;
	
	/* 
	Ray: O + V * t
	Cylinder: [this->origin,this->up,this->radius]
	A = this->origin
	O = r->start
	V = r->dir
	*/

	Vector AB = this->up;
	Vector AO = r->start - this->origin;
	Vector AOxAB = AO.cross(AB);
	Vector VxAB = r->dir.cross(AB);
	double ab2 = AB.dot(AB);

	double a = VxAB.dot(VxAB);
	double b = 2 * VxAB.dot(AOxAB);
	double c = AOxAB.dot(AOxAB) - this->radius*this->radius * ab2;

	double t = quadratic(a,b,c);
	if(t < 0) return NULL;

	intersect = r->start + t * r->dir;
	return this;
}