void opengl_scene::draw( const CView& v ) {
	opengl_static_scene::draw( );
	RECT r;
	v.GetClientRect(&r);
	gl_point a(0.0f, 0.0f);
	gl_point b(((GLfloat)r.right)/2.0f, (GLfloat)r.bottom/2.0f);
	gl_point c((GLfloat)r.right, 0.0f);
	color.purple( );
	if(rand( ) % 2) s1.draw(gl_triangle(a,b,c));
	
	
	gl_point _a(0.0f, (GLfloat)r.bottom);
	gl_point _b(((GLfloat)r.right)/2.0f, (GLfloat)r.bottom/2.0f);
	gl_point _c((GLfloat)r.right, (GLfloat)r.bottom);
	color.red( );
	if(rand( ) % 2) s2.draw( gl_triangle(_a, _b, _c));

	
	gl_point A(((GLfloat)r.right)/2.0f, (GLfloat)r.bottom/2.0f);
	gl_point B(((GLfloat)r.right), (GLfloat)r.bottom);
	gl_point C((GLfloat)r.right, 0.0f);
	color.lime( );
	if(rand( ) % 2) s3.draw( gl_triangle(A, B, C));



}