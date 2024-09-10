void dNormalize3_slow (dVector3 a)
{
	dReal a0,a1,a2,aa0,aa1,aa2,l;
	dAASSERT (a);
	a0 = a[0];
	a1 = a[1];
	a2 = a[2];
	aa0 = dFabs(a0);
	aa1 = dFabs(a1);
	aa2 = dFabs(a2);
	if (aa1 > aa0) {
		if (aa2 > aa1) {
			goto aa2_largest;
		}
		else {		// aa1 is largest
			a0 /= aa1;
			a2 /= aa1;
			l = dRecipSqrt (a0*a0 + a2*a2 + 1);
			a[0] = a0*l;
			a[1] = (dReal)_copysign(l,a1);
			a[2] = a2*l;
		}
	}
	else {
		if (aa2 > aa0) {
aa2_largest:	// aa2 is largest
			a0 /= aa2;
			a1 /= aa2;
			l = dRecipSqrt (a0*a0 + a1*a1 + 1);
			a[0] = a0*l;
			a[1] = a1*l;
			a[2] = (dReal)_copysign(l,a2);
		}
		else {		// aa0 is largest
			if (aa0 <= 0) {
				// dDEBUGMSG ("vector has zero size"); ... this messace is annoying
				a[0] = 1;	// if all a's are zero, this is where we'll end up.
				a[1] = 0;	// return a default unit length vector.
				a[2] = 0;
				return;
			}
			a1 /= aa0;
			a2 /= aa0;
			l = dRecipSqrt (a1*a1 + a2*a2 + 1);
			a[0] = (dReal)_copysign(l,a0);
			a[1] = a1*l;
			a[2] = a2*l;
		}
	}
}