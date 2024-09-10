void
InputDeviceTouch::InternalUpdate(InputDeltaState* delta)
{
	impl_->Update(delta);

	if ((manager_.IsDebugRenderingEnabled() || IsDebugRenderingEnabled())
		&& manager_.GetDebugRenderer())
	{
		DebugRenderer* debugRenderer = manager_.GetDebugRenderer();
		InputState* state = GetInputState();

		for (unsigned i = 0; i < TouchPointCount; ++i)
		{
			if (state->GetBool(Touch0Down + i*4))
			{
				const float x = state->GetFloat(Touch0X + i*4);
				const float y = state->GetFloat(Touch0Y + i*4);
				debugRenderer->DrawCircle(x, y, 0.03f);
			}
		}
	}
}