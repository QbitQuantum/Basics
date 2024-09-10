//==============================
// VRMenuMgrLocal::SubmitForRenderingRecursive
void VRMenuMgrLocal::SubmitForRenderingRecursive( OvrDebugLines & debugLines, BitmapFont const & font, 
        BitmapFontSurface & fontSurface, VRMenuRenderFlags_t const & flags, VRMenuObjectLocal const * obj, 
        Posef const & parentModelPose, Vector4f const & parentColor, Vector3f const & parentScale, 
        Bounds3f & cullBounds, SubmittedMenuObject * submitted, int const maxIndices, int & curIndex ) const
{
	if ( curIndex >= maxIndices )
	{
		// If this happens we're probably not correctly clearing the submitted surfaces each frame
		// OR we've got a LOT of surfaces.
		LOG( "maxIndices = %i, curIndex = %i", maxIndices, curIndex );
		DROID_ASSERT( curIndex < maxIndices, "VrMenu" );
		return;
	}

	// check if this object is hidden
	if ( obj->GetFlags() & VRMENUOBJECT_DONT_RENDER )
	{
		return;
	}

	Posef const & localPose = obj->GetLocalPose();

	Posef curModelPose;
	curModelPose.Position = parentModelPose.Position + ( parentModelPose.Orientation * parentScale.EntrywiseMultiply( localPose.Position ) );
	curModelPose.Orientation = localPose.Orientation * parentModelPose.Orientation;

	Vector4f curColor = parentColor * obj->GetColor();
	Vector3f const & localScale = obj->GetLocalScale();
	Vector3f scale = parentScale.EntrywiseMultiply( localScale );

	OVR_ASSERT( obj != NULL );

/*
	VRMenuObject const * parent = ToObject( obj->GetParentHandle() );
	if ( parent != NULL )
	{
		fontParms_t fontParms;
		Vector3f itemUp = curModelPose.Orientation * Vector3f( 0.0f, 1.0f, 0.0f );
		Vector3f itemNormal = curModelPose.Orientation * Vector3f( 0.0f, 0.0f, 1.0f );
		fontSurface.DrawText3D( font, fontParms, curModelPose.Position, itemNormal, itemUp, 
				1.0f, Vector4f( 1.0f, 0.0f, 1.0f, 1.0f ), parent->GetText().ToCStr() );
	}
*/
	if ( obj->GetType() != VRMENU_CONTAINER )	// containers never render, but their children may
	{
        Posef const & hilightPose = obj->GetHilightPose();
        Posef itemPose( curModelPose.Orientation * hilightPose.Orientation,
                        curModelPose.Position + ( curModelPose.Orientation * parentScale.EntrywiseMultiply( hilightPose.Position ) ) );
		Matrix4f poseMat( itemPose.Orientation );
		Vector3f itemUp = poseMat.GetYBasis();
		Vector3f itemNormal = poseMat.GetZBasis();
		curModelPose = itemPose;	// so children like the slider bar caret use our hilight offset and don't end up clipping behind us!
		VRMenuRenderFlags_t rFlags = flags;
		VRMenuObjectFlags_t oFlags = obj->GetFlags();
		if ( oFlags & VRMENUOBJECT_FLAG_POLYGON_OFFSET )
		{
			rFlags |= VRMENU_RENDER_POLYGON_OFFSET;
		}
		if ( oFlags & VRMENUOBJECT_FLAG_NO_DEPTH )
		{
			rFlags |= VRMENU_RENDER_NO_DEPTH;
		}

		// the menu object may have zero or more renderable surfaces (if 0, it may draw only text)
		Array< VRMenuSurface > const & surfaces = obj->GetSurfaces();
		for ( int i = 0; i < surfaces.GetSizeI(); ++i )
		{
			VRMenuSurface const & surf = surfaces[i];
			if ( surf.IsRenderable() )
			{
				SubmittedMenuObject & sub = submitted[curIndex];
				sub.SurfaceIndex = i;
				sub.Pose = itemPose;
				sub.Scale = scale;
				sub.Flags = rFlags;
				sub.ColorTableOffset = obj->GetColorTableOffset();
				sub.SkipAdditivePass = !obj->IsHilighted();
				sub.Handle = obj->GetHandle();
				// modulate surface color with parent's current color
				sub.Color = surf.GetColor() * curColor;
				sub.Offsets = surf.GetAnchorOffsets();
				sub.FadeDirection = obj->GetFadeDirection();
#if defined( OVR_BUILD_DEBUG )
				sub.SurfaceName = surf.GetName();
#endif
				curIndex++;
			}
		}

		OVR::String const & text = obj->GetText();
		if ( ( oFlags & VRMENUOBJECT_DONT_RENDER_TEXT ) == 0 && text.GetLengthI() > 0 )
		{
            Posef const & textLocalPose = obj->GetTextLocalPose();
            Posef curTextPose;
            curTextPose.Position = itemPose.Position + ( itemPose.Orientation * textLocalPose.Position * scale );
            curTextPose.Orientation = textLocalPose.Orientation * itemPose.Orientation;
            Vector3f textNormal = curTextPose.Orientation * Vector3f( 0.0f, 0.0f, 1.0f );
			Vector3f position = curTextPose.Position + textNormal * 0.001f; // this is simply to prevent z-fighting right now
            Vector3f textScale = scale * obj->GetTextLocalScale();

            Vector4f textColor = obj->GetTextColor();
            // Apply parent's alpha influence
            textColor.w *= parentColor.w;
			VRMenuFontParms const & fp = obj->GetFontParms();
			fontParms_t fontParms;
			fontParms.CenterHoriz = fp.CenterHoriz;
			fontParms.CenterVert = fp.CenterVert;
			fontParms.Billboard = fp.Billboard;
			fontParms.TrackRoll = fp.TrackRoll;
			fontParms.ColorCenter = fp.ColorCenter;
			fontParms.AlphaCenter = fp.AlphaCenter;

			fontSurface.DrawText3D( font, fontParms, position, itemNormal, itemUp, 
					textScale.x * fp.Scale, textColor, text.ToCStr() );
#if 0
			// this shows a ruler for the wrap width when rendering text
			float const wrapw = obj->GetWrapWidth();
			Vector3f pos = position + Vector3f( 0.0f, 0.0f, -0.1f );
			debugLines.AddLine( pos - wrapw * 0.5f * scale, pos + wrapw * 0.5f * scale,
				Vector4f( 0.0f, 1.0f, 0.0f, 1.0f ), Vector4f( 1.0f, 0.0f, 0.0f, 1.0f ), 0, false );
#endif
		}
        //DROIDLOG( "Spam", "AddPoint for '%s'", text.ToCStr() );
		//GetDebugLines().AddPoint( curModelPose.Position, 0.05f, 1, true );
	}

    cullBounds = obj->GetLocalBounds( font ) * parentScale;

	// submit all children
    if ( obj->Children.GetSizeI() > 0 )
    {
	    for ( int i = 0; i < obj->Children.GetSizeI(); ++i )
	    {
		    menuHandle_t childHandle = obj->Children[i];
		    VRMenuObjectLocal const * child = static_cast< VRMenuObjectLocal const * >( ToObject( childHandle ) );
		    if ( child == NULL )
		    {
			    continue;
		    }

            Bounds3f childCullBounds;
		    SubmitForRenderingRecursive( debugLines, font, fontSurface, flags, child, curModelPose, curColor, scale, 
                    childCullBounds, submitted, maxIndices, curIndex );

		    Posef pose = child->GetLocalPose();
		    pose.Position = pose.Position * scale;
            childCullBounds = Bounds3f::Transform( pose, childCullBounds );
            cullBounds = Bounds3f::Union( cullBounds, childCullBounds );
	    }
    }

    obj->SetCullBounds( cullBounds );

#if 0
	OvrCollisionPrimitive const * cp = obj->GetCollisionPrimitive();
	if ( cp != NULL )
	{
		cp->DebugRender( debugLines, curModelPose );
	}
    {
        // for debug drawing, put the cull bounds in world space
        //LogBounds( obj->GetText().ToCStr(), "Transformed CullBounds", myCullBounds );
        debugLines.AddBounds( curModelPose, obj->GetCullBounds(), Vector4f( 0.0f, 1.0f, 1.0f, 1.0f ) );
    }
    {
        Bounds3f localBounds = obj->GetLocalBounds( font ) * parentScale;
        //LogBounds( obj->GetText().ToCStr(), "localBounds", localBounds );
    	debugLines.AddBounds( curModelPose, localBounds, Vector4f( 1.0f, 0.0f, 0.0f, 1.0f ) );
        Bounds3f textLocalBounds = obj->GetTextLocalBounds( font );
        Posef hilightPose = obj->GetHilightPose();
        textLocalBounds = Bounds3f::Transform( Posef( hilightPose.Orientation, hilightPose.Position * scale ), textLocalBounds );
    	debugLines.AddBounds( curModelPose, textLocalBounds * parentScale, Vector4f( 1.0f, 1.0f, 0.0f, 1.0f ) );
    }
#endif
}