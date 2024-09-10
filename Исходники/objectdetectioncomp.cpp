int objectDetectionComp::run(int argc, char* argv[])
{
#ifdef USE_QTGUI
	QApplication a(argc, argv);  // GUI application
#else
	QCoreApplication a(argc, argv);  // NON-GUI application
#endif
	int status=EXIT_SUCCESS;

	// Remote server proxy access example
	// RemoteComponentPrx remotecomponent_proxy;
	InnerModelManagerPrx innermodelmanager_proxy;
RGBDPrx rgbd_proxy;


	string proxy;

	// User variables


	initialize();

	// Remote server proxy creation example
	// try
	// {
	// 	// Load the remote server proxy
	//	proxy = getProxyString("RemoteProxy");
	//	remotecomponent_proxy = RemotePrx::uncheckedCast( communicator()->stringToProxy( proxy ) );
	//	if( !remotecomponent_proxy )
	//	{
	//		rInfo(QString("Error loading proxy!"));
	//		return EXIT_FAILURE;
	//	}
	//catch(const Ice::Exception& ex)
	//{
	//	cout << "[" << PROGRAM_NAME << "]: Exception: " << ex << endl;
	//	return EXIT_FAILURE;
	//}
	//rInfo("RemoteProxy initialized Ok!");
	// 	// Now you can use remote server proxy (remotecomponent_proxy) as local object
	//Remote server proxy creation example
	try
	{
		innermodelmanager_proxy = InnerModelManagerPrx::uncheckedCast( communicator()->stringToProxy( getProxyString("InnerModelManagerProxy") ) );
	}
	catch(const Ice::Exception& ex)
	{
		cout << "[" << PROGRAM_NAME << "]: Exception: " << ex;
		return EXIT_FAILURE;
	}
	rInfo("InnerModelManagerProxy initialized Ok!");
	mprx["InnerModelManagerProxy"] = (::IceProxy::Ice::Object*)(&innermodelmanager_proxy);//Remote server proxy creation example
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
	mprx["RGBDProxy"] = (::IceProxy::Ice::Object*)(&rgbd_proxy);
	IceStorm::TopicManagerPrx topicManager = IceStorm::TopicManagerPrx::checkedCast(communicator()->propertyToProxy("TopicManager.Proxy"));
	
	
	GenericWorker *worker = new SpecificWorker(mprx);
	//Monitor thread
	GenericMonitor *monitor = new SpecificMonitor(worker,communicator());
	QObject::connect(monitor,SIGNAL(kill()),&a,SLOT(quit()));
	QObject::connect(worker,SIGNAL(kill()),&a,SLOT(quit()));
	monitor->start();
	
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
    	Ice::ObjectAdapterPtr AprilTags_adapter = communicator()->createObjectAdapter("AprilTagsTopic");
    	AprilTagsPtr apriltagsI_ = new AprilTagsI(worker);
    	Ice::ObjectPrx apriltags_proxy = AprilTags_adapter->addWithUUID(apriltagsI_)->ice_oneway();
    	IceStorm::TopicPrx apriltags_topic;
    	if(!apriltags_topic){
	    	try {
	    		apriltags_topic = topicManager->create("AprilTags");
	    	}
	    	catch (const IceStorm::TopicExists&) {
	    	  	//Another client created the topic
	    	  	try{
	       			apriltags_topic = topicManager->retrieve("AprilTags");
	    	  	}catch(const IceStorm::NoSuchTopic&){
	    	  	  	//Error. Topic does not exist
				}
	    	}
	    	IceStorm::QoS qos;
	      	apriltags_topic->subscribeAndGetPublisher(qos, apriltags_proxy);
    	}
    	AprilTags_adapter->activate();
    	// Server adapter creation and publication
		Ice::ObjectAdapterPtr adapterobjectDetection = communicator()->createObjectAdapter("objectDetectionComp");
		objectDetectionI *objectdetection = new objectDetectionI(worker);
		adapterobjectDetection->add(objectdetection, communicator()->stringToIdentity("objectdetection"));

		adapterobjectDetection->activate();
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