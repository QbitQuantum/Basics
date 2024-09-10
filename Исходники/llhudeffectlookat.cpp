//-----------------------------------------------------------------------------
// render()
//-----------------------------------------------------------------------------
void LLHUDEffectLookAt::render()
{
	static const LLCachedControl<bool> private_look_at("PrivateLookAt",false);
    if (private_look_at &&
        (gAgent.getAvatarObject() == ((LLVOAvatar*)(LLViewerObject*)mSourceObject))) return;
	if (sDebugLookAt && mSourceObject.notNull())
	{
		gGL.getTexUnit(0)->unbind(LLTexUnit::TT_TEXTURE);

		LLVector3 target = mTargetPos + ((LLVOAvatar*)(LLViewerObject*)mSourceObject)->mHeadp->getWorldPosition();
		glMatrixMode(GL_MODELVIEW);
		gGL.pushMatrix();
		gGL.translatef(target.mV[VX], target.mV[VY], target.mV[VZ]);
		glScalef(0.3f, 0.3f, 0.3f);
		gGL.begin(LLRender::LINES);
		{
			LLColor3 color = (*mAttentions)[mTargetType].mColor;
			gGL.color3f(color.mV[VRED], color.mV[VGREEN], color.mV[VBLUE]);
			gGL.vertex3f(-1.f, 0.f, 0.f);
			gGL.vertex3f(1.f, 0.f, 0.f);

			gGL.vertex3f(0.f, -1.f, 0.f);
			gGL.vertex3f(0.f, 1.f, 0.f);

			gGL.vertex3f(0.f, 0.f, -1.f);
			gGL.vertex3f(0.f, 0.f, 1.f);
		} gGL.end();
		gGL.popMatrix();
		// <edit>
		const std::string text = ((LLVOAvatar*)(LLViewerObject*)mSourceObject)->getFullname();
		LLVector3 offset = gAgent.getCameraPositionAgent() - target;
		offset.normalize();
		LLVector3 shadow_offset = offset * 0.49f;
		offset *= 0.5f;
		const LLFontGL* font = LLResMgr::getInstance()->getRes(LLFONT_SANSSERIF);
		LLGLEnable gl_blend(GL_BLEND);
		glPushMatrix();
		gViewerWindow->setupViewport();
		hud_render_utf8text(text,
			target + shadow_offset,
			*font,
			LLFontGL::NORMAL,
			-0.5f * font->getWidthF32(text) + 2.0f,
			-2.0f,
			LLColor4::black,
			FALSE);
		hud_render_utf8text(text,
			target + offset,
			*font,
			LLFontGL::NORMAL,
			-0.5f * font->getWidthF32(text),
			0.0f,
			(*mAttentions)[mTargetType].mColor,
			FALSE);
		glPopMatrix();
		// </edit>
	}
}