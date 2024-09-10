void DrawBl()
{
	Shader* s = &g_shader[g_curS];

	//return;
	for(int i=0; i<BUILDINGS; i++)
	{
		Building* b = &g_building[i];

		if(!b->on)
			continue;

		const BuildingT* t = &g_bltype[b->type];
		//const BuildingT* t = &g_bltype[BUILDING_APARTMENT];
		Model* m = &g_model[ t->model ];

		Vec3f vmin(b->drawpos.x - t->widthx*TILE_SIZE/2, b->drawpos.y, b->drawpos.z - t->widthz*TILE_SIZE/2);
		Vec3f vmax(b->drawpos.x + t->widthx*TILE_SIZE/2, b->drawpos.y + (t->widthx+t->widthz)*TILE_SIZE/2, b->drawpos.z + t->widthz*TILE_SIZE/2);

		if(!g_frustum.boxin2(vmin.x, vmin.y, vmin.z, vmax.x, vmax.y, vmax.z))
			continue;

		if(!b->finished)
			m = &g_model[ t->cmodel ];

		/*
		m->draw(0, b->drawpos, 0);
		*/

		float pitch = 0;
		float yaw = 0;
		Matrix modelmat;
		float radians[] = {(float)DEGTORAD(pitch), (float)DEGTORAD(yaw), 0};
		modelmat.translation((const float*)&b->drawpos);
		Matrix rotation;
		rotation.rotrad(radians);
		modelmat.postmult(rotation);
		glUniformMatrix4fv(s->m_slot[SSLOT_MODELMAT], 1, 0, modelmat.m_matrix);

		Matrix modelview;
#ifdef SPECBUMPSHADOW
   	 modelview.set(g_camview.m_matrix);
#endif
    	modelview.postmult(modelmat);
		glUniformMatrix4fv(s->m_slot[SSLOT_MODELVIEW], 1, 0, modelview.m_matrix);

		Matrix mvp;
#if 0
		mvp.set(modelview.m_matrix);
		mvp.postmult(g_camproj);
#elif 0
		mvp.set(g_camproj.m_matrix);
		mvp.postmult(modelview);
#else
		mvp.set(g_camproj.m_matrix);
		mvp.postmult(g_camview);
		mvp.postmult(modelmat);
#endif
		glUniformMatrix4fv(s->m_slot[SSLOT_MVP], 1, 0, mvp.m_matrix);

		Matrix modelviewinv;
		Transpose(modelview, modelview);
		Inverse2(modelview, modelviewinv);
		//Transpose(modelviewinv, modelviewinv);
		glUniformMatrix4fv(s->m_slot[SSLOT_NORMALMAT], 1, 0, modelviewinv.m_matrix);

		VertexArray* va = &b->drawva;

		m->usetex();

		glVertexAttribPointer(s->m_slot[SSLOT_POSITION], 3, GL_FLOAT, GL_FALSE, 0, va->vertices);
		glVertexAttribPointer(s->m_slot[SSLOT_TEXCOORD0], 2, GL_FLOAT, GL_FALSE, 0, va->texcoords);

		if(s->m_slot[SSLOT_NORMAL] != -1)
			glVertexAttribPointer(s->m_slot[SSLOT_NORMAL], 3, GL_FLOAT, GL_FALSE, 0, va->normals);

		glDrawArrays(GL_TRIANGLES, 0, va->numverts);
	}
}