void Hull::ComputeInertia(const Transform& transform, Point3& centerOfMass, Matrix33& inertia, float totalMass) const
{
	assert(totalMass > 0.0f);

	// order: 1, x, y, z, x^2, y^2, z^2, xy, yz, zx
	float integral[10] = {0,0,0,0,0,0,0,0,0,0};

	// for each triangle
	for (short face = 0; face < m_numFaces; face++)
	{
		short edge = GetFaceFirstEdge(face);
		Point3 v0 = m_pVerts[ GetEdgeVertex0(face, edge) ] * transform;

		edge = GetFaceNextEdge(face, edge);
		Point3 v1 = m_pVerts[ GetEdgeVertex0(face, edge) ] * transform;

		for (edge = GetFaceNextEdge(face, edge); edge != -1; edge = GetFaceNextEdge(face, edge))
		{
			Point3 v2 = m_pVerts[ GetEdgeVertex0(face, edge) ] * transform;

			// get cross product of triangle edges
			Vector3 d = Cross(v2 - v0, v1 - v0);

			// compute integral terms
			Vector3 w0 = Vector3(v0);
			Vector3 w1 = Vector3(v1);
			Vector3 w2 = Vector3(v2);

			Vector3 temp0 = w0 + w1;
			Vector3 f1 = temp0 + w2;
			Vector3 temp1 = w0 * w0;
			Vector3 temp2 = temp1 + w1 * temp0;
			Vector3 f2 = temp2 + w2 * f1;
			Vector3 f3 = w0 * temp1 + w1 * temp2 + w2 * f2;
			Vector3 g0 = f2 + w0 * (f1 + w0);
			Vector3 g1 = f2 + w1 * (f1 + w1);
			Vector3 g2 = f2 + w2 * (f1 + w2);

			// update integrals
			integral[0] += d[0] * f1[0];
			integral[1] += d[0] * f2[0];
			integral[2] += d[1] * f2[1];
			integral[3] += d[2] * f2[2];
			integral[4] += d[0] * f3[0];
			integral[5] += d[1] * f3[1];
			integral[6] += d[2] * f3[2];
			integral[7] += d[0] * (v0[1] * g0[0] + v1[1] * g1[0] + v2[1] * g2[0]);
			integral[8] += d[1] * (v0[2] * g0[1] + v1[2] * g1[1] + v2[2] * g2[1]);
			integral[9] += d[2] * (v0[0] * g0[2] + v1[0] * g1[2] + v2[0] * g2[2]);

			// next edge
			v1 = v2;
		}
	}

	integral[0] *= 1.0f / 6.0f;
	integral[1] *= 1.0f / 24.0f;
	integral[2] *= 1.0f / 24.0f;
	integral[3] *= 1.0f / 24.0f;
	integral[4] *= 1.0f / 60.0f;
	integral[5] *= 1.0f / 60.0f;
	integral[6] *= 1.0f / 60.0f;
	integral[7] *= 1.0f / 120.0f;
	integral[8] *= 1.0f / 120.0f;
	integral[9] *= 1.0f / 120.0f;

	// scale all integrals to get desired total mass
	assert(integral[0] > 0.0f);

	float invMassRatio = totalMass / integral[0];
	for (int i = 0; i < 10; i++)
		integral[i] *= invMassRatio;

	// center of mass
	centerOfMass = Point3(integral[1] / totalMass, integral[2] / totalMass, integral[3] / totalMass);

	// inertia relative to world
	inertia[0][0] = integral[5] + integral[6];
	inertia[0][1] = -integral[7];
	inertia[0][2] = -integral[9];

	inertia[1][0] = -integral[7];
	inertia[1][1] = integral[4] + integral[6];
	inertia[1][2] = -integral[8];

	inertia[2][0] = -integral[9];
	inertia[2][1] = -integral[8];
	inertia[2][2] = integral[5] + integral[5];

	// inertia relative to center of mass
	inertia[0][0] -= totalMass * (centerOfMass[1] * centerOfMass[1] + centerOfMass[2] * centerOfMass[2]);
	inertia[0][1] += totalMass * centerOfMass[0] * centerOfMass[1];
	inertia[0][2] += totalMass * centerOfMass[2] * centerOfMass[0];

	inertia[1][0] += totalMass * centerOfMass[0] * centerOfMass[1];
	inertia[1][1] -= totalMass * (centerOfMass[2] * centerOfMass[2] + centerOfMass[0] * centerOfMass[0]);
	inertia[1][2] += totalMass * centerOfMass[1] * centerOfMass[2];

	inertia[2][0] += totalMass * centerOfMass[2] * centerOfMass[0];
	inertia[2][1] += totalMass * centerOfMass[1] * centerOfMass[2];
	inertia[2][2] -= totalMass * (centerOfMass[0] * centerOfMass[0] + centerOfMass[1] * centerOfMass[1]);
}