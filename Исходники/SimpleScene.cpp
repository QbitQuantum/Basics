void onMouseDrag( GLFWwindow* window, double fx, double fy)
{
	int x=fx;
	int y=fy;
#else
void onMouseDrag( int x, int y)
{
#endif
	if (isDrag) 
	{
		printf( "in drag mode %d\n", isDrag);
		if (isDrag==V_DRAG && cowFlag)
		{
			// vertical dragging
			// TODO:
			// create a dragging plane perpendicular to the ray direction, 
			// and test intersection with the screen ray.
      // When dragged just change Y position
			Ray ray;
			screenCoordToRay(clickX, y, ray);
			PickInfo &pp=pickInfo;
			std::pair<bool, double> c=ray.intersects(dragPlane);

			vector3 currentPos=ray.getPoint(c.second);	

      matrix4 T;
      T.setTranslation(currentPos - pp.cowPickPosition, false);
      cow2wld.mult(T, pp.cowPickConfiguration);
		}
		else
		{ 
			// horizontal dragging
			// Hint: read carefully the following block to implement vertical dragging.
			if(cursorOnCowBoundingBox)
			{
				Ray ray;
				screenCoordToRay(x, y, ray);
				PickInfo &pp=pickInfo;
				Plane p(vector3(0,1,0), pp.cowPickPosition);
				std::pair<bool, double> c=ray.intersects(p);

				vector3 currentPos=ray.getPoint(c.second);	

				matrix4 T;
				T.setTranslation(currentPos-pp.cowPickPosition, false);
				cow2wld.mult(T, pp.cowPickConfiguration);
			}
		}
	}
	else
	{
		Ray ray;
		screenCoordToRay(x, y, ray);

		std::vector<Plane> planes;
		vector3 bbmin(cow->bbmin.x, cow->bbmin.y, cow->bbmin.z);
		vector3 bbmax(cow->bbmax.x, cow->bbmax.y, cow->bbmax.z);

		planes.push_back(makePlane(bbmin, bbmax, vector3(0,1,0)));
		planes.push_back(makePlane(bbmin, bbmax, vector3(0,-1,0)));
		planes.push_back(makePlane(bbmin, bbmax, vector3(1,0,0)));
		planes.push_back(makePlane(bbmin, bbmax, vector3(-1,0,0)));
		planes.push_back(makePlane(bbmin, bbmax, vector3(0,0,1)));
		planes.push_back(makePlane(bbmin, bbmax, vector3(0,0,-1)));


		std::pair<bool,double> o=ray.intersects(planes);
		cursorOnCowBoundingBox=o.first;
		PickInfo &pp=pickInfo;
		pp.cursorRayT=o.second;
		pp.cowPickPosition=ray.getPoint(pp.cursorRayT);
		pp.cowPickConfiguration=cow2wld;
		matrix4 invWorld;
		invWorld.inverse(cow2wld);
		// the local position (relative to the cow frame) of the pick position.
		pp.cowPickPositionLocal=invWorld*pp.cowPickPosition;
	}

}

/*********************************************************************************
* Call this part whenever user types keyboard. 
**********************************************************************************/
#if GLFW_VERSION_MAJOR==3
void onKeyPress(GLFWwindow *__win, int key, int __scancode, int action, int __mods)
#else
void onKeyPress( int key, int action)
#endif
{
	if (action==GLFW_RELEASE)
		return 	; // do nothing
	// If 'c' or space bar are pressed, alter the camera.
	// If a number is pressed, alter the camera corresponding the number.
	if ((key == ' ') || (key == 'c'))
	{    
		printf( "Toggle camera %d\n", cameraIndex );
		cameraIndex += 1;
	}      
	else if ((key >= '0') && (key <= '9'))
		cameraIndex = key - '0';

	if (cameraIndex >= (int)wld2cam.size() )
		cameraIndex = 0;
}
void screenCoordToRay(int x, int y, Ray& ray)
{
	int height , width;
#if GLFW_VERSION_MAJOR==3
	glfwGetWindowSize(g_window, &width, &height);
#else
	glfwGetWindowSize(&width, &height);
#endif

	matrix4 matProjection;
	matProjection.getCurrentOpenGLmatrix(GL_PROJECTION_MATRIX);
	matProjection*=wld2cam[cameraIndex];
	matrix4 invMatProjection;
	invMatProjection.inverse(matProjection);

	vector3 vecAfterProjection, vecAfterProjection2;
	// -1<=v.x<1 when 0<=x<width
	// -1<=v.y<1 when 0<=y<height
	vecAfterProjection.x = ((double)(x - 0)/(double)width)*2.0-1.0;
	vecAfterProjection.y = ((double)(y - 0)/(double)height)*2.0-1.0;
	vecAfterProjection.y*=-1;
	vecAfterProjection.z = -10;

	//std::cout<<"cowPosition in clip coordinate (NDC)"<<matProjection*cow2wld.getTranslation()<<std::endl;
	
	vector3 vecBeforeProjection=invMatProjection*vecAfterProjection;

	// camera position
	ray.origin()=cam2wld[cameraIndex].getTranslation();
	ray.direction()=vecBeforeProjection-ray.origin();
	ray.direction().normalize();

	//std::cout<<"dir" <<ray.direction()<<std::endl;

}