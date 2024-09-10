void VectorFieldRenderer::DrawSuperQuadric(Vector e){

	/* draw the superquadrics along the stream lines */

	float denom = e.X() + e.Y() + e.Z(); // common denmoinator
	float cL = ( e.X() - e.Y() )/denom; // linear
	float cP = ( 2.0 * (e.Y() - e.Z() ) )/denom; // planar
	float cS = ( 3.0 * e.Z() )/denom; // spherical

	float alpha = 0.0f;
	float beta = 0.0f;
	float gamma = 2.0f;

	float theta = 0.0f;
	float phi = 0.0f;

	int radialS = 10;
	int verticalS = 10;

	GLfloat verts[50][50][4]; 

	if(cL >= cP){ // if more linear in shape

		alpha = pow( static_cast<float>(1.0-cP), gamma);
		beta = pow( static_cast<float>(1.0-cL), gamma);

		for(int i = 0; i <= radialS; i++){
			theta = (2.0 * MY_PI * i)/radialS;			
			for(int j = 0; j <= verticalS; j++){

				phi = (MY_PI * j)/verticalS;

			verts[i][j][0] = _copysign( 1.0, cos(phi) ) * pow( fabs( cos(phi) ), beta);
			verts[i][j][1] = -_copysign( 1.0, sin(theta) ) * pow( fabs( sin(theta) ), alpha ) *
						_copysign( 1.0, sin(phi) ) * pow( fabs( sin(phi) ), beta );
			verts[i][j][2] = _copysign( 1.0, cos(theta) ) * pow( fabs( cos(theta) ), alpha ) *
						_copysign( 1.0, sin(phi) ) * pow( fabs( sin(phi) ), beta );
			verts[i][j][3] = 1.0;
			
			} // end j

		} // end i

	drawQuadric(verts, radialS, verticalS);

	}else if(cL < cP){
		
		alpha = pow( static_cast<float>(1.0-cL), gamma);
		beta = pow( static_cast<float>(1.0-cP), gamma);

		for(int i = 0; i <= radialS; i++){
			theta = (2.0 * MY_PI * i)/radialS;			
			for(int j = 0; j <= verticalS; j++){

				phi = (MY_PI * j)/verticalS;

				verts[i][j][0] = _copysign( 1.0, cos(theta) ) * pow( fabs( cos(theta) ), alpha ) *
						_copysign( 1.0, sin(phi) ) * pow( fabs( sin(phi) ), beta );
				verts[i][j][1] = _copysign( 1.0, sin(theta) ) * pow( fabs( sin(theta) ), alpha ) *
						_copysign( 1.0, sin(phi) ) * pow( fabs( sin(phi) ), beta );
				verts[i][j][2] = _copysign( 1.0, cos(phi) ) * pow( fabs( cos(phi) ), beta);
				verts[i][j][3] = 1.0;

			} // end j

		} // end i

		drawQuadric(verts, radialS, verticalS);

	} // end else
}