void TMercury::OnHit(value_type x1, state_type y1, value_type &x2, state_type &y2, int &polarisation,
			const double normal[3], solid *leaving, solid *entering, bool &trajectoryaltered, bool &traversed){
	trajectoryaltered = false;
	traversed = true;
	
	Reflect(x1, y1, x2, y2, polarisation, normal, leaving, entering, trajectoryaltered, traversed);
}