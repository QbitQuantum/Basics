void lggBeamMapFloater::draw()
{

	LLRect swatch_rect;
	LLButton* createButton = empanel->getChild<LLButton>("custom_beam_btn");

	createButton->localRectToOtherView(createButton->getLocalRect(), &swatch_rect, this);
	LLRect local_rect = getLocalRect();
	if (gFocusMgr.childHasKeyboardFocus(this) && createButton->isInVisibleChain() && mContextConeOpacity > 0.001f)
	{
		gGL.getTexUnit(0)->unbind(LLTexUnit::TT_TEXTURE);
		LLGLEnable(GL_CULL_FACE);
		gGL.begin(LLRender::QUADS);
		{
			gGL.color4f(0.f, 0.f, 0.f, CONTEXT_CONE_IN_ALPHA * mContextConeOpacity);
			gGL.vertex2i(swatch_rect.mLeft, swatch_rect.mTop);
			gGL.vertex2i(swatch_rect.mRight, swatch_rect.mTop);
			gGL.color4f(0.f, 0.f, 0.f, CONTEXT_CONE_OUT_ALPHA * mContextConeOpacity);
			gGL.vertex2i(local_rect.mRight, local_rect.mTop);
			gGL.vertex2i(local_rect.mLeft, local_rect.mTop);

			gGL.color4f(0.f, 0.f, 0.f, CONTEXT_CONE_OUT_ALPHA * mContextConeOpacity);
			gGL.vertex2i(local_rect.mLeft, local_rect.mTop);
			gGL.vertex2i(local_rect.mLeft, local_rect.mBottom);
			gGL.color4f(0.f, 0.f, 0.f, CONTEXT_CONE_IN_ALPHA * mContextConeOpacity);
			gGL.vertex2i(swatch_rect.mLeft, swatch_rect.mBottom);
			gGL.vertex2i(swatch_rect.mLeft, swatch_rect.mTop);

			gGL.color4f(0.f, 0.f, 0.f, CONTEXT_CONE_OUT_ALPHA * mContextConeOpacity);
			gGL.vertex2i(local_rect.mRight, local_rect.mBottom);
			gGL.vertex2i(local_rect.mRight, local_rect.mTop);
			gGL.color4f(0.f, 0.f, 0.f, CONTEXT_CONE_IN_ALPHA * mContextConeOpacity);
			gGL.vertex2i(swatch_rect.mRight, swatch_rect.mTop);
			gGL.vertex2i(swatch_rect.mRight, swatch_rect.mBottom);

			gGL.color4f(0.f, 0.f, 0.f, CONTEXT_CONE_OUT_ALPHA * mContextConeOpacity);
			gGL.vertex2i(local_rect.mLeft, local_rect.mBottom);
			gGL.vertex2i(local_rect.mRight, local_rect.mBottom);
			gGL.color4f(0.f, 0.f, 0.f, CONTEXT_CONE_IN_ALPHA * mContextConeOpacity);
			gGL.vertex2i(swatch_rect.mRight, swatch_rect.mBottom);
			gGL.vertex2i(swatch_rect.mLeft, swatch_rect.mBottom);
		}
		gGL.end();
	}

	static F32* opacity = rebind_llcontrol<F32>("PickerContextOpacity", &gSavedSettings, true);


	mContextConeOpacity = lerp(mContextConeOpacity, *opacity, LLCriticalDamp::getInterpolant(CONTEXT_FADE_TIME));


	//getChild<LLPanel>("beamshape_draw")->setBackgroundColor(getChild<LLColorSwatchCtrl>("back_color_swatch")->get());
	LLFloater::draw();
	LLRect rec  = getChild<LLPanel>("beamshape_draw")->getRect();
	
	gGL.pushMatrix();
	gGL.color4fv(LLColor4::white.mV);
	gl_circle_2d(rec.getCenterX(),rec.getCenterY(),2.0f,(S32)30,false);
	gGL.color4fv(LLColor4::black.mV);
	gl_circle_2d(rec.getCenterX(),rec.getCenterY(),30.0f,(S32)30,false);	
	gGL.color4fv(LLColor4::white.mV);
	gl_circle_2d(rec.getCenterX(),rec.getCenterY(),60.0f,(S32)30,false);	
	gGL.color4fv(LLColor4::black.mV);
	gl_circle_2d(rec.getCenterX(),rec.getCenterY(),90.0f,(S32)30,false);
	gGL.color4fv(LLColor4::white.mV);
	gl_circle_2d(rec.getCenterX(),rec.getCenterY(),120.0f,(S32)30,false);

	for(int i = 0; i < (int)dots.size();i++)
	{	
		gGL.color4fv(LLColor4::white.mV);
		gl_circle_2d(dots[i].x,dots[i].y,9.0f,(S32)30,true);

		gGL.color4fv(LLColor4::black.mV);
		gl_circle_2d(dots[i].x,dots[i].y,8.0f,(S32)30,true);
		
		gGL.color4fv(dots[i].c.mV);
		gl_circle_2d(dots[i].x,dots[i].y,7.0f,(S32)30,true);
		
		
	}
	gGL.popMatrix();
	
}