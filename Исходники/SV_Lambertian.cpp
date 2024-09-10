RGBColor
SV_Lambertian::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const {

	Vector3D w = sr.normal;
	Vector3D v = Vector3D(0.0034, 1, 0.0071) ^ w;
	v.normalize();
	Vector3D u = v ^ w;

	Point3D sp = sampler_ptr->sample_hemisphere();
	wi = sp.x * u + sp.y * v + sp.z * w;
	wi.normalize(); 	

	return (kd * cd->get_color(sr) * invPI); 
}