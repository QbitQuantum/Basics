void TextManipulator::ConsumeInput(IInputInjectorPtr injector, bool mouseIn)
{
	if (!mText)
		return;

	if (unsigned int chr = injector->GetChar())
	{
		auto mainWindowHandle = InputManager::GetInstance().GetMainWindowHandle();
		if (chr == 22) // Synchronous idle - ^V
		{
			injector->PopChar();	
			std::string data = GetClipboardDataAsString(mainWindowHandle);
			if (!data.empty())
			{
				if (IsHighlighting()){
					auto it = mText->begin() + mCursorPos;
					auto end = mText->begin() + mHighlightStart;
					if (mCursorPos > mHighlightStart)
					{
						std::swap(it, end);
					}
					mCursorPos = std::distance(mText->begin(), it);
					// delete selected string
					mText->erase(it, end);
					EndHighlighting();
				}
				std::wstring wclipData = AnsiToWide(data.c_str());
				mText->insert(mText->begin() + mCursorPos, wclipData.begin(), wclipData.end());				
				mCursorPos += data.size();
				OnCursorPosChanged();
				OnTextChanged();
			}
		}
		else if (chr == 3){ // ^C
			if (IsHighlighting()){
				auto it = mText->begin() + mCursorPos;
				auto end = mText->begin() + mHighlightStart;
				if (mCursorPos > mHighlightStart)
				{
					std::swap(it, end);
				}
				std::string data(it, end);
				SetClipboardStringData(mainWindowHandle, data.c_str());
			}
		}
		else{
			switch (chr)
			{
			case VK_BACK:
			{			
				if (IsHighlighting() && !mText->empty())
				{
					auto it = mText->begin() + mCursorPos;
					auto end = mText->begin() + mHighlightStart;
					if (mCursorPos > mHighlightStart)
					{
						std::swap(it, end);
					}
					mCursorPos = std::distance(mText->begin(), it);
					mText->erase(it, end);
					EndHighlighting();
				}
				else if (mCursorPos > 0 && !mText->empty())
				{
					mText->erase(mText->begin() + mCursorPos - 1);
					mCursorPos--;
				}
				OnCursorPosChanged();
				OnTextChanged();
			}
			break;
			default:
			{
				if (IsHighlighting())
				{
					auto it = mText->begin() + mCursorPos;
					auto end = mText->begin() + mHighlightStart;
					if (mCursorPos > mHighlightStart)
					{
						std::swap(it, end);
					}
					mCursorPos = std::distance(mText->begin(), it);
					// delete selected string
					mText->erase(it, end);
					EndHighlighting();
				}

				mText->insert(mText->begin() + mCursorPos, chr);
				mCursorPos++;
				OnCursorPosChanged();
				OnTextChanged();
			}
			}
		}

		injector->PopChar();
	}

	if (injector->IsKeyPressed(VK_HOME))
	{
		Highlighting(injector->IsKeyDown(VK_SHIFT));
		mCursorPos = 0;
		OnCursorPosChanged();
	}
	else if (injector->IsKeyPressed(VK_END))
	{
		Highlighting(injector->IsKeyDown(VK_SHIFT));
		mCursorPos = mText->size();
		OnCursorPosChanged();
	}
	else if (injector->IsKeyPressed(VK_DELETE))
	{
		if (!mText->empty())
		{
			if (IsHighlighting())
			{
				auto it = mText->begin() + mCursorPos;
				auto end = mText->begin() + mHighlightStart;
				if (mCursorPos > mHighlightStart)
				{
					std::swap(it, end);
				}
				mCursorPos = std::distance(mText->begin(), it);
				mText->erase(it, end);
				EndHighlighting();
			}
			else
			{
				mText->erase(mText->begin() + mCursorPos);
			}
		}
		OnCursorPosChanged();
		OnTextChanged();
	}
	else if (injector->IsKeyPressed(VK_LEFT))
	{
		Highlighting(injector->IsKeyDown(VK_SHIFT));
		if (mCursorPos>0)
		{
			mCursorPos--;
		}
		OnCursorPosChanged();
	}
	else if (injector->IsKeyPressed(VK_RIGHT))
	{
		Highlighting(injector->IsKeyDown(VK_SHIFT));
		if (mCursorPos < (int)mText->size())
		{
			mCursorPos++;
		}
		OnCursorPosChanged();
	}
	//Logger::Log(FB_DEFAULT_LOG_ARG, "(info) checking double click");
	if (mouseIn && injector->IsLButtonDoubleClicked()){
		SelectAll();
		OnCursorPosChanged();
	}

	injector->Invalidate(InputDevice::Keyboard);
}