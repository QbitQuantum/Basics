void writeQueue() {
  SensorData* data;
  std::ofstream ofG2O(&filename[0]);
  geometry_msgs::TransformStamped msg;
  int num = 0;

  
  // this is the vertex where we are packing the data
  g2o::VertexSE3* activeVertex = 0;
  // this is the timestamp of the first measurement added to the vertex
  double activeVertexTime=0;

  // this is the previous vertex
  g2o::VertexSE3* previousVertex = 0;
  // this is the timestamp of the first measurement added to the previous vertex
  double previousVertexTime=0;

  // the last position of the robot (not of the vertex, needed to measure the distances)
  Eigen::Isometry3d lastRobotPose;

  // set of sensors we packed in the current data. 
  // We do not want to put 10 camera images of the same camera in the same vertex.
  std::set<Sensor*> addedSensors;

  Eigen::Vector2d distances(0.,0);
  while (true)
  {
    if(! _queue.empty())
    {
      data = (SensorData*)_queue.front();
      double timeNow = _queue.lastElementTime();
      conditionalPrint(annoyingLevel) <<  "size=" << _queue.size() << " lastTime=" << FIXED(timeNow) << endl;
      if (timeNow - data->timeStamp()> initialDelay)
      { // we have enough stuff in the queue
	_queue.pop_front();
	if (! nptr->ok())
	  continue;
	
	tf::StampedTransform transform;
	bool we_got_transf = false;
	try
	{
	  ros::Time timeStamp;
	  // Get transformation
	  (*tfListener).lookupTransform("/odom", "/base_link", timeStamp.fromSec(data->timeStamp()), transform);
	  we_got_transf = true;
	}
	catch (tf::TransformException & ex)
	{
	  ROS_ERROR("%s", ex.what());
	}

	if (! we_got_transf)
	  continue;
				
	Eigen::Isometry3d currentRobotPose = fromStampedTransform(transform);
	double currentDataTime = data->timeStamp();
	distances += isometry2distance(lastRobotPose.inverse()*currentRobotPose);
	double passedTime = currentDataTime-previousVertexTime;
	lastRobotPose = currentRobotPose;

	conditionalPrint(annoyingLevel) << "distances: " << distances[0] << " " << distances[1] <<  " " << passedTime << endl;
	if (distances[0] < minDistances[0] && 
	    distances[1] < minDistances[1] && 
	    passedTime   < minTime){
	  conditionalPrint(annoyingLevel) << "reject: (time/distance)" << endl;
	  // SKIP THE FRAME
	  delete data;
	  data = 0;
	  continue;
	} 

	if (!activeVertex) {
	  activeVertex = new g2o::VertexSE3();
	  activeVertex->setId(num);
	  activeVertex->setEstimate(fromStampedTransform(transform));
	  activeVertexTime = currentDataTime;
	}
						
	Sensor* sensor = data->sensor();
	assert (sensor && "!");
						
	// check if we already packed the data for this kind of sensor
	if (addedSensors.count(sensor)){
	  conditionalPrint(annoyingLevel) << "reject: (sensor) "<< endl;
	  delete data;
	} else {
	  addedSensors.insert(sensor);
	  Parameter* parameter = sensor->parameter();
	  assert (parameter && "!@#");
	  //data->writeOut(filename);
	  if (! graph->parameters().getParameter(parameter->id())){
	    graph->parameters().addParameter(parameter);
	    graph->saveParameter(ofG2O, parameter);
	  }
					
	  activeVertex->addUserData(data);
	  data->setDataContainer(activeVertex);
	}
	// detach the data from the thing
	data = 0;

	if (currentDataTime - activeVertexTime > vertexTimeWindow) {
	  conditionalPrint(annoyingLevel) << "flush" << endl;
	  graph->addVertex(activeVertex);
	  graph->saveVertex(ofG2O, activeVertex);
	  				
	  if (previousVertex) {
	    EdgeSE3* e = new EdgeSE3();
	    e->setVertex(0, previousVertex);
	    e->setVertex(1, activeVertex);
	    e->setMeasurementFromState();
	    Eigen::Matrix<double, 6,6> m;
	    m.setIdentity();
	    e->setInformation(m);
	    graph->addEdge(e);
	    graph->saveEdge(ofG2O, e);

	    // JACP: do not do the remove, scan the data list and do a release() of the images which are big. The rest can stay in memory
	    g2o::HyperGraph::Data* d = previousVertex->userData();
	    while (d) {
	      RGBDData* rgbd = dynamic_cast<RGBDData*> (d);
	      if (rgbd)
		rgbd->release();
	      d = d->next();
	    }
	    vertecesQueue.push_back(previousVertex);
	  }
					
	  previousVertex = activeVertex;
	  previousVertexTime = activeVertexTime;
	  addedSensors.clear();
	  activeVertex = 0;
	  distances.setZero();
	  num++;
	  conditionalPrint(defaultLevel) << ".";
	}
      }
    }
    usleep(20e3); // queue is emp-ty
  }
}