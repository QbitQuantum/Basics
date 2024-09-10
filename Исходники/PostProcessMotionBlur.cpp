	void SetParameters(const FRenderingCompositePassContext& Context)
	{
		const FPixelShaderRHIParamRef ShaderRHI = GetPixelShader();

		FGlobalShader::SetParameters(ShaderRHI, Context.View);

		DeferredParameters.Set(ShaderRHI, Context.View);

		{
			bool bFiltered = false;

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
			static const auto CVar = IConsoleManager::Get().FindTConsoleVariableDataInt(TEXT("r.MotionBlurFiltering"));
			bFiltered = CVar->GetValueOnRenderThread() != 0;
#endif // !(UE_BUILD_SHIPPING || UE_BUILD_TEST)

			if(bFiltered)
			{
				PostprocessParameter.SetPS(ShaderRHI, Context, TStaticSamplerState<SF_Bilinear,AM_Border,AM_Border,AM_Clamp>::GetRHI());
			}
			else
			{
				PostprocessParameter.SetPS(ShaderRHI, Context, TStaticSamplerState<SF_Point,AM_Border,AM_Border,AM_Clamp>::GetRHI());
			}
		}
		
		if( Context.View.Family->EngineShowFlags.CameraInterpolation )
		{
			// Instead of finding the world space position of the current pixel, calculate the world space position offset by the camera position, 
			// then translate by the difference between last frame's camera position and this frame's camera position,
			// then apply the rest of the transforms.  This effectively avoids precision issues near the extents of large levels whose world space position is very large.
			FVector ViewOriginDelta = Context.View.ViewMatrices.ViewOrigin - Context.View.PrevViewMatrices.ViewOrigin;
			SetShaderValue(ShaderRHI, PrevViewProjMatrix, FTranslationMatrix(ViewOriginDelta) * Context.View.PrevViewRotationProjMatrix);
		}
		else
		{
			SetShaderValue( ShaderRHI, PrevViewProjMatrix, Context.View.ViewMatrices.GetViewRotationProjMatrix() );
		}

		TRefCountPtr<IPooledRenderTarget> InputPooledElement = Context.Pass->GetInput(ePId_Input0)->GetOutput()->RequestInput();

		// to mask out samples from outside of the view
		{
			FIntPoint BufferSize = GSceneRenderTargets.GetBufferSizeXY();
			FVector2D InvBufferSize(1.0f / BufferSize.X, 1.0f / BufferSize.Y);

			FIntRect ClipRect = Context.View.ViewRect;

			// to avoid leaking in content from the outside because of bilinear filtering, shrink
			ClipRect.InflateRect(-1);

			FVector2D MinUV(ClipRect.Min.X * InvBufferSize.X, ClipRect.Min.Y * InvBufferSize.Y);
			FVector2D MaxUV(ClipRect.Max.X * InvBufferSize.X, ClipRect.Max.Y * InvBufferSize.Y);
			FVector2D SizeUV = MaxUV - MinUV;

			FVector2D Mul(1.0f / SizeUV.X, 1.0f / SizeUV.Y);
			FVector2D Add = - MinUV * Mul;
			FVector4 TextureViewMadValue(Mul.X, Mul.Y, Add.X, Add.Y);
			SetShaderValue(ShaderRHI, TextureViewMad, TextureViewMadValue);
		}

		{
			const float SizeX = Context.View.ViewRect.Width();
			const float SizeY = Context.View.ViewRect.Height();
			const float AspectRatio = SizeX / SizeY;
			const float InvAspectRatio = SizeY / SizeX;

			const FSceneViewState* ViewState = (FSceneViewState*) Context.View.State;
			float MotionBlurTimeScale = ViewState ? ViewState->MotionBlurTimeScale : 1.0f;

			float ViewMotionBlurScale = 0.5f * MotionBlurTimeScale * Context.View.FinalPostProcessSettings.MotionBlurAmount;

			// MotionBlurInstanceScale was needed to hack some cases where motion blur wasn't working well, this shouldn't be needed any more, can clean this up later
			float MotionBlurInstanceScale = 1;

			float ObjectMotionBlurScale	= MotionBlurInstanceScale * ViewMotionBlurScale;
			// 0:no 1:full screen width, percent conversion
			float MaxVelocity = Context.View.FinalPostProcessSettings.MotionBlurMax / 100.0f;
			float InvMaxVelocity = 1.0f / MaxVelocity;

			// *2 to convert to -1..1 -1..1 screen space
			// / MaxFraction to map screenpos to -1..1 normalized MaxFraction
			FVector4 MotionBlurParametersValue(
				ObjectMotionBlurScale * InvMaxVelocity,
				- ObjectMotionBlurScale * InvMaxVelocity * InvAspectRatio,
				MaxVelocity * 2,
				- MaxVelocity * 2 * AspectRatio);
			SetShaderValue(ShaderRHI, MotionBlurParameters, MotionBlurParametersValue);
		}
	}