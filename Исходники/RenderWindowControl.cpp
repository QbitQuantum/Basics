    RenderWindowControl::RenderWindowControl(MyGUI::Widget* _parent) :
        wraps::BaseLayout("RenderWindow.layout", _parent),
        mCanvas(nullptr),
        mKeyFrameBar(nullptr)
    {
        mCanvas = mMainWidget->createWidget<MyGUI::Canvas>("Canvas",
            MyGUI::IntCoord(0, 0, mMainWidget->getClientCoord().width, mMainWidget->getClientCoord().height-51), MyGUI::Align::Stretch);

        mInfo = mCanvas->createWidget<MyGUI::TextBox>("TextBox", MyGUI::IntCoord(100, 10, 100, 70), MyGUI::Align::Default);
        mInfo->setTextShadow(true);
        mInfo->setTextShadowColour(MyGUI::Colour::Black);
        mInfoStatic = mCanvas->createWidget<MyGUI::TextBox>("TextBox", MyGUI::IntCoord(10, 10, 80, 70), MyGUI::Align::Default);
        mInfoStatic->setTextShadow(true);
        mInfoStatic->setTextShadowColour(MyGUI::Colour::Black);
        mInfoStatic->setCaption("Vertices :\nFaces:\nSub Models:\nBones:");
        updateInfo();

        for (int i = 0; i < MAX_BONE_NAME_NUMS; ++i)
        {
            MyGUI::TextBox* bonename = mCanvas->createWidget<MyGUI::TextBox>("TextBox", MyGUI::IntCoord(0, 10, 150, 15), MyGUI::Align::Default);
            bonename->setTextAlign(MyGUI::Align::Center);
            bonename->setTextShadow(true);
            bonename->setTextShadowColour(MyGUI::Colour::Black);
            bonename->setVisible(false);
            mBoneNames.push_back(bonename);
        }

        mKeyFrameBar = new KeyFrameBarControl(mMainWidget);

        uint32 width = (uint32)mCanvas->getWidth();
        uint32 height = (uint32)mCanvas->getHeight();
        DiBase::Driver->GetMainRenderWindow()->SetCustomizedCanvasSize(width, height);

        MyGUI::RenderManager& render = MyGUI::RenderManager::getInstance();
        DiTexturePtr canvasTexture = DiBase::Driver->GetMainRenderWindow()->GetCanvasTexture();
        MyGUI::DemiTexture* tex = static_cast<MyGUI::DemiTexture*>(render.createTexture(canvasTexture->GetName().c_str()));
        tex->loadFromDemiTexture(canvasTexture->GetName().c_str());

        mCanvas->createTexture(tex->getName());
        mCanvas->requestUpdateCanvas = MyGUI::newDelegate(this, &RenderWindowControl::onUpdateCanvas);
	}