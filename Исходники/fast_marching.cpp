/*------------------------------------------------------------------------------*/
FM_INLINE
FastMarchingVertex * UnfoldTriangle(const Eigen::MatrixXd &V, const Eigen::MatrixXi &F,
	const Eigen::MatrixXi &TT, const  Eigen::MatrixXi &TTi,
	std::vector<struct FastMarchingVertex> &vertices,
	int f, int v, int v1, int v2,
	FM_Float& dist, FM_Float& dot1, FM_Float& dot2)
{
	const Eigen::Vector3d& p = V.row(v);// vert.GetPosition();
	const Eigen::Vector3d& p1 = V.row(v1);//vert1.GetPosition();
	const Eigen::Vector3d& p2 = V.row(v2);//vert2.GetPosition();

	Eigen::Vector3d e1 = p1 - p;
	FM_Float rNorm1 = e1.norm(); //~e1
	e1.normalize(); // e1 /= rNorm1;
	Eigen::Vector3d e2 = p2 - p;
	FM_Float rNorm2 = e2.norm(); // ~e2;
	e2.normalize(); // e2 /= rNorm2;

	FM_Float dot = e1.adjoint()*e2;// e1*e2;
	FM_ASSERT(dot < 0);

	/* the equation of the lines defining the unfolding region [e.g. line 1 : {x ; <x,eq1>=0} ]*/
	Eigen::Vector2d eq1 = Eigen::Vector2d(dot, sqrt(1 - dot*dot));
	Eigen::Vector2d eq2 = Eigen::Vector2d(1, 0);

	/* position of the 2 points on the unfolding plane */
	Eigen::Vector2d x1(rNorm1, 0);
	Eigen::Vector2d x2 = eq1*rNorm2;

	/* keep track of the starting point */
	Eigen::Vector2d xstart1 = x1;
	Eigen::Vector2d xstart2 = x2;

	FastMarchingVertex* pV1 = &(vertices[v1]);
	FastMarchingVertex* pV2 = &(vertices[v2]);

	
	int cur_f, cur_v;
	
	get_oppisite_f_v(F, TT,TTi, f,v, cur_f, cur_v);

	//FM_GeodesicFace* pCurFace = (FM_GeodesicFace*)CurFace.GetFaceNeighbor(vert);


	int nNum = 0;
	while (nNum < 50 && cur_f != -1) // NULL)
	{
		//	FastMarchingVertex* pV = (FastMarchingVertex*)pCurFace->GetVertex(*pV1, *pV2); //opposite vertex to face and edge(pV1,pV2)
		//	FM_ASSERT(pV != NULL);
		FastMarchingVertex* pV = &(vertices[cur_v]); //opposite vertex to face and vert
													 /*
													 e1 = pV2->GetPosition() - pV1->GetPosition();
													 FM_Float rNorm1 = ~e1;
													 e1 /= rNorm1;
													 e2 = pV->GetPosition() - pV1->GetPosition();
													 FM_Float rNorm2 = ~e2;
													 e2 /= rNorm2;
													 */

		Eigen::Vector3d e1 = V.row(pV2->vid) - V.row(pV1->vid);
		FM_Float rNorm1 = e1.norm(); //~e1
		e1.normalize(); // e1 /= rNorm1;
		Eigen::Vector3d e2 = V.row(pV->vid) - V.row(pV1->vid);
		FM_Float rNorm2 = e2.norm(); // ~e2;
		e2.normalize(); // e2 /= rNorm2;

						/* compute the position of the new point x on the unfolding plane (via a rotation of -alpha on (x2-x1)/rNorm1 )
						| cos(alpha) sin(alpha)|
						x = |-sin(alpha) cos(alpha)| * [x2-x1]*rNorm2/rNorm1 + x1   where cos(alpha)=dot
						*/
		Eigen::Vector2d vv = (x2 - x1)*rNorm2 / rNorm1;
		dot = e1.adjoint()*e2;  //e1*e2;
								//	Eigen::Vector2d x = vv.Rotate2D();////vv.Rotate(-acos(dot)) + x1;

		Eigen::Rotation2D<double> rot2(-acos(dot));
		Eigen::Vector2d x = rot2*vv + x1;  //dhw to check


										   /* compute the intersection points.
										   We look for x=x1+lambda*(x-x1) or x=x2+lambda*(x-x2) with <x,eqi>=0, so */
		FM_Float lambda11 = -(x1.dot(eq1)) / ((x - x1).dot(eq1));	 //-(x1*eq1) / ((x - x1)*eq1);	// left most 
		FM_Float lambda12 = -(x1.dot(eq2)) / ((x - x1).dot(eq2));  //-(x1*eq2) / ((x - x1)*eq2);	// right most
		FM_Float lambda21 = -(x2.dot(eq1)) / ((x - x2).dot(eq1)); //-(x2*eq1) / ((x - x2)*eq1);	// left most 
		FM_Float lambda22 = -(x2.dot(eq2)) / ((x - x2).dot(eq2));   //-(x2*eq2) / ((x - x2)*eq2);	// right most
		bool bIntersect11 = (lambda11 >= 0) && (lambda11 <= 1);
		bool bIntersect12 = (lambda12 >= 0) && (lambda12 <= 1);
		bool bIntersect21 = (lambda21 >= 0) && (lambda21 <= 1);
		bool bIntersect22 = (lambda22 >= 0) && (lambda22 <= 1);
		if (bIntersect11 && bIntersect12)
		{
			//			FM_ASSERT( !bIntersect21 && !bIntersect22 );
			/* we should unfold on edge [x x1] */
			//	pCurFace = (FM_GeodesicFace*)pCurFace->GetFaceNeighbor(*pV2);
			f = cur_f;
			get_oppisite_f_v(F, TT,TTi, f, pV2->vid, cur_f, cur_v);

			pV2 = pV;
			x2 = x;
		}
		else if (bIntersect21 && bIntersect22)
		{
			//			FM_ASSERT( !bIntersect11 && !bIntersect12 );
			/* we should unfold on edge [x x2] */
			//	pCurFace = (FM_GeodesicFace*)pCurFace->GetFaceNeighbor(*pV1);
			f = cur_f;
			get_oppisite_f_v(F, TT,TTi, f, pV1->vid, cur_f, cur_v);

			pV1 = pV;
			x1 = x;
		}
		else
		{
			FM_ASSERT(bIntersect11 && !bIntersect12 &&
				!bIntersect21 && bIntersect22);
			/* that's it, we have found the point */
			dist = x.norm(); // ~x;
			dot1 = x.dot(xstart1) / (dist * xstart1.norm());//  ~xstart1);
			dot2 = x.dot(xstart2) / (dist * xstart2.norm());// ~xstart2);
			return pV;
		}
		nNum++;
	}

	return NULL;
}