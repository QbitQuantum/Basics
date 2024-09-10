void LLProgressView::draw()
{
	static LLTimer timer;

	if (gNoRender)
	{
		return;
	}

	// Make sure the progress view always fills the entire window.
	S32 width = gViewerWindow->getWindowWidth();
	S32 height = gViewerWindow->getWindowHeight();
	if( (width != getRect().getWidth()) || (height != getRect().getHeight()) )
	{
		reshape( width, height );
	}

	// Paint bitmap if we've got one
	glPushMatrix();
	if (gStartImageGL)
	{
		LLGLSUIDefault gls_ui;
		LLViewerImage::bindTexture(gStartImageGL);
		gGL.color4f(1.f, 1.f, 1.f, mFadeTimer.getStarted() ? clamp_rescale(mFadeTimer.getElapsedTimeF32(), 0.f, FADE_IN_TIME, 1.f, 0.f) : 1.f);
		F32 image_aspect = (F32)gStartImageWidth / (F32)gStartImageHeight;
		F32 view_aspect = (F32)width / (F32)height;
		// stretch image to maintain aspect ratio
		if (image_aspect > view_aspect)
		{
			glTranslatef(-0.5f * (image_aspect / view_aspect - 1.f) * width, 0.f, 0.f);
			glScalef(image_aspect / view_aspect, 1.f, 1.f);
		}
		else
		{
			glTranslatef(0.f, -0.5f * (view_aspect / image_aspect - 1.f) * height, 0.f);
			glScalef(1.f, view_aspect / image_aspect, 1.f);
		}
		gl_rect_2d_simple_tex( getRect().getWidth(), getRect().getHeight() );
		gStartImageGL->unbindTexture(0, GL_TEXTURE_2D);
	}
	else
	{
		LLGLSNoTexture gls_no_texture;
		gGL.color4f(0.f, 0.f, 0.f, 1.f);
		gl_rect_2d(getRect());
	}
	glPopMatrix();

	// Handle fade-in animation
	if (mFadeTimer.getStarted())
	{
		LLView::draw();
		if (mFadeTimer.getElapsedTimeF32() > FADE_IN_TIME)
		{
			gFocusMgr.removeTopCtrlWithoutCallback(this);
			LLView::setVisible(FALSE);
			gStartImageGL = NULL;
		}
		return;
	}

	S32 line_x = getRect().getWidth() / 2;
	S32 line_one_y = getRect().getHeight() / 2 + 64;
	const S32 LINE_SPACING = 25;
	S32 line_two_y = line_one_y - LINE_SPACING;
	const LLFontGL* font = LLFontGL::sSansSerif;

	LLUIImagePtr shadow_imagep = LLUI::getUIImage("rounded_square_soft.tga");
	LLUIImagePtr bar_fg_imagep = LLUI::getUIImage("progressbar_fill.tga");
	LLUIImagePtr bar_bg_imagep = LLUI::getUIImage("progressbar_track.tga");
	LLUIImagePtr bar_imagep = LLUI::getUIImage("rounded_square.tga");
	
	LLColor4 background_color = gColors.getColor("LoginProgressBarBgColor");

	F32 alpha = 0.5f + 0.5f*0.5f*(1.f + (F32)sin(3.f*timer.getElapsedTimeF32()));
	// background_color.mV[3] = background_color.mV[3]*alpha;

	std::string top_line = LLAppViewer::instance()->getSecondLifeTitle();

	S32 bar_bottom = line_two_y - 30;
	S32 bar_height = 18;
	S32 bar_width = getRect().getWidth() * 2 / 3;
	S32 bar_left = (getRect().getWidth() / 2) - (bar_width / 2);

	// translucent outline box
	S32 background_box_left = ( ( ( getRect().getWidth() / 2 ) - ( bar_width / 2 ) ) / 4 ) * 3;
	S32 background_box_top = ( getRect().getHeight() / 2 ) + LINE_SPACING * 5;
	S32 background_box_right = getRect().getWidth() - background_box_left;
	S32 background_box_bottom = ( getRect().getHeight() / 2 ) - LINE_SPACING * 5;
	S32 background_box_width = background_box_right - background_box_left + 1;
	S32 background_box_height = background_box_top - background_box_bottom + 1;

//	shadow_imagep->draw( background_box_left + 2, 
//									background_box_bottom - 2, 
//									background_box_width, 
//									background_box_height,
//									gColors.getColor( "LoginProgressBoxShadowColor" ) );
//	bar_outline_imagep->draw( background_box_left, 
//									background_box_bottom, 
//									background_box_width, 
//									background_box_height,
//									gColors.getColor("LoginProgressBoxBorderColor") );

	bar_imagep->draw( background_box_left + 1,
									background_box_bottom + 1, 
									background_box_width - 2,
									background_box_height - 2,
									gColors.getColor("LoginProgressBoxCenterColor") );

	// we'll need this later for catching a click if it looks like it contains a link
	if ( mMessage.find( "http://" ) != std::string::npos )
		mOutlineRect.set( background_box_left, background_box_top, background_box_right, background_box_bottom );
	else
		mOutlineRect.set( 0, 0, 0, 0 );

	// draw loading bar
	font->renderUTF8(top_line, 0,
		line_x, line_one_y,
		//LLColor4::white,
		gColors.getColor("LoginProgressBoxTextColor"),
		LLFontGL::HCENTER, LLFontGL::BASELINE,
		LLFontGL::DROP_SHADOW);
	font->renderUTF8(mText, 0,
		line_x, line_two_y,
		//LLColor4::white,
		gColors.getColor("LoginProgressBoxTextColor"),
		LLFontGL::HCENTER, LLFontGL::BASELINE,
		LLFontGL::DROP_SHADOW);
		
//	shadow_imagep->draw(
//		bar_left + 2, 
//		bar_bottom - 2, 
//		bar_width, 
//		bar_height,
//		gColors.getColor("LoginProgressBoxShadowColor"));

//	bar_imagep->draw(
//		bar_left, 
//		bar_bottom, 
//		bar_width, 
//		bar_height,
//		LLColor4(0.7f, 0.7f, 0.8f, 1.0f));

	bar_bg_imagep->draw(
		bar_left + 2, 
		bar_bottom + 2,
		bar_width - 4, 
		bar_height - 4,
		background_color);

	LLColor4 bar_color = gColors.getColor("LoginProgressBarFgColor");
	bar_color.mV[3] = alpha;
	bar_fg_imagep->draw(
		bar_left + 2, 
		bar_bottom + 2,
		llround((bar_width - 4) * (mPercentDone / 100.f)), 
		bar_height - 4,
		bar_color);

	S32 line_three_y = line_two_y - LINE_SPACING * 3;
	
	// draw the message if there is one
	if(!mMessage.empty())
	{
		LLColor4 text_message_color = gColors.getColor("LoginProgressBoxTextColor");
		LLWString wmessage = utf8str_to_wstring(mMessage);
		const F32 MAX_PIXELS = 640.0f;
		S32 chars_left = wmessage.length();
		S32 chars_this_time = 0;
		S32 msgidx = 0;
		while(chars_left > 0)
		{
			chars_this_time = font->maxDrawableChars(wmessage.substr(msgidx).c_str(),
													 MAX_PIXELS,
													 MAX_STRING - 1,
													 TRUE);
			LLWString wbuffer = wmessage.substr(msgidx, chars_this_time);
			font->render(wbuffer, 0,
						 (F32)line_x, (F32)line_three_y,
						 //LLColor4::white,
						 gColors.getColor("LoginProgressBoxTextColor"),
						 LLFontGL::HCENTER, LLFontGL::BASELINE,
						 LLFontGL::DROP_SHADOW);
			msgidx += chars_this_time;
			chars_left -= chars_this_time;
			line_three_y -= LINE_SPACING;
		}
	}

	// draw children
	LLView::draw();
}