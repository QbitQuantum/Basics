int main(int argc, char *argv[])
{
	CmdLine cmd;
	std::string img_name;
	cmd.add(make_option('i', img_name, "imgname"));
	try {
		if (argc == 1) throw std::string("Invalid command line parameter.");
		cmd.process(argc, argv);
	}
	catch (const std::string& s) {
		std::cerr << "Feature detector \nUsage: " << argv[0] << "\n"
			<< "[-i|--imgname name]\n"
			<< std::endl;

		std::cerr << s << std::endl;
		return EXIT_FAILURE;
	}
	cv::Mat img(cv::imread(img_name, 0));
	assert(img.type() == CV_8UC1 && !img.empty());

	AbstractCamera* cam = new PinholeCamera(752, 480, 315.5, 315.5, 376.0, 240.0);
	FramePtr frame(new Frame(cam, img, 0.0));
	Features fts;
	FastDetector fast_detector(img.cols, img.rows, 25, 3);
	Timer t;
	for (int i = 0; i < 100; ++i)
	{
		fast_detector.detect(frame.get(), frame->img_pyr_, 20.0, fts);
	}
	printf("Fast corner detection took %f ms, %d corners detected (ref i7-W520: 7.166360ms, 40000)\n", t.stop() * 10, fts.size());
	printf("Note, in this case, feature detection also contains the cam2world projection of the feature.\n");
	cv::Mat img_rgb = cv::Mat(img.size(), CV_8UC3);
	cv::cvtColor(img, img_rgb, CV_GRAY2RGB);
	std::for_each(fts.begin(), fts.end(), [&](Feature* i){
		cv::circle(img_rgb, cv::Point2f(i->px[0], i->px[1]), 4 * (i->level + 1), cv::Scalar(0, 255, 0), 1);
	});
	cv::imshow("ref_img", img_rgb);
	cv::waitKey(0);

	std::for_each(fts.begin(), fts.end(), [&](Feature* i){ delete i; });
	return 0;
}