Matrix CreateNormalTransform (const Matrix& transform)
{
	// create a 3x3 transform matrix for the normals
	Matrix normalTransform;
	*normalTransform.getx () = *transform.getx ();
	*normalTransform.gety () = *transform.gety ();
	*normalTransform.getz () = *transform.getz ();
	normalTransform.m[15]=1.0f;
	float d=normalTransform.determinant ();
	float s=1.0f/d;
	normalTransform.addscale (s,s,s);
	return normalTransform;
}