/*! gts_vertex_principal_directions:
 *  @v: a #WVertex.
 *  @s: a #GtsSurface.
 *  @Kh: mean curvature normal (a #Vec3r).
 *  @Kg: Gaussian curvature (a real).
 *  @e1: first principal curvature direction (direction of largest curvature).
 *  @e2: second principal curvature direction.
 *
 *  Computes the principal curvature directions at a point given @Kh and @Kg, the mean curvature normal and
 *  Gaussian curvatures at that point, computed with gts_vertex_mean_curvature_normal() and
 *  gts_vertex_gaussian_curvature(), respectively.
 *
 *  Note that this computation is very approximate and tends to be unstable. Smoothing of the surface or the principal
 *  directions may be necessary to achieve reasonable results.
 */
void gts_vertex_principal_directions(WVertex *v, Vec3r Kh, real Kg, Vec3r &e1, Vec3r &e2)
{
	Vec3r N;
	real normKh;

	Vec3r basis1, basis2, d, eig;
	real ve2, vdotN;
	real aterm_da, bterm_da, cterm_da, const_da;
	real aterm_db, bterm_db, cterm_db, const_db;
	real a, b, c;
	real K1, K2;
	real *weights, *kappas, *d1s, *d2s;
	int edge_count;
	real err_e1, err_e2;
	int e;
	WVertex::incoming_edge_iterator itE;

	/* compute unit normal */
	normKh = Kh.norm();

	if (normKh > 0.0) {
		Kh.normalize();
	}
	else {
		/* This vertex is a point of zero mean curvature (flat or saddle point). Compute a normal by averaging
		 * the adjacent triangles
		 */
		N[0] = N[1] = N[2] = 0.0;

		for (itE = v->incoming_edges_begin(); itE != v->incoming_edges_end(); itE++)
			N = Vec3r(N + (*itE)->GetaFace()->GetNormal());
		real normN = N.norm();
		if (normN <= 0.0)
			return;
		N.normalize();
	}

	/* construct a basis from N: */
	/* set basis1 to any component not the largest of N */
	basis1[0] =  basis1[1] =  basis1[2] = 0.0;
	if (fabs (N[0]) > fabs (N[1]))
		basis1[1] = 1.0;
	else
		basis1[0] = 1.0;

	/* make basis2 orthogonal to N */
	basis2 = (N ^ basis1);
	basis2.normalize();

	/* make basis1 orthogonal to N and basis2 */
	basis1 = (N ^ basis2);
	basis1.normalize();

	aterm_da = bterm_da = cterm_da = const_da = 0.0;
	aterm_db = bterm_db = cterm_db = const_db = 0.0;
	int nb_edges = v->GetEdges().size();

	weights = (real *)malloc(sizeof(real) * nb_edges);
	kappas = (real *)malloc(sizeof(real) * nb_edges);
	d1s = (real *)malloc(sizeof(real) * nb_edges);
	d2s = (real *)malloc(sizeof(real) * nb_edges);
	edge_count = 0;

	for (itE = v->incoming_edges_begin(); itE != v->incoming_edges_end(); itE++) {
		WOEdge *e;
		WFace *f1, *f2;
		real weight, kappa, d1, d2;
		Vec3r vec_edge;
		if (!*itE)
			continue;
		e = *itE;

		/* since this vertex passed the tests in gts_vertex_mean_curvature_normal(), this should be true. */
		//g_assert(gts_edge_face_number (e, s) == 2);

		/* identify the two triangles bordering e in s */
		f1 = e->GetaFace();
		f2 = e->GetbFace();

		/* We are solving for the values of the curvature tensor
		 *     B = [ a b ; b c ].
		 *  The computations here are from section 5 of [Meyer et al 2002].
		 *
		 *  The first step is to calculate the linear equations governing the values of (a,b,c). These can be computed
		 *  by setting the derivatives of the error E to zero (section 5.3).
		 *
		 *  Since a + c = norm(Kh), we only compute the linear equations for dE/da and dE/db. (NB: [Meyer et al 2002]
		 *  has the equation a + b = norm(Kh), but I'm almost positive this is incorrect).
		 *
		 *  Note that the w_ij (defined in section 5.2) are all scaled by (1/8*A_mixed). We drop this uniform scale
		 *  factor because the solution of the linear equations doesn't rely on it.
		 *
		 *  The terms of the linear equations are xterm_dy with x in {a,b,c} and y in {a,b}. There are also const_dy
		 *  terms that are the constant factors in the equations.
		 */

		/* find the vector from v along edge e */
		vec_edge = Vec3r(-1 * e->GetVec());

		ve2 = vec_edge.squareNorm();
		vdotN = vec_edge * N;

		/* section 5.2 - There is a typo in the computation of kappa. The edges should be x_j-x_i. */
		kappa = 2.0 * vdotN / ve2;

		/* section 5.2 */

		/* I don't like performing a minimization where some of the weights can be negative (as can be the case
		 *  if f1 or f2 are obtuse). To ensure all-positive weights, we check for obtuseness. */
		weight = 0.0;
		if (!triangle_obtuse(v, f1)) {
			weight += ve2 * cotan(f1->GetNextOEdge(e->twin())->GetbVertex(), e->GetaVertex(), e->GetbVertex()) / 8.0;
		}
		else {
			if (angle_obtuse(v, f1)) {
				weight += ve2 * f1->getArea() / 4.0;
			}
			else {
				weight += ve2 * f1->getArea() / 8.0;
			}
		}

		if (!triangle_obtuse(v, f2)) {
			weight += ve2 * cotan (f2->GetNextOEdge(e)->GetbVertex(), e->GetaVertex(), e->GetbVertex()) / 8.0;
		}
		else {
			if (angle_obtuse(v, f2)) {
				weight += ve2 * f1->getArea() / 4.0;
			}
			else {
				weight += ve2 * f1->getArea() / 8.0;
			}
		}

		/* projection of edge perpendicular to N (section 5.3) */
		d[0] = vec_edge[0] - vdotN * N[0];
		d[1] = vec_edge[1] - vdotN * N[1];
		d[2] = vec_edge[2] - vdotN * N[2];
		d.normalize();

		/* not explicit in the paper, but necessary. Move d to 2D basis. */
		d1 = d * basis1;
		d2 = d * basis2;

		/* store off the curvature, direction of edge, and weights for later use */
		weights[edge_count] = weight;
		kappas[edge_count] = kappa;
		d1s[edge_count] = d1;
		d2s[edge_count] = d2;
		edge_count++;

		/* Finally, update the linear equations */
		aterm_da += weight * d1 * d1 * d1 * d1;
		bterm_da += weight * d1 * d1 * 2 * d1 * d2;
		cterm_da += weight * d1 * d1 * d2 * d2;
		const_da += weight * d1 * d1 * (-kappa);

		aterm_db += weight * d1 * d2 * d1 * d1;
		bterm_db += weight * d1 * d2 * 2 * d1 * d2;
		cterm_db += weight * d1 * d2 * d2 * d2;
		const_db += weight * d1 * d2 * (-kappa);
	}

	/* now use the identity (Section 5.3) a + c = |Kh| = 2 * kappa_h */
	aterm_da -= cterm_da;
	const_da += cterm_da * normKh;

	aterm_db -= cterm_db;
	const_db += cterm_db * normKh;

	/* check for solvability of the linear system */
	if (((aterm_da * bterm_db - aterm_db * bterm_da) != 0.0) && ((const_da != 0.0) || (const_db != 0.0))) {
		linsolve(aterm_da, bterm_da, -const_da, aterm_db, bterm_db, -const_db, &a, &b);

		c = normKh - a;

		eigenvector(a, b, c, eig);
	}
	else {
		/* region of v is planar */
		eig[0] = 1.0;
		eig[1] = 0.0;
	}

	/* Although the eigenvectors of B are good estimates of the principal directions, it seems that which one is
	 * attached to which curvature direction is a bit arbitrary. This may be a bug in my implementation, or just
	 * a side-effect of the inaccuracy of B due to the discrete nature of the sampling.
	 *
	 * To overcome this behavior, we'll evaluate which assignment best matches the given eigenvectors by comparing
	 * the curvature estimates computed above and the curvatures calculated from the discrete differential operators.
	 */

	gts_vertex_principal_curvatures(0.5 * normKh, Kg, &K1, &K2);

	err_e1 = err_e2 = 0.0;
	/* loop through the values previously saved */
	for (e = 0; e < edge_count; e++) {
		real weight, kappa, d1, d2;
		real temp1, temp2;
		real delta;

		weight = weights[e];
		kappa = kappas[e];
		d1 = d1s[e];
		d2 = d2s[e];

		temp1 = fabs (eig[0] * d1 + eig[1] * d2);
		temp1 = temp1 * temp1;
		temp2 = fabs (eig[1] * d1 - eig[0] * d2);
		temp2 = temp2 * temp2;

		/* err_e1 is for K1 associated with e1 */
		delta = K1 * temp1 + K2 * temp2 - kappa;
		err_e1 += weight * delta * delta;

		/* err_e2 is for K1 associated with e2 */
		delta = K2 * temp1 + K1 * temp2 - kappa;
		err_e2 += weight * delta * delta;
	}
	free (weights);
	free (kappas);
	free (d1s);
	free (d2s);

	/* rotate eig by a right angle if that would decrease the error */
	if (err_e2 < err_e1) {
		real temp = eig[0];

		eig[0] = eig[1];
		eig[1] = -temp;
	}

	e1[0] = eig[0] * basis1[0] + eig[1] * basis2[0];
	e1[1] = eig[0] * basis1[1] + eig[1] * basis2[1];
	e1[2] = eig[0] * basis1[2] + eig[1] * basis2[2];
	e1.normalize();

	/* make N,e1,e2 a right handed coordinate sytem */
	e2 =  N ^ e1;
	e2.normalize();
}