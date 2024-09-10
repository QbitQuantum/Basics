	WritingExample(void)
	{
		VertexShader vs;
		// Set the vertex shader source
		vs.Source(
			"#version 330\n"
			"in vec4 Position;"
			"void main(void)"
			"{"
			"	gl_Position = Position;"
			"}"
		);
		// compile it
		vs.Compile();

		GeometryShader gs;
		// Set the geometry shader source
		gs.Source(
			"#version 330\n"
			"layout(lines) in;"
			"layout(triangle_strip, max_vertices = 4) out;"
			"void main(void)"
			"{"
			"	vec4 offs = vec4(0.02, 0.01, 0.0, 0.0);"
			"	gl_Position = gl_in[0].gl_Position - offs;"
			"	EmitVertex();"
			"	gl_Position = gl_in[0].gl_Position + offs;"
			"	EmitVertex();"
			"	gl_Position = gl_in[1].gl_Position - offs;"
			"	EmitVertex();"
			"	gl_Position = gl_in[1].gl_Position + offs;"
			"	EmitVertex();"
			"	EndPrimitive();"
			"}"
		);
		// compile it
		gs.Compile();

		FragmentShader fs;
		// set the fragment shader source
		fs.Source(
			"#version 330\n"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"	fragColor = vec4(0.0, 0.0, 0.0, 1.0);"
			"}"
		);
		// compile it
		fs.Compile();

		// attach the shaders to the program
		prog.AttachShader(vs);
		prog.AttachShader(gs);
		prog.AttachShader(fs);
		// link and use it
		prog.Link();
		prog.Use();

		const Vec2f points[] = {
			Vec2f(-0.33f, +0.50f),
			Vec2f(-0.45f, +0.70f),
			Vec2f(-0.66f, +0.70f),
			Vec2f(-0.66f, +0.30f),
			Vec2f(-0.66f, -0.20f),
			Vec2f(-0.35f, -0.15f),
			Vec2f(-0.30f, +0.05f),
			Vec2f(-0.20f, +0.50f),
			Vec2f(-0.30f, +0.50f),
			Vec2f(-0.33f, +0.50f),
			Vec2f(-0.50f, +0.45f),
			Vec2f(-0.10f, +0.40f),
			Vec2f(+0.10f, +0.55f),
			Vec2f(-0.20f, +0.40f),
			Vec2f(-0.30f, -0.10f),
			Vec2f( 0.00f, -0.10f),
			Vec2f(+0.10f, -0.10f),
			Vec2f(+0.20f, -0.10f),
			Vec2f(+0.10f, +0.55f),
			Vec2f(+0.20f, +0.00f),
			Vec2f(+0.30f, -0.70f),
			Vec2f( 0.00f, -0.75f),
			Vec2f(-0.40f, -0.75f),
			Vec2f( 0.00f,  0.00f),
			Vec2f(+0.40f, +0.10f),
			Vec2f(+0.60f, +0.10f),
			Vec2f(+0.70f, +0.90f),
			Vec2f(+0.55f, +0.90f),
			Vec2f(+0.35f, +0.90f),
			Vec2f(+0.10f, -0.10f),
			Vec2f(+0.55f,  0.00f),
			Vec2f(+0.90f,  0.10f),
			Vec2f(+0.70f,  0.10f),
			Vec2f(+0.90f,  0.20f)
		};
		BezierCurves<Vec2f, double, 3> bezier(
			std::vector<Vec2f>(
				points,
				points+sizeof(points)/sizeof(points[0])
			)
		);

		writing.Bind();
		{
			auto data = bezier.Approximate(25);
			curve_n = data.size();
			Bind(curve_verts, Buffer::Target::Array).Data(data);
			VertexAttribArray attr(prog, "Position");
			attr.Setup(2, DataType::Float);
			attr.Enable();
		}

		gl.ClearColor(0.9f, 0.9f, 0.9f, 0.0f);
	}