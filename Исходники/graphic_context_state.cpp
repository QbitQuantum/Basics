	GraphicContext_State::GraphicContext_State()
	{
		textures.reserve(8);	// Reserse space for 8 unit indexes
		viewport.resize(1);		// Always have a minimum of 1 viewport
		depth_range.push_back(Sizef(0.0f, 1.0f));		// Always have a minimum of 1 viewport
		scissor_set = false;
		program_standard_set = false;
		blend_color = Colorf::white;
		sample_mask = 0xffffffff;
		stencil_ref = 0;
		draw_buffer = buffer_back;
	}