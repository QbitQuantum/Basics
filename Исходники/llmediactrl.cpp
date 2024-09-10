void LLMediaCtrl::draw()
{
	if ( ! mWebBrowserImage || mWebBrowserImage->getNeedsUpdate())
		return;

	if ( gRestoreGL == 1 )
	{
		LLRect r = getRect();
		reshape( r.getWidth(), r.getHeight(), FALSE );
		return;
	};

	// NOTE: optimization needed here - probably only need to do this once
	// unless tearoffs change the parent which they probably do.
	const LLUICtrl* ptr = findRootMostFocusRoot();
	if ( ptr && ptr->hasFocus() )
	{
		setFrequentUpdates( true );
	}
	else
	{
		setFrequentUpdates( false );
	};

	// alpha off for this
	LLGLSUIDefault gls_ui;
	LLGLDisable gls_alphaTest( GL_ALPHA_TEST );

	bool draw_media = false;
	
	LLPluginClassMedia* media_plugin = NULL;
	LLWebBrowserTexture* media_texture =  mWebBrowserImage;
	
	if(mMediaSource && mMediaSource->hasMedia())
	{
		media_plugin = mMediaSource->getMediaPlugin();

		if(media_plugin && (media_plugin->textureValid()))
		{
			media_texture = mWebBrowserImage;
			if(media_texture)
			{
				draw_media = true;
			}
		}
	}
	if(draw_media)
	{
		gGL.pushMatrix();
		{
			if (mIgnoreUIScale)
			{
				gGL.loadIdentity();
				// font system stores true screen origin, need to scale this by UI scale factor
				// to get render origin for this view (with unit scale)
				gGL.translatef(floorf(LLFontGL::sCurOrigin.mX * LLUI::getScaleFactor().mV[VX]), 
							floorf(LLFontGL::sCurOrigin.mY * LLUI::getScaleFactor().mV[VY]), 
							LLFontGL::sCurDepth);
			}

			// scale texture to fit the space using texture coords
			gGL.getTexUnit(0)->bind(media_texture);
			LLColor4 media_color = LLColor4::white;
			gGL.color4fv( media_color.mV );
			F32 max_u = ( F32 )media_plugin->getWidth() / ( F32 )media_plugin->getTextureWidth();
			F32 max_v = ( F32 )media_plugin->getHeight() / ( F32 )media_plugin->getTextureHeight();

			LLRect r = getRect();
			S32 width, height;
			S32 x_offset = 0;
			S32 y_offset = 0;
		
			if(mStretchToFill)
			{
				if(mMaintainAspectRatio)
				{
					F32 media_aspect = (F32)(media_plugin->getWidth()) / (F32)(media_plugin->getHeight());
					F32 view_aspect = (F32)(r.getWidth()) / (F32)(r.getHeight());
					if(media_aspect > view_aspect)
					{
						// max width, adjusted height
						width = r.getWidth();
						height = llmin(llmax(llround(width / media_aspect), 0), r.getHeight());
					}
					else
					{
						// max height, adjusted width
						height = r.getHeight();
						width = llmin(llmax(llround(height * media_aspect), 0), r.getWidth());
					}
				}
				else
				{
					width = r.getWidth();
					height = r.getHeight();
				}
			}
			else
			{
				width = llmin(media_plugin->getWidth(), r.getWidth());
				height = llmin(media_plugin->getHeight(), r.getHeight());
			}
			
			x_offset = (r.getWidth() - width) / 2;
			y_offset = (r.getHeight() - height) / 2;		

			if (mIgnoreUIScale)
			{
				x_offset = llround((F32)x_offset * LLUI::getScaleFactor().mV[VX]);
				y_offset = llround((F32)y_offset * LLUI::getScaleFactor().mV[VY]);
				width = llround((F32)width * LLUI::getScaleFactor().mV[VX]);
				height = llround((F32)height * LLUI::getScaleFactor().mV[VY]);
			}

			// draw the browser
			gGL.setSceneBlendType(LLRender::BT_REPLACE);
			gGL.begin( LLRender::QUADS );
			if (! media_plugin->getTextureCoordsOpenGL())
			{
				// render using web browser reported width and height, instead of trying to invert GL scale
				gGL.texCoord2f( max_u, 0.f );
				gGL.vertex2i( x_offset + width, y_offset + height );

				gGL.texCoord2f( 0.f, 0.f );
				gGL.vertex2i( x_offset, y_offset + height );

				gGL.texCoord2f( 0.f, max_v );
				gGL.vertex2i( x_offset, y_offset );

				gGL.texCoord2f( max_u, max_v );
				gGL.vertex2i( x_offset + width, y_offset );
			}
			else
			{
				// render using web browser reported width and height, instead of trying to invert GL scale
				gGL.texCoord2f( max_u, max_v );
				gGL.vertex2i( x_offset + width, y_offset + height );

				gGL.texCoord2f( 0.f, max_v );
				gGL.vertex2i( x_offset, y_offset + height );

				gGL.texCoord2f( 0.f, 0.f );
				gGL.vertex2i( x_offset, y_offset );

				gGL.texCoord2f( max_u, 0.f );
				gGL.vertex2i( x_offset + width, y_offset );
			}
			gGL.end();
			gGL.setSceneBlendType(LLRender::BT_ALPHA);
		}
		gGL.popMatrix();
	}
	// highlight if keyboard focus here. (TODO: this needs some work)
	if ( mBorder && mBorder->getVisible() )
		mBorder->setKeyboardFocusHighlight( gFocusMgr.childHasKeyboardFocus( this ) );

	
	LLUICtrl::draw();
}