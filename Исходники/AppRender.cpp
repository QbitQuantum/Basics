void AppLocal::DrawEyeViewsPostDistorted( Matrix4f const & centerViewMatrix, const int numPresents )
{
	// update vr lib systems after the app frame, but before rendering anything
	GetGuiSys().Frame( this, vrFrame, GetVRMenuMgr(), GetDefaultFont(), GetMenuFontSurface() );
	GetGazeCursor().Frame( this->lastViewMatrix, vrFrame.DeltaSeconds );

	if ( ShowFPS )
	{
		static double  LastFrameTime = TimeInSeconds();
		static double  AccumulatedFrameInterval = 0.0;
		static int   NumAccumulatedFrames = 0;
		static float LastFrameRate = 60.0f;

		double currentFrameTime = TimeInSeconds();
		double frameInterval = currentFrameTime - LastFrameTime;
		AccumulatedFrameInterval += frameInterval;
		NumAccumulatedFrames++;
		if ( NumAccumulatedFrames > FPS_NUM_FRAMES_TO_AVERAGE ) {
			double interval = ( AccumulatedFrameInterval / NumAccumulatedFrames );  // averaged
			AccumulatedFrameInterval = 0.0;
			NumAccumulatedFrames = 0;
			LastFrameRate = 1.0f / float( interval > 0.000001 ? interval : 0.00001 );
		}    
		fontParms_t fontParms;
		fontParms.CenterHoriz = true;
		fontParms.Billboard = true;
        fontParms.TrackRoll = true;
		const Vector3f viewPos( GetViewMatrixPosition( centerViewMatrix ) );
		const Vector3f viewFwd( GetViewMatrixForward( centerViewMatrix ) );
		const Vector3f textPos( viewPos + viewFwd * 1.5f );
		GetWorldFontSurface().DrawTextBillboarded3Df( GetDefaultFont(), 
                fontParms, textPos, 0.0025f, Vector4f( 1.0f, 0.0f, 0.0f, 1.0f ), "%.1f fps", LastFrameRate );
		LastFrameTime = currentFrameTime;
	}

	if ( InfoTextEndFrame >= vrFrame.FrameNumber )
	{
		fontParms_t fontParms;
		fontParms.CenterHoriz = true;
		fontParms.Billboard = true;
        fontParms.TrackRoll = true;
		const Vector3f viewPos( GetViewMatrixPosition( centerViewMatrix ) );
		const Vector3f viewFwd( GetViewMatrixForward( centerViewMatrix ) );
		const Vector3f textPos( viewPos + viewFwd * 1.5f );
		GetWorldFontSurface().DrawTextBillboarded3Df( GetDefaultFont(), 
                fontParms, textPos, 0.0025f, Vector4f( 1.0f, 1.0f, 1.0f, 1.0f ), InfoText.ToCStr() );
	}

	GetMenuFontSurface().Finish( centerViewMatrix );
	GetWorldFontSurface().Finish( centerViewMatrix );
	GetVRMenuMgr().Finish( centerViewMatrix );

	// Increase the fov by about 10 degrees if we are not holding 60 fps so
	// there is less black pull-in at the edges.
	//
	// Doing this dynamically based just on time causes visible flickering at the
	// periphery when the fov is increased, so only do it if minimumVsyncs is set.
	const float fovDegrees = hmdInfo.SuggestedEyeFov +
			( ( ( SwapParms.MinimumVsyncs > 1 ) || ovr_GetPowerLevelStateThrottled() ) ? 10.0f : 0.0f ) +
			( ( !showVignette ) ? 5.0f : 0.0f );

	// DisplayMonoMode uses a single eye rendering for speed improvement
	// and / or high refresh rate double-scan hardware modes.
	const int numEyes = renderMonoMode ? 1 : 2;

	// Flush out and report any errors
	GL_CheckErrors("FrameStart");

	if ( drawCalibrationLines && calibrationLinesDrawn )
	{
		// doing a time warp test, don't generate new images
		LOG( "drawCalibrationLines && calibrationLinesDrawn" );
	}
	else
	{
		// possibly change the buffer parameters
		EyeTargets->BeginFrame( vrParms );

		for (int eye = 0; eye < numEyes; eye++)
		{
			EyeTargets->BeginRenderingEye( eye );

			// Call back to the app for drawing.
			const Matrix4f mvp = appInterface->DrawEyeView( eye, fovDegrees );

			DrawActivity( mvp );

			DrawPassThroughCamera( fovDegrees, vrFrame.PoseState.Pose.Orientation );

			GetVRMenuMgr().RenderSubmitted( mvp.Transposed() );
			GetMenuFontSurface().Render3D( GetDefaultFont(), mvp.Transposed() );
			GetWorldFontSurface().Render3D( GetDefaultFont(), mvp.Transposed() );

			glDisable( GL_DEPTH_TEST );
			glDisable( GL_CULL_FACE );

			// Optionally draw thick calibration lines into the texture,
			// which will be overlayed by the thinner origin cross when
			// distorted to the window.
			if ( drawCalibrationLines )
			{
				EyeDecorations.DrawEyeCalibrationLines(fovDegrees, eye);
				calibrationLinesDrawn = true;
			}
			else
			{
				calibrationLinesDrawn = false;
			}

			DrawDialog( mvp );

			GetGazeCursor().Render( eye, mvp );

			GetDebugLines().Render( mvp.Transposed() );

			if ( showVignette )
			{
				// Draw a thin vignette at the edges of the view so clamping will give black
				// This will not be reflected correctly in overlay planes.
				// EyeDecorations.DrawEyeVignette();

				EyeDecorations.FillEdge( vrParms.resolution, vrParms.resolution );
			}

			EyeTargets->EndRenderingEye( eye );
		}
	}

	// This eye set is complete, use it now.
	if ( numPresents > 0 )
	{
		const CompletedEyes eyes = EyeTargets->GetCompletedEyes();

		for ( int eye = 0 ; eye < TimeWarpParms::MAX_WARP_EYES ; eye++ )
		{
			const Matrix4f proj = Matrix4f::PerspectiveRH( DegreeToRad(fovDegrees), 1.0f, 1, 100);
			SwapParms.Images[eye][0].TexCoordsFromTanAngles = TanAngleMatrixFromProjection( proj );

			SwapParms.Images[eye][0].TexId = eyes.Textures[renderMonoMode ? 0 : eye ];
			SwapParms.Images[eye][0].Pose = SensorForNextWarp.Predicted;
		}

		ovr_WarpSwap( OvrMobile, &SwapParms );
	}
}