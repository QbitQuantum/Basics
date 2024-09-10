BOOL LLPanelDisplay::postBuild()
{
	// return to default values
	getChild<LLButton>("Defaults")->setClickedCallback(boost::bind(&LLPanelDisplay::setHardwareDefaults, this));
	
	//============================================================================
	// Resolution
	
	// radio set for fullscreen size
	
	mCtrlWindowed = getChild<LLCheckBoxCtrl>( "windowed mode");
	mCtrlWindowed->setCommitCallback(boost::bind(&LLPanelDisplay::onCommitWindowedMode,this));

	mAspectRatioLabel1 = getChild<LLTextBox>("AspectRatioLabel1");
	mDisplayResLabel = getChild<LLTextBox>("DisplayResLabel");

	S32 num_resolutions = 0;
	LLWindow::LLWindowResolution* supported_resolutions = gViewerWindow->getWindow()->getSupportedResolutions(num_resolutions);

	S32 fullscreen_mode = num_resolutions - 1;

	mCtrlFullScreen = getChild<LLComboBox>( "fullscreen combo");
	
	LLUIString resolution_label = getString("resolution_format");

	for (S32 i = 0; i < num_resolutions; i++)
	{
		resolution_label.setArg("[RES_X]", llformat("%d", supported_resolutions[i].mWidth));
		resolution_label.setArg("[RES_Y]", llformat("%d", supported_resolutions[i].mHeight));
		mCtrlFullScreen->add( resolution_label, ADD_BOTTOM );
	}

	{
		BOOL targetFullscreen;
		S32 targetWidth;
		S32 targetHeight;
		
		gViewerWindow->getTargetWindow(targetFullscreen, targetWidth, targetHeight);
		
		if (targetFullscreen)
		{
			fullscreen_mode = 0; // default to 800x600
			for (S32 i = 0; i < num_resolutions; i++)
			{
				if (targetWidth == supported_resolutions[i].mWidth
				&&  targetHeight == supported_resolutions[i].mHeight)
				{
					fullscreen_mode = i;
				}
			}
			mCtrlFullScreen->setCurrentByIndex(fullscreen_mode);
			mCtrlWindowed->set(FALSE);
			mCtrlFullScreen->setVisible(TRUE);
		}
		else
		{
			// set to windowed mode
			//fullscreen_mode = mCtrlFullScreen->getItemCount() - 1;
			mCtrlWindowed->set(TRUE);
			mCtrlFullScreen->setCurrentByIndex(0);
			mCtrlFullScreen->setVisible(FALSE);
		}
	}

	initWindowSizeControls();

	if (gSavedSettings.getBOOL("FullScreenAutoDetectAspectRatio"))
	{
		mAspectRatio = gViewerWindow->getDisplayAspectRatio();
	}
	else
	{
		mAspectRatio = gSavedSettings.getF32("FullScreenAspectRatio");
	}

	S32 numerator = 0;
	S32 denominator = 0;
	fractionFromDecimal(mAspectRatio, numerator, denominator);

	LLUIString aspect_ratio_text = getString("aspect_ratio_text");
	if (numerator != 0)
	{
		aspect_ratio_text.setArg("[NUM]", llformat("%d",  numerator));
		aspect_ratio_text.setArg("[DEN]", llformat("%d",  denominator));
	}
	else
	{
		aspect_ratio_text = llformat("%.3f", mAspectRatio);
	}

	mCtrlAutoDetectAspect = getChild<LLCheckBoxCtrl>( "aspect_auto_detect");
	mCtrlAutoDetectAspect->setCommitCallback(boost::bind(&LLPanelDisplay::onCommitAutoDetectAspect,this,_2));

	mCtrlAspectRatio = getChild<LLComboBox>( "aspect_ratio");
	mCtrlAspectRatio->setTextEntryCallback(boost::bind(&LLUICtrl::setValue, mCtrlAutoDetectAspect, false));
	mCtrlAspectRatio->setCommitCallback(boost::bind(&LLUICtrl::setValue, mCtrlAutoDetectAspect, false));
	// add default aspect ratios
	mCtrlAspectRatio->add(aspect_ratio_text, &mAspectRatio, ADD_TOP);
	mCtrlAspectRatio->setCurrentByIndex(0);

	// radio performance box
	mCtrlSliderQuality = getChild<LLSliderCtrl>("QualityPerformanceSelection");
	mCtrlSliderQuality->setSliderMouseUpCallback(boost::bind(&LLPanelDisplay::onChangeQuality,this,_1));

	mCtrlCustomSettings = getChild<LLCheckBoxCtrl>("CustomSettings");
	mCtrlCustomSettings->setCommitCallback(boost::bind(&LLPanelDisplay::refreshEnabledState, this));

	//----------------------------------------------------------------------------
	// Enable Bump/Shiny
	mCtrlBumpShiny = getChild<LLCheckBoxCtrl>("BumpShiny");
	
	//----------------------------------------------------------------------------
	// Enable Reflections
	mCtrlReflectionDetail = getChild<LLComboBox>("ReflectionDetailCombo");
	mCtrlReflectionDetail->setCommitCallback(boost::bind(&LLPanelDisplay::refreshEnabledState, this));

	// WindLight
	mCtrlWindLight = getChild<LLCheckBoxCtrl>("WindLightUseAtmosShaders");
	mCtrlWindLight->setCommitCallback(boost::bind(&LLPanelDisplay::refreshEnabledState, this));

	// Deferred
	mCtrlDeferred = getChild<LLCheckBoxCtrl>("RenderDeferred");
	mCtrlDeferred->setCommitCallback(boost::bind(&LLPanelDisplay::refreshEnabledState, this));
	mCtrlDeferredDoF = getChild<LLCheckBoxCtrl>("RenderDepthOfField");
	mCtrlDeferredDoF->setCommitCallback(boost::bind(&LLPanelDisplay::refreshEnabledState, this));
	mCtrlShadowDetail = getChild<LLComboBox>("ShadowDetailCombo");
	mCtrlShadowDetail->setCommitCallback(boost::bind(&LLPanelDisplay::refreshEnabledState, this));

	//----------------------------------------------------------------------------
	// Terrain Scale
	mCtrlTerrainScale = getChild<LLComboBox>("TerrainScaleCombo");

	//----------------------------------------------------------------------------
	// Enable Avatar Shaders
	mCtrlAvatarVP = getChild<LLCheckBoxCtrl>("AvatarVertexProgram");
	mCtrlAvatarVP->setCommitCallback(boost::bind(&LLPanelDisplay::refreshEnabledState, this));

	//----------------------------------------------------------------------------
	// Avatar Render Mode
	mCtrlAvatarCloth = getChild<LLCheckBoxCtrl>("AvatarCloth");
	mCtrlAvatarImpostors = getChild<LLCheckBoxCtrl>("AvatarImpostors");
	mCtrlAvatarImpostors->setCommitCallback(boost::bind(&LLPanelDisplay::refreshEnabledState, this));

	//----------------------------------------------------------------------------
	// Checkbox for ambient occlusion
	mCtrlAmbientOcc = getChild<LLCheckBoxCtrl>("UseSSAO");

	//----------------------------------------------------------------------------
	// radio set for terrain detail mode
	mRadioTerrainDetail = getChild<LLRadioGroup>("TerrainDetailRadio");

	//----------------------------------------------------------------------------
	// Global Shader Enable
	mCtrlShaderEnable = getChild<LLCheckBoxCtrl>("BasicShaders");
	mCtrlShaderEnable->setCommitCallback(boost::bind(&LLPanelDisplay::refreshEnabledState, this));
	
	//============================================================================

	// Object detail slider
	LLSliderCtrl* ctrl_slider = getChild<LLSliderCtrl>("ObjectMeshDetail");
	LLTextBox* slider_text = getChild<LLTextBox>("ObjectMeshDetailText");
	ctrl_slider->setCommitCallback(boost::bind(updateSliderText, ctrl_slider, slider_text));
	updateSliderText(ctrl_slider, slider_text);

	// Flex object detail slider
	ctrl_slider = getChild<LLSliderCtrl>("FlexibleMeshDetail");
	slider_text = getChild<LLTextBox>("FlexibleMeshDetailText");
	ctrl_slider->setCommitCallback(boost::bind(updateSliderText, ctrl_slider, slider_text));
	updateSliderText(ctrl_slider, slider_text);

	// Tree detail slider
	ctrl_slider = getChild<LLSliderCtrl>("TreeMeshDetail");
	slider_text = getChild<LLTextBox>("TreeMeshDetailText");
	ctrl_slider->setCommitCallback(boost::bind(updateSliderText, ctrl_slider, slider_text));
	updateSliderText(ctrl_slider, slider_text);

	// Avatar detail slider
	ctrl_slider = getChild<LLSliderCtrl>("AvatarMeshDetail");
	slider_text = getChild<LLTextBox>("AvatarMeshDetailText");
	ctrl_slider->setCommitCallback(boost::bind(updateSliderText, ctrl_slider, slider_text));
	updateSliderText(ctrl_slider, slider_text);

	// Avatar physics detail slider
	ctrl_slider = getChild<LLSliderCtrl>("AvatarPhysicsDetail");
	slider_text = getChild<LLTextBox>("AvatarPhysicsDetailText");
	ctrl_slider->setCommitCallback(boost::bind(updateSliderText, ctrl_slider, slider_text));
	updateSliderText(ctrl_slider, slider_text);

	// Terrain detail slider
	ctrl_slider = getChild<LLSliderCtrl>("TerrainMeshDetail");
	slider_text = getChild<LLTextBox>("TerrainMeshDetailText");
	ctrl_slider->setCommitCallback(boost::bind(updateSliderText, ctrl_slider, slider_text));
	updateSliderText(ctrl_slider, slider_text);

	// Terrain detail slider
	ctrl_slider = getChild<LLSliderCtrl>("SkyMeshDetail");
	slider_text = getChild<LLTextBox>("SkyMeshDetailText");
	ctrl_slider->setCommitCallback(boost::bind(updateSliderText, ctrl_slider, slider_text));
	updateSliderText(ctrl_slider, slider_text);

	// Glow detail slider
	ctrl_slider = getChild<LLSliderCtrl>("RenderPostProcess");
	slider_text = getChild<LLTextBox>("PostProcessText");
	ctrl_slider->setCommitCallback(boost::bind(updateSliderText, ctrl_slider, slider_text));
	updateSliderText(ctrl_slider, slider_text);

	// Text boxes (for enabling/disabling)

	// Hardware tab
	mVBO = getChild<LLCheckBoxCtrl>("vbo");
	mVBO->setCommitCallback(boost::bind(&LLPanelDisplay::refreshEnabledState, this));

	if(gGLManager.mIsATI)	//AMD gpus don't go beyond 8x fsaa.
	{
		LLComboBox* fsaa = getChild<LLComboBox>("fsaa");
		fsaa->remove("16x");
	}
	if(!gGLManager.mHasAdaptiveVsync)
	{
		LLComboBox* vsync = getChild<LLComboBox>("vsync");
		vsync->remove("VSyncAdaptive");
	}

	refresh();

	return TRUE;
}