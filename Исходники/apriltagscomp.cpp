int AprilTagsComp::run(int argc, char* argv[])
{
#ifdef USE_QTGUI
	QApplication a(argc, argv);  // GUI application
#else
	QCoreApplication a(argc, argv);  // NON-GUI application
#endif
	int status=EXIT_SUCCESS;

	CameraPrx camera_proxy;
	RGBDPrx rgbd_proxy;
	RGBDBusPrx rgbdbus_proxy;
	AprilTagsPrx apriltags_proxy;


	string proxy;

	initialize();


	try
	{
		camera_proxy = CameraPrx::uncheckedCast( communicator()->stringToProxy( getProxyString("CameraProxy") ) );
	}
	catch(const Ice::Exception& ex)
	{
		cout << "[" << PROGRAM_NAME << "]: Exception: " << ex;
		return EXIT_FAILURE;
	}
	rInfo("CameraProxy initialized Ok!");
	mprx["CameraProxy"] = (::IceProxy::Ice::Object*)(&camera_proxy);//Remote server proxy creation example
	try
	{
		rgbd_proxy = RGBDPrx::uncheckedCast( communicator()->stringToProxy( getProxyString("RGBDProxy") ) );
	}
	catch(const Ice::Exception& ex)
	{
		cout << "[" << PROGRAM_NAME << "]: Exception: " << ex;
		return EXIT_FAILURE;
	}
	rInfo("RGBDProxy initialized Ok!");
	mprx["RGBDProxy"] = (::IceProxy::Ice::Object*)(&rgbd_proxy);//Remote server proxy creation example
	try
	{
		rgbdbus_proxy = RGBDBusPrx::uncheckedCast( communicator()->stringToProxy( getProxyString("RGBDBusProxy") ) );
	}
	catch(const Ice::Exception& ex)
	{
		cout << "[" << PROGRAM_NAME << "]: Exception: " << ex;
		return EXIT_FAILURE;
	}
	rInfo("RGBDBusProxy initialized Ok!");
	mprx["RGBDBusProxy"] = (::IceProxy::Ice::Object*)(&rgbdbus_proxy);
	IceStorm::TopicManagerPrx topicManager = IceStorm::TopicManagerPrx::checkedCast(communicator()->propertyToProxy("TopicManager.Proxy"));
	
	IceStorm::TopicPrx apriltags_topic;
    while (!apriltags_topic)
	{
		try
		{
			apriltags_topic = topicManager->retrieve("AprilTags");
		}
		catch (const IceStorm::NoSuchTopic&)
		{
			try
			{
				apriltags_topic = topicManager->create("AprilTags");
			}
			catch (const IceStorm::TopicExists&){
				// Another client created the topic.
			}
		}
	}
	Ice::ObjectPrx apriltags_pub = apriltags_topic->getPublisher()->ice_oneway();
	AprilTagsPrx apriltags = AprilTagsPrx::uncheckedCast(apriltags_pub);
	mprx["AprilTagsPub"] = (::IceProxy::Ice::Object*)(&apriltags);
	
	GenericWorker *worker = new SpecificWorker(mprx);
	//Monitor thread
	GenericMonitor *monitor = new SpecificMonitor(worker,communicator());
	QObject::connect(monitor, SIGNAL(kill()), &a, SLOT(quit()));
	QObject::connect(worker, SIGNAL(kill()), &a, SLOT(quit()));
	monitor->start();
	worker->setPeriod(100);
	
	if ( !monitor->isRunning() )
		return status;
	try
	{
		// Server adapter creation and publication
		Ice::ObjectAdapterPtr adapterCommonBehavior = communicator()->createObjectAdapter("CommonBehavior");
		CommonBehaviorI *commonbehaviorI = new CommonBehaviorI(monitor );
		adapterCommonBehavior->add(commonbehaviorI, communicator()->stringToIdentity("commonbehavior"));
		adapterCommonBehavior->activate();
		// Server adapter creation and publication
		Ice::ObjectAdapterPtr adapterGetAprilTags = communicator()->createObjectAdapter("GetAprilTagsComp");
		GetAprilTagsI *getapriltags = new GetAprilTagsI(worker);
		adapterGetAprilTags->add(getapriltags, communicator()->stringToIdentity("getapriltags"));

		adapterGetAprilTags->activate();
		cout << SERVER_FULL_NAME " started" << endl;

		// User defined QtGui elements ( main window, dialogs, etc )

#ifdef USE_QTGUI
		//ignoreInterrupt(); // Uncomment if you want the component to ignore console SIGINT signal (ctrl+c).
		a.setQuitOnLastWindowClosed( true );
#endif
		// Run QT Application Event Loop
		a.exec();
		status = EXIT_SUCCESS;
	}	
	catch(const Ice::Exception& ex)
	{
		status = EXIT_FAILURE;

		cout << "[" << PROGRAM_NAME << "]: Exception raised on main thread: " << endl;
		cout << ex;

#ifdef USE_QTGUI
		a.quit();
#endif
		monitor->exit(0);
  }
	return status;
}