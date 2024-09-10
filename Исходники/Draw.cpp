void draw_model ( const Model& m, bool smooth)
{
	glEnable(GL_NORMALIZE);
	if(App->wireframe){glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);}
	else
		glPolygonMode(GL_FRONT, GL_FILL);

	glBegin(GL_TRIANGLES);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	if(smooth)
	{
		for(int i = 0; i < m.fsize; i++)
		{
			glColor3d(m.F[i].r/255.0, m.F[i].g/255.0, m.F[i].b/255.0);

			glNormal3d(m.N[m.F[i].na].x, m.N[m.F[i].na].y, m.N[m.F[i].na].z);
			glVertex3d(m.V[m.F[i].va].x, m.V[m.F[i].va].y, m.V[m.F[i].va].z);

			glNormal3d(m.N[m.F[i].nb].x, m.N[m.F[i].nb].y, m.N[m.F[i].nb].z);
			glVertex3d(m.V[m.F[i].vb].x, m.V[m.F[i].vb].y, m.V[m.F[i].vb].z);

			glNormal3d(m.N[m.F[i].nc].x, m.N[m.F[i].nc].y, m.N[m.F[i].nc].z);
			glVertex3d(m.V[m.F[i].vc].x, m.V[m.F[i].vc].y, m.V[m.F[i].vc].z);
		}
		glEnd();
	}

	if(!smooth)
	{
		for(int i = 0; i < m.fsize; i++)
		{
			glColor3d(m.F[i].r/255.0, m.F[i].g/255.0, m.F[i].b/255.0);

			Vec u = m.V[m.F[i].vb] - m.V[m.F[i].va];
			Vec v = m.V[m.F[i].vb] - m.V[m.F[i].vc];

			Vec w = cross(v, u);
			w.normalize();
			glNormal3d(w.x, w.y, w.z);

			glVertex3d(m.V[m.F[i].va].x, m.V[m.F[i].va].y, m.V[m.F[i].va].z);
			glVertex3d(m.V[m.F[i].vb].x, m.V[m.F[i].vb].y, m.V[m.F[i].vb].z);
			glVertex3d(m.V[m.F[i].vc].x, m.V[m.F[i].vc].y, m.V[m.F[i].vc].z);

		}
		glEnd();

	}
}