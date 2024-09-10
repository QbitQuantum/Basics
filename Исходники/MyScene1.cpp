MyScene1::MyScene1(IOContext *io, GfxDriver *driver)
{
	m_player.setPosition(Vector3(0.0f, 0.0f, 0.0f));
	m_player.setBounciness(0.1f);

	// load font
	m_font = Font::create(driver, "Data/Fonts/VeraBd.ttf", 12.0f);

	// create label widget
	m_label = Label::create();
	m_label->setFont(m_font);

	// create logo widget
	m_logo = Picture::create(driver, Image::create("Data/drome.png"));
	m_logo->setWidth(m_logo->getWidth() / 2);
	m_logo->setHeight(m_logo->getHeight() / 2);
	m_logo->setY(io->getWindowHeight() - m_logo->getHeight());

	// load normalmap shaders
	m_shaderProgram = ShaderProgram::create();
	m_shaderProgram->attachVertexShaderFromFile("Data/Shaders/normalmap.vp");
	m_shaderProgram->attachFragmentShaderFromFile("Data/Shaders/normalmap.fp");
	try {
		m_shaderProgram->linkShaders();
	} catch(Exception ex) {
		m_shaderProgram = NULL;
	}

	// create/initialize other stuff
	m_sphere = SphereMesh::create(10, 0.1f);
	m_autoCamera = true;
	m_camera.setPosition(Vector3(0.0f, -4.0f, 0.0f));
	m_camera.update();

	// initialize lights
	m_lightColor[0] = Vector3(1.0f, 0.0f, 0.0f);
	m_lightColor[1] = Vector3(0.0f, 1.0f, 0.0f);
	m_lightColor[2] = Vector3(0.0f, 0.0f, 1.0f);
	m_lightRotation = 0.0f;

	// create light textures and shadow map framebuffers
	for(int i = 0; i < 3; ++i) {
		RefPtr <Image> image = Image::create(1, 1, 3);
		image->setPixel(0, 0, Color(m_lightColor[i]));
		m_lightTextures[i] = Texture::create(image);

		if(m_shaderProgram.isSet())
			m_lightFramebuffers[i] = Framebuffer::create(512, 512, true);
	}

	// load scene definition file
	loadSceneFile("Data/scene1.xml");
}