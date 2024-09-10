void init() {


	map.initialize();
	cam_moves[0] = Translate(-0.01, 0, 0);
	cam_moves[1] = Translate(0, 0, -0.01);
	cam_moves[2] = Translate(0.01, 0, 0);
	cam_moves[3] = Translate(0, 0, 0.01);
	int* arr = map.decrypt(Snake_Head);
	int i = arr[0]- Length/2, j= arr[1]-Width/2;
	cam_COF = Translate((i+2)*sphere_width, 0, j*sphere_width) * cam_COF;
	cam_eye = Translate(-(i-2)*sphere_width, 15, j*sphere_width) * cam_eye;

	vec4 a(0, 0, 0, 1);
	vec4 b(sphere_width, 0, 0, 1);
	vec4 c(0, 0, sphere_width, 1);
	vec4 d(sphere_width, 0, sphere_width, 1);

	vec3 normal = vec3(0, 1, 0);

	normals[index] = normal;
	points[index] = a;
	index++;
	normals[index] = normal;
	points[index] = b;
	index++;
	normals[index] = normal;
	points[index] = c;
	index++;

	normals[index] = normal;
	points[index] = b;
	index++;
	normals[index] = normal;
	points[index] = c;
	index++;
	normals[index] = normal;
	points[index] = d;
	index++;

	//generate the sphere
	tetrahedron(NumTimesToSubdivide);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint buffer[2];
	glGenBuffers(2, buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);

	program = InitShader("src/vshader.glsl", "src/fshader.glsl");
	glUseProgram(program);

	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0,
			BUFFER_OFFSET(0) );

	glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
	GLuint vNormal = glGetAttribLocation(program, "vNormal");
	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

	vec4 ambient_product = light_ambient * material_ambient;
	vec4 diffuse_product = light_diffuse * material_diffuse;
	vec4 specular_product = light_specular * material_specular;

	glUniform4fv(glGetUniformLocation(program, "AmbientProduct"), 1,
			ambient_product);
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1,
			diffuse_product);
	glUniform4fv(glGetUniformLocation(program, "SpecularProduct"), 1,
			specular_product);
	lightPos_loc = glGetUniformLocation(program, "LightPosition");
	glUniform4fv(lightPos_loc, 1, light_position);
	glUniform1f(glGetUniformLocation(program, "Shininess"), material_shininess);

	model_loc = glGetUniformLocation(program, "Model");
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, mat4(1));
	camera_loc = glGetUniformLocation(program, "Camera");
	projection_loc = glGetUniformLocation(program, "Projection");

	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);

	direction = Periodic;
	step(0);
}