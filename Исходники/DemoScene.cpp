int main()
{
	////////////////////
	// ionEngine Init //
	////////////////////

	Log::AddDefaultOutputs();

	SingletonPointer<CGraphicsAPI> GraphicsAPI;
	SingletonPointer<CWindowManager> WindowManager;
	SingletonPointer<CSceneManager> SceneManager;

	GraphicsAPI->Init(new Graphics::COpenGLImplementation());
	WindowManager->Init(GraphicsAPI);
	SceneManager->Init(GraphicsAPI);

	CWindow * Window = WindowManager->CreateWindow(vec2i(1600, 900), "DemoScene", EWindowType::Windowed);
	SharedPointer<IGraphicsContext> Context = GraphicsAPI->GetWindowContext(Window);
	SharedPointer<IRenderTarget> RenderTarget = Context->GetBackBuffer();
	RenderTarget->SetClearColor(color3f(0.3f));


	///////////////////
	// Create Shader //
	///////////////////

	SharedPointer<IVertexShader> VertexShader = GraphicsAPI->CreateVertexShaderFromFile("Diffuse.vert");
	SharedPointer<IPixelShader> PixelShader = GraphicsAPI->CreatePixelShaderFromFile("Diffuse.frag");

	if (! VertexShader)
		std::cerr << "Failed to compile vertex shader!" << std::endl;

	if (! PixelShader)
		std::cerr << "Failed to compile pixel shader!" << std::endl;

	SharedPointer<IShaderProgram> ShaderProgram = GraphicsAPI->CreateShaderProgram();
	ShaderProgram->SetVertexStage(VertexShader);
	ShaderProgram->SetPixelStage(PixelShader);


	////////////////////
	// ionScene Setup //
	////////////////////

	CRenderPass * RenderPass = new CRenderPass(Context);
	RenderPass->SetRenderTarget(RenderTarget);
	SceneManager->AddRenderPass(RenderPass);

	CPerspectiveCamera * Camera = new CPerspectiveCamera(Window->GetAspectRatio());
	Camera->SetPosition(vec3f(0, 2, -4));
	Camera->SetLookAtTarget(vec3f(0, 0, 0));
	Camera->SetFocalLength(0.4f);
	RenderPass->SetActiveCamera(Camera);


	///////////////////
	// Scene Objects //
	///////////////////

	CSimpleMesh * Mesh1 = CGeometryCreator::CreateSphere();
	CSimpleMeshSceneObject * SceneObject1 = new CSimpleMeshSceneObject();
	SceneObject1->SetMesh(Mesh1);
	SceneObject1->SetShader(ShaderProgram);
	SceneObject1->SetPosition(vec3f(2, 0, 0));
	RenderPass->AddSceneObject(SceneObject1);

	CSimpleMesh * Mesh2 = CGeometryCreator::CreateCylinder(0.6f, 0.3f);
	CSimpleMeshSceneObject * SceneObject2 = new CSimpleMeshSceneObject();
	SceneObject2->SetMesh(Mesh2);
	SceneObject2->SetShader(ShaderProgram);
	SceneObject2->SetPosition(vec3f(0, -0.5f, 0));
	SceneObject2->SetRotation(vec3f(-Constants32::Pi / 2, 0, 0));
	RenderPass->AddSceneObject(SceneObject2);

	CSimpleMesh * Mesh3 = CGeometryCreator::CreateCube();
	CSimpleMeshSceneObject * SceneObject3 = new CSimpleMeshSceneObject();
	SceneObject3->SetMesh(Mesh3);
	SceneObject3->SetShader(ShaderProgram);
	SceneObject3->SetPosition(vec3f(-2, 0, 0));
	RenderPass->AddSceneObject(SceneObject3);


	///////////////
	// Main Loop //
	///////////////

	while (WindowManager->Run())
	{
		RenderTarget->ClearColorAndDepth();
		SceneManager->DrawAll();
		Window->SwapBuffers();
	}

	return 0;
}