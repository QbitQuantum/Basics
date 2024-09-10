void applyTransformation(matrix mat){
	float m[ 16 ];
	mat.transpose().ToArray( m );
	//mat.ToArray(m);
	glLoadMatrixf( m );
}