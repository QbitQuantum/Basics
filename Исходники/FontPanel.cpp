	void FontPanel::notifyMouseButtonClick(MyGUI::Widget* _widget)
	{
		// шрифто?нету
		if (mComboFont->getOnlyText().empty()) return;
		if (mEditSaveFileName->getOnlyText().empty() && _widget == mButtonSave) return;

		MyGUI::xml::Document document;
		document.createDeclaration();
		MyGUI::xml::ElementPtr root = document.createRoot("MyGUI");
		generateFontTTFXml(root);

		if (_widget == mButtonSave)
		{
			if (!document.save(mEditSaveFileName->getOnlyText() + ".xml"))
			{
				/*MyGUI::Message* message =*/ MyGUI::Message::createMessageBox("Message", "error", document.getLastError(), MyGUI::MessageBoxStyle::Ok | MyGUI::MessageBoxStyle::IconError);
			}
			else
			{
				/*MyGUI::Message* message =*/ MyGUI::Message::createMessageBox("Message", "success", mEditSaveFileName->getOnlyText() + ".xml", MyGUI::MessageBoxStyle::Ok | MyGUI::MessageBoxStyle::IconInfo);
			}

			MyGUI::IFont* font = MyGUI::FontManager::getInstance().getByName(mFontName);
			MyGUI::ITexture* texture = font->getTextureFont();
			texture->saveToFile(mEditSaveFileName->getOnlyText() + ".png");
		}
		else if (_widget == mButtonGenerate)
		{
			MyGUI::ResourceManager& manager = MyGUI::ResourceManager::getInstance();
			if (manager.isExist(mFontName))
			{
				manager.removeByName(mFontName);
			}

			MyGUI::ResourceManager::getInstance().loadFromXmlNode(root, "", MyGUI::Version());
			MyGUI::IResource* resource = manager.getByName(mFontName, false);
			MYGUI_ASSERT(resource != nullptr, "Could not find font '" << mFontName << "'");
			MyGUI::IFont* font = resource->castType<MyGUI::IFont>();

			// выво?реальног?размер?шрифта
			mFontHeight = font->getDefaultHeight();
			mTextPix->setCaption(MyGUI::utility::toString("Height of a font is ", mFontHeight, " pixels"));

			mFontView->setFontName(mFontName);
			mTextureView->setFontName(mFontName);
		}
	}