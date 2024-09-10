static inline real_t k_scalar(Body2DSW *a,Body2DSW *b,const Vector2& rA, const Vector2& rB, const Vector2& n) {


	real_t value=0;


	{
		value+=a->get_inv_mass();
		real_t rcn = rA.cross(n);
		value+=a->get_inv_inertia() * rcn * rcn;
	}

	if (b) {

		value+=b->get_inv_mass();
		real_t rcn = rB.cross(n);
		value+=b->get_inv_inertia() * rcn * rcn;
	}

	return value;

}