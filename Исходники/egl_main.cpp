void run_framedump_loop(
	eglplus::Surface& surface,
	std::unique_ptr<Example>& example,
	ExampleClock& clock,
	const ExampleOptions& opts
)
{
	std::vector<char> txtbuf(1024);
	std::cin.getline(txtbuf.data(), txtbuf.size());
	if(std::strcmp(opts.framedump_prefix, txtbuf.data()) != 0) return;

	const std::size_t mouse_path_pts = 7;
	std::vector<Vec2f> mouse_path_pos(mouse_path_pts);
	std::vector<Vec2f> mouse_path_dir(mouse_path_pts);

	for(std::size_t p=0; p!= mouse_path_pts; ++p)
	{
		mouse_path_pos[p] = Vec2f(
			std::rand() % opts.width,
			std::rand() % opts.height
		);
		mouse_path_dir[p] = Vec2f(
			(std::rand()%2?1.0:-1.0)*10.0f*
			(0.2+float(std::rand())/float(RAND_MAX)*0.8),
			(std::rand()%2?1.0:-1.0)*10.0f*
			(0.2+float(std::rand())/float(RAND_MAX)*0.8)
		);
	}

	typedef CubicBezierLoop<Vec2f, double> Loop;

	double t = 0.0;
	double period = 1.0 / 25.0;
	GLuint frame_no = 0;
	std::vector<char> pixels(opts.width * opts.height * 4);

	GLuint border = 32;

	glEnable(GL_MULTISAMPLE);

	while(true)
	{
		Vec2f mouse_pos = Loop(mouse_path_pos).Position(t*0.2);

		for(std::size_t p=0; p!= mouse_path_pts; ++p)
		{
			Vec2f dir = mouse_path_dir[p];
			Vec2f pos = mouse_path_pos[p];

			if((pos.x() < border) && (dir.x() < 0.0))
			{
				dir = Vec2f(-dir.x(), dir.y());
			}
			if((pos.y() < border) && (dir.y() < 0.0))
			{
				dir = Vec2f( dir.x(),-dir.y());
			}
			if((pos.x() > opts.width-border) && (dir.x() > 0.0))
			{
				dir = Vec2f(-dir.x(), dir.y());
			}
			if((pos.y() >opts.height-border) && (dir.y() > 0.0))
			{
				dir = Vec2f( dir.x(),-dir.y());
			}

			mouse_path_dir[p] = dir;
			mouse_path_pos[p] = pos + dir;
		}

		float mouse_x = mouse_pos.x();
		float mouse_y = mouse_pos.y();

		if(mouse_x < 0.0f) mouse_x = 0.0f;
		if(mouse_y < 0.0f) mouse_y = 0.0f;
		if(mouse_x > opts.width) mouse_x = opts.width;
		if(mouse_y > opts.height) mouse_y = opts.height;

		example->MouseMove(
			GLuint(mouse_x),
			GLuint(mouse_y),
			opts.width,
			opts.height
		);

		t += period;
		clock.Update(t);

		if(!example->Continue(clock)) break;

		unsigned part_no = 0;
		double comp = 0.0;
		do
		{
			comp = example->RenderPart(part_no++, clock);
		}
		while(comp < 1.0);

		glFinish();
		glReadPixels(
			0, 0,
			opts.width,
			opts.height,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			pixels.data()
		);
		glFinish();
		surface.SwapBuffers();
		std::stringstream filename;
		filename <<
			opts.framedump_prefix <<
			std::setfill('0') << std::setw(6) <<
			frame_no << ".rgba";
		{
			std::ofstream file(filename.str());
			file.write(pixels.data(), pixels.size());
			file.flush();
		}
		std::cout << filename.str() << std::endl;
		++frame_no;

		txtbuf.resize(filename.str().size()+1);
		std::cin.getline(txtbuf.data(), txtbuf.size());

		if(std::strncmp(
			filename.str().c_str(),
			txtbuf.data(),
			txtbuf.size()
		) != 0) break;
	}
}