	void UpdateLightShaftOverrideDirection_GameThread(const UDirectionalLightComponent* Component)
	{
		FVector NewLightShaftOverrideDirection = Component->LightShaftOverrideDirection;
		NewLightShaftOverrideDirection.Normalize();
		ENQUEUE_UNIQUE_RENDER_COMMAND_TWOPARAMETER(
			FUpdateLightShaftOverrideDirectionCommand,
			FDirectionalLightSceneProxy*,Proxy,this,
			FVector,NewLightShaftOverrideDirection,NewLightShaftOverrideDirection,
		{
			Proxy->UpdateLightShaftOverrideDirection_RenderThread(NewLightShaftOverrideDirection);
		});