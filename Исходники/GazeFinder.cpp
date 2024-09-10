void runMapper(Calibrator c)
{

	//Stop if recalibration is in progress
	while(calibrated)
	{
		std::string msg2 = "";
		std::string msg3 = "";
		std::string msg4 = "";
		int b = 1;
		while (b)
		{
			msg2 = s_recv(subscriber5);
			std::cout << "got " << msg2 << std::endl;
			msg3 = s_recv(subscriber5);
			std::cout << "got " << msg3 << std::endl;
			msg4 = s_recv(subscriber5);
			std::cout << "got " << msg4 << std::endl;
			if (atof(msg3.c_str()) != 0.0 && atof(msg4.c_str()) != 0.0) {
				b = 0;
			}
		}

		cout << "To be mapped: " << msg3 << ", " << msg4 << endl;
		dataLog.log("To be mapped: " + msg3 + ", " + msg4 + "\n");

		//Send to the mapper to map to screen points
		c.homography_map_point(atof(msg3.c_str()), atof(msg4.c_str()));
	}
}