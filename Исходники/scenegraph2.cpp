void ExportPovrayCamera(Camera* pcamera, FILE *fp)
{
	Vector3f pos, upvec, viewdir, lookat;
	float fov, fovpi;
	assert(pcamera!=NULL);
	assert(fp!=NULL);

	//output camera info.
	Vec posvec = pcamera->position();
	pos = Vector3f(posvec.x, posvec.y, posvec.z);
	Vec up = pcamera->upVector(); 
	upvec = Vector3f(up.x, up.y, up.z);
	Vec view = pcamera->viewDirection(); 
	viewdir = Vector3f(view.x, view.y, view.z);
	fovpi = pcamera->horizontalFieldOfView();
	fov = fovpi * 180 / PI;

	upvec.Normalize();
	viewdir.Normalize();
	Vector3f xAxis = CrossProd(viewdir,upvec);
	if (Magnitude(xAxis) < 1E-10){
      // target is aligned with upVector, this means a rotation around X axis
      // X axis is then unchanged, let's keep it !
		//xAxis = pcamera->frame()->inverseTransformOf(Vec(1.0, 0.0, 0.0));
		assert(0);
    }
	xAxis.Normalize();
	
	//the size matter;
	float znear = 1.0f; //pcamera->zNear();
	viewdir = viewdir*znear;
	double dw = 2*znear*tan(fovpi * 0.5);
	dw *= (800.0/pcamera->screenWidth());
	xAxis = xAxis * dw;
	//upvec = upvec * (dw / pcamera->aspectRatio());
	upvec = upvec * dw; 
	lookat = pos + viewdir;

	pos = VEC2POVVEC(pos);
	upvec = VEC2POVVEC(upvec);
	viewdir = VEC2POVVEC(viewdir);
	xAxis = VEC2POVVEC(xAxis);
	lookat = VEC2POVVEC(lookat);

	fprintf(fp, "//Window width=%d, height=%d.\n", pcamera->screenWidth(), pcamera->screenHeight());
	fprintf(fp, "camera {\n");
	fprintf(fp, "\tperspective\n");
	fprintf(fp, "\tlocation <%f, %f, %f>\n", pos.x, pos.y, pos.z);
	fprintf(fp, "\tdirection <%f, %f, %f>\n", viewdir.x, viewdir.y, viewdir.z);
	fprintf(fp, "\tright <%f, %f, %f>\n", xAxis.x, xAxis.y, xAxis.z);
	fprintf(fp, "\tup <%f, %f, %f> *(image_height/image_width)\n", upvec.x, upvec.y, upvec.z);
	//fprintf(fp, "\tlook_at <%f, %f, %f>\n", lookat.x, lookat.y, lookat.z);
	fprintf(fp, "\tangle %f\n", fov);
	fprintf(fp, "}\n\n\n");
	
	//export a view associated camera;
	fprintf(fp, "light_source{\n");
	fprintf(fp, "\t<%f, %f, %f>\n", pos.x, pos.y, pos.z); 
    fprintf(fp, "\trgb <1.0, 1.0, 1.0>*EYELIGHT_INTENSITY\n");  
    fprintf(fp, "\tshadowless");
	fprintf(fp, "}\n\n\n");
}