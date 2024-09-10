  	bool initialize()
  	{
		if (!_context.start(800, 600, "My bomberman!"))
	  		return false;

  		glEnable(GL_DEPTH_TEST);

  		if (!_shader.load("./LibBomberman_linux_x64/shaders/basic.fp", GL_FRAGMENT_SHADER)
			|| !_shader.load("./LibBomberman_linux_x64/shaders/basic.vp", GL_VERTEX_SHADER)
			|| !_shader.build())
  		{
			std::cout << "error on shader" << std::endl;
			return false;
		}

		glm::mat4 projection;
		glm::mat4 transformation;
		projection = glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 100.0f);

		transformation = glm::lookAt(glm::vec3(0, 10, -30), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		_shader.bind();

		_shader.setUniform("view", transformation);
		_shader.setUniform("projection", projection);

		AObject *cube = new Marvin();
		
		if (cube->initialize() == false)
  			return (false);
		_objects.push_back(cube);
		return true;
	}