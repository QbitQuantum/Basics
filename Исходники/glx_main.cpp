void run_example_loop(
	const x11::Display& display,
	const x11::Window& win,
	const glx::Context& ctx,
	std::unique_ptr<Example>& example,
	ExampleThreadData::Common& common,
	ExampleClock& clock,
	GLuint width,
	GLuint height
)
{
	std::cout << "-+-[Begin]" << std::endl;
#if GL_ARB_debug_output && !OGLPLUS_NO_LAMBDAS
	ARB_debug_output dbg;
	ARB_debug_output::LogSink sink(
		[](const ARB_debug_output::CallbackData& data) -> void
		{
			std::cout << " |" << std::endl;
			std::cout << " +-+-[" << data.id << "] '" <<
				data.message << "'" << std::endl;
			std::cout << " | +---[source]   '" <<
				EnumValueName(data.source).c_str()  << "'" << std::endl;
			std::cout << " | +---[type]     '" <<
				EnumValueName(data.type).c_str()  << "'" << std::endl;
			std::cout << " | `---[severity] '" <<
				EnumValueName(data.severity).c_str()  << "'" << std::endl;
		}
	);

	dbg.Control(
		DebugOutputARBSource::DontCare,
		DebugOutputARBType::DontCare,
		DebugOutputARBSeverity::Low,
		true
	);

	dbg.InsertMessage(
		DebugOutputARBSource::Application,
		DebugOutputARBType::Other,
		0,
		DebugOutputARBSeverity::Low,
		"Starting main loop"
	);
#endif // GL_ARB_debug_output

	win.SelectInput(
		StructureNotifyMask|
		PointerMotionMask|
		KeyPressMask
	);
	::Atom wmDelete = ::XInternAtom(display, "WM_DELETE_WINDOW", True);
	::XSetWMProtocols(display, win, &wmDelete, 1);

	XEvent event;
	os::steady_clock os_clock;
	bool done = false;
	while(!done && !common.failure)
	{
		while(display.NextEvent(event))
		{
			switch(event.type)
			{
				case ClientMessage:
				case DestroyNotify:
					done = true;
					break;
				case ConfigureNotify:
					width = event.xconfigure.width;
					height = event.xconfigure.height;
					example->Reshape(
						width,
						height
					);
				case MotionNotify:
					example->MouseMove(
						event.xmotion.x,
						height-
						event.xmotion.y,
						width,
						height
					);
					break;
				case KeyPress:
					if(::XLookupKeysym(
						&event.xkey,
						0
					) == XK_Escape) done = true;
					break;
				default:;
			}
		}
		clock.Update(os_clock.seconds());
		if(!example->Continue(clock)) break;
		example->Render(clock);
		ctx.SwapBuffers(win);
	}
	std::cout << " `-[Done]" << std::endl;
}