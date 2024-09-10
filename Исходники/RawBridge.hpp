  virtual void shuttle() {
    serverSocket.async_connect(destination, boost::bind(&RawBridge::handleConnect,
							this,
							Bridge::getSmartPointer(), 
							placeholders::error));      
  }