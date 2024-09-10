void GrassBlendingGame::Initialize()
{
    window->SetTitle("TestApp - Enjoy Game Dev, Have Fun.");
    window->SetAllowUserResizing(true);

    auto assets = gameHost->AssetManager();
    auto clientBounds = window->GetClientBounds();

    {
        commandList = std::make_shared<GraphicsCommandList>(*graphicsDevice);

        samplerPoint = std::make_shared<SamplerState>(graphicsDevice,
            SamplerDescription::CreateLinearWrap());

        texture = std::make_shared<Texture2D>(graphicsDevice,
            1, 1, false, SurfaceFormat::R8G8B8A8_UNorm);

        std::array<std::uint32_t, 1> pixelData = {0xffffffff};
        texture->SetData(pixelData.data());

        renderTarget = std::make_shared<RenderTarget2D>(graphicsDevice,
            clientBounds.Width, clientBounds.Height,
            false, SurfaceFormat::R8G8B8A8_UNorm, DepthFormat::None);
    }
    {
        spriteRenderer = std::make_unique<SpriteRenderer>(graphicsDevice, *assets);
        fxaa = std::make_unique<FXAA>(graphicsDevice, *assets);
        fxaa->SetViewport(clientBounds.Width, clientBounds.Height);
        screenQuad = std::make_unique<ScreenQuad>(graphicsDevice);
        polygonBatch = std::make_unique<PolygonBatch>(graphicsContext, graphicsDevice, *assets);
    }
    {
        gameEditor = std::make_unique<SceneEditor::InGameEditor>(gameHost);
        editorBackground = std::make_unique<SceneEditor::EditorBackground>(gameHost);
    }

    {
        mainCamera = gameWorld.CreateObject();
        mainCamera.AddComponent<Transform2D>();
        mainCamera.AddComponent<Camera2D>();
    }
    {
        auto textureAtlas = TexturePacker::TextureAtlasLoader::Load(*assets, "MaidChan2/skeleton.atlas");
        auto skeletonDesc = Spine::SkeletonDescLoader::Load(*assets, "MaidChan2/skeleton.json");
        maidTexture = assets->Load<Texture2D>("MaidChan2/skeleton.png");

        LogTexturePackerInfo(textureAtlas);
        LogSkeletalInfo(skeletonDesc);

        maidSkeleton = std::make_shared<Skeleton>(Spine::CreateSkeleton(skeletonDesc.Bones));
        maidSkeletonPose = std::make_shared<SkeletonPose>(SkeletonPose::CreateBindPose(*maidSkeleton));
        auto animationClip = std::make_shared<AnimationClip>(Spine::CreateAnimationClip(skeletonDesc, "Walk"));
        maidAnimationState = std::make_shared<AnimationState>(animationClip, 1.0f, true);
        maidAnimationClipIdle = std::make_shared<AnimationClip>(Spine::CreateAnimationClip(skeletonDesc, "Idle"));

        maidSkin = Spine::CreateSkin(skeletonDesc, textureAtlas, "default");
        maidSpriteAnimationTracks = Spine::CreateSpriteAnimationTrack(skeletonDesc, textureAtlas, "Walk");

        animationSystem.Add(maidAnimationState, maidSkeleton, maidSkeletonPose);

        maidGlobalPose = SkeletonHelper::ToGlobalPose(*maidSkeleton, *maidSkeletonPose);

        // NOTE: for Skinning
        auto bindPose = SkeletonPose::CreateBindPose(*maidSkeleton);
        maidSkinnedMesh = Spine::CreateSkinnedMesh(*graphicsDevice,
            SkeletonHelper::ToGlobalPose(*maidSkeleton, bindPose),
            skeletonDesc, textureAtlas,
            Vector2(maidTexture->Width(), maidTexture->Height()), "default");
        maidSkinningEffect = std::make_unique<SkinnedEffect>(*graphicsDevice, *assets);
    }

    {
        scenePanel = std::make_shared<UI::ScenePanel>(clientBounds.Width, clientBounds.Height);
        scenePanel->cameraObject = mainCamera;
        gameEditor->AddView(scenePanel);
    }
    {
        auto stackPanel = std::make_shared<UI::StackPanel>(124, 170);
        stackPanel->Transform(Matrix3x2::CreateTranslation(Vector2{5, 10}));
        gameEditor->AddView(stackPanel);

        {
            auto navigator = std::make_shared<UI::DebugNavigator>(gameHost->Clock());
            stackPanel->AddChild(navigator);
        }
        {
            slider1 = std::make_shared<UI::Slider>(-2.0, 2.0);
            slider1->Value(1.0);
            stackPanel->AddChild(slider1);
        }
        {
            slider2 = std::make_shared<UI::Slider>(0.0, 1.0);
            slider2->Value(1.0);
            stackPanel->AddChild(slider2);
        }
        {
            toggleSwitch1 = std::make_shared<UI::ToggleSwitch>();
            toggleSwitch1->IsOn(true);
            toggleSwitch1->OnContent("Play");
            toggleSwitch1->OffContent("Stop");
            stackPanel->AddChild(toggleSwitch1);
        }
        {
            toggleSwitch2 = std::make_shared<UI::ToggleSwitch>();
            toggleSwitch2->IsOn(true);
            stackPanel->AddChild(toggleSwitch2);
        }
        {
            toggleSwitch3 = std::make_shared<UI::ToggleSwitch>();
            toggleSwitch3->IsOn(false);
            stackPanel->AddChild(toggleSwitch3);
        }
        {
            toggleSwitch4 = std::make_shared<UI::ToggleSwitch>();
            toggleSwitch4->IsOn(false);
            stackPanel->AddChild(toggleSwitch4);
        }
    }

    clientViewport = Viewport{0, 0, clientBounds.Width, clientBounds.Height};

    connections.Connect(window->ClientSizeChanged, [this](int width, int height) {
        clientViewport = Viewport{0, 0, width, height};

        renderTarget = std::make_shared<RenderTarget2D>(
            graphicsDevice, width, height,
            false, SurfaceFormat::R8G8B8A8_UNorm, DepthFormat::None);

        fxaa->SetViewport(width, height);
        spriteRenderer->SetProjectionMatrix(Matrix4x4::CreateOrthographicLH(width, height, 1.0f, 100.0f));
    });
}