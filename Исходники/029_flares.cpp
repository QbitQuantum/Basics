	FlareExample(void)
	 : shape(shape_prog, shapes::SpiralSphere())
	 , n_flares(32)
	 , queries(n_flares)
	{
		std::vector<Vec3f> light_positions(n_flares);
		for(GLuint i=0; i!=n_flares; ++i)
		{
			const float rand_max = float(RAND_MAX);
			auto angle = FullCircles(std::rand()/rand_max);

			light_positions[i] = Vec3f(
				7.0f*Cos(angle),
				0.2f*(std::rand()/rand_max)-0.1f,
				7.0f*Sin(angle)
			);
		}

		shape_prog.light_position.Set(light_positions);
		shape_prog.color_1 = Vec3f(0.3f, 0.3f, 0.5f);
		shape_prog.color_2 = Vec3f(0.8f, 0.8f, 1.0f);

		Texture::Active(0);
		shape_prog.metal_tex.Set(0);
		metal_texture
			<< TextureTarget::_2D
			<< TextureMinFilter::LinearMipmapLinear
			<< TextureMagFilter::Linear
			<< TextureWrap::Repeat
			<< images::BrushedMetalUByte(
				512, 512,
				5120,
				-12, +12,
				32, 64
			)
			<< TextureMipmap();

		Texture::Active(1);
		UniformSampler(flare_prog, "FlareTex").Set(1);
		flare_texture
			<< TextureTarget::_2D
			<< TextureMinFilter::LinearMipmapLinear
			<< TextureMagFilter::Linear
			<< images::LoadTexture("flare_1")
			<< TextureMipmap();

		(TextureTarget::_2D|0) << TextureWrap::MirroredRepeat;
		(TextureTarget::_2D|1) << TextureWrap::Repeat;

		lights.Bind();
		try
		{
			light_pos.Bind(Buffer::Target::Array);
			Buffer::Data(Buffer::Target::Array, light_positions);

			light_prog.Use();
			VertexArrayAttrib light_attr(light_prog, "Position");
			light_attr.Setup<Vec3f>();
			light_attr.Enable();

			flare_prog.Use();
			VertexArrayAttrib flare_attr(flare_prog, "Position");
			flare_attr.Setup<Vec3f>();
			flare_attr.Enable();
		}
		catch(Error&)
		{ }

		gl.ClearColor(0.1f, 0.1f, 0.1f, 0.0f);
		gl.ClearDepth(1.0f);
		gl.Enable(Capability::ProgramPointSize);
		gl.Enable(Capability::DepthTest);
		gl.Enable(Capability::CullFace);
		gl.CullFace(Face::Back);
		gl.BlendFunc(BlendFn::SrcAlpha, BlendFn::One);
	}