void RenderPhysX3Debug::addConeExt(float r0, float r1, const PxVec3& p0, const PxVec3& p1 , const RendererColor& color, PxU32 renderFlags)
{
	PxVec3 axis = p1 - p0;
	PxReal length = axis.magnitude();
	PxReal rdiff = r0 - r1;
	PxReal sinAngle = rdiff / length;
	PxReal x0 = r0 * sinAngle;
	PxReal x1 = r1 * sinAngle;
	PxVec3 center = 0.5f * (p0 + p1);

	if (length < fabs(rdiff))
		return;

	PxReal r0p = sqrt(r0 * r0 - x0 * x0);
	PxReal r1p = sqrt(r1 * r1 - x1 * x1);

	if (length == 0.0f)
		axis = PxVec3(1,0,0);
	else
		axis.normalize();

	PxVec3 axis1(0.0f);
	axis1[minArgument(abs(axis))] = 1.0f;
	axis1 = axis1.cross(axis);
	axis1.normalize();

	PxVec3 axis2 = axis.cross(axis1);
	axis2.normalize();

	PxMat44 m;
	m.column0 = PxVec4(axis, 0.0f);
	m.column1 = PxVec4(axis1, 0.0f);
	m.column2 = PxVec4(axis2, 0.0f);
	m.column3 = PxVec4(center, 1.0f);

	PxTransform tr(m);

#define NUM_CONE_VERTS 72
	const PxU32 nbVerts = NUM_CONE_VERTS;

	PxVec3 pts0[NUM_CONE_VERTS] ;
	PxVec3 pts1[NUM_CONE_VERTS];
	PxVec3 normals[NUM_CONE_VERTS] ;

	const float step = PxTwoPi / float(nbVerts);
	for (PxU32 i = 0; i < nbVerts; i++)
	{
		const float angle = float(i) * step;
		const float x = cosf(angle);
		const float y = sinf(angle);

		PxVec3 p = PxVec3(0.0f, x, y);

		pts0[i] = tr.transform(r0p * p + PxVec3(-0.5f * length + x0,0,0));
		pts1[i] = tr.transform(r1p * p + PxVec3(0.5f * length + x1, 0, 0));

		normals[i] = tr.q.rotate(p.getNormalized());
		normals[i] = x0 * axis + r0p * normals[i];
		normals[i].normalize();
	}
#undef NUM_CONE_VERTS

	if(renderFlags & RENDER_DEBUG_WIREFRAME)
	{
		for(PxU32 i=0;i<nbVerts;i++)
		{
			addLine(pts1[i], pts0[i], color);
		}
	}

	if(renderFlags & RENDER_DEBUG_SOLID)
	{
		for(PxU32 i=0;i<nbVerts;i++)
		{
			const PxU32 j = (i+1) % nbVerts;
			addTriangle(pts0[i], pts1[j], pts0[j], normals[i], normals[j], normals[j], color);
			addTriangle(pts0[i], pts1[i], pts1[j], normals[i], normals[i], normals[j], color);
		}
	}

}