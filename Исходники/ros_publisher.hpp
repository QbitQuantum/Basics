	/**
	 *	Destructor
	 */
	~RosPublisher()
	{
		_pub.shutdown();
	}