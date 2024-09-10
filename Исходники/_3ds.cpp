void read_n_tri_object(CHUNK *chunk)
{
	CHUNK
		*c,
		*c_point,
		*c_face,
		*c_tex;

	c = chunk->Child;
	do
	{
		if(POINT_ARRAY == c->hdr.id) c_point = c;
		else if(FACE_ARRAY == c->hdr.id) c_face = c;
		else if(TEX_VERTS == c->hdr.id) c_tex = c;

		c = c->Next;
	}
	while(c != chunk->Child);

	if(!c_point->data) return;
	WORD point_count = *(WORD*)c_point->data;
	_3DS_POINT *points = (_3DS_POINT*)((BYTE*)c_point->data + sizeof(WORD));

#if 1
	/************************************/
	for(int a = 0; a < point_count; a++)
	{
		//points[a].x *= 1.2f;
		points[a].y += 2.5f;
		//points[a].z *= 1.2f;
	}
	/************************************/
#endif

	if(!c_face->data) return;
	WORD face_count = *(WORD*)c_face->data;
	_3DS_FACE *faces = (_3DS_FACE*)((BYTE*)c_face->data + sizeof(WORD));

	WORD w = sizeof(_3DS_FACE) * face_count;

	_3DS_FACE *new_faces;
	new_faces = (_3DS_FACE*)malloc(w);
	memset(new_faces, 0, w);

	WORD i = 0, f;
	for(f = 0; f < face_count; f++)
	{
		D3DVECTOR vA = D3DVECTOR(points[faces[f].b].x, points[faces[f].b].y, points[faces[f].b].z) - D3DVECTOR(points[faces[f].a].x, points[faces[f].a].y, points[faces[f].a].z);
		D3DVECTOR vB = D3DVECTOR(points[faces[f].c].x, points[faces[f].c].y, points[faces[f].c].z) - D3DVECTOR(points[faces[f].a].x, points[faces[f].a].y, points[faces[f].a].z);
		D3DVECTOR n = Normalize(CrossProduct(Normalize(vA), Normalize(vB)));

		if((n.x <= 1.0f) && (n.x >= -1.0f) && (n.y <= 1.0f) && (n.y >= -1.0f) && (n.z <= 1.0f) && (n.z >= -1.0f))
		{
			new_faces[i].a = faces[f].a;
			new_faces[i].b = faces[f].b;
			new_faces[i].c = faces[f].c;
			new_faces[i].flag = faces[f].flag;
			i++;
		}
		else
			dwVertFixCount++;
	}

	free(c_face->data);
	c_face->data = 0;
	c_face->data_size = 0;

	w = sizeof(WORD) + sizeof(_3DS_FACE) * i;
	c_face->data = malloc(w);
	c_face->data_size = w;

	w -= sizeof(WORD);
	*(WORD*)c_face->data = i;
	memcpy((BYTE*)c_face->data + sizeof(WORD), new_faces, w);

	free(new_faces);

	if(c_face->Child)
	{
		CHUNK *chunk0 = c_face->Child;
		do
		{
			if(chunk0->data)
			{
				char sz[17];
				strcpy(sz, (char*)chunk0->data);

				free(chunk0->data);
				chunk0->data = 0;
				chunk0->data_size = 0;

				f = lstrlen(sz) + 1;
				chunk0->data_size = f + sizeof(WORD) + sizeof(WORD) * i;
				chunk0->data = malloc(chunk0->data_size);
				strcpy((char*)chunk0->data, sz);

				WORD *pw = (WORD*)((BYTE*)chunk0->data + f);
				*pw++ = i;

				for(f = 0; f < i; f++) *pw++ = f;
			}
			chunk0 = chunk0->Next;
		}
		while(chunk0 != c_face->Child);
	}
}