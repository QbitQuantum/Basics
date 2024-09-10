Matrix4 Entity::getLookAtMatrix(const Vector3 &loc, const Vector3 &upVector) {
	rebuildTransformMatrix();
	Vector3 D;
	if(parentEntity)
		D = loc - (parentEntity->getConcatenatedMatrix() *position);		
	else
		D = loc - position;
	
	Vector3 back = D * -1;
	back.Normalize();
	
	Vector3 right = back.crossProduct(upVector) ;
	right.Normalize();
	right = right * -1;
	
	Vector3 up = back.crossProduct(right);
	
	Matrix4 newMatrix(right.x, right.y, right.z, 0, 
					  up.x, up.y, up.z, 0, 
					  back.x, back.y, back.z, 0,
					  0, 0 , 0, 1);		
	return newMatrix;
}