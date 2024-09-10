void DisplayGrid()
{
	//cout << "dg\n";

	Window * window = Window::FindCurrentWindow(windows);
	if (window->handle == BAD_GL_VALUE)
		return;

	glViewport(0 , 0 , window->size.x , window->size.y);
	vec4 crimson(0.6f , 0.0f , 0.0f , 1.0f);
	vec3 ambient = vec3(0.0f , 0.0f , 0.0f);
	vec3 specular = vec3(1.0f , 1.0f , 1.0f);
	vec3 diffuse = vec3(0.0f , 0.0f , 0.8f);

	glClearColor(crimson.r , crimson.g , crimson.b , crimson.a);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	vector<Constellation::PositionData> & pd = gc.GetPositionData();

	mat4 s = scale(mat4() , vec3(50.0f , 50.0f , 1.0f));
	mat4 view_matrix = lookAt(vec3(0.0f , 0.0f , 150.0f) , vec3(0.0f , 0.0f , 0.0f) , vec3(0.0f , 1.0f , 0.0f));
	mat4 projection_matrix = perspective(radians(window->fovy) , window->aspect , window->near_distance , window->far_distance);

	mat4 r = rotate(mat4() , radians(window->LocalTime() * 0.0f) , vec3(0.0f , 1.0f , 0.0f));

	for (vector<Constellation::PositionData>::iterator iter = pd.begin(); iter < pd.end(); iter++)
	{
		mat4 model_matrix = rotate(mat4() , radians(window->LocalTime() * 20.0f) , vec3(0.0f , 1.0f , 0.0f));
		model_matrix = translate(model_matrix , vec3(s * vec4((*iter).location , 1.0f)));

		// Beginning of orientation code.
		//
		// There is an assumption here (we are aligning z axes) that the shape you're building have
		// a natural facing down the z axis.
		//
		// The following orients the object's z axis along the axis held in outward_direction_vector.
		// target_dir gets that value. The difference in direction from the z axis to the desired direction
		// is captured by the dot product. The angle is retrieved with the acos. Then, if there's anything 
		// to do (I suspect the if statement is NOT needed), a rotation axis is made by the cross product
		// (rotating about it will swing the z axes around). Finally, the rotation is done.
		vec3 target_dir = normalize((*iter).outward_direction_vector);
		float rot_angle = acos(dot(target_dir , vec3(0.0f, 0.0f, 1.0f)));
		if (fabs(rot_angle) > glm::epsilon<float>())
		{
			vec3 rot_axis = normalize(cross(target_dir , vec3(0.0f, 0.0f, 1.0f)));
			model_matrix = rotate(model_matrix, rot_angle , rot_axis);
		}
		// End of orientation code.

		model_matrix = scale(model_matrix , vec3(2.0f, 2.0f, 1.0f));
		phong_shader.Use(model_matrix , view_matrix , projection_matrix);
		phong_shader.SetMaterial(diffuse , specular , 64.0f , ambient);
		phong_shader.SetLightPosition(vec3(0.0f , 0.0f , 1000.0f));
		phong_shader.SelectSubroutine(PhongShader::PHONG_WITH_TEXTURE);
		phong_shader.EnableTexture(textures[1] , 0);
		plane2.Draw(false);
		phong_shader.UnUse();
		if (window->draw_normals)
		{
			constant_shader.Use(model_matrix , view_matrix , projection_matrix);
			constant_shader.SetMaterial(diffuse , specular , 64.0f , vec3(1.0f , 1.0f , 1.0f));
			plane2.Draw(true);
			constant_shader.UnUse();
		}
		// Animate the rotation of the objects within the grid.
		(*iter).outward_direction_vector = vec3(r * vec4((*iter).outward_direction_vector, 1.0f));
	}
	glutSwapBuffers();
}