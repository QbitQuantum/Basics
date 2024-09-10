void R_VR_GenerateHud()
{
	int i, j;
	float numsegments = floor(vr_hud_segments->value);
	float horizFOV = vr_hud_fov->value;
	float depth = vr_hud_depth->value;
	float horizInterval = 2.0 / numsegments;
	float vertBounds = (float) hud.height / (float) hud.width;
	float vertInterval = horizInterval * vertBounds;

	int numindices = (numsegments) * (numsegments + 1) * 2 + (numsegments * 2);
	int numverts = (numsegments) * (numsegments + 1) * 2;


	vert_t *hudverts = NULL;
	GLushort *indices = NULL;
	uint32_t hudNumVerts = 0;
	GLushort currIndex = 0;
	uint32_t iboSize = sizeof(GLushort) * numindices;
	uint32_t vboSize = sizeof(vert_t) * numverts;

	// calculate coordinates for hud
	float xoff = tanf(horizFOV * (M_PI / 180.0f) * 0.5) * (depth);
	float zoff = depth * cosf(horizFOV * (M_PI / 180.0f) * 0.5);
	vec3_t offsetScale;
	VectorSet(offsetScale, xoff, xoff, zoff);

	hudverts = (vert_t *) malloc(vboSize);
	memset(hudverts, 0, vboSize);

	indices = (GLushort *) malloc(iboSize);
	memset(indices, 0, iboSize);

	for (j = 0; j < numsegments; j++)
	{
		float ypos, ypos1;
		qboolean verticalHalf = (j >= numsegments / 2);
		ypos = j * vertInterval - vertBounds;
		ypos1 = (j + 1) * vertInterval - vertBounds;

		for (i = 0; i <= numsegments; i++)
		{
			float xpos;
			vert_t vert1, vert2;
			GLushort vertNum1, vertNum2;
			qboolean horizontalHalf = (i >= (numsegments+1) / 2);
			

			xpos = i * horizInterval - 1;

			VectorSet(vert1.position, xpos, ypos, -1);
			sphereProject(vert1.position, offsetScale, vert1.position);
			vert1.texCoords[0] = (float) i / (float) (numsegments);
			vert1.texCoords[1] = (float) j / (float) (numsegments);
				

			VectorSet(vert2.position, xpos, ypos1, -1);
			sphereProject(vert2.position, offsetScale, vert2.position);
			vert2.texCoords[0] = (float) i / (float) (numsegments);
			vert2.texCoords[1] = (float) (j + 1) / (float) (numsegments);

			vertNum1 = hudNumVerts++;
			vertNum2 = hudNumVerts++;

			if (verticalHalf)
			{
				hudverts[vertNum2] = vert1;
				hudverts[vertNum1] = vert2;
			} else {
				hudverts[vertNum1] = vert1;
				hudverts[vertNum2] = vert2;
			}

			if (j > 0 && i == 0)
			{
				indices[currIndex++] = vertNum1;
			}

			indices[currIndex++] = vertNum1;
			indices[currIndex++] = vertNum2;


			if (i == numsegments && j < (numsegments - 1))
			{
				indices[currIndex++] = vertNum2;
			}
		}
	}

	R_BindIVBO(&hudVBO,NULL,0);
	R_VertexData(&hudVBO,hudNumVerts * sizeof(vert_t),hudverts);
	R_IndexData(&hudVBO,GL_TRIANGLE_STRIP,GL_UNSIGNED_SHORT,currIndex,currIndex * sizeof(GLushort),indices);
	R_ReleaseIVBO();
	free(hudverts);
	free(indices);
}