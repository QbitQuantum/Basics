void GraphicsGL2::SetupScene(
	float fov, float new_view_distance,
	const Vec3 cam_position,
	const Quat & cam_rotation,
	const Vec3 & dynamic_reflection_sample_pos)
{
	// setup the default camera from the passed-in parameters
	{
		GraphicsCamera & cam = cameras["default"];
		cam.fov = fov;
		cam.pos = cam_position;
		cam.orient = cam_rotation;
		cam.view_distance = new_view_distance;
		cam.w = w;
		cam.h = h;
	}

	// create a camera for the skybox with a long view distance
	{
		GraphicsCamera & cam = cameras["skybox"];
		cam = cameras["default"];
		cam.view_distance = 10000;
		cam.pos = Vec3(0);
	}

	// create a camera for the dynamic reflections
	{
		GraphicsCamera & cam = cameras["dynamic_reflection"];
		cam.pos = dynamic_reflection_sample_pos;
		cam.fov = 90; // this gets automatically overridden with the correct fov (which is 90 anyway)
		cam.orient.LoadIdentity(); // this gets automatically rotated for each cube side
		cam.view_distance = 100;
		cam.w = 1; // this gets automatically overridden with the cubemap dimensions
		cam.h = 1; // this gets automatically overridden with the cubemap dimensions
	}

	// create a camera for the dynamic reflection skybox
	{
		GraphicsCamera & cam = cameras["dynamic_reflection_skybox"];
		cam = cameras["dynamic_reflection"];
		cam.view_distance = 10000;
		cam.pos = Vec3(0);
	}

	// create an ortho camera for 2d drawing
	{
		GraphicsCamera & cam = cameras["2d"];

		// this is the glOrtho call we want: glOrtho( 0, 1, 1, 0, -1, 1 );
		cam.orthomode = true;
		cam.orthomin = Vec3(0, 1, -1);
		cam.orthomax = Vec3(1, 0, 1);
	}

	// put the default camera transform into texture3, needed by shaders only
	Mat4 viewMatrix;
	cam_rotation.GetMatrix4(viewMatrix);
	float translate[4] = {-cam_position[0], -cam_position[1], -cam_position[2], 0};
	viewMatrix.MultiplyVector4(translate);
	viewMatrix.Translate(translate[0], translate[1], translate[2]);

	glMatrixMode(GL_TEXTURE);

	glActiveTexture(GL_TEXTURE3);
	glLoadMatrixf(viewMatrix.GetArray());

	// create cameras for shadow passes
	if (shadows)
	{
		Mat4 viewMatrixInv = viewMatrix.Inverse();

		// derive light rotation quaternion from light direction vector
		Quat light_rotation;
		Vec3 up(0, 0, 1);
		float cosa = up.dot(light_direction);
		if (cosa * cosa < 1.0f)
		{
			float a = -acosf(cosa);
			Vec3 x = up.cross(light_direction).Normalize();
			light_rotation.SetAxisAngle(a, x[0], x[1], x[2]);
		}

		std::vector <std::string> shadow_names;
		shadow_names.push_back("near");
		shadow_names.push_back("medium");
		shadow_names.push_back("far");

		for (int i = 0; i < 3; i++)
		{
			float shadow_radius = (1<<i)*closeshadow+(i)*20.0; //5,30,60

			Vec3 shadowbox(1,1,1);
			shadowbox = shadowbox * (shadow_radius*sqrt(2.0));
			Vec3 shadowoffset(0,0,-1);
			shadowoffset = shadowoffset * shadow_radius;
			(-cam_rotation).RotateVector(shadowoffset);
			shadowbox[2] += 60.0;

			GraphicsCamera & cam = cameras["shadows_"+shadow_names[i]];
			cam = cameras["default"];
			cam.orthomode = true;
			cam.orthomin = -shadowbox;
			cam.orthomax = shadowbox;
			cam.pos = cam.pos + shadowoffset;
			cam.orient = light_rotation;

			// go through and extract the clip matrix, storing it in a texture matrix
			// premultiply the clip matrix with default camera view inverse matrix
			renderscene.SetOrtho(cam.orthomin, cam.orthomax);
			renderscene.SetCameraInfo(cam.pos, cam.orient, cam.fov, cam.view_distance, cam.w, cam.h);

			Mat4 clipmat;
			clipmat.Scale(0.5f);
			clipmat.Translate(0.5f, 0.5f, 0.5f);
			clipmat = renderscene.GetProjMatrix().Multiply(clipmat);
			clipmat = renderscene.GetViewMatrix().Multiply(clipmat);
			clipmat = viewMatrixInv.Multiply(clipmat);

			glActiveTexture(GL_TEXTURE4+i);
			glLoadMatrixf(clipmat.GetArray());
		}
	}

	glActiveTexture(GL_TEXTURE0);
	glMatrixMode(GL_MODELVIEW);
}