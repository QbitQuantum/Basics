	//---------------------------------------------------------------------
	void SceneResource::processCamera(const Util::XmlNode * cameraNode) const
	{
		CameraPtr camera;

		/// params
		{
			Util::String nearClipStr(mXmlReader->getAttribute(cameraNode, "near_clip"));
			Util::real nearClip = boost::lexical_cast<Util::real>(nearClipStr);

			Util::String farClipStr(mXmlReader->getAttribute(cameraNode, "far_clip"));
			Util::real farClip = boost::lexical_cast<Util::real>(farClipStr);

			Util::String viewportRectStr(mXmlReader->getAttribute(cameraNode, "viewport_rect"));
			XMVECTOR viewportRect = Util::StringToVector(viewportRectStr, 4);

			camera = boost::make_shared<Camera>(nearClip, farClip, 
				Util::UintPair(XMVectorGetIntX(viewportRect), XMVectorGetIntY(viewportRect)),
				Util::UintPair(XMVectorGetIntZ(viewportRect), XMVectorGetIntW(viewportRect)));

			IF_NULL_EXCEPTION(camera, "Camera creat failed!");
		}

		/// postion
		{
			Util::String posStr(mXmlReader->getAttribute(cameraNode, "position"));
			camera->setPosition(Util::StringToVector(posStr, 3));
		}

		/// lookat
		{
			Util::String str(mXmlReader->getAttribute(cameraNode, "lookat"));
			camera->lookAt(Util::StringToVector(str, 3));
		}
		
		/// movespeed
		{
			Util::String str(mXmlReader->getAttribute(cameraNode, "move_speed"));
			camera->setMoveSpeed(boost::lexical_cast<Util::real>(str));
		}

		EngineManager::getSingleton().setCamera(camera);
	}