	void RenderWallSprite::Project(RenderThread *thread, AActor *thing, const DVector3 &pos, FTexture *pic, const DVector2 &scale, int renderflags, int spriteshade, bool foggy, FDynamicColormap *basecolormap)
	{
		FWallCoords wallc;
		double x1, x2;
		DVector2 left, right;
		double gzb, gzt, tz;
		DAngle ang = thing->Angles.Yaw + 90;
		double angcos = ang.Cos();
		double angsin = ang.Sin();

		// Determine left and right edges of sprite. The sprite's angle is its normal,
		// so the edges are 90 degrees each side of it.
		x2 = pic->GetScaledWidth();
		x1 = pic->GetScaledLeftOffsetSW();

		x1 *= scale.X;
		x2 *= scale.X;

		left.X = pos.X - x1 * angcos - thread->Viewport->viewpoint.Pos.X;
		left.Y = pos.Y - x1 * angsin - thread->Viewport->viewpoint.Pos.Y;
		right.X = left.X + x2 * angcos;
		right.Y = left.Y + x2 * angsin;

		// Is it off-screen?
		if (wallc.Init(thread, left, right, TOO_CLOSE_Z))
			return;
			
		RenderPortal *renderportal = thread->Portal.get();

		if (wallc.sx1 >= renderportal->WindowRight || wallc.sx2 <= renderportal->WindowLeft)
			return;

		// Sprite sorting should probably treat these as walls, not sprites,
		// but right now, I just want to get them drawing.
		tz = (pos.X - thread->Viewport->viewpoint.Pos.X) * thread->Viewport->viewpoint.TanCos + (pos.Y - thread->Viewport->viewpoint.Pos.Y) * thread->Viewport->viewpoint.TanSin;

		int scaled_to = pic->GetScaledTopOffsetSW();
		int scaled_bo = scaled_to - pic->GetScaledHeight();
		gzt = pos.Z + scale.Y * scaled_to;
		gzb = pos.Z + scale.Y * scaled_bo;

		RenderWallSprite *vis = thread->FrameMemory->NewObject<RenderWallSprite>();
		vis->CurrentPortalUniq = renderportal->CurrentPortalUniq;
		vis->x1 = wallc.sx1 < renderportal->WindowLeft ? renderportal->WindowLeft : wallc.sx1;
		vis->x2 = wallc.sx2 >= renderportal->WindowRight ? renderportal->WindowRight : wallc.sx2;
		vis->yscale = (float)scale.Y;
		vis->idepth = float(1 / tz);
		vis->depth = (float)tz;
		vis->sector = thing->Sector;
		vis->heightsec = NULL;
		vis->gpos = { (float)pos.X, (float)pos.Y, (float)pos.Z };
		vis->gzb = (float)gzb;
		vis->gzt = (float)gzt;
		vis->deltax = float(pos.X - thread->Viewport->viewpoint.Pos.X);
		vis->deltay = float(pos.Y - thread->Viewport->viewpoint.Pos.Y);
		vis->renderflags = renderflags;
		if (thing->flags5 & MF5_BRIGHT) vis->renderflags |= RF_FULLBRIGHT; // kg3D
		vis->RenderStyle = thing->RenderStyle;
		vis->FillColor = thing->fillcolor;
		vis->Translation = thing->Translation;
		vis->FakeFlatStat = WaterFakeSide::Center;
		vis->Alpha = float(thing->Alpha);
		vis->fakefloor = NULL;
		vis->fakeceiling = NULL;
		//vis->bInMirror = renderportal->MirrorFlags & RF_XFLIP;
		vis->pic = pic;
		vis->wallc = wallc;
		vis->foggy = foggy;

		vis->Light.SetColormap(thread->Light->SpriteGlobVis(foggy) / MAX(tz, MINZ), spriteshade, basecolormap, false, false, false);

		thread->SpriteList->Push(vis);
	}