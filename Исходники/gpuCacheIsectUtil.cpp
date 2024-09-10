	bool gpuCacheIsectUtil::getClosestPointOnTri(const MPoint &toThisPoint, const MPoint &pt1, const MPoint &pt2, const MPoint &pt3, MPoint &theClosestPoint, double &currDist) 
	{
		double		sum, a, b, c, len, dist;
		MMatrix mat;
		mat.setToIdentity();
		mat[2][0] = mat[2][1] = mat[2][2] = 1.;

		MVector v = toThisPoint - pt1;
		MVector v12 = pt2 - pt1;
		MVector v13 = pt3 - pt1;
		MVector norm = v12 ^ v13;
		len = norm * norm;
		if (len < 1.175494351e-38F) return false;
		len = ( norm * v ) / len;

		MPoint pnt = toThisPoint - len * norm;

		// Do a quick test first
		if (pnt.distanceTo(toThisPoint) >= currDist)
			return false;

		int i, j;				// Find best plane to project to
		if (fabs(norm[0]) > fabs(norm[1]))
		{
			if (fabs(norm[0]) > fabs(norm[2]))
			{
				i = 1; j = 2;
			}
			else
			{
				i = 0; j = 1;
			}
		}
		else
		{
			if (fabs(norm[1]) > fabs(norm[2]))
			{
				i = 0; j = 2;
				// i = 2; j = 0;
			}
			else
			{
				i = 0; j = 1;
			}
		}

		mat[0][0] = pt1[i]; mat[0][1] = pt2[i]; mat[0][2] = pt3[i]; 
		mat[1][0] = pt1[j]; mat[1][1] = pt2[j]; mat[1][2] = pt3[j]; 

		MMatrix	matInv = mat.inverse();
		MPoint abc(pnt[i], pnt[j], 1, 0);

		abc = matInv * abc;
		// Now abc is the barycentric coordinates of pnt
		// clip to inside triangle

		if (abc[0]<0) { // a < 0
			if (abc[1]<0) { // b < 0
				a = b = 0;
				c = 1;
			} else if (abc[2]<0) { // c < 0
				a = c = 0;
				b = 1;
			} else {
				a = 0;
				// c = BP dot BC / BC square;
				MVector v23 = pt3 - pt2; // BC
				MVector vp =  toThisPoint - pt2;  // BP

				c = ( vp * v23 ) / ( v23[0]*v23[0] + v23[1]*v23[1] + v23[2]*v23[2] );
				if (c<0) c = 0; else if (c>1) c = 1;
				b = 1 - c;
			}
		} else if (abc[1]<0) { // b < 0
			if (abc[2]<0) { // c < 0
				b = c = 0;
				a = 1;
				//} else if (abc[0]<0) { // a < 0
				//	b = a = 0;	// commented-code for optimization
				//	c = 1;		// leaving it in for readability (cyclic variations)
			} else {
				b = 0;
				// a = CP dot CA / CA square;
				MVector v31 = pt1 - pt3; // CA
				MVector vp =  toThisPoint - pt3;  // CP

				a = ( vp * v31 ) / ( v31[0]*v31[0] + v31[1]*v31[1] +v31[2]*v31[2] );
				if (a<0) a = 0; else if (a>1) a = 1;
				c = 1 - a;
			} 
		} else if (abc[2]<0) { // c < 0
			//if (abc[1]<0) { // b < 0
			//	c = b = 0;
			//	a = 1;
			//} else if (abc[0]<0) { // a < 0
			//	c = a = 0;
			//	b = 1;	// commented-code for optimization
			//} else {	// leaving it in for readability (cyclic variations)
			c = 0;
			// b = AP dot AB / AB square;
			//DIFF(v23, pt3, pt2); // AB
			MVector vp =  toThisPoint - pt1;  // AP

			b = ( vp * v12 ) / ( v12[0]*v12[0] + v12[1]*v12[1] + v12[2]*v12[2] );
			if (b<0) b = 0; else if (b>1) b = 1;
			a = 1 - b;
			//}
		} else {
			if (abc[0]>0) a = abc[0]; else a = 0;
			if (abc[1]>0) b = abc[1]; else b = 0;
			if (abc[2]>0) c = abc[2]; else c = 0;
		}
		sum = a+b+c;
		a /= sum ; b /= sum ; c /= sum ; 
		pnt = a * pt1 + b * pt2 + c * pt3;
		dist = pnt.distanceTo(toThisPoint);
		if ( dist < currDist)
		{			
			// Now it's really closer, keep it
			currDist = dist;
			theClosestPoint = pnt;
			return true;
		}
		return false;
	}