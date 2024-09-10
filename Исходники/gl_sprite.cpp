//==========================================================================
//
// 
//
//==========================================================================
void GLSprite::Draw(int pass)
{
	if (pass!=GLPASS_PLAIN && pass != GLPASS_ALL && pass!=GLPASS_TRANSLUCENT) return;

	// Hack to enable bright sprites in faded maps
	uint32 backupfade = Colormap.FadeColor.d;
	if (gl_spritebrightfog && fullbright)
		Colormap.FadeColor = 0;


	bool additivefog = false;
	int rel = extralight*gl_weaponlight;

	if (pass==GLPASS_TRANSLUCENT)
	{
		// The translucent pass requires special setup for the various modes.

		// Brightmaps will only be used when doing regular drawing ops and having no fog
		if (!gl_spritebrightfog && (!gl_isBlack(Colormap.FadeColor) || level.flags&LEVEL_HASFADETABLE || 
			RenderStyle.BlendOp != STYLEOP_Add))
		{
			gl_RenderState.EnableBrightmap(false);
		}

		gl_SetRenderStyle(RenderStyle, false, 
			// The rest of the needed checks are done inside gl_SetRenderStyle
			trans > 1.f - FLT_EPSILON && gl_usecolorblending && gl_fixedcolormap < CM_FIRSTSPECIALCOLORMAP && actor && 
			fullbright && gltexture && !gltexture->GetTransparent());

		if (hw_styleflags == STYLEHW_NoAlphaTest)
		{
			gl_RenderState.EnableAlphaTest(false);
		}
		else
		{
			gl_RenderState.AlphaFunc(GL_GEQUAL,trans*gl_mask_sprite_threshold);
		}

		if (RenderStyle.BlendOp == STYLEOP_Fuzz)
		{
			float fuzzalpha=0.44f;
			float minalpha=0.1f;

			// fog + fuzz don't work well without some fiddling with the alpha value!
			if (!gl_isBlack(Colormap.FadeColor))
			{
				float xcamera=FIXED2FLOAT(viewx);
				float ycamera=FIXED2FLOAT(viewy);

				float dist=Dist2(xcamera,ycamera, x,y);

				if (!Colormap.FadeColor.a) Colormap.FadeColor.a=clamp<int>(255-lightlevel,60,255);

				// this value was determined by trial and error and is scale dependent!
				float factor=0.05f+exp(-Colormap.FadeColor.a*dist/62500.f);
				fuzzalpha*=factor;
				minalpha*=factor;
			}

			gl_RenderState.AlphaFunc(GL_GEQUAL,minalpha*gl_mask_sprite_threshold);
			gl.Color4f(0.2f,0.2f,0.2f,fuzzalpha);
			additivefog = true;
		}
		else if (RenderStyle.BlendOp == STYLEOP_Add && RenderStyle.DestAlpha == STYLEALPHA_One)
		{
			additivefog = true;
		}
	}
	if (RenderStyle.BlendOp!=STYLEOP_Fuzz)
	{
		if (actor)
		{
			lightlevel = gl_SetSpriteLighting(RenderStyle, actor, lightlevel, rel, &Colormap, ThingColor, trans,
							 fullbright || gl_fixedcolormap >= CM_FIRSTSPECIALCOLORMAP, false);
		}
		else if (particle)
		{
			if (gl_light_particles)
			{
				lightlevel = gl_SetSpriteLight(particle, lightlevel, rel, &Colormap, trans, ThingColor);
			}
			else 
			{
				gl_SetColor(lightlevel, rel, &Colormap, trans, ThingColor);
			}
		}
		else return;
	}

	if (gl_isBlack(Colormap.FadeColor)) foglevel=lightlevel;

	if (RenderStyle.Flags & STYLEF_FadeToBlack) 
	{
		Colormap.FadeColor=0;
		additivefog = true;
	}

	if (RenderStyle.Flags & STYLEF_InvertOverlay) 
	{
		Colormap.FadeColor = Colormap.FadeColor.InverseColor();
		additivefog=false;
	}

	gl_SetFog(foglevel, rel, &Colormap, additivefog);

	if (gltexture) gltexture->BindPatch(Colormap.colormap,translation);
	else if (!modelframe) gl_RenderState.EnableTexture(false);

	if (!modelframe)
	{
		// [BB] Billboard stuff
		const bool drawWithXYBillboard = ( !(actor && actor->renderflags & RF_FORCEYBILLBOARD)
		                                   //&& GLRenderer->mViewActor != NULL
		                                   && (gl_billboard_mode == 1 || (actor && actor->renderflags & RF_FORCEXYBILLBOARD )) );
		gl_RenderState.Apply();
		gl.Begin(GL_TRIANGLE_STRIP);
		if ( drawWithXYBillboard )
		{
			// Rotate the sprite about the vector starting at the center of the sprite
			// triangle strip and with direction orthogonal to where the player is looking
			// in the x/y plane.
			float xcenter = (x1+x2)*0.5;
			float ycenter = (y1+y2)*0.5;
			float zcenter = (z1+z2)*0.5;
			float angleRad = DEG2RAD(270. - float(GLRenderer->mAngles.Yaw));
			
			Matrix3x4 mat;
			mat.MakeIdentity();
			mat.Translate( xcenter, zcenter, ycenter);
			mat.Rotate(-sin(angleRad), 0, cos(angleRad), -GLRenderer->mAngles.Pitch);
			mat.Translate( -xcenter, -zcenter, -ycenter);
			Vector v1 = mat * Vector(x1,z1,y1);
			Vector v2 = mat * Vector(x2,z1,y2);
			Vector v3 = mat * Vector(x1,z2,y1);
			Vector v4 = mat * Vector(x2,z2,y2);

			if (gltexture)
			{
				gl.TexCoord2f(ul, vt); gl.Vertex3fv(&v1[0]);
				gl.TexCoord2f(ur, vt); gl.Vertex3fv(&v2[0]);
				gl.TexCoord2f(ul, vb); gl.Vertex3fv(&v3[0]);
				gl.TexCoord2f(ur, vb); gl.Vertex3fv(&v4[0]);
			}
			else	// Particle
			{
				gl.Vertex3fv(&v1[0]);
				gl.Vertex3fv(&v2[0]);
				gl.Vertex3fv(&v3[0]);
				gl.Vertex3fv(&v4[0]);
			}

		}
		else
		{
			if (gltexture)
			{
				gl.TexCoord2f(ul, vt); gl.Vertex3f(x1, z1, y1);
				gl.TexCoord2f(ur, vt); gl.Vertex3f(x2, z1, y2);
				gl.TexCoord2f(ul, vb); gl.Vertex3f(x1, z2, y1);
				gl.TexCoord2f(ur, vb); gl.Vertex3f(x2, z2, y2);
			}
			else	// Particle
			{
				gl.Vertex3f(x1, z1, y1);
				gl.Vertex3f(x2, z1, y2);
				gl.Vertex3f(x1, z2, y1);
				gl.Vertex3f(x2, z2, y2);
			}
		}
		gl.End();
	}
	else
	{
		gl_RenderModel(this, Colormap.colormap);
	}

	if (pass==GLPASS_TRANSLUCENT)
	{
		gl_RenderState.EnableBrightmap(true);
		gl_RenderState.BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		gl_RenderState.BlendEquation(GL_FUNC_ADD);
		gl_RenderState.SetTextureMode(TM_MODULATE);

		// [BB] Restore the alpha test after drawing a smooth particle.
		if (hw_styleflags == STYLEHW_NoAlphaTest)
		{
			gl_RenderState.EnableAlphaTest(true);
		}
		else
		{
			gl_RenderState.AlphaFunc(GL_GEQUAL,gl_mask_sprite_threshold);
		}
	}

	// End of gl_sprite_brightfog hack: restore FadeColor to normalcy
	if (backupfade != Colormap.FadeColor.d)
		Colormap.FadeColor = backupfade;

	gl_RenderState.EnableTexture(true);
}