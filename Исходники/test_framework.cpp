int main(int argc, char *argv[])
{
	CmdLine cmd;
	std::string first_frame_name;
	std::string second_frame_name;

	cmd.add(make_option('f', first_frame_name, "firstname"));
	cmd.add(make_option('s', second_frame_name, "secondname"));
	try {
		if (argc == 1) throw std::string("Invalid command line parameter.");
		cmd.process(argc, argv);
	}
	catch (const std::string& s) {
		std::cerr << "Feature detector \nUsage: " << argv[0] << "\n"
			<< "[-f|--firstname name]\n"
			<< "[-s|--secondname name]\n"
			<< std::endl;

		std::cerr << s << std::endl;
		return EXIT_FAILURE;
	}
	cv::Mat first_img(cv::imread(first_frame_name, 0));
	cv::Mat second_img(cv::imread(second_frame_name, 0));
	assert(first_img.type() == CV_8UC1 && !first_img.empty());
	assert(second_img.type() == CV_8UC1 && !second_img.empty());

	AbstractCamera* cam = new MonocularCamera(752, 480, 315.5, 315.5, 376.0, 240.0);
	ORBextractor *extractor = new ORBextractor(2*1000);

	System system("D:\\dataset\\Vocabulary\\ORBvoc.bin", "D:\\dataset\\TUM1.yaml");

	system.addImage(first_img, 0);
	system.addImage(second_img, 1);
	
	delete extractor;
	delete cam;
	return 0;
}