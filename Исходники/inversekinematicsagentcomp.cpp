int inversekinematicsAgentComp::run(int argc, char* argv[])
{
#ifdef USE_QTGUI
	QApplication a(argc, argv);  // GUI application
#else
	QCoreApplication a(argc, argv);  // NON-GUI application
#endif
	int status=EXIT_SUCCESS;

	// Remote server proxy access example
	// RemoteComponentPrx remotecomponent_proxy;
	BodyInverseKinematicsPrx bodyinversekinematics_proxy;
AGMAgentTopicPrx agmagenttopic_proxy;


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
		bodyinversekinematics_proxy = BodyInverseKinematicsPrx::uncheckedCast( communicator()->stringToProxy( getProxyString("BodyInverseKinematicsProxy") ) );
	}
	catch(const Ice::Exception& ex)
	{
		cout << "[" << PROGRAM_NAME << "]: Exception: " << ex;
		return EXIT_FAILURE;
	}
	rInfo("BodyInverseKinematicsProxy initialized Ok!");
	mprx["BodyInverseKinematicsProxy"] = (::IceProxy::Ice::Object*)(&bodyinversekinematics_proxy);
	IceStorm::TopicManagerPrx topicManager = IceStorm::TopicManagerPrx::checkedCast(communicator()->propertyToProxy("TopicManager.Proxy"));
	
	IceStorm::TopicPrx agmagenttopic_topic;
    while(!agmagenttopic_topic){
		try {
			agmagenttopic_topic = topicManager->retrieve("AGMAgentTopic");
		}catch (const IceStorm::NoSuchTopic&){
			try{
				agmagenttopic_topic = topicManager->create("AGMAgentTopic");
			}catch (const IceStorm::TopicExists&){
				// Another client created the topic.
			}
		}
	}
	Ice::ObjectPrx agmagenttopic_pub = agmagenttopic_topic->getPublisher()->ice_oneway();
	AGMAgentTopicPrx agmagenttopic = AGMAgentTopicPrx::uncheckedCast(agmagenttopic_pub);
	mprx["AGMAgentTopicPub"] = (::IceProxy::Ice::Object*)(&agmagenttopic);
	
	
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
    	Ice::ObjectAdapterPtr AGMExecutiveTopic_adapter = communicator()->createObjectAdapter("AGMExecutiveTopicTopic");
    	AGMExecutiveTopicPtr agmexecutivetopicI_ = new AGMExecutiveTopicI(worker);
    	Ice::ObjectPrx agmexecutivetopic_proxy = AGMExecutiveTopic_adapter->addWithUUID(agmexecutivetopicI_)->ice_oneway();
    	IceStorm::TopicPrx agmexecutivetopic_topic;
    	while(!agmexecutivetopic_topic){
	    	try {
	    		agmexecutivetopic_topic = topicManager->retrieve("AGMExecutiveTopic");
	    	 	IceStorm::QoS qos;
	      		agmexecutivetopic_topic->subscribeAndGetPublisher(qos, agmexecutivetopic_proxy);
	    	}
	    	catch (const IceStorm::NoSuchTopic&) {
	       		// Error! No topic found!
	    	}
    	}
    	AGMExecutiveTopic_adapter->activate();
    	// Server adapter creation and publication
		Ice::ObjectAdapterPtr adapterAGMCommonBehavior = communicator()->createObjectAdapter("AGMCommonBehaviorComp");
		AGMCommonBehaviorI *agmcommonbehavior = new AGMCommonBehaviorI(worker);
		adapterAGMCommonBehavior->add(agmcommonbehavior, communicator()->stringToIdentity("agmcommonbehavior"));

		adapterAGMCommonBehavior->activate();
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