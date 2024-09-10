//==========================================================================
//
//
//
//==========================================================================
void gl_DrawTexture(FTexInfo *texInfo)
{
	float x, y, w, h;
	float ox, oy, cx, cy, r, g, b;
	float light = 1.f;
	
	x = texInfo->x;
	y = texInfo->y;
	w = texInfo->width;
	h = texInfo->height;
	
	FGLTexture * gltex = FGLTexture::ValidateTexture(texInfo->tex);

	const PatchTextureInfo * pti;
	
	if (!texInfo->tex->bHasCanvas)
	{
		if (!texInfo->loadAlpha) 
		{
			int translationindex;

			if (texInfo->tex->UseType == FTexture::TEX_FontChar)
			{
				// Try to get the true color mapping from the paletted mapping which is being passed here
				//
				// Too bad that there is no decent way to get the index directly so the only way to get it
				// is to analyze the table's contents.
				byte * index0 = texInfo->font->GetColorTranslation(CR_BRICK);
				byte * index1 = texInfo->font->GetColorTranslation(CR_TAN);
				translationindex = (texInfo->translation - index0) / (index1 - index0);
				if (translationindex<0 || translationindex>=NUM_TEXT_COLORS) 
				{
					translationindex=CR_UNTRANSLATED;
				}

				// now get the corrseponding True Color table from the font.
				byte * tctstart = index0 + (NUM_TEXT_COLORS * (index1-index0));
				texInfo->translation = tctstart + 3 * (index1-index0) * translationindex;
			}
			else
			{
				// If ZDoom changes its use of translation tables this has to be adjusted for it
				// because the texture manager doesn't implement a generic translation table handling.
				//
				if (texInfo->translation == DIM_MAP)
				{
					// reducing the light produces better results than using a palette-limited translation table.
					light = .5f;
					translationindex = 0;
				}
				else if (texInfo->translation >= translationtables[TRANSLATION_Players] &&
					texInfo->translation <  translationtables[TRANSLATION_Players] + (MAXPLAYERS+1)*256)
				{
					// Aside from fonts these are the only ones being used by ZDoom and they are better passed by ID.
					//
					int in = texInfo->translation - translationtables[TRANSLATION_Players];
					translationindex = TRANSLATION(TRANSLATION_Players, in);
				}
				else
				{
					translationindex=0;
				}
				texInfo->translation=NULL;
			}
			pti = gltex->BindPatch(CM_DEFAULT, translationindex, texInfo->translation);
		}
		else 
		{
			// This is an alpha texture
			pti = gltex->BindPatch(CM_SHADE, 0);
		}

		if (!pti) return;

		cx = pti->GetUR();
		cy = pti->GetVB();
	}
	else
	{
		gltex->Bind(CM_DEFAULT);
		cx=1.f;
		cy=-1.f;
	}
	ox = oy = 0.f;
	
	if (texInfo->flipX)
	{
		float temp = ox;
		ox = cx;
		cx = temp;
	}
	
	// also take into account texInfo->windowLeft and texInfo->windowRight
	// just ignore for now...
	if (texInfo->windowLeft || texInfo->windowRight != texInfo->tex->GetScaledWidth()) return;
	
	if (texInfo->fillColor > 0  || texInfo->RenderStyle == STYLE_Shaded ||
		texInfo->RenderStyle == STYLE_TranslucentStencil || texInfo->RenderStyle == STYLE_Stencil)
	{
		r = RPART(texInfo->fillColor)/255.0f;
		g = GPART(texInfo->fillColor)/255.0f;
		b = BPART(texInfo->fillColor)/255.0f;
	}
	else
	{
		r = g = b = light;
	}
	
	// scissor test doesn't use the current viewport for the coordinates, so use real screen coordinates
	int btm = (SCREENHEIGHT - screen->GetHeight()) / 2;
	btm = SCREENHEIGHT - btm;

	gl.Enable(GL_SCISSOR_TEST);
	int space = (static_cast<OpenGLFrameBuffer*>(screen)->GetTrueHeight()-screen->GetHeight())/2;	// ugh...
	gl.Scissor(texInfo->clipLeft, btm - texInfo->clipBottom+space, texInfo->clipRight - texInfo->clipLeft, texInfo->clipBottom - texInfo->clipTop);
	
	if (texInfo->RenderStyle == STYLE_TranslucentStencil || texInfo->RenderStyle == STYLE_Stencil)
	{
		gl_SetTextureMode(TM_MASK);
	}
	else if (!texInfo->masked) 
	{
		gl_SetTextureMode(TM_OPAQUE);
	}
	gl.Color4f(r, g, b, texInfo->alpha);
	
	gl.Disable(GL_ALPHA_TEST);
	gl.Begin(GL_TRIANGLE_STRIP);
	gl.TexCoord2f(ox, oy);
	gl.Vertex2i(x, y);
	gl.TexCoord2f(ox, cy);
	gl.Vertex2i(x, y + h);
	gl.TexCoord2f(cx, oy);
	gl.Vertex2i(x + w, y);
	gl.TexCoord2f(cx, cy);
	gl.Vertex2i(x + w, y + h);
	gl.End();
	gl.Enable(GL_ALPHA_TEST);
	
	gl.Scissor(0, 0, screen->GetWidth(), screen->GetHeight());
	gl.Disable(GL_SCISSOR_TEST);
	if (!texInfo->masked || texInfo->RenderStyle == STYLE_TranslucentStencil || 
		texInfo->RenderStyle == STYLE_Stencil) 
	{
		gl_SetTextureMode(TM_MODULATE);
	}
}