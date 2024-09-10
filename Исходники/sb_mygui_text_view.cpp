	void TextView::update(const MyGUI::UString& _text, const Sandbox::FontPtr& _font , MyGUI::Align _align, int _maxWidth)
	{
		
        m_font = _font;
		mViewSize.clear();
        mTextData.Clear();
        
        FontAlign align = ALIGN_LEFT;
        if (_align.isHCenter())
            align = ALIGN_CENTER;
        if (_align.isRight())
            align = ALIGN_RIGHT;
        
        mTextData.Fill(_text.c_str(), _font, _maxWidth, align);

		mViewSize = MyGUI::IntSize(mTextData.size.w,mTextData.size.h);
	}