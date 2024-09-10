int _tmain(int argc, _TCHAR* argv[])
{
	sdl::Application app;

	DepthDetector detector(ThresholdMin, ThresholdMax);
	ScanLineSegmenter segmenter;

	OpenNI::initialize();

	Device device;
	if (device.open(ANY_DEVICE) != STATUS_OK)
	{
		std::cout << "could not open any device\r\n";
		return 1;
	}

	if (device.hasSensor(SENSOR_DEPTH))
	{
		auto info = device.getSensorInfo(SENSOR_DEPTH);
		auto& modes = info->getSupportedVideoModes();
		std::cout << "depth sensor supported modes:\r\n";
		for (int i = 0; i < modes.getSize(); ++i)
		{
			auto& mode = modes[i];
			std::cout << "pixel format: " << mode.getPixelFormat() << "\t with: " << mode.getResolutionX() << "x" << mode.getResolutionY() << "@" << mode.getFps() << " fps\r\n";
		}
	}

	VideoStream stream;
	stream.create(device, SENSOR_DEPTH);
	VideoMode mode;
	mode.setFps(25);
	mode.setPixelFormat(PIXEL_FORMAT_DEPTH_1_MM);
	mode.setResolution(320, 240);
	stream.setMirroringEnabled(true);
	stream.setVideoMode(mode);
	stream.start();

	std::cout << "press any key to capture background\r\n";
	std::cin.get();

	VideoFrameRef frame;
	stream.readFrame(&frame);

	DepthImage image(320, 240);
	copyFrameToImage(frame, image);

	detector.background(image);

	std::cout << "starting capture loop\r\n";

	sdl::GLContext::setVersion(4, 3);

	ImageViewer viewer;
	viewer.add(0, 0, 320, 240);
	viewer.add(320, 0, 320, 240);
	viewer.add(0, 240, 320, 240);
	viewer.add(320, 240, 320, 240);
	
	CenterPointExtractor centerPointExtractor(MinBlobSize);
	MotionRecorder recorder;

	while (true)
	{
		stream.readFrame(&frame);

		copyFrameToImage(frame, image);
		
		detector.detect(image);

		std::vector<LineSegment> segments;
		segmenter.segment(detector.mask(), segments);


		std::vector<std::pair<float, float>> centerPoints;
		centerPointExtractor.extract(segments, centerPoints);

		recorder.track(centerPoints);
		
		viewer.crosses.clear();
		std::transform(begin(centerPoints), end(centerPoints), std::back_inserter(viewer.crosses), [](std::pair<float, float>& coord) {
			return Cross{ coord.first, coord.second };
		});

		viewer.lines.clear();
		std::transform(begin(recorder.motions()), end(recorder.motions()), std::back_inserter(viewer.lines), [](const Motion& motion) {
			return Lines{ motion.points };
		});
		
		viewer[0].update(detector.mask());
		viewer[1].update(image);
		viewer[2].update(detector.background());
		viewer[3].update(detector.difference());
		
		viewer.update();
	}
	
	openni::OpenNI::shutdown();
	return 0;
}