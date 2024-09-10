void MultiLightDemo::Initialize()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.3f, 0.2f, 0.7f, 1.0f);
	program.AddShaderFile(ShaderType::Vertex, "Assets/Shaders/Vertex/multiLight.vert");
	program.AddShaderFile(ShaderType::Fragment, "Assets/Shaders/Fragment/multiLight.frag");
	program.Build();

	program.AddUniformBlock({ "TransformBlock",{
		{ "TransformBlock.view",&camera->GetView()[0][0], sizeof(camera->GetView()) },
		{ "TransformBlock.projection",&camera->GetProjection()[0][0], sizeof(camera->GetProjection()) },
		{ "TransformBlock.eyePosition",&camera->GetPosition()[0], sizeof(camera->GetPosition()) },
	} });

	lights[0].position = glm::vec3(0.0f, 0.0f, -2.0f);
	lights[1].position = glm::vec3(-2.0f, -3.0f, -2.0f);
	lights[2].position = glm::vec3(4.0f, 7.0f, -2.0f);

	lights[0].color = glm::vec3(0.9f,0.5f,0.3f);
	lights[1].color = glm::vec3(0.2f,0.9f,0.2f);
	lights[2].color = glm::vec3(0.2f,0.4f,0.9f);
	
	program.AddUniform("lights[0].position", &lights[0].position[0], UniformType::VEC3);
	program.AddUniform("lights[0].color", &lights[0].color[0], UniformType::VEC3);
	program.AddUniform("lights[1].position", &lights[1].position[0], UniformType::VEC3);
	program.AddUniform("lights[1].color", &lights[1].color[0], UniformType::VEC3);
	program.AddUniform("lights[2].position", &lights[2].position[0], UniformType::VEC3);
	program.AddUniform("lights[2].color", &lights[2].color[0], UniformType::VEC3);

	input->addBinding(GLFW_KEY_LEFT, [this](InputInfo info) {
		camera->MoveLeft();
		program.UpdateUniformBlock("TransformBlock");
	});

	input->addBinding(GLFW_KEY_RIGHT, [this](InputInfo info) {
		camera->MoveRight();
		program.UpdateUniformBlock("TransformBlock");
	});


	input->addBinding(GLFW_KEY_UP, [this](InputInfo info) {
		camera->MoveForward();
		program.UpdateUniformBlock("TransformBlock");
	});

	input->addBinding(GLFW_KEY_DOWN, [this](InputInfo info) {
		camera->MoveBack();
		program.UpdateUniformBlock("TransformBlock");
	});


	//program.AddUniform("light[0].position", &lights[0].position[0], UniformType::VEC3);
	//program.AddUniform("light[0].color", &lights[0].color[0], UniformType::VEC3);
	//program.AddUniform("light[1].position", &lights[1].position[0], UniformType::VEC3);
	//program.AddUniform("light[1].color", &lights[1].color[0], UniformType::VEC3);
	//program.AddUniform("light[2].position", &lights[2].position[0], UniformType::VEC3);
	//program.AddUniform("light[2].color", &lights[2].color[0], UniformType::VEC3);

	using std::unique_ptr;
	monkey = unique_ptr<GameObject>(new GameObject());
	monkey->GetTransform()->SetPosition({ 0.0f,0.0f,-5.0f });
	monkey->Update();
	Assimp::Importer importer;
	auto scene = importer.ReadFile("Assets/Models/Obj/monkey.obj", aiProcess_Triangulate);
	if (scene && scene->HasMeshes())
	{
		mesh = unique_ptr<MeshComponent>(new MeshComponent(monkey.get()));
		mesh->Initialize(scene->mMeshes[0], program, {
			{ "world", UniformType::MAT4, &monkey->GetWorld()[0][0] },
			{ "material.ambient", UniformType::VEC3, &mesh->GetMaterial().ambient[0] },
			{ "material.diffuse", UniformType::VEC3, &mesh->GetMaterial().diffuse[0] },
			{ "material.specular", UniformType::VEC4, &mesh->GetMaterial().specular[0] },
		});
		monkey->AddComponent(mesh.get());
	}

	mesh->GetMaterial().ambient = glm::vec3(0.6f, 0.7f, 0.1f);
	mesh->GetMaterial().diffuse = glm::vec3(0.5f, 0.2f, 0.8f);
	mesh->GetMaterial().specular = glm::vec4(0.3f, 0.2f, 0.2f, 10.0f);
	importer.FreeScene();

}