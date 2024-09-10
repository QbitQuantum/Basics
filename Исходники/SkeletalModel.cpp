void SkeletalModel::traverseLimbTree(Joint* j){

	Vector3f u,v,w;
	Vector4f c;
	Matrix4f rotate,scale,translate;
	
	translate =  Matrix4f::translation(0.0f,0.0f,0.5f);

	m_matrixStack.push(j->transform);

	for (int i = 0; i < j->children.size(); i++){
		
		c = j->children[i]->transform.getCol(3);

		w = c.xyz().normalized();
		v = Vector3f::cross(w,Vector3f(0,0,1)).normalized();
		u = Vector3f::cross(v,w).normalized();

		scale = Matrix4f::scaling(.025,.025,c.xyz().abs());
		rotate = Matrix4f(Vector4f(u,0),Vector4f(v,0),Vector4f(w,0),Vector4f(0,0,0,1));
	
		glLoadMatrixf(m_matrixStack.top()*rotate*scale*translate);
		glutSolidCube(1.0f);

		traverseLimbTree(j->children[i]);
	}
	
	m_matrixStack.pop();
}