void ActionNode::initWithDictionary(const rapidjson::Value& dic, Ref* root)
{
    Widget * rw = dynamic_cast<Widget *>(root);
    if (nullptr == rw)
        return;

    setActionTag(DICTOOL->getIntValue_json(dic, "ActionTag"));
    Widget* node = Helper::seekActionWidgetByActionTag(rw, getActionTag());
    bool positionOffset = node && (nullptr == (dynamic_cast<Layout *>(node)));

    int actionFrameCount = DICTOOL->getArrayCount_json(dic, "actionframelist");
    for (int i=0; i<actionFrameCount; i++)
    {
        const rapidjson::Value& actionFrameDic = DICTOOL->getDictionaryFromArray_json(dic, "actionframelist", i);
        int frameInex = DICTOOL->getIntValue_json(actionFrameDic,"frameid");

        int frameTweenType = DICTOOL->getIntValue_json(actionFrameDic,"tweenType");

        std::vector<float> frameTweenParameter;
        int frameTweenParameterNum = DICTOOL->getArrayCount_json(actionFrameDic, "tweenParameter");

        for (int j = 0; j < frameTweenParameterNum; j++)
        {
            float value = DICTOOL->getFloatValueFromArray_json(actionFrameDic, "tweenParameter", j);
            frameTweenParameter.push_back(value);
        }


        bool existPosition = DICTOOL->checkObjectExist_json(actionFrameDic,"positionx");
        if (existPosition)
        {
            float positionX = DICTOOL->getFloatValue_json(actionFrameDic, "positionx");
            float positionY = DICTOOL->getFloatValue_json(actionFrameDic, "positiony");
            if (positionOffset && (nullptr != node->getParent()) && ActionManagerEx::getInstance()->getStudioVersionNumber() < 1600)
            {
                Vec2 AnchorPointIn = node->getParent()->getAnchorPointInPoints();
                positionX += AnchorPointIn.x;
                positionY += AnchorPointIn.y;
            }
            ActionMoveFrame* actionFrame = new (std::nothrow) ActionMoveFrame();
            actionFrame->setFrameIndex(frameInex);
            actionFrame->setEasingType(frameTweenType);
            actionFrame->setEasingParameter(frameTweenParameter);
            actionFrame->setPosition(Vec2(positionX, positionY));
            auto cActionArray = _frameArray.at((int)kKeyframeMove);
            cActionArray->pushBack(actionFrame);
            actionFrame->release();
        }

        bool existScale = DICTOOL->checkObjectExist_json(actionFrameDic,"scalex");
        if (existScale)
        {
            float scaleX = DICTOOL->getFloatValue_json(actionFrameDic, "scalex");
            float scaleY = DICTOOL->getFloatValue_json(actionFrameDic, "scaley");
            ActionScaleFrame* actionFrame = new (std::nothrow) ActionScaleFrame();
            actionFrame->setFrameIndex(frameInex);
            actionFrame->setEasingType(frameTweenType);
            actionFrame->setEasingParameter(frameTweenParameter);
            actionFrame->setScaleX(scaleX);
            actionFrame->setScaleY(scaleY);
            auto cActionArray = _frameArray.at((int)kKeyframeScale);
            cActionArray->pushBack(actionFrame);
            actionFrame->release();             
        }

        bool existRotation = DICTOOL->checkObjectExist_json(actionFrameDic,"rotation");
        if (existRotation)
        {
            float rotation = DICTOOL->getFloatValue_json(actionFrameDic, "rotation");
            ActionRotationFrame* actionFrame = new (std::nothrow) ActionRotationFrame();
            actionFrame->setFrameIndex(frameInex);
            actionFrame->setEasingType(frameTweenType);
            actionFrame->setEasingParameter(frameTweenParameter);
            actionFrame->setRotation(rotation);
            auto cActionArray = _frameArray.at((int)kKeyframeRotate);
            cActionArray->pushBack(actionFrame);
            actionFrame->release();
        }

        bool existOpacity = DICTOOL->checkObjectExist_json(actionFrameDic,"opacity");
        if (existOpacity)
        {
            int opacity = DICTOOL->getIntValue_json(actionFrameDic, "opacity");
            ActionFadeFrame* actionFrame = new (std::nothrow) ActionFadeFrame();
            actionFrame->setFrameIndex(frameInex);
            actionFrame->setEasingType(frameTweenType);
            actionFrame->setEasingParameter(frameTweenParameter);
            actionFrame->setOpacity(opacity);
            auto cActionArray = _frameArray.at((int)kKeyframeTint);
            cActionArray->pushBack(actionFrame);
            actionFrame->release();
        }

        bool existColor = DICTOOL->checkObjectExist_json(actionFrameDic,"colorr");
        if (existColor)
        {
            int colorR = DICTOOL->getIntValue_json(actionFrameDic, "colorr");
            int colorG = DICTOOL->getIntValue_json(actionFrameDic, "colorg");
            int colorB = DICTOOL->getIntValue_json(actionFrameDic, "colorb");
            ActionTintFrame* actionFrame = new (std::nothrow) ActionTintFrame();
            actionFrame->setFrameIndex(frameInex);
            actionFrame->setEasingType(frameTweenType);
            actionFrame->setEasingParameter(frameTweenParameter);
            actionFrame->setColor(Color3B(colorR,colorG,colorB));
            auto cActionArray = _frameArray.at((int)kKeyframeFade);
            cActionArray->pushBack(actionFrame);
            actionFrame->release();
        }
    }
    initActionNodeFromRoot(root);
}