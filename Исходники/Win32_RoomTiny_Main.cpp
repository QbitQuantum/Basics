//-------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hinst, HINSTANCE, LPSTR, int)
{
    // Initializes LibOVR, and the Rift
    ovr_Initialize();
    HMD = ovrHmd_Create(0);

    if (!HMD)                       { MessageBoxA(NULL,"Oculus Rift not detected.","", MB_OK); return(0); }
    if (HMD->ProductName[0] == '\0')  MessageBoxA(NULL,"Rift detected, display not enabled.", "", MB_OK);

    // Setup Window and Graphics - use window frame if relying on Oculus driver
    bool windowed = (HMD->HmdCaps & ovrHmdCap_ExtendDesktop) ? false : true;    
    if (!WND.InitWindowAndDevice(hinst, Recti(HMD->WindowsPos, HMD->Resolution), windowed))
        return(0);

    WND.SetMaxFrameLatency(1);
    ovrHmd_AttachToWindow(HMD, WND.Window, NULL, NULL);
    ovrHmd_SetEnabledCaps(HMD, ovrHmdCap_LowPersistence | ovrHmdCap_DynamicPrediction);

    // Start the sensor which informs of the Rift's pose and motion
    ovrHmd_ConfigureTracking(HMD, ovrTrackingCap_Orientation | ovrTrackingCap_MagYawCorrection |
                                  ovrTrackingCap_Position, 0);

    // Make the eye render buffers (caution if actual size < requested due to HW limits). 
    for (int eye=0; eye<2; eye++)
    {
        Sizei idealSize             = ovrHmd_GetFovTextureSize(HMD, (ovrEyeType)eye,
                                                               HMD->DefaultEyeFov[eye], 1.0f);
        pEyeRenderTexture[eye]      = new ImageBuffer(true, false, idealSize);
        pEyeDepthBuffer[eye]        = new ImageBuffer(true, true, pEyeRenderTexture[eye]->Size);
        EyeRenderViewport[eye].Pos  = Vector2i(0, 0);
        EyeRenderViewport[eye].Size = pEyeRenderTexture[eye]->Size;
    }

    // Setup VR components
#if SDK_RENDER
	#if RENDER_OPENGL
    ovrGLConfig oglcfg;
    oglcfg.OGL.Header.API				= ovrRenderAPI_OpenGL;
    oglcfg.OGL.Header.BackBufferSize	= Sizei(HMD->Resolution.w, HMD->Resolution.h);
    oglcfg.OGL.Header.Multisample		= 1;
	oglcfg.OGL.Window					= OGL.Window;
	oglcfg.OGL.DC						= GetDC(OGL.Window);

    if (!ovrHmd_ConfigureRendering(HMD, &oglcfg.Config,
		                           ovrDistortionCap_Chromatic | ovrDistortionCap_Vignette |
                                   ovrDistortionCap_TimeWarp | ovrDistortionCap_Overdrive,
								   HMD->DefaultEyeFov, EyeRenderDesc))	
		return(1);
	#else
    ovrD3D11Config d3d11cfg;
    d3d11cfg.D3D11.Header.API            = ovrRenderAPI_D3D11;
    d3d11cfg.D3D11.Header.BackBufferSize = Sizei(HMD->Resolution.w, HMD->Resolution.h);
    d3d11cfg.D3D11.Header.Multisample    = 1;
    d3d11cfg.D3D11.pDevice               = WND.Device;
    d3d11cfg.D3D11.pDeviceContext        = WND.Context;
    d3d11cfg.D3D11.pBackBufferRT         = WND.BackBufferRT;
    d3d11cfg.D3D11.pSwapChain            = WND.SwapChain;

    if (!ovrHmd_ConfigureRendering(HMD, &d3d11cfg.Config,
                                   ovrDistortionCap_Chromatic | ovrDistortionCap_Vignette |
                                   ovrDistortionCap_TimeWarp | ovrDistortionCap_Overdrive,
                                   HMD->DefaultEyeFov, EyeRenderDesc))
        return(1);
	#endif
#else
    APP_RENDER_SetupGeometryAndShaders();
#endif

    // Create the room model
    Scene roomScene(false); // Can simplify scene further with parameter if required.

    // Initialize Webcams and threads
	WebCamManager WebCamMngr(HMD);

    // MAIN LOOP
    // =========
    while (!(WND.Key['Q'] && WND.Key[VK_CONTROL]) && !WND.Key[VK_ESCAPE])
    {
        WND.HandleMessages();
        
        float       speed                    = 1.0f; // Can adjust the movement speed. 
        int         timesToRenderScene       = 1;    // Can adjust the render burden on the app.
		ovrVector3f useHmdToEyeViewOffset[2] = {EyeRenderDesc[0].HmdToEyeViewOffset,
			                                    EyeRenderDesc[1].HmdToEyeViewOffset};
        // Start timing
    #if SDK_RENDER
        ovrHmd_BeginFrame(HMD, 0);
    #else
        ovrHmd_BeginFrameTiming(HMD, 0);
    #endif

        // Handle key toggles for re-centering, meshes, FOV, etc.
        ExampleFeatures1(&speed, &timesToRenderScene, useHmdToEyeViewOffset);

        // Keyboard inputs to adjust player orientation
        if (WND.Key[VK_LEFT])  Yaw += 0.02f;
        if (WND.Key[VK_RIGHT]) Yaw -= 0.02f;

        // Keyboard inputs to adjust player position
        if (WND.Key['W']||WND.Key[VK_UP])   Pos+=Matrix4f::RotationY(Yaw).Transform(Vector3f(0,0,-speed*0.05f));
        if (WND.Key['S']||WND.Key[VK_DOWN]) Pos+=Matrix4f::RotationY(Yaw).Transform(Vector3f(0,0,+speed*0.05f));
        if (WND.Key['D'])                    Pos+=Matrix4f::RotationY(Yaw).Transform(Vector3f(+speed*0.05f,0,0));
        if (WND.Key['A'])                    Pos+=Matrix4f::RotationY(Yaw).Transform(Vector3f(-speed*0.05f,0,0));
        Pos.y = ovrHmd_GetFloat(HMD, OVR_KEY_EYE_HEIGHT, Pos.y);
  
        // Animate the cube
        if (speed)
            roomScene.Models[0]->Pos = Vector3f(9*sin(0.01f*clock),3,9*cos(0.01f*clock));

		// Get both eye poses simultaneously, with IPD offset already included. 
		ovrPosef temp_EyeRenderPose[2];
		ovrHmd_GetEyePoses(HMD, 0, useHmdToEyeViewOffset, temp_EyeRenderPose, NULL);

		// Update textures with WebCams' frames
		WebCamMngr.Update();	

        // Render the two undistorted eye views into their render buffers.  
        for (int eye = 0; eye < 2; eye++)
        {
            ImageBuffer * useBuffer      = pEyeRenderTexture[eye];  
            ovrPosef    * useEyePose     = &EyeRenderPose[eye];
            float       * useYaw         = &YawAtRender[eye];
            bool          clearEyeImage  = true;
            bool          updateEyeImage = true;

            // Handle key toggles for half-frame rendering, buffer resolution, etc.
            ExampleFeatures2(eye, &useBuffer, &useEyePose, &useYaw, &clearEyeImage, &updateEyeImage);

            if (clearEyeImage)
			#if RENDER_OPENGL
				WND.ClearAndSetRenderTarget(useBuffer, Recti(EyeRenderViewport[eye]));
			#else
                WND.ClearAndSetRenderTarget(useBuffer->TexRtv,
                                             pEyeDepthBuffer[eye], Recti(EyeRenderViewport[eye]));	
			#endif

            if (updateEyeImage)
            {
                // Write in values actually used (becomes significant in Example features)
                *useEyePose = temp_EyeRenderPose[eye];
                *useYaw     = Yaw;

                // Get view and projection matrices (note near Z to reduce eye strain)
                Matrix4f rollPitchYaw       = Matrix4f::RotationY(Yaw);
                Matrix4f finalRollPitchYaw  = rollPitchYaw * Matrix4f(useEyePose->Orientation);
                Vector3f finalUp            = finalRollPitchYaw.Transform(Vector3f(0, 1, 0));
                Vector3f finalForward       = finalRollPitchYaw.Transform(Vector3f(0, 0, -1));
                Vector3f shiftedEyePos      = Pos + rollPitchYaw.Transform(useEyePose->Position);

                Matrix4f view = Matrix4f::LookAtRH(shiftedEyePos, shiftedEyePos + finalForward, finalUp);
                Matrix4f proj = ovrMatrix4f_Projection(EyeRenderDesc[eye].Fov, 0.2f, 1000.0f, true); 

				// Keyboard input to switch from "look through" to scene mode
				static bool bOldLookThrough	= false;
				static bool bLookThrough	= true;
				if (WND.Key['X'] && bOldLookThrough != WND.Key['X']) { bLookThrough = !bLookThrough; }
				bOldLookThrough = WND.Key['X'];

				if(!bLookThrough)
				{
					// Render the scene
					for (int t=0; t<timesToRenderScene; t++)
						roomScene.Render(view, proj.Transposed());

					WebCamMngr.DrawBoard(view, proj.Transposed());
				}
				else { WebCamMngr.DrawLookThrough(eye); }
            }
        }

        // Do distortion rendering, Present and flush/sync
    #if SDK_RENDER
		#if RENDER_OPENGL
		ovrGLTexture eyeTexture[2]; // Gather data for eye textures 
        for (int eye = 0; eye<2; eye++)
        {
            eyeTexture[eye].OGL.Header.API				= ovrRenderAPI_OpenGL;
            eyeTexture[eye].OGL.Header.TextureSize		= pEyeRenderTexture[eye]->Size;
            eyeTexture[eye].OGL.Header.RenderViewport	= EyeRenderViewport[eye];
            eyeTexture[eye].OGL.TexId					= pEyeRenderTexture[eye]->TexId;
        }
		#else
        ovrD3D11Texture eyeTexture[2]; // Gather data for eye textures 
        for (int eye = 0; eye<2; eye++)
        {
            eyeTexture[eye].D3D11.Header.API            = ovrRenderAPI_D3D11;
            eyeTexture[eye].D3D11.Header.TextureSize    = pEyeRenderTexture[eye]->Size;
            eyeTexture[eye].D3D11.Header.RenderViewport = EyeRenderViewport[eye];
            eyeTexture[eye].D3D11.pTexture              = pEyeRenderTexture[eye]->Tex;
            eyeTexture[eye].D3D11.pSRView               = pEyeRenderTexture[eye]->TexSv;
        }
		#endif
		ovrHmd_EndFrame(HMD, EyeRenderPose, &eyeTexture[0].Texture);
    #else
        APP_RENDER_DistortAndPresent();
    #endif
    }

	WebCamMngr.StopCapture();

    // Release and close down
    ovrHmd_Destroy(HMD);
    ovr_Shutdown();
	WND.ReleaseWindow(hinst);

    return(0);
}