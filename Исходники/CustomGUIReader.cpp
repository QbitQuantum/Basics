	void CustomGUIReader::setCustomProps(const std::string &classType, cocos2d::Ref *widget, const rapidjson::Value &customOptions)
	{
        if (_setPropsFunc != 0)
        {
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            customOptions.Accept(writer);

            auto stack = LuaEngine::getInstance()->getLuaStack();
            stack->pushString(classType.c_str(), classType.size());
            stack->pushObject(widget, "cc.Ref");
            stack->pushString(buffer.GetString(), buffer.Size());
            stack->executeFunctionByHandler(_setPropsFunc, 3);
        }
	}