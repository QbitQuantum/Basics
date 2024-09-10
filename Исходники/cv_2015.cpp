int main(int argc, char* argv[])
{
    // get command line interface config options
    CmdLineInterface interface(argc, argv);
    AppConfig config = interface.getConfig();

    GUIManager gui;
    VideoDevice camera;
    LProcessor processor;
    NetworkController networkController;
    ArduinoController arduino;

    //init camera
    if(config.getIsDevice())
    {
        camera.startCapture(config.getDeviceID());
        if(config.getIsDebug())
            std::cout << "Camera ready!\n";
    }

    //init networking
    if(config.getIsNetworking())
        networkController.startServer();

    if(!config.getIsHeadless())
        gui.init();

    if (config.getHasArduino())
    {
        //16 is /dev/ttyUSB0, 24 is /dev/ttyACM0
        arduino.init(9600, 24);  //baud rate, serial port
    }
    //continuous server loop
    do
    {
        if(config.getIsNetworking())
            networkController.waitForPing();

        LDetector detector;

        cv::Mat image;
        if(config.getIsFile());
            //image = cv::imread(config.getFileName());
        //else
        //    image = camera.getImage(config.getIsDebug());

        //detector.elLoad(image);
        //detector.elSplit();
        //detector.elThresh();
        //detector.elContours(); detector.elFilter();

        bool foundL = true;
        if (detector.getLs().size() > 0)
            detector.largest2();
        else
            foundL = false;
        if (detector.getLs().size() == 0)
            foundL = false;
        if (foundL)
        {
            processor.determineL(detector.getLs());
            processor.determineAzimuth();
            processor.determineDistance();
            double azimuth = processor.getAzimuth();
            double distance = processor.getDistance();

            if(config.getIsDebug())
            {
                processor.outputData();
                std::cout << "Final distance (m): " << processor.getDistance() << std::endl;
            }

            if(!config.getIsHeadless())
            {
                int i_dist = (int) (distance * 1000.0);
                int dist_left = i_dist / 1000;
                int dist_right = i_dist % 1000;
                std::string dist_str = boost::lexical_cast<std::string>(dist_left) + "." + boost::lexical_cast<std::string>(dist_right);

                gui.setImage(detector.show());
                gui.setImageText("Distance: " + dist_str + " m");
                gui.show(config.getIsFile());
            }

            if(config.getIsNetworking())
            {
                networkController.sendMessage(boost::lexical_cast<std::string> ("true") + std::string(";")
                                              + boost::lexical_cast<std::string> (distance) + std::string(";")
                                              + boost::lexical_cast<std::string> (azimuth));
            }

        }
        else
        {
            if(config.getIsNetworking())
                networkController.sendMessage(boost::lexical_cast<std::string> ("false") + std::string(";"));
            if(!config.getIsHeadless())
            {
                gui.setImage(detector.show());
                gui.setImageText("No L's Found");
                gui.show(config.getIsFile());
            }
        }

        if(config.getHasArduino())
        {
            char c = std::rand() % 26 + 'A';
            arduino.sendMessage(c, cv::Point(5, 5));
            cv::waitKey(300);
        }

    }
    while(config.getIsDevice());

    return 0;
}