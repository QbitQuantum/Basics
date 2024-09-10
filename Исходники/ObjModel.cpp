void ObjModel::render() {
	material.apply();
	int j;
	Matrix4 glMatrix = model2world;
	glMatrix.transpose();
	//glPushMatrix();
	glLoadMatrixd(glMatrix.getPointer());
	//glPopMatrix();
	glBegin(GL_TRIANGLES);
		
		for (int i = 0; i < numFaces * 6; i += 6) {
			j = i + 1;

			// color
			if (hasColors)
				glColor3f(colors[faces[i] - 1].getR(), colors[faces[i + 2] - 1].getG(), colors[faces[i + 4] - 1].getB());
			else
				glColor3f(0.6, 0.6, 0.6);
				//glColor3f(fabs(normals[faces[j]-1].getX()) * 0.8, fabs(normals[faces[j + 2]-1].getY()) * 0.8, fabs(normals[faces[j + 4]-1].getZ()) * 0.8);
			
			// Vertex 1
			glNormal3f(normals[faces[j]-1].getX(), normals[faces[j]-1].getY(), normals[faces[j]-1].getZ());
			glVertex3f(vertices[faces[i]-1].getX(), vertices[faces[i]-1].getY(), vertices[faces[i]-1].getZ());

			// Vertex 2
			glNormal3f(normals[faces[j + 2]-1].getX(), normals[faces[j + 2]-1].getY(), normals[faces[j + 2]-1].getZ());
			glVertex3f(vertices[faces[i + 2]-1].getX(), vertices[faces[i + 2]-1].getY(), vertices[faces[i + 2]-1].getZ());

			// Vertex 3
			glNormal3f(normals[faces[j + 4]-1].getX(), normals[faces[j + 4]-1].getY(), normals[faces[j + 4]-1].getZ());
			glVertex3f(vertices[faces[i + 4]-1].getX(), vertices[faces[i + 4]-1].getY(), vertices[faces[i + 4]-1].getZ());
		}
	glEnd();
}